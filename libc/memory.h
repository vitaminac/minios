#ifndef MEMORY_H
#define MEMORY_H

#include "libc/types.h"

void memory_copy(char *source, char *dest, nat32 no_bytes);
void memory_fill(char *source, int no_bytes, char *value, nat32 value_size);
int32 memcmp(const byte *ptr1, const byte *ptr2, nat32 size);
ptr const malloc(nat32 nBytes);
#define low_16(address) (nat16)((address)&0xFFFF)
#define high_16(address) (nat16)(((address) >> 16) & 0xFFFF)
#define low_8(address) (nat16)((address)&0xFF)
#define high_8(address) (nat16)(((address) >> 8) & 0xFF)

#endif