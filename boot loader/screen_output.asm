; screen output in real mode
[bits 16]
print_string:
	pusha
	mov ah, 0x0e
	mov al, [bx]
	cmp al, 0
	je end_loop
start_loop:
	int 0x10
	add bx, 1
	mov al, [bx]
	cmp al, 0
	jne start_loop
end_loop:
	popa
	ret

;print_hex:
;	pusha
;	mov ax, HEX_OUT
;	add ax, 5	; pointer to the last 0 in HEX_OUT
;	mov cx, 0	; number of iterations
;loop:
;	mov dx, bx
;	and dx, 0x000f
;set_digit:		; set digit in HEX_OUT
;	cmp dx, 9
;	jg set_letter
;	add dl, 48
;	mov [eax], dl
;	jmp next
;set_letter:		; set letter in HEX_OUT
;	add dl, 87
;	mov [eax], dl
;next:
;	sub ax, 1
;	shr bx, 4
;	add cx, 1
;	cmp cx, 4
;	jne loop
;	mov bx, HEX_OUT
;	call print_string
;	popa
;	ret
	
	







HEX_OUT:
	db '0x0000', 0	
