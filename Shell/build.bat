nasm -f obj win32.nasm
alink -c -oPE -subsys console win32 -filealign 0x800 -objectalign 0x800 -base 0x10000