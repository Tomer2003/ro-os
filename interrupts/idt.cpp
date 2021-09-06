#include "idt.hpp"
#include "../libc/include/bits_operations.h"

GtdSelector::GtdSelector() : selector(0){};
GtdSelector::GtdSelector(unsigned short selector) : selector(selector){};
GtdSelector::GtdSelector(unsigned short index, bool ti, unsigned char rpl)
{
    setIndex(index);
    setTI(ti);
    setRPL(rpl);
}

void GtdSelector::setIndex(unsigned short index)
{
    setBits(&selector, 3, 13, &index);
}

void GtdSelector::setTI(bool ti)
{
    setBits(&selector, 2, 1, &ti);
}

void GtdSelector::setRPL(unsigned char rpl)
{
    setBits(&selector, 0, 2, &rpl);
}

unsigned short GtdSelector::getSelector() const
{
    return selector;
}