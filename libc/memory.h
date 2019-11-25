#ifndef MEMORY_H
#define MEMORY_H

#include "cpu/types.h"

void memory_copy(char *source, char *dest, nat32 no_bytes);
void memory_fill(char *source, int no_bytes, char *value, nat32 value_size);
int *malloc(nat32 size);
#define low_16(address) (nat16)((address)&0xFFFF)
#define high_16(address) (nat16)(((address) >> 16) & 0xFFFF)
#define low_8(address) (nat16)((address)&0xFF)
#define high_8(address) (nat16)(((address) >> 8) & 0xFF)

#endif