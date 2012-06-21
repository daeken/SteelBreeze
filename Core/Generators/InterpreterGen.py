from opcodes import opcodes
import sys

onebyte = sorted([opcd for opcd in opcodes.keys() if not isinstance(opcd, tuple)])

fp = file('Core/CPU/Interpreter/Interpreter_inst.cgen', 'w')

registers = {}
for i, reg in enumerate('AL CL DL BL AH CH DH BH'.split(' ')):
	registers[reg] = i, 1
for i, reg in enumerate('AX CX DX BX SP BP SI DI'.split(' ')):
	registers[reg] = i, 2
for i, reg in enumerate('EAX ECX EDX EBX ESP EBP ESI EDI'.split(' ')):
	registers[reg] = i, 4
	registers[reg.replace('E', 'R')] = i, 4

segmentRegisters = dict(CS=0, DS=1, SS=2, ES=3, FS=4, GS=5)

size2type = {1: 'uint8_t', 2: 'uint16_t', 4: 'uint32_t'}

for opcd in onebyte:
	insn, operands = opcodes[opcd]
	print >>fp, 'case 0x%02X: { // %s' % (opcd, '%s %s' % (insn, ','.join(operands)))

	hasModrm = False
	opsizeDependent = False
	for operand in operands:
		if operand[0] in 'MGERPQNVWU' and (len(operand) == 1 or operand[1] not in 'S'):
			hasModrm = True
		if len(operand) > 1 and operand[1] in 'vz':
			opsizeDependent = True
	if hasModrm:
		print >>fp, '\tuint8_t mod = *eip >> 6, reg = (*eip >> 3) & 0x7, rm = *eip & 0x7;'
		print >>fp, '\teip++;'

	def generateSet(opsize):
		def addr(type, expr):
			print >>fp, '\t\t%s *_%i = (%s *) %s;' % (type, i, type, expr)
			params.append('(*_%i)' % i)

		def value(type, expr):
			print >>fp, '\t\t%s _%i = (%s) %s;' % (type, i, type, expr)
			params.append('_%i' % i)

		params = []
		for i, operand in enumerate(operands):
			if len(operand) == 2:
				a, b = list(operand)
				if opsizeDependent and b in 'vz':
					b = 'w' if opsize else 'd'
			else:
				a = b = None

			if operand.upper() in registers:
				reg, size = registers[operand.upper()]
				addr(size2type[size], 'Reg(%i, %i)' % (reg, size))
			elif operand in segmentRegisters:
				reg = segmentRegisters[operand]
				addr('int16_t', 'SegReg(%i)' % (reg))
			elif a == 'E':
				if b == 'b':
					addr('int8_t', 'RmAddr(mod, rm, 1)')
				elif b == 'w':
					addr('int16_t', 'RmAddr(mod, rm, 2)')
				elif b == 'd':
					addr('int32_t', 'RmAddr(mod, rm, 4)')
				else:
					assert False
			elif a == 'G':
				if b == 'b':
					addr('int8_t', 'Reg(reg, 1)')
				elif b == 'w':
					addr('int16_t', 'Reg(reg, 2)')
				elif b == 'd':
					addr('int32_t', 'Reg(reg, 4)')
				else:
					assert False
			elif a in 'IJ':
				if b == 'b':
					value('int8_t', '*eip++')
				elif b == 'w':
					value('int16_t', '*(int16_t *) eip')
					print >>fp, '\t\teip += 2;'
				elif b == 'd':
					value('int32_t', '*(int32_t *) eip')
					print >>fp, '\t\teip += 4;'
				else:
					assert False
			elif a == 'M':
				if b == 'a':
					print >>fp, '\t\tASSERT(mod != 11, "M instructions require memory operands");'
					if opsize:
						addr('int16_t', 'RmAddr(mod, rm, 2)')
					else:
						addr('int32_t', 'RmAddr(mod, rm, 4)')
				elif b == 'p':
					print >>fp, '\t\tBAIL("Mp instructions unsupported.");'
					addr('void', '0')
				else:
					assert False
			elif a == 'X':
				if b == 'b':
					addr('int8_t', 'EMU_ADDR(Esi)')
				elif b == 'w':
					addr('int16_t', 'EMU_ADDR(Esi)')
				elif b == 'd':
					addr('int32_t', 'EMU_ADDR(Esi)')
				else:
					assert False
			elif a == 'Y':
				print >>fp, '\t\tWARN("Y operands use data segment.");'
				if b == 'b':
					addr('int8_t', 'EMU_ADDR(Edi)')
				elif b == 'w':
					addr('int16_t', 'EMU_ADDR(Edi)')
				elif b == 'd':
					addr('int32_t', 'EMU_ADDR(Edi)')
				else:
					assert False
			elif a == 'A':
				print >>fp, '\t\tWARN("Address and no ADSIZE: support.");'
				if b == 'p':
					addr('int32_t', 'eip')
					print >>fp, '\t\teip += 32;'
				else:
					assert False
			elif a == 'O':
				print >>fp, '\t\tWARN("Address and no ADSIZE: support.");'
				if b == 'b':
					addr('int8_t', 'EMU_ADDR(*(int32_t *) eip)')
					print >>fp, '\t\teip += 4;'
				elif b == 'w':
					addr('int16_t', 'EMU_ADDR(*(int32_t *) eip)')
					print >>fp, '\t\teip += 4;'
				elif b == 'd':
					addr('int32_t', 'EMU_ADDR(*(int32_t *) eip)')
					print >>fp, '\t\teip += 4;'
				else:
					assert False
			else:
				assert False

		print >>fp, '\t\tINSN_%s(%s)' % (insn, ', '.join(params))

	if opsizeDependent:
		print >>fp, '\tif(opsize) {'
		generateSet(True)
		print >>fp, '\t} else {'
		generateSet(False)
		print >>fp, '\t}'
	else:
		print >>fp, '\t{'
		generateSet(False)
		print >>fp, '\t}'

	print >>fp, '\tbreak;'
	print >>fp, '}'

stubs = []
for insn, operands in opcodes.values():
	paramcount = len(operands)
	if (insn, paramcount) not in stubs:
		stubs.append((insn, paramcount))

stubs = sorted(stubs, key=lambda x: x[0])
for insn, paramcount in stubs:
	print '#define INSN_%s(%s) { WARN("STUB Instruction %s"); }' % (insn, ', '.join(chr(ord('a') + i) for i in xrange(paramcount)), insn)
