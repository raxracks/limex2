#include <taskbar.h>
#include <framebuffer.h>
#include <stdint.h>
#include <rtc.h>

int main()
{
    uint32_t *front_buffer;
    front_buffer = framebuffer_init();
    taskbar_state internal_taskbar_state = taskbar_init();

    uint32_t framebuffer[1024 * 768];

    while (1)
    {
        fb_clear(0xd93838, front_buffer);

        taskbar_loop(internal_taskbar_state, front_buffer);

        internal_taskbar_state.x = internal_taskbar_state.x + 1;
    }
}