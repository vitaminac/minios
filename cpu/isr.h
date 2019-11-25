#ifndef ISR_H
#define ISR_H

#include "types.h"

/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Struct which aggregates many registers
// pushing and popping the stack always change 4-byte data to the stack
typedef struct
{
    // Data segment selector
    nat32 ds;
    // Pushed by pusha
    nat32 edi,
        esi,
        ebp,
        esp,
        ebx,
        edx,
        ecx,
        eax;
    // Interrupt number and error code (if applicable)
    nat32 int_no;
    nat32 err_code;
    // Pushed by the processor automatically
    nat32 eip,
        cs,
        eflags,
        useresp,
        ss;
} registers_t;

void isr_install();
void isr_handler(registers_t r);

/* To print the message which defines every exception */
static char *exception_messages[] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};

#endif