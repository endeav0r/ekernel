#include "idt.h"
#include "irq.h"

extern void ax86_irq0  ();
extern void ax86_irq1  ();
extern void ax86_irq2  ();
extern void ax86_irq3  ();
extern void ax86_irq4  ();
extern void ax86_irq5  ();
extern void ax86_irq6  ();
extern void ax86_irq7  ();
extern void ax86_irq8  ();
extern void ax86_irq9  ();
extern void ax86_irq10 ();
extern void ax86_irq11 ();
extern void ax86_irq12 ();
extern void ax86_irq13 ();
extern void ax86_irq14 ();
extern void ax86_irq15 ();

void * ax86_irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void ax86_irq_install_handler (int irq, void (* handler) (struct ax86_irq_regs *))
{
    ax86_irq_routines[irq] = handler;
}

void ax86_irq_uninstall_handler (int irq)
{
    ax86_irq_routines[irq] = 0;
}


// thanks http://www.osdever.net/bkerndev/Docs/irqs.htm
/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void ax86_irq_remap()
{
    ax86_outportb(0x20, 0x11);
    ax86_outportb(0xA0, 0x11);
    ax86_outportb(0x21, 0x20);
    ax86_outportb(0xA1, 0x28);
    ax86_outportb(0x21, 0x04);
    ax86_outportb(0xA1, 0x02);
    ax86_outportb(0x21, 0x01);
    ax86_outportb(0xA1, 0x01);
    ax86_outportb(0x21, 0x0);
    ax86_outportb(0xA1, 0x0);
}

void ax86_irq_install ()
{
    ax86_irq_remap();

    ax86_idt_set_gate(32, (unsigned) ax86_irq0,  0x08, 0x8E);
    ax86_idt_set_gate(33, (unsigned) ax86_irq1,  0x08, 0x8E);
    ax86_idt_set_gate(34, (unsigned) ax86_irq2,  0x08, 0x8E);
    ax86_idt_set_gate(35, (unsigned) ax86_irq3,  0x08, 0x8E);
    ax86_idt_set_gate(36, (unsigned) ax86_irq4,  0x08, 0x8E);
    ax86_idt_set_gate(37, (unsigned) ax86_irq5,  0x08, 0x8E);
    ax86_idt_set_gate(38, (unsigned) ax86_irq6,  0x08, 0x8E);
    ax86_idt_set_gate(39, (unsigned) ax86_irq7,  0x08, 0x8E);
    ax86_idt_set_gate(40, (unsigned) ax86_irq8,  0x08, 0x8E);
    ax86_idt_set_gate(41, (unsigned) ax86_irq9,  0x08, 0x8E);
    ax86_idt_set_gate(42, (unsigned) ax86_irq10, 0x08, 0x8E);
    ax86_idt_set_gate(43, (unsigned) ax86_irq11, 0x08, 0x8E);
    ax86_idt_set_gate(44, (unsigned) ax86_irq12, 0x08, 0x8E);
    ax86_idt_set_gate(45, (unsigned) ax86_irq13, 0x08, 0x8E);
    ax86_idt_set_gate(46, (unsigned) ax86_irq14, 0x08, 0x8E);
    ax86_idt_set_gate(47, (unsigned) ax86_irq15, 0x08, 0x8E);
}

void ax86_irq_handler (struct ax86_irq_regs * regs)
{
    void (* handler) (struct ax86_irq_regs * regs);

    // do we have a custom handler
    handler = ax86_irq_routines[regs->int_no - 32];
    if (handler)
        handler(regs);

    // send EOI to resume interrupts
    if (regs->int_no >= 40)
        ax86_outportb(0xA0, 0x20);
    ax86_outportb(0x20, 0x20);
}
