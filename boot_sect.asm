;
; A simple boot sector program that 
; prints a message to the screen
; loops forever.
;

; Define a label , " loop ", that will allow
; us to jump back to it , forever.
loop:

; int 10/ah = 0eh -> scrolling teletype BIOS routine
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

; Use a simple CPU instruction that jumps
; to a new memory address to continue execution.
; In our case , jump to the address of the current
; instruction.
jmp $

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
