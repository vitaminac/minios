#ifndef PIC_H
#define PIC_H

#include "def/types.h"

/* PCI common definitions https://wiki.osdev.org/PIC#Programming_with_the_8259_PIC */
// IO base address for master PIC
#define PIC_MASTER 0x20
// IO port address for Master PIC - Command
#define PIC_MASTER_COMMAND_PORT PIC_MASTER
// IO port address for Master PIC - Data
#define PIC_MASTER_DATA_PORT (PIC_MASTER + 1)
// IO base address for slave PIC
#define PIC_SALVE 0xA0
// IO port address for Slave PIC - Command
#define PIC_SLAVE_COMMAND_PORT PIC_SALVE
// IO port address for Slave PIC - Data
#define PIC_SLAVE_DATA_PORT (PIC_SALVE + 1)
// The initialise command for two PCI
#define PIC_INIT_COMMAND 0x10
#define PIC_INIT_COMMAND_ICW4_NEEDED_PARAM 0x01
#define PIC_INITIALIZATION_COMMAND (PIC_INIT_COMMAND | PIC_INIT_COMMAND_ICW4_NEEDED_PARAM)
// Set the master PIC's offset to 0x20 and the slave's to 0x28
#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET 0x28
// 8086/88 (MCS-80/85) mode
#define PIC_8086_MODE 0x01

void pci_init();

#endif