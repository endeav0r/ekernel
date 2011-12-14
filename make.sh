mkdir o         2> /dev/null
mkdir o/aci     2> /dev/null
mkdir o/aci/x86 2> /dev/null

# make aci
tcc -c src/aci/aci.c              -o o/aci/aci.o
tcc -c src/aci/common/vga.c       -o o/aci/vga.o
tcc -c src/aci/common/interrupt.c -o o/aci/interrupt.o
tcc -c src/aci/stdlib/stdlib.c    -o o/aci/stdlib.o
tcc -c src/aci/stdlib/test.c      -o o/aci/test.o

# make aci/arch/x86
nasm    src/aci/arch/x86/gdt.s       -o o/aci/x86/gdt_asm.o  -f elf
nasm    src/aci/arch/x86/idt.s       -o o/aci/x86/idt_asm.o  -f elf
nasm    src/aci/arch/x86/irq.s       -o o/aci/x86/irq_asm.o  -f elf
nasm    src/aci/arch/x86/isr.s       -o o/aci/x86/isr_asm.o  -f elf
tcc  -c src/aci/arch/x86/arch.c      -o o/aci/x86/arch.o
tcc  -c src/aci/arch/x86/common.c    -o o/aci/x86/common.o
tcc  -c src/aci/arch/x86/gdt.c       -o o/aci/x86/gdt.o
tcc  -c src/aci/arch/x86/idt.c       -o o/aci/x86/idt.o
tcc  -c src/aci/arch/x86/interrupt.c -o o/aci/x86/interrupt.o
tcc  -c src/aci/arch/x86/irq.c       -o o/aci/x86/irq.o
tcc  -c src/aci/arch/x86/isr.c       -o o/aci/x86/isr.o

# make kernel
nasm    src/loader.s -o o/loader.o -f elf
tcc  -c src/kernel.c -o o/kernel.o

# link aci and kernel
ld -T src/linker.ld -o kernel.bin \
o/kernel.o o/loader.o \
o/aci/aci.o o/aci/vga.o o/aci/stdlib.o o/aci/test.o \
o/aci/interrupt.o \
o/aci/x86/arch.o o/aci/x86/common.o   \
o/aci/x86/gdt.o  o/aci/x86/gdt_asm.o  \
o/aci/x86/idt.o  o/aci/x86/idt_asm.o  \
o/aci/x86/interrupt.o \
o/aci/x86/irq.o  o/aci/x86/irq_asm.o  \
o/aci/x86/isr.o  o/aci/x86/isr_asm.o  \

