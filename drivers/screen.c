#include "screen.h"

int get_cursor_offset()
{
    /**
     * The device uses its control register as an index
     * to select its internal registers, of which we are
     * interested in:
     * reg 14: which is the high byte of the cursor's offset
     * reg 15: which is the low byte of the cursor's offset
     * Once the internal register has been selected,
     * we may read or write a byte on the data register
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    /**
     * Since the cursor offset reported by the VGA hardware is the number of characters, 
     * we multiply by two to convert it to a character cell offset.
     */
    return offset * 2;
}

void set_cursor_offset(int offset)
{
    // Convert from cell offset to char offset
    offset /= 2;
    // This is similar to get_cursor,
    // only now we write bytes to those internal device registers
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

/* Advance the text cursor , scrolling the video buffer if necessary . */
int handle_scrolling(int cursor_offset)
{
    // If the cursor is within the screen , return it unmodified .
    if (cursor_offset < MAX_ROWS * MAX_COLS * 2)
    {
        return cursor_offset;
    }
    /* Shuffle the rows back one . */
    int i;
    for (i = 1; i < MAX_ROWS; i++)
    {
        memory_copy(GET_SCREEN_OFFSET(0, i) + VIDEO_ADDRESS,
                    GET_SCREEN_OFFSET(0, i - 1) + VIDEO_ADDRESS,
                    MAX_COLS * 2);
    }
    /* Blank the last line by setting all bytes to 0 */
    char *last_line = VIDEO_ADDRESS + GET_SCREEN_OFFSET(0, MAX_ROWS - 1);
    for (i = 0; i < MAX_COLS * 2; i++)
    {
        last_line[i] = 0;
    }
    // Move the offset back one row , such that it is now on the last
    // row , rather than off the edge of the screen .
    cursor_offset -= 2 * MAX_COLS;
    // Return the updated cursor position .
    return cursor_offset;
}

/* Print a char on the screen at col , row , or at cursor position */
void print_char(char character, int col, int row, char attribute_byte)
{
    /* Create a byte (char) pointer to the start of video memory
     * and point it to the first text cell (i.e. top-left of the screen)
     */
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

    /* If attribute byte is zero , assume the blank style . */
    if (!attribute_byte)
    {
        attribute_byte = WHITE_ON_BLACK;
    }

    /* Get the video memory offset for the screen location */
    int offset;
    /* If col and row are non - negative , use them for offset . */
    if (col >= 0 && row >= 0)
    {
        offset = GET_SCREEN_OFFSET(col, row);
    }
    /* Otherwise , use the current cursor position . */
    else
    {
        offset = get_cursor_offset();
    }
    // If we see a newline character , set offset to the end of
    // current row , so it will be advanced to the first col
    // of the next row.
    if (character == '\n')
    {
        int rows = offset / (2 * MAX_COLS);
        offset = GET_SCREEN_OFFSET(79, rows);
        // Otherwise , write the character and its attribute byte to
        // video memory at our calculated offset .
    }
    else
    {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }

    // Update the offset to the next character cell, which is
    // two bytes ahead of the current cell .
    offset += 2;

    // Make scrolling adjustment , for when we reach the bottom
    // of the screen.
    offset = handle_scrolling(offset);

    // Update the cursor position on the screen device .
    set_cursor_offset(offset);
}

void print(char *string)
{
    // Loop through each char of the message and print it.
    for (; *string; string++)
    {
        // print the character pointed to by string
        print_char(*string, -1, -1, 0);
    }
}

void clear()
{
    char blank[2] = {' ', WHITE_ON_BLACK};
    int screen_size = MAX_COLS * MAX_ROWS;
    memory_fill(VIDEO_ADDRESS, screen_size * 2, blank, 2);
    set_cursor_offset(GET_SCREEN_OFFSET(0, 0));
}