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

IdtOptions::IdtOptions()
{
    setBit(&options, 9, 1);
    setBit(&options, 10, 1);
    setBit(&options, 11, 1);
    setBit(&options, 12, 0);
}

IdtOptions::IdtOptions(bool present, bool interruptGate, unsigned char dpl, unsigned char index)
{
    setBit(&options, 9, 1);
    setBit(&options, 10, 1);
    setBit(&options, 11, 1);
    setBit(&options, 12, 0);
    setDPL(dpl);
    setInterrupStackTableIndex(index);
    setInterruptGate(interruptGate);
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

IdtOptions& IdtOptions::setInterruptGate(bool interruptGate)
{
    setBit(&options, 8, interruptGate);
    return *this;
}

IdtOptions& IdtOptions::setPresent(bool present)
{
    setBit(&options, 15, present);
    return *this;
}



