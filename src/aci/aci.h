#ifndef aci_HEADER
#define aci_HEADER

#define ACI_INT_KEYBOARD  0
#define ACI_INT_PAGEFAULT 1
#define ACI_INT_NUM       2

typedef void (* aci_callback) (int args[4]);

typedef struct _aci_t {
} aci_t;



/**********************
* ACI FUNCTIONS       *
**********************/
aci_t * aci_init           ();
void    aci_panic          ();

// these functions are used internally by aci
// you do not need to worry about them
void    aci_interrupt_handler (int interrupt, int args[4]);
void    aci_interrupt_init    ();


/**********************
* INTERRUPT FUNCTIONS *
**********************/

/** Registers a callback to an interrupt
* When the CPU fires the corresponding interrupt, the given callback function
* will be called.
* @param callback the callback function to be called
* @param args up to four arguments will be passed on this interrupt. not all
              arguments are useful depending on the interrupt type.
* @return 0 on success, -1 on failure
*/
int aci_interrupt_register (aci_callback callback, int interrupt);



/**********************
* VGA FUNCTIONS       *
**********************/

/** Scrolls the screen down one line */
void aci_vga_scroll ();

/** Writes a character to the screen
* Automatically scrolls the screen down one line if needed. Handles newlines.
* @param c the character to write
*/
void aci_vga_write_char (unsigned char c);

/** Writes a null-terminated string to the screen
* Automatically scrolls the screen as needed. Handles newlines.
* @param string the null-terminated string to write
*/
void aci_vga_write (unsigned char * string);

/** Clears the screen
* Resets the cursor to the beginning.
*/
void aci_vga_clear ();

#endif
