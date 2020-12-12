#ifndef STRING_H
#define STRING_H

#include "libc/types.h"

void str_dec(int32 n, char *des);
void str_hex(nat32 n, char *des);
void str_bin(int32 n, char *des);
nat32 strlen(char *s);
int32 strcmp(char *s1, char *s2);
void strcpy(char *src, char *des);

#endif