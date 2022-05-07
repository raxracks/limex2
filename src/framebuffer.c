#define SSFN_CONSOLEBITMAP_TRUECOLOR

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
int text_foreground = 0xffffff;
int fb_terminal_padding = 5;

int x_spacing = 8;
int y_spacing = 16;

int init_framebuffer(uint64_t sfn)
{
    print_status("Checking for valid framebuffer response...", PENDING, 0);

    if (framebuffer_request.response != NULL)
    {
        print_status("Framebuffer response is non-null.", SUCCESS, 1);

        char buf[100];
        sprintf_(buf, "%d framebuffer(s) present.", framebuffer_request.response->framebuffer_count);
        print_status(buf, INFO, 0);

        for (int i = 0; i < framebuffer_request.response->framebuffer_count; i++)
        {
            sprintf_(buf, "Framebuffer #%d resolution: %dx%d", i + 1, framebuffer_request.response->framebuffers[i]->width, framebuffer_request.response->framebuffers[i]->height);
            print_status(buf, INFO, 0);
        }

        framebuffer_struct = framebuffer_request.response->framebuffers[0];
        front_buffer = framebuffer_struct->address;

        width = framebuffer_struct->width;
        height = framebuffer_struct->height;

        fb_clear(0);

        return 1;
    }
    else
        print_status("Framebuffer response is null!", ERROR, 1);

    ssfn_src = &sfn; /* the bitmap font to use */

    ssfn_dst.ptr = front_buffer;             /* address of the linear frame buffer */
    ssfn_dst.w = framebuffer_struct->width;  /* width */
    ssfn_dst.h = framebuffer_struct->height; /* height */
    ssfn_dst.p = 4096;                       /* bytes per line */
    ssfn_dst.x = ssfn_dst.y = 0;             /* pen position */
    ssfn_dst.fg = 0xFFFFFF;                  /* foreground color */

    return 0;
}

void pixel(int x, int y, int color)
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

void fb_fill_rect(int x, int y, int w, uint32_t h, uint32_t color)
{
    uint32_t i = width * (y - 1);

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

// void putchar_(char character)
// {
// if (character == '\n')
// {
//     cursor_x = 0;
//     cursor_y += y_spacing;
//     return;
// }

// int px = 0;
// uint64_t bCh = FONT[character];

// if (cursor_x + 8 < 0 || cursor_x > width || cursor_y + 8 < 0 || cursor_y > height)
//     return;

// if (cursor_x >= 0 && cursor_x + 8 < width && cursor_y >= 0 && cursor_y + 8 < height)
// {
//     int i = width * (cursor_y - 1 + fb_terminal_padding) + cursor_x + 8 + fb_terminal_padding;
//     int incAmount = width - 8;
//     for (int yy = 7; yy >= 0; yy--)
//     {
//         i += incAmount;
//         for (int xx = 7; xx >= 0; xx--)
//         {
//             if ((bCh >> px++) & 1)
//             {
//                 framebuffer[i] = text_foreground;
//             }
//             i++;
//         }
//     }
// }
// else
// {
//     int xpos = 0;
//     int i = width * (cursor_y - 1 + fb_terminal_padding);
//     for (int yy = 0; yy < 8; yy++)
//     {
//         i += width;
//         xpos = cursor_x + fb_terminal_padding;
//         for (int xx = 7; xx >= 0; xx--)
//         {
//             if ((bCh >> px++) & 1)
//             {
//                 if (xpos > 0 && xpos < width && yy + cursor_y + fb_terminal_padding > 0 && yy + cursor_y + fb_terminal_padding < height)
//                     framebuffer[i + xpos] = text_foreground;
//             }
//             xpos++;
//         }
//     }
// }

// cursor_x += x_spacing;

//     ssfn_putc(character);
// }

void fb_cursor_up()
{
    cursor_y -= y_spacing;

    if (cursor_y < 0)
        cursor_y = 0;
}