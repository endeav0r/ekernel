#ifndef aci_x86_irq_HEADER
#define aci_x86_irq_HEADER

struct ax86_irq_regs {
    unsigned int gs,  fs,  es,  ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no,   err_code;
    unsigned int eip, cs,  eflags,   useresp,  ss;
};

void ax86_irq_install_handler (int irq, void (* handler) (struct ax86_irq_regs *));

void ax86_irq_uninstall_handler (int irq);

void ax86_irq_remap ();

void ax86_irq_install ();

void ax86_irq_handler (struct ax86_irq_regs * regs);

#endif
