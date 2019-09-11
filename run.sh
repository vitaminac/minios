# compile kernel
gcc -ffreestanding -c kernel.c -o kernel.o
ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary
# build boot sect
nasm ./boot_sect.asm -f bin -o ./boot_sect.bin
# combine
cat boot_sect.bin kernel.bin > os.img
# run bochs
bochsdbg.exe