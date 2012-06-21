#include "Interpreter.hpp"

int main(void) {
	uint8_t memory[11];
	memory[0] = 0x05; *((uint32_t *) (memory+1)) = 0x00000001;
	memory[5] = 0x66; memory[6] = 0x05; *((uint16_t *) (memory+7)) = 0x0007;
	memory[9] = 0xEB; memory[10] = 0xF5;
	Interpreter interpreter((void *) memory);
	interpreter.Run();
	return 0;
}