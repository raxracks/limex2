#include <kernel.h>
#include <stdint.h>

void main()
{
    syscall(169, 0x10, 0x20, 0x30, "hello");
    while (1)
        ;
    return;
}