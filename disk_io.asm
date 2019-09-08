; load DH sectors to ES:BX from drive DL
disk_load:
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
    push bp
    mov bp, sp
    push DISK_ERROR_MSG
    call print_string
    mov sp, bp
    pop bp
    jmp $

; Disk Message
DISK_ERROR_MSG db " Disk read error !" , 0