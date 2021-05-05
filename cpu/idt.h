#ifndef IDT_H
#define IDT_H

#include "def/types.h"
#include "libc/memory.h"

// Segment selectors
#define KERNEL_CS 0x08 // define in gdt.asm

/* How every interrupt gate (handler) is defined */
typedef struct
{
    nat16 low_offset; /* Lower 16 bits of handler function address */
    nat16 sel;        /* Kernel segment selector */
    nat8 always0;
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    nat8 flags;
    nat16 high_offset; /* Higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct
{
    nat16 limit;
    nat32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

/* Functions implemented in idt.c */
void set_idt_gate(int n, nat32 handler);
void set_idt();

#endif