#ifndef PIC_H
#define PIC_H

#define PIC1 0x20            // I/O base address for master PIC
#define PIC2 0xA0            // I/O base address for slave PIC
#define PIC1_COMMAND PIC1    // master PIC command port
#define PIC1_DATA (PIC1 + 1) // master PIC data port
#define PIC2_COMMAND PIC2    // slave PIC command port
#define PIC2_DATA (PIC2 + 1) // slave PIC data port
#define ICW4_8086 0x01       // 8086/88 (MCS-80/85) mode

#include <stdint.h>

void pic_disable(void);
void pic_remap(void);
void pic_set_mask(unsigned char irq_line);
void pic_clear_mask(unsigned char irq_line);
void pic_end_of_interrupt(uint64_t isr_number);

#endif