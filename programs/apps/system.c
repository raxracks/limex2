#include <taskbar.h>
#include <framebuffer.h>
#include <stdint.h>

int main()
{
    uint32_t *front_buffer;
    front_buffer = framebuffer_init();
    taskbar_state internal_taskbar_state = taskbar_init();

    uint32_t framebuffer[1024 * 768];

    // fb_clear(0xd93838, front_buffer);

    while (1)
    {
        taskbar_loop(internal_taskbar_state, front_buffer);
    }
}