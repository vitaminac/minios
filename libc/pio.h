#ifndef PIO_H
#define PIO_H
#include "libc/types.h"

b16 in_b16(nat16 port);
void out_b16(nat16 port, b16 data);
void out_byte(nat16 port, byte data);

#endif