INC_DIR = .
# The option -ffreestanding directs the compiler to not assume that standard functions have their usual definition
C_FLAGS = -fno-pic -fno-pie -fno-exceptions -ffreestanding -m32 -Wall -Wextra -I $(INC_DIR) -std=c17 -pedantic-errors -g
NASM_FLAGS = -f elf -I $(INC_DIR)

# Tools path
OBJCOPY = objcopy
GCC = gcc

# Automatically generate lists of sources using wildcards
KERNEL_C_SOURCES = $(wildcard kernel/*.c cpu/*.c drivers/*.c libc/*.c hal/i386/*.c)
# Convert the *.c filenames to *.o to give a list of object files to build
KERNEL_OBJECTS = $(KERNEL_C_SOURCES:.c=.o) cpu/interrupt.o

BOOT_SECTOR_MEMOERY_ADDRESS = 0x7c00

# Default build target .
all: os.img

# Generic rule for compiling C code to an object file
# The compiler outputs annotated machine code,
# where meta information, such as textual labels, 
# that are redundant for execution, 
# remain present to enable more flexibilty 
# in how the code is eventually put together.
# One big advantage of this intermediary format 
# is that the code may be easily relocated into a larger binary file
# when linked in with routines from other routines in other libraries, 
# since code in the object file uses relative 
# rather than absolute internel memory references.
# $< is the first dependancy and $@ is the target file
%.o: %.c
	$(GCC) $(C_FLAGS) -c $< -o $@

# The option -f elf tells the assembler 
# to output an object file of the particular format Executable 
# and Linking Format (ELF), 
# which is the default format output by out C compiler
%.o: %.asm
	nasm $< $(NASM_FLAGS) -o $@

# In order to create the actual executable code
# we have to use a linker, 
# whose role is to link together all of the routines 
# described in the input object files 
# into one executable binary file, 
# effectively stitching them together 
# and converting those relative addresses 
# into absolute addresses within the aggregated machine code

# The -Ttext option puts the .text section of your program by the given address.
# We set its value to KERNEL_OFFSET we define in boot_sect.asm

# the linker can output executable files in various formats
# some of which may retain meta data from the input object files.
# meta data can be retained to describe 
# how those applications are 
# to be loaded into memory; 
# and for debugging purposes
# Anyhow, since we are interested in writing an operating system,
# CPU is unware of metadata and will execute every byte as machine code
# This is why we specify an output format of (raw) binary

# This builds our kernel from compiled C kernel objects
# $^ is substituted with all of the target's dependancy files
# However normally linker generates elf format which contains no executable metadata:
# e.g. relacation table for dynamic linking, symbols and annotations for debugging purpose
kernel.elf: $(KERNEL_OBJECTS)
	ld -m elf_i386 -o $@ -Ttext 0x1000 --entry kmain $^

# To extract flat binary format from elf format we use objcopy
# The final binary file will only have following sections .text - .rodata - .data
kernel.bin: kernel.elf
	$(OBJCOPY) -O binary kernel.elf $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sect.asm
boot_sect.bin: boot/boot_sect.asm
	nasm $< -f bin -I ./boot/ -o $@

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os.img: boot_sect.bin kernel.bin
	cat $^ > $@

# Disassemble our kernel - might be useful for debugging
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

# Clear away all generated files .
clean:
	rm -fr *.bin *.dis os.img *.map *.elf *.dis $(KERNEL_OBJECTS)

# Run bochs to simulate booting of our code
debug: all kernel.elf
	qemu-system-i386 -s -vnc :0 -fda os.img -d guest_errors,int & gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"