[bits 32]

; switch to long mode
switch_to_lm:
    call enable_paging
    lgdt [gdt_lm_descriptor_start]
    jmp CODE_SEG_LM:init_lm


init_lm:
    cli
    mov ax, DATA_SEG_LM
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call BEGIN_LM