; prints a message to the screen
; int 10/ah=0eh -> scrolling teletype BIOS routine
print_string:
    mov ah, 0x0e
; Define a label, that will allow
; us to jump back to it
print_string_while:
    mov al, [bx]
    or al, al
    jz print_string_done
    int 0x10 ; print the character in al
    add bx, 1
    jmp print_string_while
print_string_done:
    ret