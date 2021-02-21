/**
 * https://wiki.osdev.org/Shutdown
 * https://elixir.bootlin.com/linux/2.3.35/source/arch/i386/kernel/acpi.c#L879
 * https://forum.osdev.org/viewtopic.php?t=16990
 */
#include "acpi.h"
#include "libc/memory.h"
#include "libc/pio.h"

// global variables
static b16 SLP_TYPa;
static b16 SLP_TYPb;
static struct acpi_fadt *fadt;

// initialization
static struct acpi_rsdp *search_RSDP_from_BIOS_memory(void);
static struct acpi_rsdt *fetch_and_validate_RSDT_from_RSDP(struct acpi_rsdp *rsdp);
static struct acpi_fadt *search_FADT_from_RSDT(struct acpi_rsdt *rsdt);
static struct acpi_dsdt *fetch_and_validate_DSDT_from_FADT(struct acpi_fadt *fadt);
static struct byte *search_S5_from_DSDT(struct acpi_dsdt *dsdt);
static bool is_valid_S5_address(byte *S5_address);
static void extract_SLP_TYPa_and_SLP_TYPb(byte *S5_address, b16_ptr SLP_TYPa_ptr, b16_ptr SLP_TYPb_ptr);

STATUS acpi_init(void)
{
    struct acpi_rsdp *rsdp;
    struct acpi_rsdt *rsdt;
    struct acpi_dsdt *dsdt;
    byte *S5_address;

    if ((rsdp = search_RSDP_from_BIOS_memory()) == NULL)
    {
        return ENODEV;
    }

    if ((rsdt = fetch_and_validate_RSDT_from_RSDP(rsdp)) == NULL)
    {
        return ENODEV;
    }

    if ((fadt = search_FADT_from_RSDT(rsdt)) == NULL)
    {
        return ENODEV;
    }

    if ((dsdt = fetch_and_validate_DSDT_from_FADT(fadt)) == NULL)
    {
        return ENODEV;
    }

    /**
      * bytecode of the \_S5 object
      * -----------------------------------------
      * /          | (optional) |     | point by S5_address
      * AML code   | NameOP     | '\' | '_' | 'S' | '5'  | '_'
      * byte value | 08         | 5A  | 5F  | 53  | 35   | 5F

      * -----------------------------------------------------------------------------------------------------------
      *         |           |              | ( SLP_TYPa   ) | ( SLP_TYPb   ) | ( Reserved   ) | (Reserved    )
      * PackageOP | PkgLength | NumElements  | byteprefix Num | byteprefix Num | byteprefix Num | byteprefix Num
      * 12        | 0A        | 04           | 0A         05  | 0A          05 | 0A         05  | 0A         05

      * ----this-structure-was-also-seen----------------------
      * PackageOP | PkgLength | NumElements |
      * 12        | 06        | 04          | 00 00 00 00
     */
    if ((S5_address = search_S5_from_DSDT(dsdt)) == NULL)
    {
        return ENODEV;
    }

    if (!is_valid_S5_address(S5_address))
    {
        return EACCERT;
    }

    extract_SLP_TYPa_and_SLP_TYPb(S5_address, &SLP_TYPa, &SLP_TYPb);

    return SUCCESS;
}

static struct acpi_rsdp *search_RSDP_from_BIOS_memory(void)
{
    nat32 i = 0;
    struct acpi_rsdp *rsdp;
    for (i = ACPI_BIOS_ROM_BASE; i < ACPI_BIOS_ROM_END; i += 16)
    {
        rsdp = (struct acpi_rsdp *)i;
        if (rsdp->signature[0] == ACPI_RSDP1_SIG && rsdp->signature[1] == ACPI_RSDP2_SIG)
        {
            return rsdp;
        }
    }
    return NULL;
}

static struct acpi_rsdt *fetch_and_validate_RSDT_from_RSDP(struct acpi_rsdp *rsdp)
{
    struct acpi_rsdt *rsdt = rsdp->rsdt;
    if (rsdt && rsdt->header.signature == ACPI_RSDT_SIG)
    {
        return rsdt;
    }
    return NULL;
}

struct acpi_fadt *search_FADT_from_RSDT(struct acpi_rsdt *rsdt)
{
    nat32 sdt_entry_index;
    nat32 sdt_entries_count = (nat32)((rsdt->header.length - sizeof(rsdt->header)) / sizeof(struct acpi_sdt_header *));
    for (sdt_entry_index = 0; sdt_entry_index < sdt_entries_count; sdt_entry_index++)
    {
        struct acpi_sdt_header *sdt_entry = rsdt->sdt_ptrs[sdt_entry_index];
        if (sdt_entry && sdt_entry->signature == ACPI_FADT_SIG)
        {
            return (struct acpi_fadt *)sdt_entry;
        }
    }
    return NULL;
}

