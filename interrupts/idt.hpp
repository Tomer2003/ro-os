#pragma once

class GtdSelector{
private:
    unsigned short selector;

public:
    GtdSelector(unsigned short selector);
    GtdSelector(unsigned short index, bool ti, unsigned char rpl);
    GtdSelector();

    /**
     * @brief set index of descriptor.
     * 
     * @param index - if greater than 2^13 - 1, so 2^13 - 1 in default.
     */
    void setIndex(unsigned short index);
    /**
     * @brief set wich table to use.
     * 
     * @param ti - true for gdt, false for ldt.
     */
    void setTI(bool ti);
    /**
     * @brief  set recent privilege level.
     * 
     * @param rpl - privilege level = 0|1|2|3, if larger so 3 in default.
     */
    void setRPL(unsigned char rpl);
    /**
     * @brief Get the Selector object
     * 
     * @return unsigned short 
     */
    unsigned short getSelector() const;
};

typedef struct __attribute__((__packed__)) idtEntry{
    unsigned short pointerLow;
    //gdt selector
    //options
    unsigned short pointerMid;
    unsigned int pointerEnd;
    unsigned int reserved;
}idtEntry;