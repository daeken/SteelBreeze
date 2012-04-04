#include "stdafx.h"

int __stdcall kernel_PsCreateSystemThreadEx(OUT PHANDLE ThreadHandle,
	IN PVOID ObjectAttributes OPTIONAL,
 	IN ULONG KernelStackSize,
	IN ULONG TlsDataSize,
	OUT PULONG ThreadId OPTIONAL,
	IN PVOID StartContext1,
	IN PVOID StartContext2,
	IN BOOLEAN CreateSuspended,
	IN BOOLEAN DebugStack,
	IN PKSTART_ROUTINE StartRoutine) {
		printf("Stub for PsCreateSystemThreadEx! -- %08x\n", StartRoutine);
		return 0;
}

