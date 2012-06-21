#include <stdio.h>
#include <stdlib.h>

#define null NULL

#define WARN(msg) { printf("Warning: %s\n", msg); }
#define ASSERT(comp, msg) { if(!(comp)) { printf("Assertion failed: %s\n", msg); exit(1); } }
#define BAIL(msg) { printf("Bailing: %s\n", msg); exit(1); }
