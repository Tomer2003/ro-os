#pragma once
#define NUMBER_OF_GDT_ENTRIES 5
class __attribute__((__packed__)) GtdSelector
{
private:
    unsigned short selector;

public:
    GtdSelector(unsigned short selector);
    GtdSelector(unsigned short index, bool ti, unsigned char rpl);
    GtdSelector();

    /**
     * @brief set index of descriptor.
     * 
     * @param index - val of index.
     */
    GtdSelector& setIndex(unsigned short index);
    /**
     * @brief set witch table to use.
     * 
     * @param ti - true for gdt, false for ldt.
     */
    GtdSelector& setTI(bool ti);
    /**
     * @brief  set recent privilege level.
     * 
     * @param rpl - privilege level = 0|1|2|3.
     */
    GtdSelector& setRPL(unsigned char rpl);
    /**
     * @brief Get the Selector object
     * 
     * @return unsigned short 
     */
    unsigned short getSelector() const;
};

/**
 * @brief get current cs register value
 * 
 * @return unsigned short 
 */
unsigned short getCsSelector();


class __attribute__((__packed__)) TSS
{
private:
    unsigned int reserved0;
    void* PST[3]; //Privilege Stack Table
    unsigned long reserved1;
    void* IST[7]; //Interrupt Stack Table
    unsigned long reserved2;
    unsigned short reserved3;
    unsigned short IOPB; //I/O Map Base Address
public:
    TSS();
    
    void addPrivilegeStack(char index, void* addr);
    void addInterruptStack(char index, void* addr);
    void setIOPB(unsigned short val);
};

class __attribute__((__packed__)) GdtDescriptor
{
private:
    unsigned short size; //(gdt size) - 1
    unsigned long addr; //start address of the gdt
public:
    GdtDescriptor(unsigned short size, unsigned long addr);
};

class GDT
{
private:
    long segmentDescriptors[NUMBER_OF_GDT_ENTRIES];
    GdtDescriptor gdtDdescriptor;
public:
    GDT();

    /**
     * @brief add entry to segmentDescriptors
     * 
     * @param index - index of descriptor
     * @param isExecutable - if set, it's a code segment, else it's a data segment
     * @param descriptorType - should be 1 for code and data segments
     * @param privilege - the ring level: 0 for kernel, 3 for user
     */
    void addSegmentDescriptor(char index, char isExecutable, char descriptorType, char privilege);
    void addTssDescriptor(char index, const TSS& tss);
    void load() const;
    void loadTss(unsigned char index) const;
};

void setCodeSegmentRegister(long val);