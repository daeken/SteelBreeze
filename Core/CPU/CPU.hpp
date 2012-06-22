#include <stdint.h>

#define EMU_ADDR(off) (void *) (((uint8_t *) MemoryBase) + (off))

class CPU {
public:
	CPU(void *base) : MemoryBase(base),
	Eip(0), Eflags(0), 
	Eax(0), Ebx(0), Ecx(0), Edx(0), 
	Ebp(0), Esp(0), Edi(0), Esi(0) {}

	virtual ~CPU() {}

	virtual void Run() {}

	uint32_t Eax, Ebx, Ecx, Edx,
	         Ebp, Esp, Edi, Esi;
	uint32_t Eip;

	union {
		uint32_t Eflags;
		struct {
			unsigned CF:1;
			unsigned _0:1;
			unsigned PF:1;
			unsigned _1:1;
			unsigned AF:1;
			unsigned _2:1;
			unsigned ZF:1;
			unsigned SF:1;
			unsigned TF:1;
			unsigned IF:1;
			unsigned DF:1;
			unsigned OF:1;
			unsigned IOPL:2;
			unsigned NT:1;
			unsigned _3:1;
			unsigned RF:1;
			unsigned VM:1;
			unsigned AC:1;
			unsigned VIF:1;
			unsigned VIP:1;
			unsigned ID:1;
			unsigned _4:10;
		};
	};

	void *MemoryBase;
};
