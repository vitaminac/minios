# compile kernel
gcc -ffreestanding -c ./kernel/kernel.c -o ./out/kernel.o
ld -o ./out/kernel.bin -Ttext 0x1000 ./out/kernel.o --oformat binary
# build boot sect
nasm -i ./boot/ ./boot/boot_sect.asm -f bin -o ./out/boot_sect.bin
# combine
cat ./out/boot_sect.bin ./out/kernel.bin > os.img
# run bochs
bochsdbg.exe