#include "Interpreter.hpp"

int main(void) {
	uint8_t memory[7];
	memory[0] = 0x05; *((uint32_t *) (memory+1)) = 0x00000001;
	memory[5] = 0xEB; memory[6] = 0xF9;
	Interpreter interpreter((void *) memory);
	interpreter.Run();
	return 0;
}