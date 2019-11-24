; Cylinder-Head-Sector (CHS)
; Cylinder: the cylinder describes the head’s discrete distance from the outer edge
; Head: the head describes which specific platter surface
; Sector: the circular track is divided into sectors, usually of capacity 512 bytes
; load DH sectors to ES:BX from drive DL
disk_load:
    ;  the CPU has a limited number of registers 
    ; for the temporary storage of our routine’s local variables
    ; So, the CPU offers two instructions push and pop that allow us, 
    ; respectively, to store a value and retrieve a value from the top of the stack, 
    ; and so without worrying exactly where they are stored.
    ; However, that we cannot push and pop single bytes 
    ; onto and off the stack: in 16-bit mode, 
    ; the stack works only on 16-bit boundaries.
    ; The stack is implemented by two special CPU registers, bp and sp, 
    ; which maintain the addresses of the stack base (i.e. the stack bottom) 
    ; and the stack top respectively.
    ; It grows downwards, when we issue a push 
    ; the value gets stored below, 
    ; the address of bp and sp is decremented by the value's size.

    ; Store DX on stack so later we can recall
    ; how many sectors were request to be read ,
    ; even if it is altered in the meantime
    push dx
    
    ; BIOS read sector function
    mov ah, 0x02

    ; Read DH sectors from the start point
    mov al, dh

    ; Select cylinder 0
    mov ch, 0x00

    ; Select head 0
    ; Select the track this count has a base of 0
    mov dh, 0x00

    ; Start reading from second sector
    ; (i.e. after the boot sector),
    ; since this has a base of 1.
    mov cl, 0x02

    ; issue the BIOS interrupt to do the actual read.
    int 0x13

    ; jc is another jumping instruction, 
    ; that jumps only if the carry flag was set.
    jc disk_error ; Jump if error (i.e. carry flag set)

    ; This jumps if what BIOS reported as the number of sectors
    ;  actually read in AL is not equal to the number we expected.
    pop dx ; Restore DX from the stack
    cmp dh, al ; if AL ( sectors read ) != DH ( sectors expected )
    jne disk_error ; display error message
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

; Disk Message
DISK_ERROR_MSG db " Disk read error!", 10, 0