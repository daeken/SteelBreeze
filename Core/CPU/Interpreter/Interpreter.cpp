#include "Interpreter.hpp"
#include "Instructions.hpp"

void Interpreter::Run() {
	while(true) {
		uint8_t *eip = (uint8_t *) MemoryBase + Eip;
		// Prefixes
		bool foundPrefix = true;
		bool opsize = false, adsize = false;
		while(foundPrefix)
			switch(*eip++) {
				case 0x66: {// OPSIZE
					opsize = true;
					break;
				}
				case 0x67: {// ADSIZE
					adsize = true;
					break;
				}
				default: {
					foundPrefix = false;
					eip--;
				}
			}

		uint8_t op = *eip++;
		Eip++;
		printf("Op %02x\n", op);
		printf("Eax %08x\n", Eax);
		// Instructions
		switch(op) {
#include "Interpreter_inst.cgen"
			default: {
				printf("Undefined opcode %02x @ %08X\n", op, Eip);
				exit(1);
			}
		}
		Eip = (uint32_t) (eip - (uint8_t *) MemoryBase);
	}
}

void *Interpreter::RmAddr(uint8_t mod, uint8_t rm, int size) {
	return null;
}

void *Interpreter::Reg(int reg, int size) {
	uint32_t *regaddr;
	size_t off = 0;
	if(reg > 4 && size == 1) {
		reg -= 4;
		off = 1;
	}
	switch(reg) {
		case 0: regaddr = &Eax; break;
		case 1: regaddr = &Ecx; break;
		case 2: regaddr = &Edx; break;
		case 3: regaddr = &Ebx; break;
		case 4: regaddr = &Esp; break;
		case 5: regaddr = &Ebp; break;
		case 6: regaddr = &Esi; break;
		case 7: regaddr = &Edi; break;
	}

	return ((uint8_t *) regaddr) + off;
}

uint16_t *Interpreter::SegReg(int reg) {
	return null;
}
