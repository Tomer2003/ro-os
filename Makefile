os-image: kernel.bin boot_sect.bin
	cat boot_sect.bin kernel.bin > os-image

boot_sect.bin:
	nasm boot\ loader/boot_sect.asm -i./boot\ loader/  -f  bin -o boot_sect.bin

kernel.bin: kernel_entry.o kernel.o port_io.o vga_driver.o memcpy.o
	ld -o kernel.bin -Ttext 0x9500 kernel_entry.o memcpy.o port_io.o vga_driver.o kernel.o --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm kernel_entry.asm -f elf64 -o kernel_entry.o

kernel.o: kernel.cpp
	g++ -ffreestanding -c kernel.cpp -o kernel.o

port_io.o: drivers/port_io/port_io.cpp
	g++ -ffreestanding -c drivers/port_io/port_io.cpp -o port_io.o

vga_driver.o: drivers/vga/vga_driver.cpp
	g++ -ffreestanding -c drivers/vga/vga_driver.cpp -o vga_driver.o

memcpy.o: libc/strings/memcpy.c
	gcc -ffreestanding -c libc/strings/memcpy.c -o memcpy.o


clean:
	rm *.o
	rm *.bin
	rm os-image

start:
	qemu-system-x86_64 -fda os-image