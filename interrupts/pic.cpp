#include "pic.hpp"
#include "../drivers/port_io/port_io.hpp"

PIC::PIC(){}

void PIC::initialize() const{
    
    //Send ICW 1
    portWriteByte(PIC1_COMMAND, 0x11);
    portWriteByte(PIC2_COMMAND, 0x11);

    //Send ICW 2
    portWriteByte(PIC1_DATA, INTERRUPT_VECTOR_NUMBER_PIC1);
    portWriteByte(PIC2_DATA, INTERRUPT_VECTOR_NUMBER_PIC2);

    //Send ICW 3
    portWriteByte(PIC1_DATA, 0X4);
    portWriteByte(PIC2_DATA, 0X2);

    //Send ICW 4
    portWriteByte(PIC1_DATA, 0x1);
    portWriteByte(PIC2_DATA, 0x1);

    //Null out the data registers
    portWriteByte(PIC1_DATA, 0x0);
    portWriteByte(PIC2_DATA, 0x0);
}

void PIC::notify_end_of_interrupt(unsigned char interruptVectorNumber){
    if(INTERRUPT_VECTOR_NUMBER_PIC1 <= interruptVectorNumber && interruptVectorNumber < INTERRUPT_VECTOR_NUMBER_PIC2){
        //if the interrupt sent from the primary pic
        portWriteByte(PIC1_COMMAND, 0x20);
    } else if(INTERRUPT_VECTOR_NUMBER_PIC2 <= interruptVectorNumber && interruptVectorNumber < INTERRUPT_VECTOR_NUMBER_PIC2 + 8){
        //if the interrupt sent from the secondary pic
        portWriteByte(PIC1_COMMAND, 0x20);
        portWriteByte(PIC2_COMMAND, 0x20);
    }
}

void enableInterrupts(){
    __asm__ __volatile__("sti");
}