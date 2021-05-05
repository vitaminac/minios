#ifndef TYPES_H
#define TYPES_H

#ifdef __i386__
#include "def/hal/i386/types.h"
#endif

typedef unsigned char byte;

#define true 1
#define false 0
#define NULL 0
#define WORD_SIZE sizeof(word)
#define WORD_MASK (WORD_SIZE - 1)

#endif