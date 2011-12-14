#ifndef aci_x86_gdt_HEADER
#define aci_x86_gdt_HEADER

struct ax86_gdt_entry
{
    __attribute__((__packed__)) unsigned short limit_low;
    __attribute__((__packed__)) unsigned short base_low;
    __attribute__((__packed__)) unsigned char  base_middle;
    __attribute__((__packed__)) unsigned char  access;
    __attribute__((__packed__)) unsigned char  granularity;
    __attribute__((__packed__)) unsigned char  base_high;
} __attribute__((packed));

struct ax86_gdt_ptr
{
    __attribute__((__packed__)) unsigned short limit;
    __attribute__((__packed__)) struct ax86_gdt_entry * base;
} __attribute__((__packed__));

extern void ax86_gdt_flush (); // in gdt.s

void ax86_gdt_set_gate (int num,
                   unsigned int base, 
                   unsigned int limit, 
                   unsigned char access, 
                   unsigned char granularity);

void ax86_gdt_install ();

#endif
