#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

int init_framebuffer(uint64_t sfn);
void pixel(int x, int y, int color);
void fb_clear(int color);
void fb_fill_rect(int x, int y, int w, uint32_t h, uint32_t color);
void fb_swap();
void fb_putchar(char ch);
// void putchar_(char character);
void fb_cursor_up();

#endif