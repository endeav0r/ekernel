#include "kshell.h"
#include "../aci/aci.h"
#include "../aci/stdlib/stdlib.h"
#include "../common/keyboard_us.h"
#include "../filesystem/filesystem.h"

static char command_buf[64];
static int  command_buf_i = 0;

void kshell_init ()
{
    aci_interrupt_register(kshell_keyboard_callback, ACI_INT_KEYBOARD);
    aci_vga_write("\n> ");
}

// we control the keyboard now
void kshell_keyboard_callback (word_t args[4])
{
    if ((args[0] & 0x80) == 0) {
        if (keyboard_us[args[0]] != 0) {
            aci_vga_write_char(keyboard_us[args[0]]);
            if (keyboard_us[args[0]] == '\n') {
                command_buf[command_buf_i] = '\0';
                kshell_execute(command_buf);
                aci_vga_write("\n> ");
                command_buf_i = 0;
            }
            else
                command_buf[command_buf_i++] = keyboard_us[args[0]];
        }
    }
}

void kshell_execute (char * input) {
    char * filename;
    char buf[64];
    int fd, error;

    if (aci_strncmp(input, "ls", 2) == 0) {
        aci_vga_write("ls\n");
        fd = fs_opendir("/");
        if (fd < 0)
            aci_vga_write("error opening path");
        else {
            while ((filename = fs_readdir(fd)) != NULL) {
                aci_vga_write("file: ");
                aci_vga_write(filename);
                aci_vga_write("\n");
            }
            fs_closedir(fd);
        }
    }
    else if (aci_strncmp(input, "mkdir", 5)) {
        error = fs_mkdir(&(input[6]));
        if (error)
            aci_vga_write("error creating file\n");
    }
}
