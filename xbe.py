from struct import unpack

class Xbe(object):
	def __init__(self, fn):
		self.fp = file(fn, 'rb')
		assert self.bytes(4) == 'XBEH'
		sig = self.bytes(256)
		uint32 = self.uint32

		self.baseAddr, hdrsSize, imageSize, imageHdrSize = uint32(4)
		timeDate, certAddr, numSects, sectHdrAddr = uint32(4)
		initFlags, entryPoint, tlsAddr, self.stackCommit = uint32(4)
		self.heapReserve, self.heapCommit, peBase, peImageSize = uint32(4)
		peCsum, self.peTimeDate, debugPath, debugName = uint32(4)
		debugNameU, thunkAddr, nonkImp, numLibV = uint32(4)
		libVer, kernVer, xapiVer, logoAddr, logoSize = uint32(5)

		if (entryPoint ^ 0x94859D4B) & 0x80000000:
			entryPoint ^= 0xA8FC57AB
			thunkAddr ^= 0x5B6D40B6
		else:
			entryPoint ^= 0x94859D4B
			thunkAddr ^= 0xEFB1F152
		
		self.entryPoint, self.thunkAddr = entryPoint, thunkAddr

		self.fp.seek(sectHdrAddr - self.baseAddr, 0)

		self.sections = {}
		for i in xrange(numSects):
			flags, virtAddr, virtSize, rawAddr = uint32(4)
			rawSize, sectName, sectNameRef, headAddr = uint32(4)
			tailAddr, digest = uint32(), self.bytes(20)
			curLoc = self.fp.tell()
			self.fp.seek(rawAddr, 0)
			data = self.bytes(rawSize)
			self.fp.seek(sectName - self.baseAddr, 0)
			name = ''
			while not name or name[-1] != '\0':
				name += self.bytes(1)
			self.sections[name.strip()] = (flags, virtAddr, virtSize, data)
			self.fp.seek(curLoc, 0)
	
	def uint32(self, count=None):
		if count != None:
			return unpack('<' + 'L'*count, self.fp.read(4*count))
		return unpack('<L', self.fp.read(4))[0]
	
	def bytes(self, count):
		return self.fp.read(count)

if __name__=='__main__':
	import sys
	Xbe(sys.argv[1])
