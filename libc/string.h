#ifndef STRING_H
#define STRING_H

#include "cpu/types.h"

void str(int n, int base, char* destination);
inline void int_to_ascii(int n, char* destination)
{
    str(n, 10, destination);
}
inline void hex_to_ascii(int n, char* destination)
{
    str(n, 16, destination);
}
int strcmp(char *a, char *b);
void strcpy(char *src, char *des);

#endif