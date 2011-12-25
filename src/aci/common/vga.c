#include "../config.h"

/*
* aci_vga writes to memory provided to us by the BIOS
*
* In order to update the cursor, we must communicate directly with the VGA
* device. We must do this in an architecture dependent way. Therefor,
* aci_vga_cursor is written architecture specific. You can use it here.
* It's definition is:
*
* ** sets the vga cursor
* * @param x horizontal position for cursor, (0-79)
* * @param y vertical position for cursor, (0-24)
* 
* void aci_vga_cursor (int x, int y);
*/

int aci_vga_cursor_x = 0;
int aci_vga_cursor_y = 0;
unsigned char * aci_vga_videoram = (unsigned char *) 0xb8000;

void aci_vga_scroll ()
{
    int x, y;
    for (y = 0; y < 24; y++) {
        for (x = 0; x < 80; x++)
            aci_vga_videoram[y * 160 + x * 2] = aci_vga_videoram[(y+1) * 160 + x * 2];
    }
    for (x = 0; x < 80; x++) {
        aci_vga_videoram[(24 * 160) + x * 2] = ' ';
    }
}

void aci_vga_write_char (unsigned char c)
{
    int loc;

    if (c == '\n') {
        aci_vga_cursor_y++;
        aci_vga_cursor_x = 0;
    }
    else {
        loc = aci_vga_cursor_x * 2 + aci_vga_cursor_y * 160;
        aci_vga_videoram[loc] = c;
        aci_vga_videoram[loc + 1] = ACI_VGA_COLOR;
        aci_vga_cursor_x++;
        if (aci_vga_cursor_x >= 80) {
            aci_vga_cursor_x = 0;
            aci_vga_cursor_y++;
        }
    }

    while (aci_vga_cursor_y >= 25) {
        aci_vga_scroll();
        aci_vga_cursor_y--;
    }
    aci_vga_cursor(aci_vga_cursor_x, aci_vga_cursor_y);
}

void aci_vga_write (unsigned char * string)
{
    unsigned char * c;
    for (c = string; *c != '\0'; c++) 
        aci_vga_write_char(*c);
}

void aci_vga_clear ()
{
    int i;
    for (i = 0; i < 80 * 25; i++) {
        aci_vga_videoram[i * 2 + 1] = ACI_VGA_COLOR;
        aci_vga_videoram[i * 2] = ' ';
    }
    aci_vga_cursor_x = 0;
    aci_vga_cursor_y = 0;
    aci_vga_cursor(0,0);
}
