#include "Interpreter.hpp"

void Interpreter::Run() {
	while(true) {
		uint8_t *eip = (uint8_t *) MemoryBase + Eip;
		// Prefixes
		switch(*eip) {
		}

		uint8_t op = *eip++;
		Eip++;
		printf("Op %02x\n", op);
		// Instructions
		switch(op) {
			case 0x05: {// ADD rAX, Iz
				uint32_t val = *(uint32_t *) eip;
				eip += 4;
				// XXX: Add 16-bit check.
				Eax += val;
				printf("%08x\n", Eax);
				break;
			}
			case 0xEB: {// JMP Ib
				eip += (int8_t) *eip++;
				break;
			}
			default: {
				printf("Undefined opcode %02x @ %08X\n", op, Eip);
				exit(1);
			}
		}
		Eip = (uint32_t) (eip - (uint8_t *) MemoryBase);
	}
}
