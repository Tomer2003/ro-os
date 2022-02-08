void memset(void* s, char c, unsigned int n)
{
    for(unsigned int i = 0; i < n; ++i)
    {
        *((char*)s + i) = c;
    }
}