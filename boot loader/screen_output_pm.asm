[bits 32]
VGA_MEMORY_BUFFER equ 0xb8000		; start address of vga local buffer
WHITE_ON_BLACK equ 0x0f			; black & white vga style printing 

;The function print string in top
;param ebx - address of string
print_string_pm:
	pusha
	mov edx, VGA_MEMORY_BUFFER
	mov ah, WHITE_ON_BLACK
	mov al, [ebx]
	cmp al, 0
	je print_string_pm_done
print_string_pm_loop:
	mov [edx], ax
	
	add ebx, 1
	add edx, 2
	mov al, [ebx]
	cmp al, 0
	jne print_string_pm_loop
print_string_pm_done:
	popa
	ret

