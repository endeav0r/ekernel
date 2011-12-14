#ifndef aci_config_HEADER
#define aci_config_HEADER

/*
* set your architecture here
* 1 = x86
*/
#define ACI_ARCH 1

/*
* this needs to be set to the maximum number of CPUs this kernel will support.
* more CPUs implies more memory. this is currently unused and untested. leave
* it at 1 for now.
*/
#define ACI_MAX_CPUS 1

/*
* set colors for writing to the monitor here
* 0x0 BLACK      0x1 BLUE          0x2 GREEN
* 0x3 CYAN       0x4 RED           0x5 MAGENTA
* 0x6 BROWN      0x7 LIGHT GRAY    0x8 DARK GRAY
* 0x9 LIGHT BLUE 0xA LIGHT GREEN   0xB LIGHT CYAN
* 0xC LIGHT RED  0xD LIGHT MAGENTA 0xE LIGHT BROWN
* 0xF WHITE
*/
#define ACI_VGA_FOREGROUND 0x2
#define ACI_VGA_BACKGROUND 0x0
#define ACI_VGA_COLOR ((ACI_VGA_BACKGROUND << 4) | ACI_VGA_FOREGROUND)

#if ACI_ARCH == 1
    #include "arch/x86/arch.h"
#endif

#endif
