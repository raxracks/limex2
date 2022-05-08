#include <framebuffer.h>
#include <printf.h>
#include <io.h>

#define KB_CONTROLLER_DATA 0x60

void keyboard_irq_handler()
{
    // read from keyboard controller so that in any case it will be able to send more IRQs
    inb(KB_CONTROLLER_DATA);
    outb(0xa0, 0x20);
}