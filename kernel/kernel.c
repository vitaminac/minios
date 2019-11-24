#include "drivers/screen.h"

void main()
{
    clear();
    // ou caller function is calling callee function
    // and ensure pass argument to callee function
    // eax register is used to hold a function’s return value:
    print("Hello World!\n");
    print_at("Welcome to my first OS.", 28, 12);
}