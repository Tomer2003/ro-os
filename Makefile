os-image: kernel.bin boot_sect.bin
	cat boot_sect.bin kernel.bin > os-image

boot_sect.bin:
	nasm boot\ loader/boot_sect.asm -i./boot\ loader/  -f  bin -o boot_sect.bin

kernel.bin: kernel_entry.o kernel.o port_io.o vga_driver.o memcpy.o utoa.o reverse.o idt.o setBits.o gdt.o memset.o control_regs.o pic.o
	ld -o kernel.bin -Ttext 0x9500 kernel_entry.o utoa.o reverse.o memcpy.o port_io.o idt.o vga_driver.o kernel.o gdt.o memset.o setBits.o control_regs.o pic.o --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm kernel_entry.asm -f elf64 -o kernel_entry.o

kernel.o: kernel.cpp
	g++ -ffreestanding -c kernel.cpp -o kernel.o 

port_io.o: drivers/port_io/port_io.cpp
	g++ -ffreestanding -c drivers/port_io/port_io.cpp -o port_io.o

vga_driver.o: drivers/vga/vga_driver.cpp
	g++ -ffreestanding -c drivers/vga/vga_driver.cpp -o vga_driver.o

idt.o: interrupts/idt.cpp
	g++ -ffreestanding -c interrupts/idt.cpp -o idt.o

pic.o: interrupts/pic.cpp
	g++ -ffreestanding -c interrupts/pic.cpp -o pic.o

memset.o: libc/strings/memset.c
	gcc -ffreestanding -c libc/strings/memset.c -o memset.o

memcpy.o: libc/strings/memcpy.c
	gcc -ffreestanding -c libc/strings/memcpy.c -o memcpy.o

utoa.o: libc/stdlib/utoa.c
	gcc -ffreestanding -c libc/stdlib/utoa.c -o utoa.o

control_regs.o: libc/regs_operations/control_regs.c
	gcc -ffreestanding -c libc/regs_operations/control_regs.c -o control_regs.o

reverse.o: libc/array_operations/reverse.c
	gcc -ffreestanding -c libc/array_operations/reverse.c -o reverse.o

setBits.o: libc/bits_operations/setBits.c
	gcc -ffreestanding -c libc/bits_operations/setBits.c -o setBits.o

gdt.o: gdt/gdt.cpp
	g++ -ffreestanding -c gdt/gdt.cpp -o gdt.o

clean:
	rm *.o
	rm *.bin
	rm os-image

start:
	qemu-system-x86_64 -fda os-image