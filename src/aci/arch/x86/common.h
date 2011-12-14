#ifndef aci_x86_common_HEADER
#define aci_x86_common_HEADER

unsigned char ax86_inportb  (unsigned short port);
void          ax86_outportb (unsigned short port, unsigned char data);
void          ax86_cli ();
void          ax86_sti ();

#endif
