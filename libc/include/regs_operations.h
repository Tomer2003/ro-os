#pragma once

#define popCallerSaversRegs()\
__asm__ __volatile__("popq %%r11\n\t"\
                    "popq %%r10\n\t"\
                    "popq %%r9\n\t"\
                    "popq %%r8\n\t"\
                    "popq %%rdi\n\t"\
                    "popq %%rsi\n\t"\
                    "popq %%rdx\n\t"\
                    "popq %%rcx\n\t"\
                    "popq %%rax\n\t":::);

#define pushCallerSaversRegs()\
__asm__ __volatile__("pushq %%rax\n\t"\
                    "pushq %%rcx\n\t"\
                    "pushq %%rdx\n\t"\
                    "pushq %%rsi\n\t"\
                    "pushq %%rdi\n\t"\
                    "pushq %%r8\n\t"\
                    "pushq %%r9\n\t"\
                    "pushq %%r10\n\t"\
                    "pushq %%r11\n\t":::);

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief get cr2 register
     * 
     * @return unsigned long 
    */
    unsigned long getCr2();











#ifdef __cplusplus
}
#endif