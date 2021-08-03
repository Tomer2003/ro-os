
[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x9500

mov [BOOT_STORAGE_DEVICE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel

call switch_to_pm

;The function load kernel code that start from sector 2, to the memory that start from KERNEL_OFFSET
load_kernel:
	mov bx, KERNEL_OFFSET
	mov al, 15
	mov dl, [BOOT_STORAGE_DEVICE]
	mov dh, 0x0
	mov ch, 0x0
	mov cl, 2
	call disk_load
	ret

[bits 32]

BEGIN_PM:
	call switch_to_lm

BEGIN_LM:
	call KERNEL_OFFSET
	jmp $

%include "screen_output.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"
%include "screen_output_pm.asm"
%include "disk_io.asm"
%include "paging.asm"
%include "switch_to_lm.asm"


MSG_REAL_MODE:
	db 'real', 13, 10, 0

MSG_PROTECTED_MODE:
	db 'pm!', 13, 10, 0
MSG_LONG_MODE:
	db 'lm!', 13, 10, 0
MSG_LOAD_KERNEL:
	db 'loaded!', 13, 10, 0
BOOT_STORAGE_DEVICE:
	db 0x0

times 510-($ - $$) db 0 ; When compiled , our program must fit into 512 bytes ,
			; with the last two bytes being the magic number ,
			; so here , tell our assembly compiler to pad out our
			; program with enough zero bytes (db 0) to bring us to the
			; 510 th byte.


dw 0xaa55 		; Last two bytes ( one word ) form the magic number ,
			; so BIOS knows we are a boot sector.
