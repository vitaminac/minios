#include "port.h"
#include "libc/util.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define GET_SCREEN_OFFSET(COL, ROW) (2 * (ROW * MAX_COLS + COL))
#define GET_OFFSET_ROW(OFFSET) (OFFSET / (2 * MAX_COLS))
#define GET_OFFSET_COL(OFFSET) ((OFFSET - (GET_OFFSET_ROW(OFFSET) * 2 * MAX_COLS)) / 2)

extern void clear();
extern void print(char *string);