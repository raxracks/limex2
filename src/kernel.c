#include <stddef.h>
#include <kernel.h>
#include <structs.h>
#include <terminal.h>
#include <printf.h>
#include <rtc.h>
#include <limine.h>
#include <framebuffer.h>
#include <ssfn.h>
#include <cpu.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#include <io.h>
#include <memory.h>
#include <system_exec.h>
#include <syscall.h>

// nice hardcoding
int frames = 0;
int framesInSecond = 0;
int second = 0;

int x = 0;
int y = 0;

int xRev = 0;
int yRev = 0;

void panic(char *reason)
{
    fb_clear(0xff0000);
    fb_cursor_reset();
    printf("KERNEL PANIC!\n", RED);
    printf("%s", reason);

    fb_swap();
}

struct limine_file *find_limine_module(char *module_name)
{
    for (size_t i = 0; i < module_request.response->module_count; i++)
    {
        printf("[%x] %s module found.\n", module_request.response->modules[i]->address, module_request.response->modules[i]->cmdline);
        if (strcmp(module_request.response->modules[i]->cmdline, module_name) == 0)
            return module_request.response->modules[i];
    }

    return NULL;
}

void _start(void)
{
    init_terminal();
    tm_print_status("Terminal initialized.", SUCCESS, 0);

    struct limine_file *sfn_module = find_limine_module("sfn");

    if (!init_framebuffer(sfn_module->address))
        panic("Framebuffer failed to initialize.");

    fb_print_status_swap(0);

    fb_cursor_reset();

    fb_swap();

    if (paging_request.response != NULL)
        fb_print_status("5 level paging enabled.", SUCCESS, 0);
    else
        fb_print_status("5 level paging disabled.", WARNING, 0);

    fb_print_status("Initializing GDT...", PENDING, 0);
    gdt_init();
    fb_print_status("GDT Initialized.", SUCCESS, 0);

    fb_print_status("Initializing IDT...", PENDING, 0);
    idt_init();
    fb_print_status("IDT Initialized.", SUCCESS, 0);

    // outb(0x21, 0xfd);
    // outb(0xa1, 0xff);
    asm("sti");

    // int addr = &hi;

    unsigned char *destptr = (unsigned char *)0x20000000;
    memcpy(destptr, system_exec, system_exec_length);

    typedef void (*func_ptr)(void);
    func_ptr system_exec = (func_ptr)(destptr);
    system_exec();

    // syscall(0x1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60);

    rtc_print();
    // printf("FPS: %d\n", framesInSecond);

    fb_swap();

    while (1)
    {
        // fb_clear(0x333333);
        // fb_cursor_reset();

        // rtc_print();
        // printf("FPS: %d\n", framesInSecond);

        // if (paging_request.response != NULL)
        //     fb_print_status("5 level paging enabled.", SUCCESS, 0);
        // else
        //     fb_print_status("5 level paging disabled.", WARNING, 0);

        // fb_print_status("Initializing GDT...", PENDING, 0);
        // fb_print_status("GDT Initialized.", SUCCESS, 0);

        // fb_print_status("Initializing IDT...", PENDING, 0);
        // fb_print_status("IDT Initialized.", SUCCESS, 0);

        // fb_fill_rect(x, y, 100, 100, 0xffffff);

        // if (!xRev)
        //     x++;
        // else
        //     x--;
        // if (!yRev)
        //     y++;
        // else
        //     y--;

        // if (x > 924)
        // {
        //     xRev = 1;
        // }
        // else if (x < 0)
        // {
        //     xRev = 0;
        // }

        // if (y > 668)
        // {
        //     yRev = 1;
        // }
        // else if (y < 0)
        // {
        //     yRev = 0;
        // }

        // fb_swap();

        // frames++;

        // if (rtc_second() != second)
        // {
        //     framesInSecond = frames;
        //     frames = 0;
        //     second = rtc_second();
        // }
    }
}