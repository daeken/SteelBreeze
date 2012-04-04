#include "stdafx.h"

void queryMemory(void *addr)
{
	MEMORY_BASIC_INFORMATION info;
	VirtualQuery(addr, &info, sizeof(MEMORY_BASIC_INFORMATION));
	printf("BaseAddress: %08x\n", info.BaseAddress);
	printf("AllocationBase: %08x\n", info.AllocationBase);
	printf("AllocationProtect: %08x\n", info.AllocationProtect);
	printf("RegionSize: %08x\n", info.RegionSize);
	printf("State: %08x\n", info.State);
	printf("Protect: %08x\n", info.Protect);
	printf("Type: %08x\n", info.Type);
}

CORE_API int Init(struct InitData *initData) {
	void (*entry)() = (void (*)()) initData->entryPoint;
	
	unsigned long *thunk = (unsigned long *) initData->thunkAddr;
	while(*thunk != 0) {
		*thunk = (unsigned long) mapKernel(*thunk);
		++thunk;
	}

	trapperInit();
	buildFs();

	entry();
	return 1;
}
