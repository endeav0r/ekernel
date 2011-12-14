#ifndef aci_x86_interrupt_HEADER
#define aci_x86_interrupt_HEADER

#include "irq.h"
#include "../../aci.h"

/*
* This file contains the aci platform-independent interface code for
* x86 interrupts
*/

extern int aci_arch_interrupt_set[ACI_INT_NUM];

int aci_arch_interrupt_register (int interrupt);

void aci_arch_interrupt_handler (struct ax86_irq_regs * regs);

void aci_arch_interrupt_init ();

#endif
