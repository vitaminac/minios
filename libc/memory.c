#include "memory.h"

/* Copy bytes from one place to another */
extern void memory_copy(char *source, char *dest, nat32 no_bytes)
{
    for (nat32 i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

extern void memory_fill(char *source, int no_bytes, char *value, nat32 value_size)
{
    for (int i = 0; i < no_bytes; i++, source++)
    {
        *source = *(value + (i % value_size));
    }
}

extern ptr const malloc(nat32 nBytes)
{
    static word free_mem_addr = 0x10000;
    ptr const ret = (ptr) free_mem_addr;
    free_mem_addr += nBytes;
    if (free_mem_addr & WORD_MASK) {
        free_mem_addr &= ~WORD_MASK;
        free_mem_addr += WORD_SIZE;
    }
    return ret;
}