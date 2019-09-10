; A boot sector that boots a C kernel in 32-bit protected mode

; BIOS likes always to load 
; the boot sector to the address 0x7c00
; org directive tell the assembler 
; where you expect the code will be loaded in memory
; assembler will precalculate label address 
; by offset + this value when it is compiled
[org 0x7c00]

; Typical lower memory layout afer boot
; -----------------------------
; Free Memory
; ----------0x100000-----------
; BIOS (256 KB)
; ----------0xC0000------------
; Video Memory (128 KB)
; ----------0xA0000------------
; Extended BIOS Data Area (639 KB)
; ----------0x9fc00------------
; Free (638 KB)
; ----------0x7e00-------------
; Loaded Boot Sector (512 Bytes)
; ----------0x7c00-------------
; Nothing
; ----------0x500--------------
; BIOS Data Area (256 Bytes)
; ----------0x400--------------
; Interrupt Vector Table (1 KB)
; ----------0x0----------------

Boot:
    ; Greet when we start
    mov bx, MSG_REAL_MODE
    call print_string

Hang:
    ; Use a simple CPU instruction that jumps
    ; to a new memory address to continue execution.
    ; In our case,
    ; jump to the address of the current instruction.
    ; and loops forever.
    jmp $

; Includes
%include "print.asm"

; Global Variables
MSG_REAL_MODE: db "Booting from 16-bit Real Mode", 10, 0

; >>>>>>>>>>> Bootsector padding and magic number <<<<<<<<<<
; When compiled, our program must fit into 512 bytes,
; with the last two bytes being the magic number,
; so here, tell our assembly compiler to pad out our
; program with enough zero bytes (db 0) to bring us to the
; 510 th byte.
; $ is the address of the current position before emitting the bytes
; $$ evaluates to the beginning of the current section
; so ($−$$) tell you how far into the section
; db #value# just the byte #value# 
times 510 - ($ - $$) db 0

; Last two bytes ( one word ) form the magic number,
; so BIOS knows we are a boot sector.
; dw #value# just the word #value# 
dw 0xaa55