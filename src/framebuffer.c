#define SSFN_CONSOLEBITMAP_TRUECOLOR
#define SSFN_CONSOLEBITMAP_CONTROL
#define __THROW

#include <framebuffer.h>
#include <structs.h>
#include <terminal.h>
#include <printf.h>
#include <font.h>
#include <ssfn.h>

#define WIDTH 1024
#define HEIGHT 768

struct limine_framebuffer *framebuffer_struct;
static uint32_t *front_buffer;
static uint32_t framebuffer[WIDTH * HEIGHT];
int width;
int height;
int cursor_x = 0;
int cursor_y = 0;
int do_swap = 1;

int init_framebuffer(uint64_t sfn)
{
    tm_print_status("Checking for valid framebuffer response...", PENDING, 0);

    if (framebuffer_request.response != NULL)
    {
        tm_print_status("Framebuffer response is non-null.", SUCCESS, 1);

        char buf[100];
        sprintf(buf, "%d framebuffer(s) present.", framebuffer_request.response->framebuffer_count);
        tm_print_status(buf, INFO, 0);

        for (int i = 0; i < framebuffer_request.response->framebuffer_count; i++)
        {
            sprintf(buf, "Framebuffer #%d resolution: %dx%d", i + 1, framebuffer_request.response->framebuffers[i]->width, framebuffer_request.response->framebuffers[i]->height);
            tm_print_status(buf, INFO, 0);
        }

        framebuffer_struct = framebuffer_request.response->framebuffers[0];
        front_buffer = framebuffer_struct->address;

        width = framebuffer_struct->width;
        height = framebuffer_struct->height;

        fb_clear(0);

        ssfn_src = (ssfn_font_t *)(sfn); /* the bitmap font to use */

        ssfn_dst.ptr = framebuffer;              /* address of the linear frame buffer */
        ssfn_dst.w = framebuffer_struct->width;  /* width */
        ssfn_dst.h = framebuffer_struct->height; /* height */
        ssfn_dst.p = 4096;                       /* bytes per line */
        ssfn_dst.x = 0;                          /* pen position */
        ssfn_dst.y = 0;
        ssfn_dst.fg = 0xFFFFFF; /* foreground color */

        return 1;
    }
    else
        tm_print_status("Framebuffer response is null!", ERROR, 1);

    return 0;
}

void fb_pixel(int x, int y, int color)
{
    framebuffer[width * y + x] = color;
}

void fb_clear(int color)
{
    for (int i = 0; i < width * height; i++)
        framebuffer[i] = color;
}

void fb_swap()
{
    for (int i = width * height; i >= 0; i--)
    {
        front_buffer[i] = framebuffer[i];
    }
}

void fb_fill_rect(int x, int y, int w, int h, int color)
{
    int i = width * (y - 1);

    if (x >= 0 && x + w < width && y >= 0 && y + h < height)
    {
        i += x + w;
        for (int yy = h; yy > 0; yy--)
        {
            i += width - w;
            for (int xx = w; xx > 0; xx--)
            {
                framebuffer[i++] = color;
            }
        }
    }
    else
    {
        for (int yy = y; yy < y + h; yy++)
        {
            i += width;
            for (int xx = x; xx < x + w; xx++)
            {
                if (xx >= 0 && xx < width && yy >= 0 && yy < height)
                    framebuffer[i + xx] = color;
            }
        }
    }
}

void fb_putchar(char character)
{
    if (character == '\n')
    {
        cursor_x = 0;
        fb_cursor_down();
        return;
    }

    fb_cursor_right();

    ssfn_putc(character);
}

void fb_cursor_set_pos(int x, int y)
{
    ssfn_dst.x = x * 8;
    ssfn_dst.y = y * 16;
    cursor_x = x;
    cursor_y = y;
}

void fb_cursor_reset()
{
    fb_cursor_set_pos(0, 0);
}

void fb_text_color(int foreground, int background)
{
    if (foreground != NULL)
        ssfn_dst.fg = foreground;
    if (background != NULL)
        ssfn_dst.bg = background;
}

void fb_cursor_up()
{
    cursor_y--;

    fb_cursor_set_pos(cursor_x, cursor_y);

    if (ssfn_dst.y < 0)
        fb_cursor_set_pos(cursor_x, 1);
}

void fb_cursor_down()
{
    cursor_y++;

    fb_cursor_set_pos(cursor_x, cursor_y);
}

void fb_cursor_left()
{
    cursor_x--;

    fb_cursor_set_pos(cursor_x, cursor_y);

    if (ssfn_dst.x < 0)
        fb_cursor_set_pos(1, cursor_y);
}

void fb_cursor_right()
{
    cursor_x++;

    fb_cursor_set_pos(cursor_x, cursor_y);
}

void fb_print_status(char *text, int level, int go_up)
{
    switch (level)
    {
    case 0:
        if (go_up == 1)
            fb_cursor_up(1);

        fb_text_color(0xffffff, NULL);
        printf("[INFO]    %s                              \n", text);
        break;
    case 1:
        if (go_up == 1)
            fb_cursor_up(1);

        fb_text_color(0xffffff, NULL);
        printf("[");
        fb_text_color(0x3ce663, NULL);
        printf("SUCCESS");
        fb_text_color(0xffffff, NULL);
        printf("] %s                          \n", text);
        break;
    case 2:
        if (go_up == 1)
            fb_cursor_up(1);

        fb_text_color(0xffffff, NULL);
        printf("[");
        fb_text_color(0xfcf44e, NULL);
        printf("WARNING");
        fb_text_color(0xffffff, NULL);
        printf("] %s                          \n", text);
        break;
    case 3:
        if (go_up == 1)
            fb_cursor_up(1);

        fb_text_color(0xffffff, NULL);
        printf("[");
        fb_text_color(0xfc4e4e, NULL);
        printf("ERROR");
        fb_text_color(0xffffff, NULL);
        printf("]   %s                          \n", text);
        break;
    case 4:
        if (go_up == 1)
            fb_cursor_up(1);

        fb_text_color(0xffffff, NULL);
        printf("[");
        fb_text_color(0x4eb4fc, NULL);
        printf("PENDING");
        fb_text_color(0xffffff, NULL);
        printf("] %s                          \n", text);
        break;
    }

    if (do_swap)
        fb_swap();
}

void fb_print_status_swap(int state)
{
    do_swap = state;
}