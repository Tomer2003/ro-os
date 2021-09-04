#include "drivers/vga/vga_driver.hpp"

void* _Unwind_Resume;
void* __gxx_personality_v0;

void main()
{
	clearScreen();
	print("Welcome to RO-OS, developed by Tomer Royf.\n");
	printUnsignedInt(0);
	printUnsignedInt(29480);
}
