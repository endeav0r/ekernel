#include "../aci/stdlib/stdlib.h"

#define DEBUG_MESSAGES_N 4
#define DEBUG_MESSAGE_SIZE 32

char debug_messages[DEBUG_MESSAGES_N][DEBUG_MESSAGE_SIZE];
int debug_message_i = 0;

void debug_stack_trace (char * message)
{
    aci_strncpy(debug_messages[debug_message_i], message, DEBUG_MESSAGE_SIZE);
    debug_messages[debug_message_i][DEBUG_MESSAGE_SIZE - 1] = '\0';
    debug_message_i = (debug_message_i + 1) % DEBUG_MESSAGES_N;
}

void debug_vga_trace ()
{
    int i;

    aci_vga_write(debug_messages[debug_message_i]);
    aci_vga_write("\n");
    for (i = (debug_message_i + 1) % DEBUG_MESSAGES_N;
         i != debug_message_i;
         i = (i + 1) % DEBUG_MESSAGES_N) {
        aci_vga_write(debug_messages[i]);
        aci_vga_write("\n");
    }
}

void debug_panic(char * message)
{
    aci_vga_write("\n");
    if (message != NULL) {
        aci_vga_write(message);
        aci_vga_write("\n");
    }

    debug_vga_trace();
    while (1) {}
}
