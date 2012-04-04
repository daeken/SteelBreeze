#include "stdafx.h"

void swapFs() {
	FSPair *pair;
	void **cur;
	__asm {
		mov eax, fs:[0x18]
		mov cur, eax
	}

	pair = (FSPair *) cur[5];
	memcpy(pair->backup, cur, sizeof(KPCR));
	memcpy((char *) pair->other + 0x30, (char *) cur + 0x30, 4);
	memcpy((char *) pair->other + 0x94, (char *) cur + 0x94, 4*16);
	memcpy(cur, pair->other, sizeof(KPCR));
}

void buildFs() {
	void *origTib, *pcrBackup;

	KPCR *pcr;

	// XXX: Handle TLS shit

	__asm {
		mov eax, fs:[0x18]
		mov origTib, eax
	};
	
	pcr = (KPCR *) malloc(sizeof(KPCR));
	memset(pcr, 0, sizeof(KPCR));
	
	{
		ETHREAD *thread = (ETHREAD *) malloc(sizeof(ETHREAD));
		thread->Tcb.TlsData = NULL;
		thread->UniqueThread = GetCurrentThreadId();

		memcpy(&pcr->NtTib, origTib, sizeof(NT_TIB));
		pcr->NtTib.Self = (NT_TIB *) origTib;
		pcr->PrcbData.CurrentThread = (KTHREAD *) thread;
		pcr->Prcb = &pcr->PrcbData;
	}
	
	{
		FSPair *origOther, *xboxOther;
		pcrBackup = malloc(sizeof(KPCR));

		origOther = (FSPair *) malloc(sizeof(FSPair));
		origOther->other = (void *) pcr;
		origOther->backup = pcrBackup;
		((void **) origTib)[5] = origOther;

		xboxOther = (FSPair *) malloc(sizeof(FSPair));
		xboxOther->other = (void *) origTib;
		xboxOther->backup = pcrBackup;
		pcr->NtTib.ArbitraryUserPointer = xboxOther;
	}

	swapFs();
}
