#include "port_io.hpp"

void portWriteByte(unsigned short portAddress, unsigned char data)
{
    __asm__ __volatile__("out %%al, %%dx" :: "a"(data), "d"(portAddress));
}

unsigned char portReadByte(unsigned short portAddress)
{
    unsigned char result;
    __asm__ __volatile__("in %%dx, %%al" : "=a"(result) : "d"(portAddress));
    return result;
}

void portWriteWord(unsigned short portAddress, unsigned short data)
{
    __asm__ __volatile__("out %%ax, %%dx" :: "a"(data), "d"(portAddress));
}

unsigned short portReadWord(unsigned short portAddress)
{
    unsigned short result;
    __asm__ __volatile__("in %%dx, %%ax" : "=a"(result) : "d"(portAddress));
    return result;
}