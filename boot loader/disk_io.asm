[bits 16]
;DISK IO

;The function load data from device storage to memory location
; param bx - memory address to load
; param al - how many sectors to read
; param dl - index of storage device to read from
; param dh - index of head to read from
; param ch - index of cylinder to read from
; param cl - index of sector to read from
disk_load:
	pusha
	push ax
	mov ah, 0x02
	int 0x13
	
	jc disk_error

	pop bx
	cmp bl, al
	jne disk_error
	popa
	ret
	

disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

DISK_ERROR_MSG:
	db "Disk read error!", 13, 10, 0

