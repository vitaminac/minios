# build boot sect
nasm ./boot_sect.asm -f bin -o ./boot_sect.bin
# run bochs
bochsdbg.exe