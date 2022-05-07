#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

int init_framebuffer(uint64_t sfn);
void fb_pixel(int x, int y, int color);
void fb_clear(int color);
void fb_fill_rect(int x, int y, int w, int h, int color);
void fb_swap();
void fb_putchar(char character);
void fb_cursor_up();
void fb_cursor_down();
void fb_cursor_left();
void fb_cursor_right();
void fb_text_color(int foreground, int background);
void fb_cursor_set_pos(int x, int y);
void fb_cursor_reset();

#endif