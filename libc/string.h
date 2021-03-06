#ifndef STRING_H
#define STRING_H

#include "libc/types.h"

void str_dec(int32 n, byte *des);
void str_hex(nat32 n, byte *des);
void str_bin(int32 n, byte *des);
nat32 strlen(byte *s);
int32 strcmp(byte *s1, byte *s2);
void strcpy(byte *src, byte *des);

#endif