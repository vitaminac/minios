;
; A simple boot sector program that 
; prints a message to the screen
; loops forever.
;

; Define a label , " loop ", that will allow
; us to jump back to it , forever.
START:

; int 10/ah=0eh -> scrolling teletype BIOS routine
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

; Use a simple CPU instruction that jumps
; to a new memory address to continue execution.
; In our case , jump to the address of the current
; instruction.
jmp $

; BIOS likes always to load 
; the boot sector to the address 0x7c00

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

; When compiled , our program must fit into 512 bytes,
; with the last two bytes being the magic number,
; so here , tell our assembly compiler to pad out our
; program with enough zero bytes (db 0) to bring us to the
; 510 th byte.

; $ is the address of the current position before emitting the bytes
; $$ evaluates to the beginning of the current section
; so ($−$$) tell you how far into the section
; db #value# just the byte #value# 
times 510 - ( $ - $$ ) db 0

; Last two bytes ( one word ) form the magic number,
; so BIOS knows we are a boot sector.
; dw #value# just the word #value# 
dw 0xaa55
