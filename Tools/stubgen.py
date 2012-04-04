header = file('kernel.h', 'w')
source = file('kernel.c', 'w')
mapping = file('mapping.c', 'w')

print >>header, 'void *mapKernel(unsigned long id);'
print >>header
print >>mapping, 'void *mapKernel(unsigned long id) {'
print >>mapping, '\tswitch(id) {'

for line in file('kernel.imp', 'r'):
	name, addr = [x.strip() for x in line.split(' ', 1)]
	print >>source, 'void kernel_%s() { printf("Stub for %s!\n"); exit(0); }' % (name, name)
	print >>source
	print >>header, 'void kernel_%s();' % name
	print >>mapping, '\t\tcase %s: return (void *) kernel_%s;' % (addr, name)
print >>mapping, '\t\tdefault: return (void *) 0;'
print >>mapping, '\t}'
print >>mapping, '}'
