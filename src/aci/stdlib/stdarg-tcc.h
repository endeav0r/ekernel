#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list;

/* only correct for i386 */
#define va_start(ap,last) ap = ((char *)&(last)) + ((sizeof(last)+3)&~3)
#define va_arg(ap,type) (ap += (sizeof(type)+3)&~3, *(type *)(ap - ((sizeof(type)+3)&~3)))
#define va_copy(dest, src) (dest) = (src)
#define va_end(ap)

#define _VA_LIST_DEFINED

#endif /* _STDARG_H */
