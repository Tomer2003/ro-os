#include "../include/array_operations.h"
#define ASCII_VAL_OF_ZERO 48

void utoa(unsigned int num, char* str)
{
    int i = 0;
    while (num / 10)
    {
        *(str + i) = num % 10 + ASCII_VAL_OF_ZERO;
        num = num / 10;
        i++;
    }
    *(str + i) = num % 10 + ASCII_VAL_OF_ZERO;
    reverse(str, i + 1);
    *(str + i + 1) = 0;
}