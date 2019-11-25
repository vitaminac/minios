#include "keyboard.h"
#include "port.h"
#include "cpu/isr.h"
#include "screen.h"
#include "libc/string.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char input_buffer[256];
static nat32 input_size = 0;
static bool ready = false;

#define SC_MAX 57
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs)
{
    /* The PIC leaves us the scancode in port 0x60 */
    nat8 scancode = port_byte_in(0x60);

    if (scancode > SC_MAX)
        return;
    if (scancode == BACKSPACE)
    {
        input_size = input_size - 1;
        if (input_size < 0)
            input_size = 0;
    }
    else if (scancode == ENTER)
    {
        input_buffer[input_size] = '\0';
        print("\n");
        ready = true;        
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        input_buffer[input_size++] = letter;
        char str[2] = {letter, '\0'};
        print(str);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void scanf(char *buffer)
{
    while (!ready);
    strcpy(input_buffer, buffer);
    input_size = 0;
    ready = false;
}