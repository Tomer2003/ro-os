#include "idt.hpp"
#include "../libc/include/bits_operations.h"
#include "../libc/include/strings.h"
#include "../drivers/vga/vga_driver.hpp"

IdtOptions::IdtOptions() : options(0)
{
    setBit(&options, 9, 1);
    setBit(&options, 10, 1);
    setBit(&options, 11, 1);
    setBit(&options, 12, 0);
}

IdtOptions::IdtOptions(bool present, bool disable, unsigned char dpl, unsigned char index) : options(0)
{
    setBit(&options, 9, 1);
    setBit(&options, 10, 1);
    setBit(&options, 11, 1);
    setBit(&options, 12, 0);
    setDPL(dpl);
    setInterrupStackTableIndex(index);
    disableInterrupts(disable);
    setPresent(present);
}


IdtOptions& IdtOptions::setDPL(unsigned char dpl)
{
    setBits(&options, 13, 2, &dpl);
    return *this;
}

IdtOptions& IdtOptions::setInterrupStackTableIndex(unsigned char index)
{
    setBits(&options, 0, 3, &index);
    return *this;
}

IdtOptions& IdtOptions::disableInterrupts(bool disable)
{
    setBit(&options, 8, !disable);
    return *this;
}

IdtOptions& IdtOptions::setPresent(bool present)
{
    setBit(&options, 15, present);
    return *this;
}

unsigned short IdtOptions::getOptionsVal() const
{
    return options;
}

IdtEntry::IdtEntry(const GtdSelector& gdtSelector, const IdtOptions& idtOptions, void (*handlerFunction)()) : gdtSelector(gdtSelector), idtOptions(idtOptions), pointerLow(*((unsigned short*)&handlerFunction)), pointerMid(*((unsigned short*)&handlerFunction + 1)), pointerEnd(*((unsigned int*)&handlerFunction + 1)){}
IdtEntry::IdtEntry(){}

const GtdSelector& IdtEntry::getGdtSelector() const
{
    return gdtSelector;
}

const IdtOptions& IdtEntry::getIdtOptions() const
{
    return idtOptions;
}

IDT::IDT()
{
    memset(idtEntries, 0, sizeof(IdtEntry) * IDT_ENTRIES_NUM);
    idtDescriptor.base = idtEntries;
    idtDescriptor.limit = sizeof(IdtEntry) * IDT_ENTRIES_NUM;
}

void IDT::addEntry(const IdtEntry& entry, unsigned char entryIndex)
{
    idtEntries[entryIndex] = entry;
}

void IDT::load()
{
   __asm__ __volatile__("lidt %0" :: "m"(idtDescriptor));
}

const IdtEntry& IDT::getEntry(unsigned char entryIndex) const
{
    return idtEntries[entryIndex];
}

void ExceptionStackFrame::show() const
{
    print("instruction pointer = ");
    printUnsignedInt(instructionPointer);
    print("\ncode segment = ");
    printUnsignedInt(codeSegmentSelector);
    print("\ncpu flags = ");
    printUnsignedInt(flagsRegister);
    print("\nstack pointer = ");
    printUnsignedInt(stackPointer);
    print("\nstack segment = ");
    printUnsignedInt(stackSegment);
    print("\n");
}

void ErrorCode::show() const
{
    print("error code: ");
    if(getBit((void*)&errorCode, 0))
    {
        print("PROTECTION_VIOLATION ");
    }
    if(getBit((void*)&errorCode, 1))
    {
        print("CAUSED_BY_WRITE ");
    }
    if(getBit((void*)&errorCode, 2))
    {
        print("USER_MODE ");
    }
    if(getBit((void*)&errorCode, 3))
    {
        print("MALFORMED_TABLE ");
    }
    if(getBit((void*)&errorCode, 4))
    {
        print("INSTRUCTION_FETCH ");
    }
    print("\n");
}