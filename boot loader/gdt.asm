;GLOBAL DESCRIPTOR TABLE DEFENITION

gdt_start:

gdt_null_segment_descriptor:
	dd 0x0
	dd 0x0

gdt_code_segment_descriptor:
	dw 0xffff		; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10011010b		; flags
	db 11001111b		; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_data_segment_descriptor:
	dw 0xffff		; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10010010b		; flags
	db 11001111b		; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_end:

gdt_descriptor_start:
	dw gdt_end - gdt_start - 1	; (gdt size) - 1
	dd gdt_start			; start address of the gdt



CODE_SEG equ gdt_code_segment_descriptor - gdt_start		; code segment descriptor offset from start of gdt, that cs must contain
DATA_SEG equ gdt_data_segment_descriptor - gdt_start		; data segment descriptor offset from start of gdt, that ds must contain
