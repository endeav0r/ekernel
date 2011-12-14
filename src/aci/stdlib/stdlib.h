#ifndef aci_stdlib_HEADER
#define aci_stdlib_HEADER

#include "stdarg.h"

void * aci_memcpy  (void * dest, const void * src, int n);
void * aci_memset  (void * dest, unsigned char c, int n);
int    aci_sprintf (char * str, const char * format, ...);
int    aci_strcmp  (const char * s1, const char * s2);
char * aci_strcpy  (char * dest, const char * src);
int    aci_strlen  (const char * str);

void aci_stdlib_test ();

#endif
