
#include "isr.h"
#include "idt.h"
#include "drivers/screen.h"
#include "libc/string.h"

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

    set_idt(); // Load with ASM
}

void isr_handler(registers_t r)
{
    print("received interrupt: ");
    char s[3];
    str(r.int_no, 10, s);
    print(s);
    print("\n");
    print(exception_messages[r.int_no]);
    print("\n");
}