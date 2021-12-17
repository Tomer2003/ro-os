#include "gdt.hpp"
#include "../libc/include/bits_operations.h"
#include "../libc/include/strings.h"
#include "../drivers/vga/vga_driver.hpp"

GtdSelector::GtdSelector() : selector(0){};
GtdSelector::GtdSelector(unsigned short selector) : selector(selector){};
GtdSelector::GtdSelector(unsigned short index, bool ti, unsigned char rpl)
{
    setIndex(index);
    setTI(ti);
    setRPL(rpl);
}

GtdSelector& GtdSelector::setIndex(unsigned short index)
{
    setBits(&selector, 3, 13, &index);
    return *this;
}

GtdSelector& GtdSelector::setTI(bool ti)
{
    setBits(&selector, 2, 1, &ti);
    return *this;
}

GtdSelector& GtdSelector::setRPL(unsigned char rpl)
{
    setBits(&selector, 0, 2, &rpl);
    return *this;
}

unsigned short GtdSelector::getSelector() const
{
    return selector;
}

unsigned short getCsSelector()
{
    unsigned short csSelector;
    __asm__ __volatile__("mov %%cs, %%ax" : "=a"(csSelector));
    return csSelector;
}

TSS::TSS()
{
    memset(&PST, 0x0, 3 * sizeof(unsigned long));
    memset(&IST, 0x0, 7 * sizeof(unsigned long));
    IOPB = 0;
    reserved0 = 0;
    reserved1 = 0;
    reserved2 = 0;
    reserved3 = 0;
}

void TSS::addPrivilegeStack(char index, void* addr)
{
    if(index >= 0 && index <= 2)
    {
        PST[index] = addr;
    }
}

void TSS::addInterruptStack(char index, void* addr)
{
    if(index >= 0 && index <= 7)
    {
        IST[index] = addr;
    }
}

void TSS::setIOPB(unsigned short val)
{
    //pass
}

GdtDescriptor::GdtDescriptor(unsigned short size, unsigned long addr) : size(size - 1), addr(addr){}

GDT::GDT() : gdtDdescriptor(NUMBER_OF_GDT_ENTRIES * 8, (long)segmentDescriptors)
{
    memset(segmentDescriptors, 0x0, NUMBER_OF_GDT_ENTRIES * 8);
}

void GDT::addSegmentDescriptor(char index, char isExecutable, char descriptorType, char privilege)
{
    if(index >= 0 && index < NUMBER_OF_GDT_ENTRIES && privilege >= 0 && privilege <= 3)
    {
        setBit((long*)segmentDescriptors + index, 43, isExecutable);
        setBit((long*)segmentDescriptors + index, 44, descriptorType);
        setBits((long*)segmentDescriptors + index, 45, 2, (void*)&privilege);
        setBit((long*)segmentDescriptors + index, 53, 1);//64-bit flag
        setBit((long*)segmentDescriptors + index, 47, 1);//present
        setBit((long*)segmentDescriptors + index, 41, 1);
    }
}

void GDT::addTssDescriptor(char index, const TSS& tss)
{
    unsigned short sizeOfTss = sizeof(TSS) - 1;
    const void* tssPtr = &tss;
    if(index >= 0 && index < NUMBER_OF_GDT_ENTRIES)
    {
        setBits((long*)segmentDescriptors + index, 0, 16, (void*)&sizeOfTss);
        setBits((long*)segmentDescriptors + index, 16, 24, (void*)&tssPtr);
        setBit((long*)segmentDescriptors + index, 40, 1);
        setBit((long*)segmentDescriptors + index, 43, 1);
        setBits((long*)segmentDescriptors + index, 56, 40, (char*)&tssPtr + 3);
        setBit((long*)segmentDescriptors + index, 47, 1);
        //setBit((long*)segmentDescriptors + index, 53, 1);
        //setBit((long*)segmentDescriptors + index, 54, 1);
    }
}

void GDT::load() const
{
    __asm__ __volatile__("lgdt %0" :: "m"(gdtDdescriptor));
}

void GDT::loadTss(unsigned char index) const
{
    index *= 8;
    __asm__ __volatile__("mov %%ax, %0\n\t"
                        "ltr %%ax" :: "m"(index) : "eax");
}

void setCodeSegmentRegister(long val)
{
    __asm__ __volatile__("pushq %0\n\t"
                        "push $ret_from_cs_setter\n\t"
                        "retfq\n\t"
                        "ret_from_cs_setter:"::"m"(val));
}