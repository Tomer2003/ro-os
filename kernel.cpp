#include "drivers/vga/vga_driver.hpp"
#include "drivers/port_io/port_io.hpp"
#include "interrupts/idt.hpp"
#include "gdt/gdt.hpp"
#include "interrupts/pic.hpp"
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

void timerInterruptHandler(const ExceptionStackFrame* exceptionStackFrame)
{
	print(".");
	PIC::notify_end_of_interrupt(32);
}

void keyboardInterruptHandler(const ExceptionStackFrame* exceptionStackFrame)
{
	char scancode = portReadByte(0x60);
	switch (scancode)
	{
		case 0x02:
			print("1");
			break;
		case 0x03:
			print("2");
			break;
		case 0x04:
			print("3");
			break;
		case 0x05:
			print("4");
			break;
		case 0x06:
			print("5");
			break;
		case 0x07:
			print("6");
			break;
		case 0x08:
			print("7");
			break;
		case 0x09:
			print("8");
			break;
		case 0x0a:
			print("9");
			break;
		case 0x0b:
			print("0");
			break;
		default:
			break;
	}
	PIC::notify_end_of_interrupt(33);
}


void recu(long a)
{
	long b[10000] = {0};
	print("aaaaaaa\n");
	recu(1);
}

void doubleFaultHandler(const ExceptionStackFrame* exceptionStackFrame, const ErrorCode errorCode)
{
	print("In double fault\n");
	exceptionStackFrame->show();
	while (true)
	{
	}
}

char stack[3000];
generateHandlerFunction(divideByZeroWrapper, divideByZeroHandler)
generateHandlerFunctionWithErrorCode(pageFaultWrapper, pageFaultHandler)
generateHandlerFunction(breakPointWrapper, breakPointHandler)
generateHandlerFunction(timerInterruptWrapper, timerInterruptHandler)
generateHandlerFunction(keyboardInterruptWrapper, keyboardInterruptHandler)
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


	IDT idt;
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), pageFaultWrapper), 14);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), divideByZeroWrapper), 0);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), breakPointWrapper), 3);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 1), doubleFaultWrapper), 8);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), timerInterruptWrapper), 32);
	idt.addEntry(IdtEntry(getCsSelector(), IdtOptions(1, 1, 0, 0), keyboardInterruptWrapper), 33);
	idt.load();

	PIC pic;
	pic.initialize();
	enableInterrupts();

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
	//print("before recu\n");
	//recu(1);
	//print("\npassed!!!!!!!!!\n");
	__asm__ __volatile__("hlt");
	while(true)
	{
		
	}
}
