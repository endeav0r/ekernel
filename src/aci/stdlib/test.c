#include "stdlib.h"

void aci_stdlib_testfail (const char * msg)
{
    aci_vga_write("\ntest fail: ");
    aci_vga_write(msg);
    aci_panic();
}

void aci_stdlib_test ()
{
    int i;
    void * ptrs[100];
    unsigned char buf [64];

    aci_vga_write("aci stdlib tests ");

    if (aci_strcmp("hamburgers", "hamburgers") != 0)
        aci_stdlib_testfail("aci_strcmp 1");
    aci_vga_write(".");

    if (aci_strcmp("a", "b") >= 0)
        aci_stdlib_testfail("aci_strcmp 2");
    aci_vga_write(".");

    aci_strcpy(buf, "cheeseburgers");
    if (aci_strcmp(buf, "cheeseburgers") != 0)
        aci_stdlib_testfail("aci_strcpy");
    aci_vga_write(".");

    aci_sprintf(buf, "%x %s", 0xF00D, "is good");
    if (aci_strcmp(buf, "F00D is good") != 0)
        aci_stdlib_testfail("aci_sprintf");
    aci_vga_write(".");

    if (aci_strlen("0123456789") != 10)
        aci_stdlib_testfail("aci_strlen");
    aci_vga_write(".");


    buf[17] = 0x66;
    aci_memset(buf, 0x77, 17);
    for (i = 0; i < 17; i++) {
        if (buf[i] != 0x77)
            aci_stdlib_testfail("aci_memset 1");
    }
    aci_vga_write(".");
    if (buf[17] != 0x66)
        aci_stdlib_testfail("aci_memset 2");
    aci_vga_write(".");

    aci_memset(buf, 0x77, 10);
    aci_memcpy(buf, "test", 5);
    if (aci_strcmp(buf, "test") != 0)
        aci_stdlib_testfail("aci_memcpy1");
    aci_vga_write(".");
    if (buf[6] != 0x77)
        aci_stdlib_testfail("aci_memcpy 2");
    aci_vga_write(".");

    aci_vga_write(" pass\n");

    aci_vga_write("malloc tests (only prints fails): ");

    for (i = 0; i < 10; i++)
        ptrs[i] = aci_malloc(i);

    for (i = 0; i < 10; i++) {
        if (aci_free(ptrs[i])) {
            aci_sprintf(buf, "malloc fail on %x\n", i);
            aci_vga_write(buf);
        }
    }

    aci_vga_write("done\n");
}
