;
; A simple boot sector program

; BIOS likes always to load 
; the boot sector to the address 0x7c00
; tell exactly the assembler 
; where you expect the code will be loaded in memory
; <- it will be used as a reference location
; when you deference an address
[org 0x7c00]

; Define a label, that will allow
; us to jump back to it
program:
    mov ah, 0x0e
    mov al, 'H'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, 0xA
    int 0x10

; Typical lower memory layout afer boot

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

; declare some data in out program
the_secret:
    db "X"

demonstrates_addressing:
    mov ah, 0x0e
    ; print the offset of the data
    mov al, the_secret
    int 0x10
    ; dereference a offset
    ; we have to use org 
    ; to set the correct location
    mov al, [the_secret]
    int 0x10
    ; print the content of the data
    ; assume we haven't use org
    mov bx, the_secret
    add bx, 0x7c00
    mov al, [bx]
    int 0x10

demonstrates_stack:
    mov ah, 0x0e
    ; Set the base of the stack a little above where BIOS
    ; loads our boot sector - so it won ’t overwrite us.
    mov bp, 0x8000
    mov sp, bp
    ; Push some characters on the stack for later
    push 'A'
    push 'B'
    push 'C'

    pop bx
    mov al, bl
    int 0x10

    pop bx
    mov al, bl
    int 0x10

    pop bx
    mov al, bl
    int 0x10

greet:
    mov ah, 0x0e
    mov bx, GREETING
    call print_string

; Use a simple CPU instruction that jumps
; to a new memory address to continue execution.
; In our case , jump to the address of the current
; instruction.
; loops forever.
hang: 
    jmp $

; Includes
%include "print_string.asm"

; Data
GREETING:
    ; The zero on the end tells our routine
    ; when to stop printing characters.
    db 'Booting OS', 0

; >>>>>>>>>>>>> Padding and magic number <<<<<<<<<<
; When compiled , our program must fit into 512 bytes,
; with the last two bytes being the magic number,
; so here , tell our assembly compiler to pad out our
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
