#ifndef KERNEL_H
#define KERNEL_H

void syscall()
{
    asm("mov $0x0, %rax");
    asm("mov $0x5, %rbx");
    asm("int $0x22");
}

#endif