; prints a message to the screen
; int 10/ah=0eh -> scrolling teletype BIOS routine
print_string:
    mov ah, 0x0e
print_string_while:
    mov al, [bx]
    or al, al
    jz print_string_done
    int 0x10 ; print the character in al
    add bx, 1
    jmp print_string_while
print_string_done:
    ret

print_hex:
    mov ah, 0x0e
    mov cx, 0
print_hex_while_parse:
    mov dx, bx
    and dx, 0xf
    push dx
    add cx, 1
    shr bx, 4
    jnz print_hex_while_parse
print_hex_while_print:
    cmp cx, 0
    je print_hex_done
    sub cx, 1
    pop dx
    add dx, '0'
    mov al, dl
    int 0x10
    jmp print_hex_while_print
print_hex_done:
    ret