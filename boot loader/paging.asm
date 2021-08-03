[bits 32]

;   PML4T - at offset 0x1000.
;   PDPT - at offset 0x2000.
;   PDT - at offset 0x3000.
;   PT - at offset 0x4000.

;set paging
set_paging:
    call check_cpuid
	call check_long_mode
    
    mov edi, 0x1000
    xor eax, eax
    mov ecx, 4096
    rep stosd       ; clear paging tables, write 4096 * 4 bytes of 0x0 from 0x1000
                           
                            ; two bits sets(3) for writable and readable of the page
    mov DWORD [edi], 0x2003 ; set PML4 first entry to point to PDPT 
    add edi, 0x1000
    mov DWORD [edi], 0x3003 ; set PDPT first entry to point to DPT
    add edi, 0x1000
    mov DWORD [edi], 0x4003 ; set DPT first entry to point to PT
    add edi, 0x1000

    mov ebx, 0x00000003
    mov ecx, 512
    mov edx, 0
set_entry:                  ; set identity map between virtual and physical memory in PT
    mov DWORD [edi], ebx
    add ebx, 0x1000
    add edi, 8
    add edx, 1
    cmp edx, ecx
    jne set_entry
    
    mov eax, cr4                 ; Set the A-register to control register 4.
    or eax, 1 << 5               ; Set the PAE-bit, which is the 6th bit (bit 5).
    mov cr4, eax                 ; Set control register 4 to the A-register.


%include "cpuid.asm"