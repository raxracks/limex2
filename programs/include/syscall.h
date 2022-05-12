#ifndef SYSCALL_H
#define SYSCALL_H

#define SYSCALL_FB_ADDR 0x1
#define SYSCALL_FB_SWAP 0x2

#include <stdint.h>

__attribute__((always_inline)) static inline uint64_t syscall(uint64_t number, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6)
{
  register uint64_t r10 __asm__("r10") = a4;
  register uint64_t r8 __asm__("r8") = a5;
  register uint64_t r9 __asm__("r9") = a6;
  __asm__ volatile("int $0x22"
                   :
                   : "a"(number), "D"(a1), "S"(a2),
                     "d"(a3), "r"(r10), "r"(r8), "r"(r9)
                   : "rcx", "r11", "memory");

  register uint64_t ret asm("r15");
  return ret;
}

#endif