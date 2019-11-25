#include "memory.h"

/* Copy bytes from one place to another */
extern void memory_copy(char *source, char *dest, nat32 no_bytes)
{
    int i;
    for (i = 0; i < no_bytes; i++)
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

int *malloc(nat32 size)
{
    static nat32 free_mem_addr = 0x10000;
    int *ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
    return ret;
}