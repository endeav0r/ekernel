#include "arch.h"
#include "common.h"
#include "gdt.h"
#include "idt.h"
#include "interrupt.h"

#include "../../aci.h"

int aci_arch_init ()
{
    aci_vga_write("x86 INIT ( GDT ");
    ax86_gdt_install();

    aci_vga_write("IDT ");
    ax86_idt_install();

    aci_vga_write("ISRS ");
    ax86_isrs_install();

    aci_vga_write("IRQ ");
    ax86_irq_remap();
    ax86_irq_install();

    aci_vga_write("INTERRUPTS_ON ");
    ax86_sti();

    aci_vga_write(") DONE\n");

    aci_vga_write("ACI x86 INIT ( INTERRUPTS ");
    aci_interrupt_init();

    aci_vga_write(") DONE\n");

    return 0;
}

void aci_vga_cursor (int x, int y)
{
    unsigned short position = (y * 80) + x;
    ax86_outportb(0x3d4, 0x0f);
    ax86_outportb(0x3d5, (unsigned char) (position & 0xff));
    ax86_outportb(0x3d4, 0x0e);
    ax86_outportb(0x3d5, (unsigned char) ((position >> 8) & 0xff));
}
