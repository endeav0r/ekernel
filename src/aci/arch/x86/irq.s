global ax86_irq0
global ax86_irq1
global ax86_irq2
global ax86_irq3
global ax86_irq4
global ax86_irq5
global ax86_irq6
global ax86_irq7
global ax86_irq8
global ax86_irq9
global ax86_irq10
global ax86_irq11
global ax86_irq12
global ax86_irq13
global ax86_irq14
global ax86_irq15

; 32: IRQ0
ax86_irq0 :
    cli
    push byte 0
    push byte 32
    jmp ax86_irq_common_stub

ax86_irq1 :
    cli
    push byte 0
    push byte 33
    jmp ax86_irq_common_stub

ax86_irq2 :
    cli
    push byte 0
    push byte 34
    jmp ax86_irq_common_stub

ax86_irq3 :
    cli
    push byte 0
    push byte 35
    jmp ax86_irq_common_stub

ax86_irq4 :
    cli
    push byte 0
    push byte 36
    jmp ax86_irq_common_stub

ax86_irq5 :
    cli
    push byte 0
    push byte 37
    jmp ax86_irq_common_stub

ax86_irq6 :
    cli
    push byte 0
    push byte 38
    jmp ax86_irq_common_stub

ax86_irq7 :
    cli
    push byte 0
    push byte 39
    jmp ax86_irq_common_stub

ax86_irq8 :
    cli
    push byte 0
    push byte 40
    jmp ax86_irq_common_stub

ax86_irq9 :
    cli
    push byte 0
    push byte 41
    jmp ax86_irq_common_stub

ax86_irq10 :
    cli
    push byte 0
    push byte 42
    jmp ax86_irq_common_stub

ax86_irq11 :
    cli
    push byte 0
    push byte 43
    jmp ax86_irq_common_stub

ax86_irq12 :
    cli
    push byte 0
    push byte 44
    jmp ax86_irq_common_stub

ax86_irq13 :
    cli
    push byte 0
    push byte 45
    jmp ax86_irq_common_stub

ax86_irq14 :
    cli
    push byte 0
    push byte 46
    jmp ax86_irq_common_stub

ax86_irq15 :
    cli
    push byte 0
    push byte 47
    jmp ax86_irq_common_stub

extern ax86_irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
ax86_irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, ax86_irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
