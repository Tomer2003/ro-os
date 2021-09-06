os-image: kernel.bin boot_sect.bin
	cat boot_sect.bin kernel.bin > os-image

boot_sect.bin:
	nasm boot\ loader/boot_sect.asm -i./boot\ loader/  -f  bin -o boot_sect.bin

kernel.bin: kernel_entry.o kernel.o port_io.o vga_driver.o memcpy.o utoa.o reverse.o idt.o setBits.o
	ld -o kernel.bin -Ttext 0x9500 kernel_entry.o utoa.o reverse.o memcpy.o port_io.o idt.o vga_driver.o kernel.o setBits.o --oformat binary

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

memcpy.o: libc/strings/memcpy.c
	gcc -ffreestanding -c libc/strings/memcpy.c -o memcpy.o

utoa.o: libc/stdlib/utoa.c
	gcc -ffreestanding -c libc/stdlib/utoa.c -o utoa.o

reverse.o: libc/array_operations/reverse.c
	gcc -ffreestanding -c libc/array_operations/reverse.c -o reverse.o

setBits.o: libc/bits_operations/setBits.c
	gcc -ffreestanding -c libc/bits_operations/setBits.c -o setBits.o


clean:
	rm *.o
	rm *.bin
	rm os-image

start:
	qemu-system-x86_64 -fda os-image