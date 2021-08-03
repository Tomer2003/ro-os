[bits 32]

;check if cpu support cpuid instruction
check_cpuid:
    pushfd
    pop eax
    
    and eax, 0x00200000
    cmp eax, 0x0
    je cpuid_invalid
    ret

;check if cpu support long mode
check_long_mode:
    mov eax, 0x80000000    
    cpuid                  
    cmp eax, 0x80000001    
    jb no_long_mode         ; It is less, there is no long mode.

    mov eax, 0x80000001    
    cpuid                  
    test edx, 1 << 29      
    jz no_long_mode         ; They aren't, there is no long mode.


cpuid_invalid:
    ret

no_long_mode:
    ret
