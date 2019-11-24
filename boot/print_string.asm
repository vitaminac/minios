; Interrupts are a mechanism that 
; allow the CPU temporarily to halt what it is doing and run some other, 
; higher-priority instructions before returning to the original task.

; An interrupt could be raised either by a software instruction (e.g. int 0x10) 
; or by some hardware device that requires high-priority action

; Each interrupt is represented by a unique number that 
; is an index to the interrupt vector, 
; a table initially set up by BIOS at the start of memory
; at physical address0x0) that contains address pointers 
; to interrupt service routines (ISRs)

; An ISR is simply a sequence of machine instructions, 
; much like our boot sector code, that deals
; with a specific interrupt

; BIOS adds some of its own ISRs to the interrupt vector 
; that specialise in certain aspects of the computer

; for example: interrupt 0x10 causes the screen-related ISR to be invoked
; and interrupt 0x13, the disk-related I/O ISR

; prints a message to the screen
; int 10/ah=0eh -> scrolling teletype BIOS routine
print_string:
    mov ah, 0x0e
; Define a label, that will allow
; us to jump back to it
print_string_while:
    mov al, [bx]
    or al, al
    ; Conditional jumps are achieved in assembly language 
    ; by first running a comparison instruction, 
    ; then by issuing a specific conditional jump instruction.
    ; the content of special flags register is used 
    ; to capture the outcome of some instructions
    ; je target ; jump if equal ( i.e. x == y)
    ; jne target ; jump if not equal ( i.e. x != y)
    ; jl target ; jump if less than ( i.e. x < y)
    ; jle target ; jump if less than or equal ( i.e. x <= y)
    ; jg target ; jump if greater than ( i.e. x > y)
    ; jge target ; jump if greater than or equal ( i.e. x >= y)
    jz print_string_done
    int 0x10 ; print the character in al
    add bx, 1
    jmp print_string_while
print_string_done:
    ret