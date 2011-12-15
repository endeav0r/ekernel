#ifndef debug_HEADER
#define debug_HEADER

#define DEBUG_STACK_TRACE(x) debug_stack_trace(x);

void debug_stack_trace (char * function_name);
void debug_vga_trace   ();
void debug_panic       (char * message);

#endif
