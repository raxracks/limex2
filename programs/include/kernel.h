#ifndef KERNEL_H
#define KERNEL_H

__attribute__((naked)) static inline void syscall(int number, ...)
{
    asm volatile(
        "push %rbp;"
        "mov %rsp, %rbp;"
        "mov %rdi, %rax;"
        "mov %rsi, %rdi;"
        "mov %rdx, %rsi;"
        "mov %rcx, %rdx;"
        "mov %r8, %r10;"
        "mov %r9, %r8;"
        "mov 8(%rsp), %r9;"
        "int $0x22;"
        "mov %rbp, %rsp;"
        "pop %rbp;"
        "ret;");
}

#endif