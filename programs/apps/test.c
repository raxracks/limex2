#include <kernel.h>
#include <stdint.h>

void main()
{
    // test values
    syscall(0x1, 0x10, 0x20, 0x30, 0x40);
}