static struct acpi_dsdt *fetch_and_validate_DSDT_from_FADT(struct acpi_fadt *fadt)
{
    struct acpi_dsdt *dsdt = fadt->dsdt;
    if (dsdt && dsdt->header.signature == ACPI_DSDT_SIG)
    {
        return dsdt;
    }
    return NULL;
}

static struct byte *search_S5_from_DSDT(struct acpi_dsdt *dsdt)
{
    byte *S5_address = dsdt->aml_code;
    nat32 aml_code_length = dsdt->header.length - sizeof(dsdt->header);
    while (aml_code_length-- > 0)
    {
        if (memcmp(S5_address, "_S5_", 4) == 0)
        {
            return S5_address;
        }
        ++S5_address;
    }
    return NULL;
}

static bool is_valid_S5_address(byte *S5_address)
{
    return (*(S5_address - 1) == 0x08 || (*(S5_address - 2) == 0x08 && *(S5_address - 1) == '\\')) && *(S5_address + 4) == 0x12;
}

#define ACPI_SLP_TYP_SHIFT 10
static void extract_SLP_TYPa_and_SLP_TYPb(byte *S5_address, b16_ptr SLP_TYPa_ptr, b16_ptr SLP_TYPb_ptr)
{
    S5_address += 5;
    S5_address += ((*S5_address & 0xC0) >> 6) + 2; // calculate PkgLength size

    if (*S5_address == 0x0A)
        S5_address++; // skip byteprefix
    *SLP_TYPa_ptr = *(S5_address) << ACPI_SLP_TYP_SHIFT;
    S5_address++;

    if (*S5_address == 0x0A)
        S5_address++; // skip byteprefix
    *SLP_TYPb_ptr = *(S5_address) << ACPI_SLP_TYP_SHIFT;
}

// power off command
static STATUS ensure_acpi_is_enabled(struct acpi_fadt *fadt);
static void sendShutdownCommand(struct acpi_fadt *fadt, b16 SLP_TYPa, b16 SLP_TYPb);
STATUS acpi_power_off(void)
{
    STATUS status;
    status = ensure_acpi_is_enabled(fadt);
    if (status != SUCCESS)
    {
        return status;
    }
    sendShutdownCommand(fadt, SLP_TYPa, SLP_TYPb);
    return SUCCESS;
}

static bool acpi_is_enabled(struct acpi_fadt *fadt);
static void acpi_enable_SCI(struct acpi_fadt *fadt);
static STATUS ensure_acpi_is_enabled(struct acpi_fadt *fadt)
{
    nat32 attempts = 5000;
    if (!acpi_is_enabled(fadt))
    {
        acpi_enable_SCI(fadt);
        while (!acpi_is_enabled(fadt) && attempts-- > 0)
        {
            io_wait();
        }
        if (!acpi_is_enabled(fadt))
        {
            return EACCERT;
        }
    }
    return SUCCESS;
}

#define ACPI_SCI_EN 0x0001
static void acpi_enable_SCI(struct acpi_fadt *fadt)
{
    if (fadt->smi_cmd)
        out_byte((nat16)fadt->smi_cmd, fadt->acpi_enable);
}

static word acpi_read_pm1_control(struct acpi_fadt *fadt);
static bool acpi_is_enabled(struct acpi_fadt *fadt)
{
    return ((acpi_read_pm1_control(fadt) & ACPI_SCI_EN) ? true : false);
}

static word acpi_read_pm1_control(struct acpi_fadt *fadt)
{
    word value = 0;
    if (fadt->pm1a_cnt)
        value = in_b16(fadt->pm1a_cnt);
    if (fadt->pm1b_cnt)
        value |= in_b16(fadt->pm1b_cnt);
    return value;
}

#define ACPI_SLP_TYP_MASK 0x1c00
#define ACPI_SLP_EN 0x2000 // = 1 << 13
static void sendShutdownCommand(struct acpi_fadt *fadt, b16 SLP_TYPa, b16 SLP_TYPb)
{
    b16 value = in_b16(fadt->pm1a_cnt) & ~ACPI_SLP_TYP_MASK;
    out_b16(fadt->pm1a_cnt, value | SLP_TYPa | ACPI_SLP_EN);
    if (fadt->pm1b_cnt != 0)
    {
        value = in_b16(fadt->pm1b_cnt) & ~ACPI_SLP_TYP_MASK;
        out_b16(fadt->pm1b_cnt, value | SLP_TYPb | ACPI_SLP_EN);
    }
}