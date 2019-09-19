# Automatically generate lists of sources using wildcards
C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c)
INC_DIR = .
CFLAGS= -fno-pic -fno-pie -ffreestanding -m32 -Wall -I $(INC_DIR) -std=gnu11

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files
# $< is the first dependancy and $@ is the target file
%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

# Build the kernel entry object file
kernel_entry.o: ./boot/kernel_entry.asm
	nasm  $< -f elf -o $@

# This builds the binary of our kernel from two object files:
# the kernel_entry, which jumps to main() in our kernel
# the compiled C kernel
# Build the kernel binary
# $^ is substituted with all of the target's dependancy files
kernel.bin: kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sect . asm
boot_sect.bin: ./boot/boot_sect.asm
	nasm $< -f bin -i ./boot/ -o $@

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os.img: boot_sect.bin kernel.bin
	cat $^ > os.img

# Default build target .
all: os.img

# Clear away all generated files .
clean:
	rm ${OBJ}
	rm -fr *.bin *.dis *.o os.img *.map

# Run bochs to simulate booting of our code .
run: all
	bochsdbg.exe