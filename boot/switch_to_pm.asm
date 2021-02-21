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
    mov cr0 , eax ; Update the control register

    ; the modern processors use a technique called pipelining, 
    ; that allows them to process different stages 
    ; of an instruction’s execution in parallel
    ; each instruction might be fetched from memory,
    ; decoded into microcode instructions, executed, 
    ; then perhaps the result is stored back to memory; 
    ; and since these stages are semi-independent, 
    ; they could all be done within the same CPU cycle 
    ; but within different circuitry
    ; switching CPU modes is a risk that 
    ; the CPU may process some stages of 
    ; an instruction’s execution in the wrong mode
    ; So after instructing the CPU to switch mode, 
    ; is to force the CPU to finish any jobs in its pipeline,
    ;  that we can be confident that 
    ; all future instructions will be executed in the correct mode.
    ; pipelining doesn't like instruction such as jmp or call,
    ; because until those instructions have been executed fully 
    ; the CPU can have no idea about the instructions 
    ; that will follow them, especially if we use a far jump or call, 
    ; which means that we jump to another segment.
    ; So immediately after instructing the CPU to switch mode, 
    ; we can issue a far jump, which will force the CPU to flush the pipeline
    ; To issue a far jump, 
    ; we additionally provide the target segment


    ; Make a far jump ( i.e. to a new segment ) to our 32-bit code.
    ; This also forces the CPU to flush
    ; its cache of prefetched and real-mode decoded instructions,
    ; which can cause problems.
    jmp CODE_SEG:init_pm

%include "gdt.asm"

; Registers are extended to 32 bits
; there are two additional general purpose segment registers, 
; fs and gs.
; 32-bit memory offsets are available, 
; so an offset can reference a whopping 4 GB of memory
; The CPU supports a more sophisticated and complex of memory segmentation
; Code in one segment can be prohibited from executing code in a more privilidged segment
; The CPU can implement virtual memory for user processes, 
; such that pages (i.e. fixed-sized chunks) of a process’s memory 
; can be swapped transparently between the disk and memory on an as-needed basis
; Interrupt handling is also more sophisticated
; we can no longer use BIOS once switched into 32-bit protected mode
; we need to use the [bits 32] directive to tell our assembler that,
; from that point onwards, it should encode in 32-bit mode instructions
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

    ; Set the stack
    ; Update our stack position so it is right
    ; at the top of the free space.
    mov ebp, 0x90000
    mov esp, ebp

    ; Finally, jump to the address of our loaded kernel code
    call KERNEL_OFFSET

poweroff:
    ; Try to turn off the computer when we return from the kernel
    cli ; mask all maskable interrupts on CPU core
suspend:
    hlt ; turn CPU into HALT state (power saving mode C1)
    jmp suspend ; try again if no maskable interrupt had happened