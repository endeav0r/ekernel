#ifndef kshell_HEADER
#define kshell_HEADER

#include "../aci/config.h"

void kshell_init ();
void kshell_keyboard_callback (word_t args[4]);
void kshell_execute (char * input);

#endif
