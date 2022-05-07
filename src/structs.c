#include <structs.h>

volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0};

volatile struct limine_5_level_paging_request paging_request = {
    .id = LIMINE_5_LEVEL_PAGING_REQUEST,
    .revision = 0};

volatile struct limine_boot_time_request boot_time_request = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0};

volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0};

volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0};