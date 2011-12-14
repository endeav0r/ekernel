#include "aci/aci.h"
#include "aci/stdlib/stdlib.h"

#include "common/keyboard_us.h"

void keyboard_callback (int args[4])
{
    if ((args[0] & 0x80) == 0) {
        if (keyboard_us[args[0]] != 0)
            aci_vga_write_char(keyboard_us[args[0]]);
    }
}

void kmain ()
{
    aci_init();

    aci_interrupt_register(keyboard_callback, ACI_INT_KEYBOARD);
    
    aci_panic();
}
