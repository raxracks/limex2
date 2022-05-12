#ifndef TASKBAR_H
#define TASKBAR_H

#include <syscall.h>
#include <stdint.h>
#include <framebuffer.h>

typedef struct taskbar_state
{
    int x;
    int y;
} taskbar_state;

static inline taskbar_state taskbar_init()
{
    struct taskbar_state state;
    state.x = 0;
    state.y = 0;
    return state;
}

static inline void taskbar_loop(taskbar_state state, uint32_t *fb)
{
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
            fb_pixel(state.x + x, state.y + y, 0xffffff, fb);
}

#endif