#include "timer.h"
#include "isr.h"
#include "libc/string.h"
#include "libc/memory.h"

// static functions are functions that are only visible to other functions in the same translation unit
static void timer_callback(registers_t regs)
{
    static tick = 0;
    tick++;
}

void init_timer(nat32 freq)
{
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    // The programmable interval timer is a chip connected to IRQ0
    // It can interrupt the CPU at a user-defined rate (between 18.2Hz and 1.1931 MHz).
    // The PIT is the primary method used for implementing a system clock
    // and the only method available for implementing multitasking
    // The PIT has an internal clock which oscillates at approximately 1.1931MHz.
    // Get the Programmable Interval Timer (PIT) value
    nat32 divisor = 1193180 / freq;
    nat8 low = (nat8)low_8(divisor);
    nat8 high = (nat8)high_8(divisor);
    // PIT has 4 registers in I/O space
    // 0x40-0x42 are the data ports for channels 0-2 respectively,
    // and 0x43 is the command port.
    // set frequency
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}