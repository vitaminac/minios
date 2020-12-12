#ifndef PORT_H
#define PORT_H

#include "libc/types.h"

/*
Internally, controller chips usually have several registers 
that can be read, written or both by the CPU,
and it is the state of these registers that tell the controller what to do

In Intel architecture systems 
the registers of device controllers 
are mapped into an I/O address space, 
that is seperate from the main memory address space, 
then varients of the I/O instructions in and out 
are used to read and write data to the I/O addresses 
that are mapped to specific controller registers.
*/

byte port_byte_in(nat16 port);
void port_byte_out (nat16 port, nat8 data);
nat16 port_word_in (nat16 port);
void port_word_out (nat16 port, nat16 data);
void io_wait();

#endif