from xbe import Xbe
from pe import Pe
from ctypes import *
from ctypes.wintypes import BOOL
import win32process
from struct import pack

BYTE      = c_ubyte
WORD      = c_ushort
DWORD     = c_ulong
LPBYTE    = POINTER(c_ubyte)
LPTSTR    = POINTER(c_char) 
HANDLE    = c_void_p
PVOID     = c_void_p
LPVOID    = c_void_p
UNIT_PTR  = c_ulong
SIZE_T    = c_ulong

class STARTUPINFO(Structure):
	_fields_ = [("cb",            DWORD),        
				("lpReserved",    LPTSTR), 
				("lpDesktop",     LPTSTR),  
				("lpTitle",       LPTSTR),
				("dwX",           DWORD),
				("dwY",           DWORD),
				("dwXSize",       DWORD),
				("dwYSize",       DWORD),
				("dwXCountChars", DWORD),
				("dwYCountChars", DWORD),
				("dwFillAttribute",DWORD),
				("dwFlags",       DWORD),
				("wShowWindow",   WORD),
				("cbReserved2",   WORD),
				("lpReserved2",   LPBYTE),
				("hStdInput",     HANDLE),
				("hStdOutput",    HANDLE),
				("hStdError",     HANDLE),]

class PROCESS_INFORMATION(Structure):
	_fields_ = [("hProcess",    HANDLE),
				("hThread",     HANDLE),
				("dwProcessId", DWORD),
				("dwThreadId",  DWORD),]

class MEMORY_BASIC_INFORMATION (Structure):
	_fields_ = [
				("BaseAddress",  c_ulong),
				("AllocationBase", c_ulong),
				("AllocationProtect", c_long),
				("RegionSize", c_long),
				("State", c_long),
				("Protect", c_long),
				("Type", c_long)    ]

class Process(object):
	def __init__(self, binary):
		startupinfo = STARTUPINFO()
		procinfo = PROCESS_INFORMATION()

		startupinfo.dwFlags = 1
		startupinfo.wShowWindow = 1
		startupinfo.cb = sizeof(startupinfo)

		windll.kernel32.CreateProcessA(
			binary, 
			None, 
			None, None, 
			False, 
			4, 
			None, 
			None, 
			byref(startupinfo), 
			byref(procinfo)
		)

		self.process = procinfo.hProcess
	
	def map(self, addr, size):
		ret = windll.kernel32.VirtualAllocEx(
			self.process, 
			addr, 
			size, 
			0x3000, # MEM_COMMIT | MEM_RESERVE
			0x40 # PAGE_EXECUTE_READWRITE
		)
		return ret
	
	def unmap(self, addr, size):
		info = self.query(addr)
		if info.State == 0x10000: # MEM_FREE
			return
		elif info.Type == 0x1000000: # MEM_IMAGE
			windll.ntdll.ZwUnmapViewOfSection(
				self.process, 
				addr
			)
		elif info.State == 0x1000: # MEM_COMMIT
			windll.kernel32.VirtualFreeEx(
				self.process, 
				addr, 
				0, 
				0x4000 # MEM_DECOMMIT
			)
		elif info.State == 0x2000: # MEM_RESERVE
			windll.kernel32.VirtualFreeEx(
				self.process, 
				addr, 
				size, 
				0x8000 # MEM_RELEASE
			)
	
	def query(self, addr, debug=False):
		info = MEMORY_BASIC_INFORMATION()
		windll.kernel32.VirtualQueryEx(
			self.process, 
			addr,
			byref(info), 
			sizeof(info)
		)
		if debug:
			print '%08x' % info.BaseAddress
			print '%08x' % info.AllocationBase
			print '%08x' % info.AllocationProtect
			print '%08x' % info.RegionSize
			print '%08x' % info.State
			print '%08x' % info.Protect
			print '%08x' % info.Type
			print
		return info
	
	def terminate(self):
		windll.kernel32.TerminateProcess(self.process, 0)
	
	def write(self, addr, data):
		return 0 != windll.kernel32.WriteProcessMemory(
			self.process, 
			addr, 
			c_char_p(data), 
			len(data), 
			None
		)
	
	def read(self, addr, size):
		buf = size * ' '
		windll.kernel32.ReadProcessMemory(
			self.process, 
			addr, 
			buf, 
			len(buf), 
			None
		)
		return buf
	
	def injectDll(self, name, ep, thunk):
		name += '\0'
		addr = self.map(0, len(name))
		self.write(addr, name)
		loadlib = windll.kernel32.GetProcAddress(
			windll.kernel32.GetModuleHandleA('kernel32.dll'), 
			'LoadLibraryA'
		)
		thread = windll.kernel32.CreateRemoteThread(
			self.process, 
			None, 
			0, 
			c_long(loadlib), 
			c_long(addr), 
			0, 
			None
		)
		windll.kernel32.WaitForSingleObject(thread, 2147483647)
		base = win32process.GetExitCodeThread(thread)

		mybase = windll.kernel32.LoadLibraryA(name)
		func = windll.kernel32.GetProcAddress(mybase, 'Init')
		rfunc = base + (func - mybase)

		self.write(addr, pack('<LL', ep, thunk))

		raw_input('Enter to run...')
		thread = windll.kernel32.CreateRemoteThread(
			self.process, 
			None, 
			0, 
			c_long(rfunc), 
			c_long(addr), 
			0, 
			None
		)
		windll.kernel32.WaitForSingleObject(thread, 2147483647)
		code = win32process.GetExitCodeThread(thread)
		if code != 0:
			print '%08x' % code

		return 1

import sys
xbefn = sys.argv[1]
xbe = Xbe(xbefn)
proc = Process('Shell\\win32_stripped.exe')

try:
	data = proc.read(0x10000, 0x1000)
	proc.unmap(0x10000, 0x1000)
	proc.unmap(0x11000, 0x10000000)

	bottom = min(addr for flags, addr, size, data in xbe.sections.values())
	top = max(addr + size for flags, addr, size, data in xbe.sections.values())
	assert bottom >= 0x11000 and top >= 0x11000
	bottom = 0x10000
	assert proc.map(bottom, top - bottom) != 0

	proc.write(0x10000, data)
	xbedata = file(xbefn, 'rb').read(4096)
	proc.write(0x10108, xbedata[0x108:0x10C])
	proc.write(0x10118, xbedata[0x118:0x11C])

	for name, (flags, virtAddr, virtSize, data) in xbe.sections.items():
		assert proc.write(virtAddr, data)

	assert proc.injectDll('Core\\Release\\Core.dll', xbe.entryPoint, xbe.thunkAddr) != None
finally:
	proc.terminate()
