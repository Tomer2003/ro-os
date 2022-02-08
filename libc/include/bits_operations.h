#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief set numOfBits bits to val in dest from startIndex
     * 
     * @param addr - where set the bits
     * @param setIndex - index from where set the bits
     * @param numOfBitsToSet - how much bits set
     * @param val - value that represent the bits to set
     */
    void setBits(void* dest, unsigned int setIndex, unsigned int numOfBitsToSet, void* val);

    /**
     * @brief get bit of val in spesific index 
     * 
     * @param val - val
     * @param index - index of the bit
     * @return unsigned char 
     */
    unsigned char getBit(void* val, unsigned int index);

    /**
     * @brief set bit of val in spesific index
     * 
     * @param val - val
     * @param setIndex - index of the bit
     * @param bit - value of bit
     */
    void setBit(void* val, unsigned int setIndex, unsigned char bit);
#ifdef __cplusplus
}
#endif