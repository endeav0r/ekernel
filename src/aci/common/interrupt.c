#include "../aci.h"
#include "../config.h"

aci_callback aci_interrupt_callbacks[ACI_INT_NUM];

void aci_interrupt_init ()
{
    int i;
    for (i = 0; i < ACI_INT_NUM; i++)
        aci_interrupt_callbacks[i] = 0;
}

int aci_interrupt_register (aci_callback callback, int interrupt)
{
    if (interrupt >= ACI_INT_NUM)
        return -1;
    aci_interrupt_callbacks[interrupt] = callback;
    return aci_arch_interrupt_register(interrupt);
}

void aci_interrupt_handler (int interrupt, word_t args[4])
{
    char buf[16];

    aci_callback callback = aci_interrupt_callbacks[interrupt];
    if (callback == 0) {
        aci_sprintf(buf, "%d", interrupt);
        aci_vga_write("unhandled interrupt [");
        aci_vga_write(buf);
        aci_vga_write("]\n");
        aci_panic();
    }

    callback(args);
}
