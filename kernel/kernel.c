#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "libc/string.h"
#include "cpu/isr.h"
#include "cpu/timer.h"

void main()
{
    char input[255];
    clear();
    // ou caller function is calling callee function
    // and ensure pass argument to callee function
    // eax register is used to hold a function’s return value:
    print_at("Welcome to my first OS\n", 28, 12);
    print_at("Type END to halt the CPU\n", 28, 13);

    isr_install();

    // set timer interrupt frequency and init appropriate timer handler
    init_timer(50);

    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    init_keyboard();

    while (true)
    {
        print("\n> ");
        scanf(input);
        if (strcmp(input, "END") == 0)
        {
            print("Stopping the CPU. Bye!\n");
            __asm__ __volatile__("hlt"); // TODO: close power
            return;
        }
        print("You said: ");
        print(input);
    }
}