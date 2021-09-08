#pragma once
#include "../gdt/gdt.hpp"

#define IDT_ENTRIES_NUM 256 

class __attribute__((__packed__)) IdtOptions
{
private:
    unsigned short options;

public:
    IdtOptions();
    IdtOptions(bool present, bool dissable, unsigned char dpl, unsigned char index);
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
    IdtOptions& dissableInterrupts(bool dissable);
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
//private:
public:
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