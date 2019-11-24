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