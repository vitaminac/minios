#ifndef ISR_H
#define ISR_H

#include "def/types.h"
#include "drivers/pic.h"

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

// https://en.wikipedia.org/wiki/Interrupt_request_(PC_architecture)
// Interrupt request
// Master PIC
// IRQ 0 – system timer
#define IRQ0 32
extern void irq0();
// IRQ 1 – keyboard controller
#define IRQ1 33
extern void irq1();
// IRQ 2 – cascaded signals from IRQs 8–15
#define IRQ2 34
extern void irq2();
// IRQ 3 – serial port controller for serial port 2
#define IRQ3 35
extern void irq3();
// IRQ 4 – serial port controller for serial port 1
#define IRQ4 36
extern void irq4();
// IRQ 5 – parallel port 2 and 3  or  sound card
#define IRQ5 37
extern void irq5();
// IRQ 6 – floppy disk controller
#define IRQ6 38
extern void irq6();
// IRQ 7 – parallel port 1. 
// It is used for printers or for any parallel port if a printer is not present. 
// It can also be potentially be shared 
// with a secondary sound card with careful management of the port.
#define IRQ7 39
extern void irq7();
// IRQ 8 – real-time clock (RTC)
#define IRQ8 40
extern void irq8();
// IRQ 9 – Advanced Configuration and Power Interface (ACPI) system control interrupt on Intel chipsets.
// Other chipset manufacturers might use another interrupt for this purpose, 
// or make it available for the use of peripherals 
// (any devices configured to use IRQ 2 will actually be using IRQ 9)
#define IRQ9 41
extern void irq9();
// IRQ 10 – The Interrupt is left open for the use of peripherals
#define IRQ10 42
extern void irq10();
// IRQ 11 – The Interrupt is left open for the use of peripherals
#define IRQ11 43
extern void irq11();
// IRQ 12 – mouse on PS/2 connector
#define IRQ12 44
extern void irq12();
// IRQ 13 – CPU co-processor  or  integrated floating point unit  or  inter-processor interrupt
#define IRQ13 45
extern void irq13();
// IRQ 14 – primary ATA channel (ATA interface usually serves hard disk drives and CD drives)
#define IRQ14 46
extern void irq14();
// IRQ 15 – secondary ATA channel
#define IRQ15 47
extern void irq15();

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
typedef void (*isr_handler_t)(registers_t);
void register_interrupt_handler(nat8 n, isr_handler_t handler);

#endif