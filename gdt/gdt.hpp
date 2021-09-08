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


unsigned short getCsSelector();
