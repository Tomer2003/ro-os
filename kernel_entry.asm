; ensure that we call the main function of the kernel from the boot sector that call to the start address of the kernel(this file)
[bits 64]
[extern main]	; note to the linker that main is external symbol, so th linker should resolve the address of main

call main
jmp $
