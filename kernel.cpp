#include "drivers/vga/vga_driver.hpp"
#include "interrupts/idt.hpp"

void* _Unwind_Resume;
void* __gxx_personality_v0;

void main()
{
	clearScreen();
	print("Welcome to RO-OS, developed by Tomer Royf.\n");
	GtdSelector selector;
	printUnsignedInt(selector.getSelector());
	print("\n");
	selector.setIndex(5);
	printUnsignedInt(selector.getSelector());
	print("\n");
	selector.setRPL(3);
	printUnsignedInt(selector.getSelector());
	print("\n");
	selector.setTI(1);
	printUnsignedInt(selector.getSelector());
	print("\n");
}
