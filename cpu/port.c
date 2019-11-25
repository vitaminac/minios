#include "port.h"

nat8 port_byte_in(nat16 port)
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