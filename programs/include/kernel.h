#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void syscall()
{
    int _eax = 10;

    __asm__(
        "mov %0,  %%rax\n"
        : "=m"(_eax)
        :        //"0" (*_eax) -- not required and throws errors !!
        : "%rax" // ESSENTIAL "clobbers"
    );
    asm("int $0x22");
}

#endif