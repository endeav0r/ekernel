#ifndef aci_stdlib_HEADER
#define aci_stdlib_HEADER

#include "stdarg.h"

#define NULL 0

void * aci_memcpy  (void *       dest, const void *  src,    int n);
void * aci_memset  (void *       dest, unsigned char c,      int n);
int    aci_sprintf (char *       str,  const char *  format, ...);
char * aci_strcat  (char *       dest, const char *  src);
int    aci_strcmp  (const char * s1,   const char *  s2);
char * aci_strcpy  (char *       dest, const char *  src);
int    aci_strlen  (const char * str);
int    aci_strncmp (const char * s1,   const char * s2,  int nbytes);
char * aci_strncpy (char *       dest, const char * src, int nbytes);

void * aci_malloc_align (unsigned int size, unsigned int align);
void * aci_malloc       (unsigned int size);
void * aci_realloc      (void * address, unsigned int size);
int    aci_free         (void * address);

void aci_stdlib_test ();

#endif
