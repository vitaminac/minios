#include "port.h"

byte port_byte_in(nat16 port)
{
    // A handy C wrapper function that reads a byte from the specified port
    // "=a" ( result ) means : put AL register in variable RESULT when finished
    // "d" ( port ) means : load EDX with port
    nat8 result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (nat16 port, nat8 data) {
    // "a" ( data ) means : load EAX with data
    // "d" ( port ) means : load EDX with port
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}

nat16 port_word_in (nat16 port) {
    nat16 result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (nat16 port, nat16 data) {
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

// https://wiki.osdev.org/Inline_Assembly/Examples#IO_WAIT
// use another I/O cycle on an 'unused' port
void io_wait()
{
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    __asm__ __volatile__( "outb %%al, $0x80" : : "a"(0));
}