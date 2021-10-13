#include "drivers/vga/vga_driver.hpp"
#include "interrupts/idt.hpp"
#include "gdt/gdt.hpp"
#include "interrupts/idt.hpp"
void* _Unwind_Resume;
void* __gxx_personality_v0;
void divideByZeroHandler(const ExceptionStackFrame& exceptionStackFrame)
{
	print("Exception divide by zero!!!\n");
	exceptionStackFrame.show();
}

__attribute__((naked)) void divideByZeroWrapper()
{
	__asm__ __volatile__("movq %%rsp, %%rdi\n\t"
						"call %0" ::"d"(divideByZeroHandler):"%rdi");
	while(true)
	{

	}
}
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
	printUnsignedInt(getCsSelector());
	print("\n");

	IDT idt;
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), divideByZeroWrapper), 0);
	idt.load();
	print("selector = ");
	printUnsignedInt(idt.getEntry(0).getGdtSelector().getSelector());
	print("\n");
	print("options = ");
	printUnsignedInt(idt.getEntry(0).getIdtOptions().getOptionsVal());
	print("\n");
	print("pointer vals = ");
	printUnsignedInt(idt.getEntry(0).pointerEnd);
	print(", ");
	printUnsignedInt(idt.getEntry(0).pointerMid);
	print(", ");
	printUnsignedInt(idt.getEntry(0).pointerLow);
	print("\n");
	print("pointer = ");
	/*printUnsignedInt(*((unsigned int*)&printZeroDivError + 1));
	print(", ");
	printUnsignedInt(*((unsigned short*)&printZeroDivError + 1));
	print(", ");
	printUnsignedInt(*((unsigned short*)&printZeroDivError));
	print("\n");*/
	int a = 3/0;
	print("\npassed!!!!!!!!!\n");
	while(true)
	{

	}
}
