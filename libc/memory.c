#include "memory.h"

/* Copy bytes from one place to another */
void memory_copy(byte *source, byte *dest, nat32 no_bytes)
{
    for (nat32 i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

void memory_fill(byte *source, int no_bytes, byte *value, nat32 value_size)
{
    for (int i = 0; i < no_bytes; i++, source++)
    {
        *source = *(value + (i % value_size));
    }
}

void *const malloc(nat32 nBytes)
{
    static word free_mem_addr = 0x10000;
    void *const ret = (void *)free_mem_addr;
    free_mem_addr += nBytes;
    if (free_mem_addr & WORD_MASK)
    {
        free_mem_addr &= ~WORD_MASK;
        free_mem_addr += WORD_SIZE;
    }
    return ret;
}

int32 memcmp(const byte *ptr1, const byte *ptr2, nat32 size)
{
    while (size-- > 0)
    {
        if (*ptr1 != *ptr2)
        {
            return *ptr1 - *ptr2;
        }
        ++ptr1;
        ++ptr2;
    }
    return 0;
}