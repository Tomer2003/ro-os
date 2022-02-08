#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define INTERRUPT_VECTOR_NUMBER_PIC1 32
#define INTERRUPT_VECTOR_NUMBER_PIC2 40

class PIC{
public:
    PIC();

    //initialize interrupts vector numbers of pic
    void initialize() const;

    //notify to pci eoi
    static void notify_end_of_interrupt(unsigned char interruptVectorNumber);
};

void enableInterrupts();