#ifndef PIO_H
#define PIO_H
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

byte in_byte(nat16 port);
void out_byte(nat16 port, byte data);
b16 in_b16(nat16 port);
void out_b16(nat16 port, b16 data);
void io_wait();

#endif