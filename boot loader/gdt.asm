;GLOBAL DESCRIPTOR TABLE DEFENITION

;protected mode gdt
gdt_pm_start:

gdt_pm_null_segment_descriptor:
	dd 0x0
	dd 0x0

gdt_pm_code_segment_descriptor:
	dw 0xffff		; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10011010b		; flags
	db 11001111b		; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_pm_data_segment_descriptor:
	dw 0xffff		; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10010010b		; flags
	db 11001111b		; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_pm_end:

gdt_pm_descriptor_start:
	dw gdt_pm_end - gdt_pm_start - 1	; (gdt size) - 1
	dd gdt_pm_start			; start address of the gdt



CODE_SEG_PM equ gdt_pm_code_segment_descriptor - gdt_pm_start		; code segment descriptor offset from start of gdt, that cs must contain
DATA_SEG_PM equ gdt_pm_data_segment_descriptor - gdt_pm_start		; data segment descriptor offset from start of gdt, that ds must contain

;long mode gdt
gdt_lm_start:

gdt_lm_null_segment_descriptor:
	dd 0x0
	dd 0x0

gdt_lm_code_segment_descriptor:
	dw 0x0	 	; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10011010b		; flags
	db 10101111b		; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_lm_data_segment_descriptor:
	dw 0x0			; Limit (0-15 bits)
	dw 0x0			; Base  (0-15 bits)
	db 0x0			; Base  (16-23 bits)
	db 10010010b	; flags
	db 00000000b	; flags, Limit (16-19 bits)
	db 0x0			; Base (24-31 bits)

gdt_lm_end:

gdt_lm_descriptor_start:
	dw gdt_lm_end - gdt_lm_start - 1	; (gdt size) - 1
	dd gdt_lm_start			; start address of the gdt



CODE_SEG_LM equ gdt_lm_code_segment_descriptor - gdt_lm_start		; code segment descriptor offset from start of gdt, that cs must contain
DATA_SEG_LM equ gdt_lm_data_segment_descriptor - gdt_lm_start		; data segment descriptor offset from start of gdt, that ds must contain
