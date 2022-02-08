unsigned long getCr2()
{
    unsigned long cr2Reg;
    __asm__ __volatile__("movq %%cr2, %%rax" :"=a"(cr2Reg));
    return cr2Reg;
}