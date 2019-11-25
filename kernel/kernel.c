#include "drivers/screen.h"
#include "libc/string.h"
#include "cpu/isr.h"

void main()
{
    clear();
    // ou caller function is calling callee function
    // and ensure pass argument to callee function
    // eax register is used to hold a function’s return value:
    print_at("Welcome to my first OS\n", 28, 12);
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}