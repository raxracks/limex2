#include <pic.h>
#include <io.h>
#include <stdint.h>

void pic_disable(void)
{
    outb(PIC2_DATA, 0xFF);
    outb(PIC1_DATA, 0xFF);
}

// remap the programmable interrupt controller
void pic_remap(void)
{
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);
    io_wait();

    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    io_wait();

    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    io_wait();

    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

// use internel PIC register: IMR to ignore irq_lines
void pic_set_mask(uint8_t irq_line)
{
    uint16_t port;
    uint8_t value;

    if (irq_line < 8)
        port = PIC1_DATA;

    else
    {
        port = PIC2_DATA;
        irq_line -= 8;
    }

    value = inb(port) | (1 << irq_line);
    outb(port, value);
}

// "undo" pic_set_mask
void pic_clear_mask(uint8_t irq_line)
{
    uint16_t port;
    uint8_t value;

    if (irq_line < 8)
        port = PIC1_DATA;

    else
    {
        port = PIC2_DATA;
        irq_line -= 8;
    }

    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}

// signal an end of interrupt
void pic_signal_EOI(uint64_t isr_number)
{
    if (isr_number >= 40) // if the IRQ came from the slave PIC
        outb(PIC2_COMMAND, 0x20);

    outb(PIC1_COMMAND, 0x20); // if the IRQ came from the master and/or the slave PIC
}