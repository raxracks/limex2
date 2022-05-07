#ifndef STRUCTS_H
#define STRUCTS_H

#include <limine.h>

volatile struct limine_terminal_request terminal_request;
volatile struct limine_5_level_paging_request paging_request;
volatile struct limine_boot_time_request boot_time_request;
volatile struct limine_framebuffer_request framebuffer_request;
volatile struct limine_module_request module_request;

#endif