#include "Interpreter.hpp"

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
		// Instructions
		switch(op) {
			case 0x05: {// ADD rAX, Iz
				int32_t val;
				if(opsize) { // 16-bit
					val = *(int16_t *) eip;
					eip += 2;
				} else {
					val = *(int32_t *) eip;
					eip += 4;
				}
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
