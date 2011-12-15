#include "aci.h"
#include "config.h"
#include "stdlib/stdlib.h"
#include "common/debug.h"

void aci_init ()
{
    aci_vga_clear();
    aci_vga_write("ACI INIT\n");

    aci_arch_init();

    aci_stdlib_test();

    aci_debug();
}

void aci_panic ()
{
    while (1) {}
}
