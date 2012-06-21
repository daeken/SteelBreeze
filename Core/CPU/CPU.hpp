#include <stdint.h>

#define EMU_ADDR(off) (void *) (((uint8_t *) MemoryBase) + (off))

class CPU {
public:
	CPU(void *base) : MemoryBase(base),
	Eip(0), 
	Eax(0), Ebx(0), Ecx(0), Edx(0), 
	Ebp(0), Esp(0), Edi(0), Esi(0) {}

	virtual ~CPU() {}

	virtual void Run() {}

	uint32_t Eax, Ebx, Ecx, Edx,
	         Ebp, Esp, Edi, Esi;
	uint32_t Eip;

	void *MemoryBase;
};
