#include "stdlib.h"

void * aci_memcpy (void * dest, const void * src, int n)
{
    int i;
    for (i = 0; i < n; i++)
        *((unsigned char *) &(dest[i])) = src[i];
    return dest;
}

void * aci_memset (void * dest, unsigned char c, int n)
{
    int i;
    for (i = 0; i < n; i++)
        *((unsigned char *) &(dest[i])) = c;
    return dest;
}

char * strreverse (char * s)
{
    int first = 0;
    int last = aci_strlen(s) - 1;
    while (first < last) {
        s[first]   ^= s[last];
        s[last]    ^= s[first];
        s[first++] ^= s[last--];
    }
    return s;
}

char * strx (unsigned int n)
{
    static char charset[] = "0123456789ABCDEF";
    static char buf[32];
    int buf_i = 0;

    if (n == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    
    while (n > 0) {
        buf[buf_i++] = charset[n % 16];
        n /= 16;
    }
    buf[buf_i] = '\0';

    return strreverse(buf);
}

int aci_sprintf (char * str, const char * format, ...)
{
    char * s = str;
    const char * f = format;
    char * buf, * bufc;
    int length = 0;

    va_list args;
    va_start(args, format);

    while (*f != '\0') {
        if (*f == '%' ) {
            f++;
            buf = 0;
            switch (*f) {
            case 'x' :
                buf = strx(va_arg(args, unsigned int));
                break;
            case 's' :
                buf = va_arg(args, char *);
            }
            if (buf != 0) {
                for (bufc = buf; *bufc != '\0'; bufc++) {
                    *(s++) = *bufc;
                    length++;
                }
            }
        }
        else if (*f == '\\')
            *(s++) = *(++f);
        else
            *(s++) = *f;
        f++;
        length++;
    }
    *s = '\0';

    return length;
}

int aci_strcmp (const char * s1, const char * s2)
{
    const char * a = s1;
    const char * b = s2;
    while ((*a != '\0') && (*b != '\0')) {
        if (*a != *b)
            return *a - *b;
        a++;
        b++;
    }
    if (*a != '\0')
        return 1;
    else if (*b != '\0')
        return -1;
    return 0;
}

char * aci_strcpy (char * dest, const char * src)
{
    char * d       = dest;
    const char * s = src;
    while (*s != '\0')
        *(d++) = *(s++);
    *d = '\0';
    return d;
}

int aci_strlen (const char * str)
{
    const char * c = str;
    while (*c != '\0') c++;
    return (int) (c - str);
}

