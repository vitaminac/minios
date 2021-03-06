#include "cmos.h"
#include "libc/pio.h"

#define RTC_REGISTER 0X70
#define RTC_DATA 0X71

/**
 * Status Register B, Bit 1 (value = 2): Enables 24 hour format if set
 * Status Register B, Bit 2 (value = 4): Enables Binary mode if set
 */
#define RTC_STATUS_REG_B 0X0B
nat32 standardizeFromBCD(nat32 value)
{
    static bool initialized = false;
    static bool BCD_mode = false;
    if (!initialized)
    {
        out_byte(RTC_REGISTER, RTC_STATUS_REG_B);
        byte format = in_byte(RTC_DATA);
        BCD_mode = (format & 0x04) == 0;
        initialized = true;
    }
    if (BCD_mode)
    {
        return ((value / 16) * 10) + (value & 0x0F);
    }
    else
    {
        return value;
    }
}

nat32 standardizeFrom12h(nat32 hour)
{
    static bool initialized = false;
    static bool h12_mode = false;
    if (!initialized)
    {
        out_byte(RTC_REGISTER, RTC_STATUS_REG_B);
        byte format = in_byte(RTC_DATA);
        h12_mode = (format & 0x02) == 0;
        initialized = true;
    }
    if (h12_mode)
    {
        return ((hour & 0x7F) + 12) % 24;
    }
    else
    {
        return hour;
    }
}

#define RTC_SECONDS 0X00
nat32 getRTCSeconds()
{
    out_byte(RTC_REGISTER, RTC_SECONDS);
    return standardizeFromBCD(in_byte(RTC_DATA));
}

#define RTC_MINUTES 0X02
nat32 getRTCMinutes()
{
    out_byte(RTC_REGISTER, RTC_MINUTES);
    return standardizeFromBCD(in_byte(RTC_DATA));
}

#define RTC_HOURS 0X04
nat32 getRTCHours()
{
    nat32 hours;
    out_byte(RTC_REGISTER, RTC_HOURS);
    hours = in_byte(RTC_DATA);
    return standardizeFrom12h(standardizeFromBCD(hours & 0x7F) | (hours & 0x80));
}

#define RTC_WEEKDAY 0X06
nat32 getRTCWeekday()
{
    out_byte(RTC_REGISTER, RTC_WEEKDAY);
    return standardizeFromBCD(in_byte(RTC_DATA));
}

#define RTC_DAY_OF_MONTH 0X07
nat32 getRTCDayOfMonth()
{
    out_byte(RTC_REGISTER, RTC_DAY_OF_MONTH);
    return standardizeFromBCD(in_byte(RTC_DATA));
}

#define RTC_MONTH 0X08
nat32 getRTCMonth()
{
    out_byte(RTC_REGISTER, RTC_MONTH);
    return standardizeFromBCD(in_byte(RTC_DATA));
}

#define RTC_YEAR 0X09
#define RTC_CENTURY 0X32
nat32 getRTCYear()
{
    nat32 century;
    nat32 year;
    out_byte(RTC_REGISTER, RTC_CENTURY);
    century = standardizeFromBCD(in_byte(RTC_DATA));
    out_byte(RTC_REGISTER, RTC_YEAR);
    year = standardizeFromBCD(in_byte(RTC_DATA));
    return century * 100 + year;
}