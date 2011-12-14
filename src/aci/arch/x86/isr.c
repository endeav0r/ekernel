#include "idt.h"
#include "interrupt.h"
#include "isr.h"
#include "../../aci.h"
#include "../../stdlib/stdlib.h"

extern void ax86_isr0  ();
extern void ax86_isr1  ();
extern void ax86_isr2  ();
extern void ax86_isr3  ();
extern void ax86_isr4  ();
extern void ax86_isr5  ();
extern void ax86_isr6  ();
extern void ax86_isr7  ();
extern void ax86_isr8  ();
extern void ax86_isr9  ();
extern void ax86_isr10 ();
extern void ax86_isr11 ();
extern void ax86_isr12 ();
extern void ax86_isr13 ();
extern void ax86_isr14 ();
extern void ax86_isr15 ();
extern void ax86_isr16 ();
extern void ax86_isr17 ();
extern void ax86_isr18 ();
extern void ax86_isr19 ();
extern void ax86_isr20 ();
extern void ax86_isr21 ();
extern void ax86_isr22 ();
extern void ax86_isr23 ();
extern void ax86_isr24 ();
extern void ax86_isr25 ();
extern void ax86_isr26 ();
extern void ax86_isr27 ();
extern void ax86_isr28 ();
extern void ax86_isr29 ();
extern void ax86_isr30 ();
extern void ax86_isr31 ();

void ax86_isrs_install ()
{
    ax86_idt_set_gate(0,  (unsigned) ax86_isr0,  0x08, 0x8E);
    ax86_idt_set_gate(1,  (unsigned) ax86_isr1,  0x08, 0x8E);
    ax86_idt_set_gate(2,  (unsigned) ax86_isr2,  0x08, 0x8E);
    ax86_idt_set_gate(3,  (unsigned) ax86_isr3,  0x08, 0x8E);
    ax86_idt_set_gate(4,  (unsigned) ax86_isr4,  0x08, 0x8E);
    ax86_idt_set_gate(5,  (unsigned) ax86_isr5,  0x08, 0x8E);
    ax86_idt_set_gate(6,  (unsigned) ax86_isr6,  0x08, 0x8E);
    ax86_idt_set_gate(7,  (unsigned) ax86_isr7,  0x08, 0x8E);
    ax86_idt_set_gate(8,  (unsigned) ax86_isr8,  0x08, 0x8E);
    ax86_idt_set_gate(9,  (unsigned) ax86_isr9,  0x08, 0x8E);
    ax86_idt_set_gate(10, (unsigned) ax86_isr10, 0x08, 0x8E);
    ax86_idt_set_gate(11, (unsigned) ax86_isr11, 0x08, 0x8E);
    ax86_idt_set_gate(12, (unsigned) ax86_isr12, 0x08, 0x8E);
    ax86_idt_set_gate(13, (unsigned) ax86_isr13, 0x08, 0x8E);
    ax86_idt_set_gate(14, (unsigned) ax86_isr14, 0x08, 0x8E);
    ax86_idt_set_gate(15, (unsigned) ax86_isr15, 0x08, 0x8E);
    ax86_idt_set_gate(16, (unsigned) ax86_isr16, 0x08, 0x8E);
    ax86_idt_set_gate(17, (unsigned) ax86_isr17, 0x08, 0x8E);
    ax86_idt_set_gate(18, (unsigned) ax86_isr18, 0x08, 0x8E);
    ax86_idt_set_gate(19, (unsigned) ax86_isr19, 0x08, 0x8E);
    ax86_idt_set_gate(20, (unsigned) ax86_isr20, 0x08, 0x8E);
    ax86_idt_set_gate(21, (unsigned) ax86_isr21, 0x08, 0x8E);
    ax86_idt_set_gate(22, (unsigned) ax86_isr22, 0x08, 0x8E);
    ax86_idt_set_gate(23, (unsigned) ax86_isr23, 0x08, 0x8E);
    ax86_idt_set_gate(24, (unsigned) ax86_isr24, 0x08, 0x8E);
    ax86_idt_set_gate(25, (unsigned) ax86_isr25, 0x08, 0x8E);
    ax86_idt_set_gate(26, (unsigned) ax86_isr26, 0x08, 0x8E);
    ax86_idt_set_gate(27, (unsigned) ax86_isr27, 0x08, 0x8E);
    ax86_idt_set_gate(28, (unsigned) ax86_isr28, 0x08, 0x8E);
    ax86_idt_set_gate(29, (unsigned) ax86_isr29, 0x08, 0x8E);
    ax86_idt_set_gate(30, (unsigned) ax86_isr30, 0x08, 0x8E);
    ax86_idt_set_gate(31, (unsigned) ax86_isr31, 0x08, 0x8E);
}

void ax86_fault_handler (struct ax86_isr_regs * regs)
{
    char buf[64];

    if (    (regs->int_no == AX86_ISR_PAGE_FAULT)
         && (aci_arch_interrupt_set[ACI_INT_PAGEFAULT]))
        // we can do this because ax86_isr_regs and ax86_irq_regs are identical
        aci_arch_interrupt_handler((struct ax86_irq_regs *) regs);
    else if (regs->int_no < 32)
    {
        aci_sprintf(buf, "x86 unhandled interrupt %x\n", regs->int_no);
        aci_vga_write(buf);
        aci_panic();
    }
}
