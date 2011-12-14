; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!
global ax86_isr0
global ax86_isr1
global ax86_isr2
global ax86_isr3
global ax86_isr4
global ax86_isr5
global ax86_isr6
global ax86_isr7
global ax86_isr8
global ax86_isr9
global ax86_isr10
global ax86_isr11
global ax86_isr12
global ax86_isr13
global ax86_isr14
global ax86_isr15
global ax86_isr16
global ax86_isr17
global ax86_isr18
global ax86_isr19
global ax86_isr20
global ax86_isr21
global ax86_isr22
global ax86_isr23
global ax86_isr24
global ax86_isr25
global ax86_isr26
global ax86_isr27
global ax86_isr28
global ax86_isr29
global ax86_isr30
global ax86_isr31


ax86_isr0 :
    cli
    push byte 0
    push byte 0
    jmp ax86_isr_common_stub

ax86_isr1 :
    cli
    push byte 0
    push byte 1
    jmp ax86_isr_common_stub

ax86_isr2 :
    cli
    push byte 0
    push byte 2
    jmp ax86_isr_common_stub

ax86_isr3 :
    cli
    push byte 0
    push byte 3
    jmp ax86_isr_common_stub

ax86_isr4 :
    cli
    push byte 0
    push byte 4
    jmp ax86_isr_common_stub

ax86_isr5 :
    cli
    push byte 0
    push byte 5
    jmp ax86_isr_common_stub

ax86_isr6 :
    cli
    push byte 0
    push byte 6
    jmp ax86_isr_common_stub

ax86_isr7 :
    cli
    push byte 0
    push byte 7
    jmp ax86_isr_common_stub

ax86_isr8 :
    cli
    push byte 8
    jmp ax86_isr_common_stub

ax86_isr9 :
    cli
    push byte 0
    push byte 9
    jmp ax86_isr_common_stub

ax86_isr10 :
    cli
    push byte 10
    jmp ax86_isr_common_stub

ax86_isr11 :
    cli
    push byte 11
    jmp ax86_isr_common_stub

ax86_isr12 :
    cli
    push byte 12
    jmp ax86_isr_common_stub

ax86_isr13 :
    cli
    push byte 13
    jmp ax86_isr_common_stub

ax86_isr14 :
    cli
    push byte 14
    jmp ax86_isr_common_stub

ax86_isr15 :
    cli
    push byte 0
    push byte 15
    jmp ax86_isr_common_stub

ax86_isr16 :
    cli
    push byte 0
    push byte 16
    jmp ax86_isr_common_stub

ax86_isr17 :
    cli
    push byte 0
    push byte 17
    jmp ax86_isr_common_stub

ax86_isr18 :
    cli
    push byte 0
    push byte 18
    jmp ax86_isr_common_stub

ax86_isr19 :
    cli
    push byte 0
    push byte 19
    jmp ax86_isr_common_stub

ax86_isr20 :
    cli
    push byte 0
    push byte 20
    jmp ax86_isr_common_stub

ax86_isr21 :
    cli
    push byte 0
    push byte 21
    jmp ax86_isr_common_stub

ax86_isr22 :
    cli
    push byte 0
    push byte 22
    jmp ax86_isr_common_stub

ax86_isr23 :
    cli
    push byte 0
    push byte 23
    jmp ax86_isr_common_stub

ax86_isr24 :
    cli
    push byte 0
    push byte 24
    jmp ax86_isr_common_stub

ax86_isr25 :
    cli
    push byte 0
    push byte 25
    jmp ax86_isr_common_stub

ax86_isr26 :
    cli
    push byte 0
    push byte 26
    jmp ax86_isr_common_stub

ax86_isr27 :
    cli
    push byte 0
    push byte 27
    jmp ax86_isr_common_stub

ax86_isr28 :
    cli
    push byte 0
    push byte 28
    jmp ax86_isr_common_stub

ax86_isr29 :
    cli
    push byte 0
    push byte 29
    jmp ax86_isr_common_stub

ax86_isr30 :
    cli
    push byte 0
    push byte 30
    jmp ax86_isr_common_stub

ax86_isr31 :
    cli
    push byte 0
    push byte 31
    jmp ax86_isr_common_stub
    
; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file
extern ax86_fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
ax86_isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, ax86_fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
