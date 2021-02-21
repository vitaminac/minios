#include "pio.h"

b16 in_b16(nat16 port)
{
    b16 result;
    __asm__("in %%dx, %%ax"
            : "=a"(result)
            : "d"(port));
    return result;
}

void out_b16(nat16 port, b16 data)
{
    __asm__ __volatile__("out %%al, %%dx"
                         :
                         : "a"(data), "d"(port));
}

void out_byte(nat16 port, byte data)
{
    __asm__ __volatile__("out %%al, %%dx"
                         :
                         : "a"(data), "d"(port));
}