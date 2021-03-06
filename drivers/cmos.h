// https://wiki.osdev.org/CMOS
#ifndef CMOS_H
#define CMOS_H
#include "libc/types.h"

nat32 getRTCSeconds();
nat32 getRTCMinutes();
nat32 getRTCHours();
nat32 getRTCWeekday();
nat32 getRTCDayOfMonth();
nat32 getRTCMonth();
nat32 getRTCYear();

#endif