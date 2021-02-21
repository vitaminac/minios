#ifndef _LINUX_ACPI_H
#define _LINUX_ACPI_H
#include "libc/types.h"
#include "libc/errno.h"

// Root System Description Table Pointer - RSDP
#define ACPI_BIOS_ROM_BASE (0x0E0000)
#define ACPI_BIOS_ROM_END (0x100000)
#define ACPI_RSDP1_SIG 0x20445352 /* 'RSD ' */
#define ACPI_RSDP2_SIG 0x20525450 /* 'PTR ' */
// https://elixir.bootlin.com/linux/2.3.35/source/include/linux/acpi.h#L267
struct acpi_rsdp
{
    b32 signature[2];
    nat8 checksum;
    byte oem_id[6];
    nat8 revision;
    struct acpi_rsdt *rsdt;
} __attribute__((packed));

// Root System Description Table - https://wiki.osdev.org/RSDT
#define ACPI_RSDT_SIG 0x54445352 /* 'RSDT' */
// https://elixir.bootlin.com/linux/2.3.35/source/include/linux/acpi.h#L275
struct acpi_sdt_header
{
    b32 signature;
    nat32 length; // Total size of the table, inclusive of the header.
    nat8 rev;
    nat8 checksum;
    byte oem_id[6];
    byte oem_table_id[8];
    nat32 oem_revision;
    nat32 creator_id;
    nat32 creator_revision;
} __attribute__((packed));
struct acpi_rsdt
{
    struct acpi_sdt_header header;
    struct acpi_sdt_header *sdt_ptrs[]; // pointer to other sdt
};

// Fixed ACPI Description Table - https://wiki.osdev.org/FADT
#define ACPI_FADT_SIG 0x50434146 // equals to four bytes value of "FACP" encode with ASCII
// https://elixir.bootlin.com/linux/2.3.35/source/include/linux/acpi.h#L287
struct acpi_fadt
{
    struct acpi_sdt_header header;
    nat32 facs;
    struct acpi_dsdt *dsdt;
    nat8 int_model;
    nat8 reserved;
    nat16 sci_int;
    nat32 smi_cmd;
    nat8 acpi_enable;
    nat8 acpi_disable;
    nat8 s4bios_req;
    nat8 reserved2;
    nat32 pm1a_evt;
    nat32 pm1b_evt;
    nat32 pm1a_cnt;
    nat32 pm1b_cnt;
    nat32 pm2_cnt;
    nat32 pm_tmr;
    nat32 gpe0;
    nat32 gpe1;
    nat8 pm1_evt_len;
    nat8 pm1_cnt_len;
    nat8 pm2_cnt_len;
    nat8 pm_tm_len;
    nat8 gpe0_len;
    nat8 gpe1_len;
    nat8 gpe1_base;
    nat8 reserved3;
    nat16 p_lvl2_lat;
    nat16 p_lvl3_lat;
    nat16 flush_size;
    nat16 flush_stride;
    nat8 duty_offset;
    nat8 duty_width;
    nat8 day_alarm;
    nat8 mon_alarm;
    nat8 century;
    byte reserved4;
    byte reserved5;
    byte reserved6;
    b32 flags;
} __attribute__((packed));

// Differentiated System Description Table - https://wiki.osdev.org/DSDT
#define ACPI_DSDT_SIG 0x54445344 /* 'DSDT' */
struct acpi_dsdt
{
    struct acpi_sdt_header header;
    byte aml_code[];
} __attribute__((packed));

STATUS acpi_init(void);
STATUS acpi_power_off(void);

#endif