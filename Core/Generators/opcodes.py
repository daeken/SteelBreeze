opcodes = {}

fp = file('Core/Generators/opcodes.txt')

for line in fp:
	line = line.strip()
	try:
		hex, insn, operands = line.split(' ')
		operands = operands.split(',')
	except:
		hex, insn = line.split(' ')
		operands = []

	if insn[0] == '-':
		continue
	
	ops = tuple(int(hex[i:i+2], 16) for i in xrange(0, len(hex), 2))
	if len(ops) == 1:
		ops, = ops

	opcodes[ops] = insn, operands

__all__ = ('opcodes', )
