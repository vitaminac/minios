; prints a message to the screen
; int 10/ah=0eh -> scrolling teletype BIOS routine
print_string:
    mov ah, 0x0e
print_while:
    mov al, [bx]
    or al, al
    jz print_done
    int 0x10 ; print the character in al
    add bx, 1
    jmp print_while
print_done:
    ret
