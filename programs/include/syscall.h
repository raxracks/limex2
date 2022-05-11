#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

typedef uint64_t syscall_return;
typedef uint64_t syscall_number;

__attribute__((always_inline)) static inline syscall_return syscall(syscall_number number, syscall_number a1, syscall_number a2, syscall_number a3, syscall_number a4, syscall_number a5, syscall_number a6)
{
  syscall_return ret;
  register uint64_t r10 __asm__("r10") = a4;
  register uint64_t r8 __asm__("r8") = a5;
  register uint64_t r9 __asm__("r9") = a6;
  __asm__ volatile("int $0x22"
                   : "=a"(ret)
                   : "a"(number), "D"(a1), "S"(a2),
                     "d"(a3), "r"(r10), "r"(r8), "r"(r9)
                   : "rcx", "r11", "memory");
  return ret;
}

#endif