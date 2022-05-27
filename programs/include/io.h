#ifndef IO_H
#define IO_H

#include <syscall.h>

static inline void outb(uint64_t port, uint64_t val)
{
    syscall(SYSCALL_OUTB, (uint64_t)port, (uint64_t)val, 0, 0, 0, 0);
}

static inline int inb(uint16_t port)
{
    return (int)syscall(SYSCALL_INB, port, 0, 0, 0, 0, 0);
}

#endif