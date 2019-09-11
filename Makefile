# Build the kernel object file
# $< is the first dependancy and $@ is the target file
kernel.o: ./kernel/kernel.c
	gcc -fno-pic -fno-pie -ffreestanding -m32 -c  $< -o $@

# Build the kernel entry object file
kernel_entry.o: ./boot/kernel_entry.asm
	nasm  $< -f elf -o $@

# Build the kernel binary
# $^ is substituted with all of the target's dependancy files
kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sect . asm
boot_sect.bin: ./boot/boot_sect.asm
	nasm $< -f bin -i ./boot/ -o $@

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os.img: boot_sect.bin kernel.bin
	cat $^ > os.img

# Default make target .
all: os.img

# Clear away all generated files .
clean:
	rm -fr *.bin *.dis *.o os.img *.map

# Run bochs to simulate booting of our code .
run: all
	bochsdbg.exe