#ifndef aci_x86_isr_HEADER
#define aci_x86_isr_HEADER

#define AX86_ISR_DIV_BY_ZERO     0
#define AX86_ISR_DEBUG           1
#define AX86_ISR_NON_MASKABLE    2
#define AX86_ISR_BREAKPOINT      3
#define AX86_ISR_INTO_DET_OFLOW  4
#define AX86_ISR_OUT_OF_BOUNDS   5
#define AX86_ISR_INVALID_OPCODE  6
#define AX86_ISR_NO_COPROCESSOR  7
#define AX86_ISR_DOUBLE_FAULT    8
#define AX86_ISR_CO_SEG_OVERRUN  9
#define AX86_ISR_BAD_TSS         10
#define AX86_ISR_SEG_NOT_PRESENT 11
#define AX86_ISR_STACK_FAULT     12
#define AX86_ISR_GEN_PROT_FAULT  13
#define AX86_ISR_PAGE_FAULT      14
#define AX86_ISR_UKWN_INTERRUPT  15
#define AX86_ISR_COPROC_FAULT    16
#define AX86_ISR_ALIGNMENT_CHECK 17
#define AX86_ISR_MACHINE_CHECK   18

struct ax86_isr_regs {
    unsigned int gs,  fs,  es,  ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no,   err_code;
    unsigned int eip, cs,  eflags,   useresp,  ss;
};

void ax86_isrs_install  ();
void ax86_fault_handler (struct ax86_isr_regs * regs);

#endif
