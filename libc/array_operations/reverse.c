void reverse(char* array, unsigned int size)
{
    char temp;
    for(unsigned int i = 0; i < size / 2; ++i)
    {
        temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}