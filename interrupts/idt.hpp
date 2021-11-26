#pragma once
#include "../gdt/gdt.hpp"
#include "../libc/include/regs_operations.h"

#define IDT_ENTRIES_NUM 256 

#define generateHandlerFunctionWithErrorCode(wrapper, handler)\
__attribute__((naked)) void wrapper()\
{\
    pushCallerSaversRegs()\
    __asm__ __volatile__("movq %%rsp, %%rdi\n\t"\
						"addq $80, %%rdi\n\t"\
                        "movq 72(%%rsp), %%rsi\n\t"\
                        "subq $8, %%rsp\n\t"\
						"call %0\n\t"\
                        "addq $8, %%rsp" ::"d"(handler):"%rdi");\
    popCallerSaversRegs()\
    __asm__ __volatile__("addq $8, %%rsp\n\t"\
                        "iretq":::);\
}

#define generateHandlerFunction(wrapper, handler)\
__attribute__((naked)) void wrapper()\
{\
    pushCallerSaversRegs()\
	__asm__ __volatile__("movq %%rsp, %%rdi\n\t"\
						"addq $72, %%rdi\n\t"\
						"call %0" ::"d"(handler):"%rdi");\
    popCallerSaversRegs()\
    __asm__ __volatile__("iretq":::);\
}

class __attribute__((__packed__)) IdtOptions
{
private:
    unsigned short options;

public:
    IdtOptions();
    IdtOptions(bool present, bool disable, unsigned char dpl, unsigned char index);
    /**
     * @brief set present field
     * 
     * @param present - present
     * @return IdtOptions& - same object 
     */
    IdtOptions& setPresent(bool present);
    /**
     * @brief disable interrupts
     * 
     * @param interruptGate - If this bit is 0, interrupts are disabled when this handler is called
     * @return IdtOptions& - same object 
     */
    IdtOptions& disableInterrupts(bool disable);
    /**
     * @brief set Descriptor Privilege Level field
     * 
     * @param dpl - The minimal privilege level required for calling this handler
     * @return IdtOptions& - same object 
     */
    IdtOptions& setDPL(unsigned char dpl);
    /**
     * @brief Set the Interrup Stack Table Index field
     * 
     * @param index - 0: Don't switch stacks, 1-7: Switch to the n-th stack in the Interrupt Stack Table when this handler is called
     * @return IdtOptions& - same object 
     */
    IdtOptions& setInterrupStackTableIndex(unsigned char index);
    /**
     * @brief get options val
     * 
     * @return unsigned short - options val
     */
    unsigned short getOptionsVal() const;
};

class __attribute__((__packed__)) IdtEntry{
private:
    unsigned short pointerLow;
    GtdSelector gdtSelector;
    IdtOptions idtOptions;
    unsigned short pointerMid;
    unsigned int pointerEnd;
    unsigned int reserved;

public:
    IdtEntry();
    IdtEntry(const GtdSelector& gdtSelector, const IdtOptions& idtOptions, void (*handlerFunction)());
    /**
     * @brief get gdt selector
     * 
     * @return const GtdSelector& - gdt selector 
     */
    const GtdSelector& getGdtSelector() const;
    /**
     * @brief get idt options
     * 
     * @return const IdtOptions& - idt options
     */
    const IdtOptions& getIdtOptions() const;
};

typedef struct __attribute__((__packed__)) IdtDescriptor
{
    unsigned short limit;
    void* base;
}IdtDescriptor;


class IDT
{
private:
    IdtEntry idtEntries[IDT_ENTRIES_NUM];
    IdtDescriptor idtDescriptor;

public:
    IDT();
    /**
     * @brief add entry to idt
     * 
     * @param entry - entry description
     * @param entryIndex - index of entry in idt
     */
    void addEntry(const IdtEntry& entry, unsigned char entryIndex);
    /**
     * @brief load idt descriptor to the cpu
     * 
     */
    void load();
    /**
     * @brief get entry of idt
     * 
     * @param entryIndex - index of entry in idt
     * @return const IdtEntry& - entry description
     */
    const IdtEntry& getEntry(unsigned char entryIndex) const;
};

class __attribute__((__packed__)) ExceptionStackFrame
{
private:
    unsigned long instructionPointer;
    unsigned long codeSegmentSelector;
    unsigned long flagsRegister;
    unsigned long stackPointer;
    unsigned long stackSegment;

public:
    /**
     * @brief Print the exception stack frame.
     * 
     */
    void show() const;
};

class ErrorCode
{
private:
    unsigned long errorCode;

public:
    /**
     * @brief Print the fields of error code.
     * 
     */
    void show() const;
};