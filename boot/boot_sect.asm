; A boot sector that boots from 16-bits mode into 32-bit protected mode and load a C kernel

; When we reboot our computer, it doesn't have any notion of an operating system.
; Luckily, we do have the Basic Input/Output Software (BIOS), 
; a collection of software routines that are initially loaded from a chip into memory 
; and initialised when the computer is switched on.

; BIOS load the boot sector to the address 0x7c00
; org directive tell the assembler where you expect the code will be loaded
; assembler will precalculate label address with this offset
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

; This is the memory offset to which we will load our kernel
KERNEL_OFFSET equ 0x1000

; When the CPU runs in its intial 16-bit real mode,
; the maximum size of the registers is 16 bits,
; which means that the highest address 
; we can reference in an instruction is 0xffff (64 KB = 65536 bytes)
; the CPU designers added a few more special registers,
; cs, ds, ss, and es, called segment registers
; We can imagine main memory as being divided into segments 
; that are indexed by the segment registers
; the CPU will offset our address from 
; the segment register appropriate for the context of our instruction
; To calculate the absolute address the CPU multiplies the value 
; in the segment register by 16 and then adds your offset address
[bits 16]
Boot:
    ; BIOS stores our boot drive in DL,
    ; so it's best to remember this for later.
    mov [BOOT_DRIVE], dl

    ; Announce that we are starting
    ; booting from 16-bit real mode
    mov bx, MSG_REAL_MODE
    
    ; At the CPU level a function is nothing more than 
    ; a jump to the address of a useful routine 
    ; then a jump back again to the instruction 
    ; immediately following the first jump
    ; the caller and callee must have some agreement 
    ; on where and how many parameters will be passed
    ; the caller code could store the correct return address
    ; in some well-known location,
    ; then the called code could jump back to that stored address.
    ; The CPU keeps track of the current instruction 
    ; being executed in the special register ip
    ;  the CPU provides a pair of instructions, call and ret, 
    ; call behaves like jmp but additionally, 
    ; before actually jumping, pushes the return address on to the stack; 
    ; ret then pops the return address off the stack and jumps to it
    call print_string

; Load our kernel
load_kernel:
    ; Print a message to say we are loading the kernel
    mov bx, MSG_LOAD_KERNEL
    call print_string
    ; we load the first 40 sectors that (excluding the boot sector)
    ; we must increment this value when kernel size go over 20kb
    mov dh, 40;
    ; read from the boot disk
    mov dl, [BOOT_DRIVE]
    ; set the address that we'd like BIOS to read the sectors to
    mov bx, KERNEL_OFFSET
    ; load kernel code
    call disk_load
    ; switch to 32-bits protected mode
    call switch_to_pm

; Includes our useful routines
%include "print_string.asm"
%include "disk_load.asm"
%include "switch_to_pm.asm"

; db = declare bytes of data which tells the assembler
; to write the subsequent bytes directly to the binary output file
; we often use a label to mark the start of our data
; Global Variables
BOOT_DRIVE: db 0 ; drive 0 (first floppy drive)
; 10 is ascii code for line change and 0 is null character
MSG_REAL_MODE: db "Booting from 16-bit Real Mode", 10, 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 10, 0

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

; Last two bytes ( one word ) make up the magic number,
; so BIOS knows we are a boot sector.
; dw #value# just the word #value# 
dw 0xaa55