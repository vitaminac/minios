#include "pic.h"
#include "libc/pio.h"

/**
     * https://wiki.osdev.org/PIC#Protected_Mode
     * In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved by Intel up until 0x1F.
     * Consequently it is difficult to tell the difference between an IRQ or an software error.
     * It is thus recommended to change the PIC's offsets, also known as remapping the PIC, IRQ table
     * so that IRQs use non-reserved vectors.
     */
void pci_init()
{
    // save masks
    byte b1, b2;
    b1 = in_byte(PIC_MASTER_DATA_PORT);
    b2 = in_byte(PIC_SLAVE_DATA_PORT);

    // When you enter protected mode the first command you will need to give the two PICs is the initialise command (code 0x11)
    out_byte(PIC_MASTER_COMMAND_PORT, PIC_INITIALIZATION_COMMAND);
    io_wait();
    out_byte(PIC_SLAVE_COMMAND_PORT, PIC_INITIALIZATION_COMMAND);
    io_wait();
    /**
     * https://wiki.osdev.org/PIC#Initialisation
     * This command makes the PIC wait for 3 extra "initialisation words" on the data port. 
     * These bytes give the PIC:
     *   1. Its vector offset. (ICW2)
     *   2. Tell it how it is wired to master/slaves. (ICW3)
     *   3. Gives additional information about the environment. (ICW4)
     */
    // ICW2: set the master PIC's offset
    out_byte(PIC_MASTER_DATA_PORT, PIC_MASTER_OFFSET);
    io_wait();
    // ICW2: set the slave PIC's offset
    out_byte(PIC_SLAVE_DATA_PORT, PIC_SLAVE_OFFSET);
    io_wait();
    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    out_byte(PIC_MASTER_DATA_PORT, 0x04);
    io_wait();
    // ICW3: tell Slave PIC its cascade identity (0000 0010)
    out_byte(PIC_SLAVE_DATA_PORT, 0x02);
    io_wait();
    // ICW4: Gives additional information about the environment
    out_byte(PIC_MASTER_DATA_PORT, PIC_8086_MODE);
    io_wait();
    out_byte(PIC_SLAVE_DATA_PORT, PIC_8086_MODE);
    io_wait();
    // restore masks
    out_byte(PIC_MASTER_DATA_PORT, b1);
    out_byte(PIC_SLAVE_DATA_PORT, b2);
}