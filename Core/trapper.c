#include "stdafx.h"

LONG CALLBACK handler(PEXCEPTION_POINTERS exc) {
	unsigned int size = 0;
	//swapFs();
	switch(exc->ExceptionRecord->ExceptionCode) {
		default:
			printf("%08x @ %08x\n", exc->ExceptionRecord->ExceptionCode, exc->ContextRecord->Eip);
			exit(0);
			break;
	}
	if(size == 0)
		return EXCEPTION_CONTINUE_SEARCH;
	exc->ContextRecord->Eip += size;
	return EXCEPTION_CONTINUE_EXECUTION;
}

void trapperInit() {
	AddVectoredExceptionHandler(1, handler);
}
