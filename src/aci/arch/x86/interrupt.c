#include "interrupt.h"
#include "isr.h"
#include "../../config.h"

int aci_arch_interrupt_set[ACI_INT_NUM];

void aci_arch_interrupt_init ()
{
    int i;
    for (i = 0; i < ACI_INT_NUM; i++)
        aci_arch_interrupt_set[i] = 0;
}

int aci_arch_interrupt_register (int interrupt)
{
    aci_arch_interrupt_set[interrupt] = 1;
    switch (interrupt) {
    case ACI_INT_KEYBOARD :
        ax86_irq_install_handler(1, aci_arch_interrupt_handler);
        break;
    case ACI_INT_PAGEFAULT :
        break; // isrs will check aci_arch_interrupt_set
    }
    return 0;
}

void aci_arch_interrupt_handler (struct ax86_irq_regs * regs)
{
    static int args[ACI_MAX_CPUS][4];
    switch (regs->int_no) {
    case 33 : // keyboard
        args[0][0] = ax86_inportb(0x60);
        aci_interrupt_handler(ACI_INT_KEYBOARD, args[0]);
        break;
    case AX86_ISR_PAGE_FAULT :
        asm volatile ("mov %%cr2, %0" : "=r" (args[0][0]));
        aci_interrupt_handler(ACI_INT_PAGEFAULT, args[0]);
        break;
    }   
}
