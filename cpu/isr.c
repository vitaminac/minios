
#include "isr.h"
#include "idt.h"
#include "drivers/screen.h"
#include "libc/string.h"
#include "libc/pio.h"

isr_handler_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install()
{
    set_idt_gate(0, (nat32)isr0);
    set_idt_gate(1, (nat32)isr1);
    set_idt_gate(2, (nat32)isr2);
    set_idt_gate(3, (nat32)isr3);
    set_idt_gate(4, (nat32)isr4);
    set_idt_gate(5, (nat32)isr5);
    set_idt_gate(6, (nat32)isr6);
    set_idt_gate(7, (nat32)isr7);
    set_idt_gate(8, (nat32)isr8);
    set_idt_gate(9, (nat32)isr9);
    set_idt_gate(10, (nat32)isr10);
    set_idt_gate(11, (nat32)isr11);
    set_idt_gate(12, (nat32)isr12);
    set_idt_gate(13, (nat32)isr13);
    set_idt_gate(14, (nat32)isr14);
    set_idt_gate(15, (nat32)isr15);
    set_idt_gate(16, (nat32)isr16);
    set_idt_gate(17, (nat32)isr17);
    set_idt_gate(18, (nat32)isr18);
    set_idt_gate(19, (nat32)isr19);
    set_idt_gate(20, (nat32)isr20);
    set_idt_gate(21, (nat32)isr21);
    set_idt_gate(22, (nat32)isr22);
    set_idt_gate(23, (nat32)isr23);
    set_idt_gate(24, (nat32)isr24);
    set_idt_gate(25, (nat32)isr25);
    set_idt_gate(26, (nat32)isr26);
    set_idt_gate(27, (nat32)isr27);
    set_idt_gate(28, (nat32)isr28);
    set_idt_gate(29, (nat32)isr29);
    set_idt_gate(30, (nat32)isr30);
    set_idt_gate(31, (nat32)isr31);

    pci_init();

    // Install the IRQs
    set_idt_gate(IRQ0, (nat32)irq0);
    set_idt_gate(IRQ1, (nat32)irq1);
    set_idt_gate(IRQ2, (nat32)irq2);
    set_idt_gate(IRQ3, (nat32)irq3);
    set_idt_gate(IRQ4, (nat32)irq4);
    set_idt_gate(IRQ5, (nat32)irq5);
    set_idt_gate(IRQ6, (nat32)irq6);
    set_idt_gate(IRQ7, (nat32)irq7);
    set_idt_gate(IRQ8, (nat32)irq8);
    set_idt_gate(IRQ9, (nat32)irq9);
    set_idt_gate(IRQ10, (nat32)irq10);
    set_idt_gate(IRQ11, (nat32)irq11);
    set_idt_gate(IRQ12, (nat32)irq12);
    set_idt_gate(IRQ13, (nat32)irq13);
    set_idt_gate(IRQ14, (nat32)irq14);
    set_idt_gate(IRQ15, (nat32)irq15);

    set_idt(); // Load with ASM
    /* Enable interruptions */
    __asm__ __volatile__("sti");
}

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

void isr_handler(registers_t r)
{
    print("received interrupt: ");
    char s[3];
    dec2str(r.int_no, s);
    print(s);
    print("\n");
    print(exception_messages[r.int_no]);
    print("\n");
}

void register_interrupt_handler(nat8 n, isr_handler_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40)
        out_byte(0xA0, 0x20); /* slave */
    out_byte(0x20, 0x20);     /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0)
    {
        isr_handler_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}