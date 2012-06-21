#include <stdio.h>
#include <stdlib.h>

#define null NULL

#define WARN(msg) { printf("%s\n", msg); }
#define ASSERT(comp, msg) { if(!(comp)) { printf("%s\n", msg); exit(1); } }
#define BAIL(msg) { printf("%s\n", msg); exit(1); }
