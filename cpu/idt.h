#ifndef IDT_H
#define IDT_H

#include "def/types.h"

void set_idt_gate(int n, nat32 handler);
void set_idt();

#endif