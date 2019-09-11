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

; This is the memory offset to which we will load our kernel
KERNEL_OFFSET equ 0x1000

[bits 16]
Boot:
    ; BIOS stores our boot drive in DL,
    ; so it's best to remember this for later.
    mov [BOOT_DRIVE], dl

    ; Announce that we are starting
    ; booting from 16-bit real mode
    mov bx, MSG_REAL_MODE
    call print_string

; Load our kernel
load_kernel:
    ; Print a message to say we are loading the kernel
    mov bx, MSG_LOAD_KERNEL
    call print_string
    ; we load the first 15 sectors that (excluding the boot sector)
    mov dh, 15;
    ; from the boot disk
    mov dl, [BOOT_DRIVE]
    ; to address KERNEL_OFFSET
    mov bx, KERNEL_OFFSET
    ; load kernel code
    call disk_load 

; Switch to protected mode
switch_to_pm:
    ; We must switch of interrupts until we have
    ; set -up the protected mode interrupt vector
    ; otherwise interrupts will run riot.
    cli

    ; Load our global descriptor table,
    ; which defines the protected mode segments
    lgdt [gdt_descriptor]

    ; To make the switch to protected mode,
    ; we set the first bit of CR0, a control register
    mov eax, cr0
    or eax, 0x1
    mov cr0 , eax

    ; Make a far jump ( i.e. to a new segment ) to our 32-bit code.
    ; This also forces the CPU to flush
    ; its cache of prefetched and real-mode decoded instructions,
    ; which can cause problems.
    jmp CODE_SEG:init_pm

Hang:
    ; Jumps to a new memory address to continue execution.
    ; In our case, jump to the address of the current instruction.
    ; Hang forever when we return from the kernel
    jmp $

; Includes
%include "print_string.asm"
%include "disk_load.asm"
%include "gdt.asm"

[bits 32]
; Initialise registers and the stack once in PM.
init_pm:
    ; Now in PM , our old segments are meaningless,
    ; so we point our segment registers to the
    ; data selector we defined in our GDT

    ; Stack Segment (SS). Pointer to the stack.
    ; Code Segment (CS). Pointer to the code.
    ; Data Segment (DS). Pointer to the data.
    ; The address used in the instruction mov ax, [0x123f]
    ; would by default offset from the data segment indexed by ds
    ; Extra Segment (ES). Pointer to extra data ('E' stands for 'Extra').
    ; F Segment (FS). Pointer to more extra data ('F' comes after 'E').
    ; G Segment (GS). Pointer to still more extra data ('G' comes after 'F').
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Update our stack position so it is right
    ; at the top of the free space.
    mov ebp, 0x90000
    mov esp, ebp

    ; Finally, jump to the address of our loaded kernel code
    call KERNEL_OFFSET

; Global Variables
BOOT_DRIVE: db 0
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

; Last two bytes ( one word ) form the magic number,
; so BIOS knows we are a boot sector.
; dw #value# just the word #value# 
dw 0xaa55