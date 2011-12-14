#ifndef idt_HEADER
#define idt_HEADER

// http://www.osdever.net/bkerndev/Docs/idt.htm
struct ax86_idt_entry {
    __attribute__((__packed__)) unsigned short base_lo;
    __attribute__((__packed__)) unsigned short sel;
    __attribute__((__packed__)) unsigned char  always0;
    __attribute__((__packed__)) unsigned char  flags;
    __attribute__((__packed__)) unsigned short base_hi;
} __attribute__((__packed__));

struct ax86_idt_ptr {
    __attribute__((__packed__)) unsigned short limit;
    __attribute__((__packed__)) struct ax86_idt_entry * base;
} __attribute__((packed));

extern void ax86_idt_load (); // in idt.s

void ax86_idt_set_gate (unsigned char  num,
                        unsigned int   base,
                        unsigned short sel,
                        unsigned char  flags);
void ax86_idt_install  ();

#endif
