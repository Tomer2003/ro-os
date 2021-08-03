[bits 16]

;The function switch to protected mode from real mode
switch_to_pm:
	cli		; disable interrupts, beacuase bios interrupt serviece  routins implemented for real mode
			;, so it can crash the cpu assuming we use 16 bit segmentation.

	lgdt [gdt_pm_descriptor_start]		; load gdt descriptor to cpu

	mov eax, cr0		; make switch to protected mode
	or eax, 0x1
	mov cr0, eax		

	jmp CODE_SEG_PM:init_pm		; make far jump against pipelining of the cpu that can start execute instructions in real mode, also updtae cs register to CODE_SEG

[bits 32]
;The funtion init segmentation registers, and the stack pointer in protected mode
init_pm:
	mov ax, DATA_SEG_PM
	mov ds, ax
	mov ss, ax
	mov gs, ax
	mov es, ax
	mov fs, ax

	mov ebp, 0x90000		; update stack pointer to free space memory
	mov esp, ebp
	
	call BEGIN_PM
