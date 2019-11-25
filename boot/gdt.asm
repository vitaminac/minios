; GDT global descriptor table
; defines memory segments and their protected-mode attributes
; Once the CPU has been switched into 32-bit protected mode, 
; the process by which it translates logical addresses 
; to physical address is completely different
; rather than multiply the value of a segment register by 16 
; and then add to it the offset, 
; a segment register becomes an index to 
; a particular segment descriptor (SD) in the 
; A segment descriptor is an 8-byte structure 
; that defines the following properties of a protected-mode segment
; Base address (32 bits), which defines where the segment begins in physical memory
; Segment Limit (20 bits), which defines the size of the segment
; Various flags, which affect how the CPU interprets the segment, 
; such as the privilige level of code 
; that runs within it or whether it is read- or write-only.
; The simplest workable configuration of segment registers 
; is described by Intel as the basic flat model, 
; whereby two overlapping segments are defined 
; that cover the full 4 GB of addressable memory, 
; one for code and the other for data
gdt_start:

; the CPU requires that the first entry
; in the GDT purposely be an invalid null descriptor
; The null descriptor is a simple mechanism to catch mistakes 
; where we forget to set a particular segment register before accessing an address
; If an addressing attempt is made with the null descriptor, 
; then the CPU will raise an exception, which essentially is an interrupt
gdt_null: ; the mandatory null descriptor
    dd 0x0 ; ’dd ’ means define double word ( i.e. 4 bytes )
    dd 0x0

; |31          24|23 |22   |21 |20  |19         16|15 |14   13|12 |11    8|7          0|
; |Base 31:24    |G  |D/B  |L  |AVL |Seg. Limit   |P  |DPL    |S  |Type   |Base 23:16  |
; |Base 15::00                                    |Segment Limit 15:00            |
; L: 64-bit code segment (IA-32e mode only)
; AVL: Available for use by system software
; BASE: Segment base address
; D/B: Default operation size (0 = 16-bit segment; 1 = 32-bit segment)
; DPL: Descriptor privilege level
; G: Granuarity
; LIMIT: Segment Limit
; P: Segment present
; S: Descriptor type (0 = system; 1 = code or data)
; TYPE: Segment type

; Our code segment will have the following configuration
; Base: 0x0
; Limit: 0xfffff
; Present: 1, since segment is present in memory - used for virtual memory
; Privilige: 0, ring 0 is the highest privilige
; Descriptor type: 1 for code or data segment, 0 is used for traps
; Type:
;   - Code: 1 for code, since this is a code segment
;   – Conforming: 0, code in a segment with a lower privilege may not call code in this segment
;   – Readable: 1, 1 if readible, 0 if execute-only. Readible allows us to read constants defined in the code.
;   – Accessed: 0 This is often used for debugging and virtual memory techniques,
;       since the CPU sets the bit when it accesses the segment
; Other flags:
;   - Granularity: 1, if set, this multiplies our limit by 4K
;   - 32-bit default: 1, since our segment will hold 32-bit code
;   - 64-bit code segment: 0
;   - AVL: 0, We can set this for our own uses
; Since we are using a simple flat model, with two overlapping code and data segments,
; the data segment will be identical but for the type flags
;   - Code: 0 for data
;   - Expand down: 0
;   - Writable: 1
;   - Accessed: 0
gdt_code: ; the code segment descriptor
    ; base =0x0 , limit =0 xfffff ,
    ; 1st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
    ; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
    ; 2nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
    dw 0xffff ; Limit ( bits 0 -15)
    dw 0x0 ; Base ( bits 0 -15)
    db 0x0 ; Base ( bits 16 -23)
    db 10011010b ; 1st flags , type flags
    db 11001111b ; 2nd flags , Limit ( bits 16 -19)
    db 0x0 ; Base ( bits 24 -31)

gdt_data: ; the data segment descriptor
    ; Same as code segment except for the type flags :
    ; type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
    dw 0xffff ; Limit ( bits 0 -15)
    dw 0x0 ; Base ( bits 0 -15)
    db 0x0 ; Base ( bits 16 -23)
    db 10010010b ; 1st flags , type flags
    db 11001111b ; 2nd flags , Limit ( bits 16 -19)
    db 0x0 ; Base ( bits 24 -31)

; The reason for putting a label at the end of the
; GDT is so we can have the assembler calculate
; the size of the GDT for the GDT decriptor ( below )
; GDT descriptior
gdt_end: 

; the CPU needs to know how long our GDT is
; we instead give the address 
; of a much simpler structure called the GDT descriptor
gdt_descriptor: ; GDT descriptior
    dw gdt_end - gdt_start - 1  ; size of our GDT, (16 bits)
                                ; always less one of the true size
    dd gdt_start ; Start address of our GDT (32 bits)

; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT, 
; which in our case is the DATA segment 
; (0x0 -> NULL ; 0x08 -> CODE ; 0x10 -> DATA )
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start