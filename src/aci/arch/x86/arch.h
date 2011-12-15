#ifndef arch_HEADER
#define arch_HEADER

typedef unsigned int word_t;

#define ACI_HEAP_BEGIN 0x400000 /* 4mb */
#define ACI_HEAP_SIZE  0x800000 /* 8mb */

/** performs all architecture initialization calls
* @return 0 on success, 1 otherwise
*/
int aci_arch_init ();

/** sets the vga cursor
* @param x horizontal position for cursor (0-79)
* @param y vertical position for curosr (0-24)
*/
void aci_vga_cursor (int x, int y);

#endif
