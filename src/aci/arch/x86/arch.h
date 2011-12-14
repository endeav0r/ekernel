#ifndef arch_HEADER
#define arch_HEADER

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
