#include "gdt.hpp"
#include "../libc/include/bits_operations.h"

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