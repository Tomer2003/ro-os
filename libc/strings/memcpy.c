#include "include/strings.h"

void memcpy( void * destination, const void * source, unsigned int num)
{
    char* srcBytePtr = (char*)source;
    char* dstBytePtr = (char*)destination;
    for(unsigned int i = 0; i < num; ++i)
    {
        *srcBytePtr++ = *dstBytePtr++;
    }
}

