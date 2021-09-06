#pragma once

class __attribute__((__packed__)) GtdSelector{
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
     * @brief set wich table to use.
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

class __attribute__((__packed__)) IdtOptions
{
private:
    unsigned short options;

public:
    IdtOptions();
    IdtOptions(bool present, bool interruptGate, unsigned char dpl, unsigned char index);
    /**
     * @brief set present field
     * 
     * @param present - present
     * @return IdtOptions& - same object 
     */
    IdtOptions& setPresent(bool present);
    /**
     * @brief Set the Interrupt Gate field
     * 
     * @param interruptGate - If this bit is 0, interrupts are disabled when this handler is called
     * @return IdtOptions& - same object 
     */
    IdtOptions& setInterruptGate(bool interruptGate);
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
    IdtEntry(const GtdSelector& gdtSelector, const IdtOptions& idtOptions, void (*handlerFunction)());
};