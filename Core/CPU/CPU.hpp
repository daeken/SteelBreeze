#include <stdint.h>

class CPU {
public:
	CPU(void *base) : MemoryBase(base),
	Eip(0), 
	Eax(0), Ebx(0), Ecx(0), Edx(0), 
	Ebp(0), Esp(0), Ebi(0), Edi(0) {}

	virtual ~CPU() {}

	virtual void Run() {}

	uint32_t Eax, Ebx, Ecx, Edx,
	         Ebp, Esp, Ebi, Edi;
	uint32_t Eip;

	void *MemoryBase;
};
