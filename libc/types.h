#ifndef TYPES_H
#define TYPES_H

#ifdef __i386__

typedef unsigned char      byte;
typedef unsigned short int b16;
typedef unsigned int       b32;
typedef          b32       word;
#define                WORD_SIZE     sizeof(word)
#define                WORD_MASK     (WORD_SIZE - 1)
typedef          void* ptr;
typedef          word* word_ptr;
typedef          b16*  b16_ptr;

// CPU specific
typedef unsigned int   nat32;
typedef          int   int32;
typedef unsigned short nat16;
typedef          short int16;
typedef unsigned char  nat8;
typedef          char  int8;

typedef          word   bool;
#define          true    1
#define          false   0

#endif

#define NULL 0
typedef int STATUS;
#define SUCCESS 0

#endif