#include "cpu/types.h"

void memory_copy(char *source, char *dest, nat32 no_bytes);
void memory_fill(char *source, int no_bytes, char *value, nat32 value_size);
#define low_16(address) (nat16)((address) & 0xFFFF)
#define high_16(address) (nat16)(((address) >> 16) & 0xFFFF)