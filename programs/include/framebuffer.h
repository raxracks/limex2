#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <syscall.h>
#include <stdint.h>

static inline uint32_t *framebuffer_init()
{
    return (uint32_t *)syscall(SYSCALL_FB_ADDR, 0, 0, 0, 0, 0, 0);
}

static inline void fb_swap(uint32_t *front_buffer, uint32_t *framebuffer)
{
    for (int i = 1024 * 768; i >= 0; i--)
    {
        front_buffer[i] = framebuffer[i];
    }
}

static inline void fb_pixel(int x, int y, int color, uint32_t *framebuffer)
{
    framebuffer[1024 * y + x] = color;
}

static inline void fb_clear(int color, uint32_t *framebuffer)
{
    for (int i = 1024 * 768; i >= 0; i--)
    {
        framebuffer[i] = color;
    }
}

#endif