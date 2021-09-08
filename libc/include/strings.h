#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
    void memcpy( void * destination, const void * source, unsigned int num);
    void memset(void* s, char c, unsigned int n);
#ifdef __cplusplus
}
#endif