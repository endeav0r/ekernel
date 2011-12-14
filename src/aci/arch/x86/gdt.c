#include "gdt.h"
#include "common.h"
#include "../../aci.h"

/*
* this code was shamelessly ripped (with minor modifications) from 
* http://www.osdever.net/bkerndev/Docs/gdt.htm
* to understand more about what's going on here, please visit the above link
*/

struct ax86_gdt_entry ax86_gdt[3];
struct ax86_gdt_ptr   ax86_gp;

/* Setup a descriptor in the Global Descriptor Table */
void ax86_gdt_set_gate (int num,
                        unsigned int base,
                        unsigned int limit,
                        unsigned char access, 
                        unsigned char granularity)
{
    /* Setup the descriptor base address */
    ax86_gdt[num].base_low    = (base & 0xFFFF);
    ax86_gdt[num].base_middle = (base >> 16) & 0xFF;
    ax86_gdt[num].base_high   = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    ax86_gdt[num].limit_low   = (limit & 0xFFFF);
    ax86_gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    ax86_gdt[num].granularity |= (granularity & 0xF0);
    ax86_gdt[num].access = access;
}

/* Should be called by arch_init. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void ax86_gdt_install()
{
    /* Setup the GDT pointer and limit */
    ax86_gp.limit = (sizeof(struct ax86_gdt_entry) * 3) - 1;
    ax86_gp.base = ax86_gdt;

    /* Our NULL descriptor */
    ax86_gdt_set_gate(0, 0, 0, 0, 0);
    
    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    ax86_gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    ax86_gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    /* Flush out the old GDT and install the new changes! */
    ax86_gdt_flush();
}
