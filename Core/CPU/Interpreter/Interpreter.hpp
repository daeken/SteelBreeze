#include "../../Base.hpp"
#include "../CPU.hpp"

class Interpreter : CPU {
public:
	Interpreter(void *base) : CPU(base) {
	}
	void Run();
};
