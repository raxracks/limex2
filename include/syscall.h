#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

typedef uint64_t _vos_syscallret_t;
typedef uint64_t _vos_syscallarg_t;
typedef uint64_t _vos_syscallnum_t;

__attribute__((always_inline)) static inline _vos_syscallret_t syscall(_vos_syscallnum_t n, _vos_syscallarg_t a1, _vos_syscallarg_t a2, _vos_syscallarg_t a3, _vos_syscallarg_t a4, _vos_syscallarg_t a5, _vos_syscallarg_t a6)
{
    _vos_syscallret_t ret;
    register uint64_t r10 __asm__("r10") = a4;
    register uint64_t r8 __asm__("r8") = a5;
    register uint64_t r9 __asm__("r9") = a6;
    __asm__ volatile("int $0x22"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2),
                       "d"(a3), "r"(r10), "r"(r8), "r"(r9)
                     : "rcx", "r11", "memory");
    return ret;
}

#endif