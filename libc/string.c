#include "string.h"

void dec2str(int32 n, char *des)
{
    int len;
    if (n > 0)
    {
        n = -n;
        len = 0;
    }
    else
    {
        len = 1;
        des[0] = '-';
    }
    do
    {
        des[len] = -(n % 10) + '0';
        n /= 10;
        len += 1;
    } while (n < 0);
    des[len] = '\0';
    if (des[0] == '-')
        str_reverse(des + 1);
    else
        str_reverse(des);
}

const char n_to_ascii[] = "0123456789abcdef";

void hex2str(nat32 n, char *des)
{
    nat32 len = 0;
    do
    {
        des[len++] = n_to_ascii[n & 0xf];
        n >>= 4;
    } while (n != 0);
    des[len++] = 'x';
    des[len++] = '0';
    des[len] = '\0';
    str_reverse(des);
}

/* K&R */
void str_reverse(char *s)
{
    char c;
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
nat32 strlen(char *s)
{
    nat32 i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

/* K&R */
int32 strcmp(char *s1, char *s2)
{
    int32 i;
    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
            return 0;
    }
    return s1[i] - s2[i];
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