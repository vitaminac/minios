/*
When most computers boot, despite that they may infact have more advanced graphics hardware, 
they begin in a simple Video Graphics Array (VGA) colour text mode with dimmensions 80x25 characters.

In text mode, the programmer does not need to render
individual pixels to describe specific characters, 
since a simple font is already defined
in the internal memory of the VGA display device.

Instead, each character cell of the screen 
is represented by two bytes in memory: 
the first byte is the ASCII code of the character to be displayed, 
and the second byte encodes the characters attributes
such as the foreground and background colour and if the character should be blinking.

So, if we’d like to display a character on the screen, 
then we need to set its ASCII code and attributes 
at the correct memory address for the current VGA mode, 
which is usually at address 0xb8000

We use friendlier form of hardware I/O, known as memory-mapped I/O, 
whereby data written directly to a certain address range in main memory 
is written to the device’s internal memory buffer.
Since port I/O involves reading or writing individual bytes or words, the transfer of large
amounts of data between a disk device and memory could potentially take up a great
deal of better-spent CPU time. And an interrupt is raised 
when either the work is finished 
or if there was some error 
that is stopping the work from being finished.
*/

#include "port.h"
#include "libc/memory.h"

// display buffer
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
extern void print_at(char *string, int col, int row);
