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
        buffer[i] = n % base;
        if (buffer[i] >= 10)
        {
            buffer[i] = buffer[i] - 10 + 'a';
        }
        else
        {
            buffer[i] += '0';
        }
        n /= base;
        ++i;
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

int strcmp(char *a, char *b)
{
    do
    {
        if (a == b)
        {
            a++;
            b++;
        }
        else if (a == '\0')
            return -1;
        else if (b == '\0')
            return 1;
        else
            return *b - *a;
    } while (true);
}

void strcpy(char *src, char *des)
{

    while (*src != '\0')
    {
        *des = *src;
        des++;
        src++;
    }
    *des = '\0';
}