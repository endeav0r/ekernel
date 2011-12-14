#include "idt.h"
#include "../../stdlib/stdlib.h"

#include "../../aci.h"

struct ax86_idt_entry ax86_idt[256];
struct ax86_idt_ptr   ax86_idtp;

void ax86_idt_set_gate (unsigned char  num,
                        unsigned int   base, 
                        unsigned short sel, 
                        unsigned char  flags)
{
    ax86_idt[num].base_lo = (base & 0xFFFF);
    ax86_idt[num].base_hi = (base >> 16) & 0xFFFF;
    ax86_idt[num].sel     = sel;
    ax86_idt[num].flags   = flags;
}

void ax86_idt_install ()
{
    ax86_idtp.limit = (sizeof(struct ax86_idt_entry) * 256) - 1;
    ax86_idtp.base  = ax86_idt;

    aci_memset(&ax86_idt, 0, sizeof(struct ax86_idt_entry) * 256);

    ax86_idt_load ();
}
