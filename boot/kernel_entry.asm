; Ensures that we jump straight into the kernel's entry function.
[bits 32] ; We ’re in protected mode by now , so use 32 - bit instructions.
[extern main] ; Declate that we will be referencing the external symbol 'main',
; so the linker can substitute the final address
call main ; invoke main () in our C kernel