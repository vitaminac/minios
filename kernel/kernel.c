#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "libc/string.h"
#include "def/status.h"
#include "cpu/isr.h"
#include "cpu/timer.h"
#include "drivers/cmos.h"
#include "hal/i386/acpi.h"

void kmain()
{
    byte input[255];
    byte buffer[255];
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

    if (acpi_init() != SUCCESS)
    {
        print("Failed to initialized ACPI\n");
    }

    while (true)
    {
        print(">");
        scanf(input);
        if (strcmp(input, "POWEROFF") == 0)
        {
            print("Turning off the power. \n");
            acpi_power_off();
            print("Failed on turning off the power. \n");
            return;
        }
        else if (strcmp(input, "NOW") == 0)
        {
            str_dec(getRTCYear(), buffer);
            print(buffer);
            print(" ");
            str_dec(getRTCMonth(), buffer);
            print(buffer);
            print(" ");
            str_dec(getRTCDayOfMonth(), buffer);
            print(buffer);
            print(" W");
            str_dec(getRTCWeekday(), buffer);
            print(buffer);
            print(" ");
            str_dec(getRTCHours(), buffer);
            print(buffer);
            print(":");
            str_dec(getRTCMinutes(), buffer);
            print(buffer);
            print(":");
            str_dec(getRTCSeconds(), buffer);
            print(buffer);
            print("\n");
        }
        else if (strcmp(input, "MALLOC") == 0)
        {
            int *phys_addr = malloc(50);
            char phys_str[16] = "";
            str_hex(phys_addr, phys_str);
            print("physical address: ");
            print(phys_str);
            print("\n");
        }
        else
        {
            print("You said: ");
            print(input);
            print("\n");
        }
    }
}