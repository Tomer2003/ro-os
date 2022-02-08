#define NUM_BITS_IN_BYTE 8

unsigned char getBit(void* val, unsigned int index)
{
    unsigned int byteIndex = index / NUM_BITS_IN_BYTE;
    return ((*((char*)val + byteIndex) >> (index % NUM_BITS_IN_BYTE)) & 1);
}

void setBit(void* val, unsigned int setIndex, unsigned char bit)
{
    unsigned int byteIndex = setIndex / NUM_BITS_IN_BYTE;
    if(bit)
    {
        *((char*)val + byteIndex) = *((char*)val + byteIndex) | (1 << (setIndex % NUM_BITS_IN_BYTE));
    }
    else
    {
        *((char*)val + byteIndex) = *((char*)val + byteIndex) & ~(1 << (setIndex % NUM_BITS_IN_BYTE));
    }
}

void setBits(void* dest, unsigned int setIndex, unsigned int numOfBitsToSet, void* val)
{
    for(unsigned int i = 0; i < numOfBitsToSet; ++i)
    {
        setBit(dest, setIndex + i, getBit(val, i));
    }
}