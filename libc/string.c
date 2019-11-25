#include "string.h"

void str(int n, int base, char *destination)
{
    char buffer[32];
    int i = 0, j, negative = false;
    if (n < 0)
    {
        n = -n;
        negative = true;
    }
    do
    {
        buffer[i++] = n % base + '0';
        n /= base;
    } while (n > 0);
    for (int j = (negative) ? 1 : 0; i > 0;)
    {
        destination[j++] = buffer[--i];
    }
    destination[j] = '\0';
    if (negative)
    {
        destination[0] = '-';
    }
}