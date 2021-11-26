#include "drivers/vga/vga_driver.hpp"
#include "interrupts/idt.hpp"
#include "gdt/gdt.hpp"
#include "interrupts/idt.hpp"
#include "libc/include/regs_operations.h"

void* _Unwind_Resume;
void* __gxx_personality_v0;


void divideByZeroHandler(const ExceptionStackFrame* exceptionStackFrame)
{
	print("Exception divide by zero!!!\n");
	exceptionStackFrame->show();
}

void pageFaultHandler(const ExceptionStackFrame* exceptionStackFrame, const ErrorCode errorCode)
{
	print("Exception page Fault! while accesing ");
	printUnsignedInt(getCr2());
	print("\n");
	errorCode.show();
	exceptionStackFrame->show();
}

void breakPointHandler(const ExceptionStackFrame* exceptionStackFrame)
{
	print("In break point!!!!\n");
	exceptionStackFrame->show();
}

void recu(long a)
{
	long b[10000] = {0};
	print("aaaaaaa\n");
	recu(1);
}

void doubleFaultHandler(const ExceptionStackFrame* exceptionStackFrame, const ErrorCode errorCode)
{
	exceptionStackFrame->show();
	print("In double Fault");
	while (true)
	{
	}
}

char stack[3000];
generateHandlerFunction(divideByZeroWrapper, divideByZeroHandler)
generateHandlerFunctionWithErrorCode(pageFaultWrapper, pageFaultHandler)
generateHandlerFunction(breakPointWrapper, breakPointHandler)
generateHandlerFunctionWithErrorCode(doubleFaultWrapper, doubleFaultHandler)
void main()
{
	clearScreen();
	print("Welcome to RO-OS, developed by Tomer Royf.\n");
	TSS tss;
	tss.addInterruptStack(0, stack + 500);

	

	GDT gdt;
	gdt.addSegmentDescriptor(1, 1, 1, 0);
	gdt.addSegmentDescriptor(2, 0, 1, 0);
	
	

	gdt.addTssDescriptor(3, tss);
	gdt.load();
	gdt.loadTss(3);


	print("\n");
	printUnsignedInt(*((int*)&gdt));
	print(" ");
	printUnsignedInt(*((int*)&gdt + 1));
	print("\n");
	printUnsignedInt(*((int*)&gdt + 2));
	print(" ");
	printUnsignedInt(*((int*)&gdt + 3));
	print("\n");
	printUnsignedInt(*((int*)&gdt + 4));
	print(" ");
	printUnsignedInt(*((int*)&gdt + 5));
	print("\n");
	printUnsignedInt(*((int*)&gdt + 6));
	print(" ");
	printUnsignedInt(*((int*)&gdt + 7));
	print("\n");

	IDT idt;
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), pageFaultWrapper), 14);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), divideByZeroWrapper), 0);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), breakPointWrapper), 3);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 1), doubleFaultWrapper), 8);
	idt.load();
	//while(true) {}
	/*print("selector = ");
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
	//int a = 3/0;
	//*(char*)0xdeadbeef = 0;
	//__asm__("int3");
	print("before recu\n");
	recu(1);
	print("\npassed!!!!!!!!!\n");
	while(true)
	{

	}
}
