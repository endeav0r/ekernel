global ax86_idt_load
extern ax86_idtp
ax86_idt_load :
    lidt [ax86_idtp]
    ret
