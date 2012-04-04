#pragma once

typedef struct _KTHREAD {
	unsigned char unk1[0x28];
	void *TlsData;
	unsigned char unk2[0xE4];
} KTHREAD;

typedef struct _ETHREAD {
	struct _KTHREAD Tcb;
	unsigned char unk1[0x1C];
	unsigned int UniqueThread;
} ETHREAD;

struct _KPRCB {
	struct _KTHREAD *CurrentThread;
	struct _KTHREAD *NextThread;
	struct _KTHREAD *IdleThread;

	unsigned char unknown[0x250];
};

#pragma pack(4)
typedef struct KPCR_s {
	struct _NT_TIB NtTib;
	struct _KPCR *SelfPcr;
	struct _KPRCB *Prcb;
	unsigned char Irql;
	struct _KPRCB PrcbData;
} KPCR;
#pragma pack()

typedef struct FSPair_s {
	void *other;
	void *backup;
} FSPair;

void buildFs();
void swapFs();
