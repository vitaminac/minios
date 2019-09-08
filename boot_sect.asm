    global _start
    section .text
; A simple boot sector program

; Define a label, that will allow
; us to jump back to it
_start:

    ; BIOS likes always to load 
    ; the boot sector to the address 0x7c00

    ; org directive tell the assembler 
    ; where you expect the code will be loaded in memory
    ; it will be used as a reference location
    ; when you deference an address
    ; assemble will precalculate offset added this value when it is compiled
    [org 0x7c00]

    ; Stack Segment (SS). Pointer to the stack.
    ; Code Segment (CS). Pointer to the code.
    ; Data Segment (DS). Pointer to the data.
    ; The address used in the instruction mov ax, [0x123f]
    ; would by default offset from the data segment indexed by ds
    ; Extra Segment (ES). Pointer to extra data ('E' stands for 'Extra').
    ; F Segment (FS). Pointer to more extra data ('F' comes after 'E').
    ; G Segment (GS). Pointer to still more extra data ('G' comes after 'F').

    ; BIOS stores our boot drive in DL,
    ; so it's best to remember this for later.
    mov [BOOT_DRIVE], dl

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

; declare some data in out program
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
    push bp
    mov bp, sp
    push GREETING
    call print_string
    mov sp, bp
    pop bp
    ; make new call frame
    push bp
    mov bp, sp
    push 0x520f
    call print_hex
    mov sp, bp
    pop bp

demonstrates_segment_offsetting:
    mov ah, 0x0e

    ; Can’t set ds directly, so set bx
    mov bx, 0x7c0
    mov ds, bx
    mov al, [the_secret]
    int 0x10

    ; Tell the CPU to use the es (not ds) segment
    mov al, [es:the_secret]
    int 0x10

    mov bx, 0x7c0
    mov es, bx
    mov al, [es:the_secret]
    int 0x10

; Read some sectors from the boot disk using our disk_read function
disk_read:
    ; set the address that we ’d like BIOS to read the
    ; sectors to, which BIOS expects to find in ES:BX
    ; (i.e. segment ES with offset BX).

    ; Load 5 sectors to 0x0000 (ES):0x9000 (BX)

    ; Indirectly set ES to 0x0
    mov bx, 0x0
    mov es, bx

    ; Read from the boot disk.
    mov bx, 0x9000
    mov dh, 5
    ; Select BOOT_DRIVE
    mov dl, [BOOT_DRIVE]

    ; In our case, data will be read to 0x0:0x9000, 
    ; which the CPU will translate to physical address 0x9000
    call disk_load

    ; Print out the first loaded word, which
    ; we expect to be 0xdada , stored
    ; at address 0x9000
    mov dx, [es:0x9000]
    push bp
    mov bp, sp
    push dx
    call print_hex
    mov sp, bp
    pop bp

    ; Also , print the first word from the
    ; 2nd loaded sector : should be 0xface
    mov dx, [es:0x9000+512]
    push bp
    mov bp, sp
    push dx
    call print_hex
    mov sp, bp
    pop bp

hang:
    ; Use a simple CPU instruction that jumps
    ; to a new memory address to continue execution.
    ; In our case , jump to the address of the current
    ; instruction.
    ; loops forever.
    jmp $

; Includes
%include "print.asm"
%include "disk_io.asm"

; Global Variables
;    section .data
; The zero on the end tells our routine
; when to stop printing characters.
the_secret: db "X"
GREETING: db 'Booting OS ', 10, 0
BOOT_DRIVE: db 0

    ; >>>>>>>>>>> Bootsector padding and magic number <<<<<<<<<<
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

    ; We know that BIOS will load only the first 512 - byte sector from the disk ,
    ; so if we purposely add a few more sectors to our code by repeating some
    ; familiar numbers , we can prove to ourselfs that we actually loaded those
    ; additional two sectors from the disk we booted from.
    times 256 dw 0xdada
    times 256 dw 0xface