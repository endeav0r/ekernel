#ifndef common_HEADER
#define common_HEADER

unsigned char ax86_inportb (unsigned short port)
{
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void ax86_outportb (unsigned short port, unsigned char data)
{
    asm volatile ("outb %1, %0" :: "dN" (port), "a" (data));
}

void ax86_cli ()
{
    asm volatile ("cli");
}

void ax86_sti ()
{
    asm volatile ("sti");
}

#endif
