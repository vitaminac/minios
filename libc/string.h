#ifndef STRING_H
#define STRING_H

#include "def/types.h"

void dec2str(int32 n, char *des);
void hex2str(nat32 n, char *des);
void str_bin(int32 n, byte *des);
nat32 strlen(char *s);
int32 strcmp(char *s1, char *s2);
void strcpy(char *src, char *des);
void str_reverse(char *s);

#endif