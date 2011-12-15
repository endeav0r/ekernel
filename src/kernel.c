#include "aci/aci.h"
#include "aci/stdlib/stdlib.h"

#include "filesystem/filesystem.h"
#include "kshell/kshell.h"

#include "common/keyboard_us.h"

void keyboard_callback (word_t args[4])
{
    if ((args[0] & 0x80) == 0) {
        if (keyboard_us[args[0]] != 0)
            aci_vga_write_char(keyboard_us[args[0]]);
    }
}

void kmain ()
{
    aci_init();

    aci_vga_write("filesystem init\n");
    filesystem_init();

    aci_vga_write("launching kshell");
    kshell_init();

    aci_panic();
}
