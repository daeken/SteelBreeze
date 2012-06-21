#include "../../Base.hpp"
#include "../CPU.hpp"

class Interpreter : CPU {
public:
	Interpreter(void *base) : CPU(base) {
	}
	void Run();

	void *RmAddr(uint8_t mod, uint8_t rm, int size);
	void *Reg(int reg, int size);
	uint16_t *SegReg(int reg);
};
