from struct import pack

class Pe(object):
	def __init__(self, xbe):
		self.xbe = xbe
		self.sections = []
		for name, (flags, addr, size, data) in xbe.sections.items():
			W = (flags & 0x1) != 0
			X = (flags & 0x4) != 0
			self.sections.append((name, addr, size, data, W, X))
		self.sections = sorted(self.sections, lambda a, b: cmp(a[1], b[1]))
		last = self.sections[-1]
		self.stubLoc = highest = (last[1] + last[2] + 0x1000) & 0xFFFFE000
		stub  = '\x68' + pack('<L', xbe.thunkAddr)
		stub += '\x68' + pack('<L', xbe.entryPoint)
		stub += '\xE8\x01\x00\x00\x00'
		stub += '\x90' * 12
		#self.sections.append(('.stub', highest, 0x1000, stub, False, True))
		self.sections.append(('.cxbximp', 0x41080, 0x80, '\0'*0x80, False, False))
		self.sections.append(('.cxbxplg', 0x41100, 0x12000, '\0'*0x12000, False, True))
		self.impAddr = highest + len(stub)
	
	def write(self, fn):
		fp = file(fn, 'wb')
		w = fp.write

		round = lambda v, m: v - ((v - 1) % m) + (m - 1)

		# IMAGE_DOS_HEADER
		w('MZ')
		w('\0' * (29 * 2))
		w(pack('<L', fp.tell() + 4))

		# IMAGE_FILE_HEADER
		w('PE\0\0')
		w('\x4C\x01')
		w(pack('<H', len(self.sections)))
		w(pack('<L', self.xbe.peTimeDate))
		w('\0\0\0\0')
		w('\0\0\0\0')
		w(pack('<H', 224))
		w(pack('<H', 0x010F))

		sizehere = fp.tell()

		# IMAGE_OPTIONAL_HEADER
		w('\x0B\x01')
		w('\6\0')
		w(pack('<L', round(sum(size for name, addr, size, data, W, X in self.sections if X), 0x20)))
		w(pack('<L', round(sum(size for name, addr, size, data, W, X in self.sections if not X), 0x20)))
		w('\0\0\0\0')
		w(pack('<L', self.stubLoc - self.xbe.baseAddr))
		w(pack('<L', self.sections[0][1] - self.xbe.baseAddr))
		found = False
		for name, addr, size, data, W, X in self.sections:
			if not X:
				w(pack('<L', addr - self.xbe.baseAddr))
				found = True
				break
		assert found

		# additional fields
		w(pack('<L', self.xbe.baseAddr))
		w('\x20\0\0\0')
		w('\x20\0\0\0')
		w('\x04\0\0\0')
		w('\0\0\0\0')
		w('\x04\0\0\0')
		w('\0\0\0\0')
		temp = round(sizehere + 224 + 40 * len(self.sections), 0x20)
		temp2 = temp
		for name, addr, size, data, W, X in self.sections:
			temp2 += size
			temp2 = round(temp2, 0x20)
		print '%08x' % temp2
		w(pack('<L', temp2))
		w(pack('<L', temp))
		w('\0\0\0\0')
		w('\x03\0')
		w('\0\0')
		w(pack('<L', self.xbe.stackCommit))
		w(pack('<L', self.xbe.stackCommit))
		w(pack('<L', self.xbe.heapReserve))
		w(pack('<L', self.xbe.heapCommit))
		w('\0\0\0\0')
		w(pack('<L', 16))
		directories = [
			(0, 0), 
			(0x41088, 0x28), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
			(0x41080, 8), 
			(0, 0), 
			(0, 0), 
			(0, 0), 
		]
		for addr, size in directories:
			if addr == 0:
				w('\0\0\0\0\0\0\0\0')
			else:
				w(pack('<LL', addr - self.xbe.baseAddr, size))

		opos = pos = fp.tell() + 40 * len(self.sections)
		pos = round(pos, 0x20)
		
		# Section headers
		for name, addr, size, data, W, X in self.sections:
			print '%s %08x' % (name, pos)
			w(name[:8])
			if len(name) < 8:
				w('\0' * (8 - len(name)))
			w(pack('<L', size))
			w(pack('<L', addr - self.xbe.baseAddr))
			w(pack('<L', round(size, 0x20)))
			w(pack('<L', pos))
			w('\0\0\0\0')
			w('\0\0\0\0')
			w('\0\0')
			w('\0\0')
			flags = 0x40000000
			if W:
				flags |= 0x80000000
			if X:
				flags |= 0x20000020
			else:
				flags |= 0x00000040
			w(pack('<L', flags))
			pos += size
			pos = round(pos, 0x20)
		pos = opos
		temp = round(pos, 0x20) - pos
		if temp:
			w('\0' * temp)
		
		for i, (name, addr, size, data, W, X) in enumerate(self.sections):
			print name, '%08x' % fp.tell()
			w(data)
			if size > len(data):
				w('\0' * (size - len(data)))
			pos += size
			if i < len(self.sections) - 1:
				temp = round(pos, 0x20) - pos
				if temp:
					w('\0' * temp)
					pos += temp
			#if len(data) < size:
			#	w('\0' * (size - len(data)))
		print 
