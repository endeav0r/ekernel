#include "aci.h"
#include "config.h"
#include "stdlib/stdlib.h"

aci_t aci;

aci_t * aci_init ()
{
    aci_vga_clear();
    aci_vga_write("ACI INIT\n");

    aci_arch_init();

    aci_stdlib_test();

    return &aci;
}

void aci_panic ()
{
    while (1) {}
}
