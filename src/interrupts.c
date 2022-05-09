#include <stdint.h>
#include <pic.h>
#include <interrupts.h>
#include <printf.h>
#include <framebuffer.h>
#include <keyboard.h>

static const char *exceptions[] =
    {
        "#DE: Divide Error",
        "#DB: Debug Exception",
        " — : NMI Interrupt",
        "#BP: Breakpoint",
        "#OF: Overflow",
        "#BR: BOUND Range Exceeded",
        "#UD: Invalid Opcode (Undefined Opcode)",
        "#NM: Device Not Available (No Math Coprocessor)",
        "#DF: Double Fault",
        "— : Coprocessor Segment Overrun (reserved)",
        "#TS: Invalid TSS",
        "#NP: Segment Not Present",
        "#SS: Stack-Segment Fault",
        "#GP: General Protection",
        "#PF: Page Fault",
        "— : (Intel reserved. Do not use.)",
        "#MF: x87 FPU Floating-Point Error (Math Fault)",
        "#AC: Alignment Check",
        "#MC: Machine Check",
        "#XM: SIMD Floating-Point Exception",
        "#VE: Virtualization Exception",
        "#CP: Control Protection Exception",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use.",
        "— : Intel reserved. Do not use."};

uint64_t isr_handler(uint64_t rsp)
{
    interrupt_cpu_state_t *cpu = (interrupt_cpu_state_t *)rsp;

    // handle exceptions
    if (cpu->isr_number <= 31)
    {
        fb_clear(0);
        fb_text_color(0xff3c26, NULL);
        printf("\n────────────────────────\n");
        printf("⚠ EXCEPTION OCCURRED! ⚠\n\n");
        printf("⤷ ISR-No. %d: %s\n", cpu->isr_number, exceptions[cpu->isr_number]);
        printf("⤷ Error code: 0x%.16llx\n\n\n", cpu->error_code);

        fb_text_color(0x52bfff, NULL);
        printf("ℹ Register dump:\n\n");
        printf("⤷ rax: 0x%.16llx, rbx:    0x%.16llx, rcx: 0x%.16llx, rdx: 0x%.16llx\n"
               "⤷ rsi: 0x%.16llx, rdi:    0x%.16llx, rbp: 0x%.16llx, r8 : 0x%.16llx\n"
               "⤷ r9 : 0x%.16llx, r10:    0x%.16llx, r11: 0x%.16llx, r12: 0x%.16llx\n"
               "⤷ r13: 0x%.16llx, r14:    0x%.16llx, r15: 0x%.16llx, ss : 0x%.16llx\n"
               "⤷ rsp: 0x%.16llx, rflags: 0x%.16llx, cs : 0x%.16llx, rip: 0x%.16llx\n",
               cpu->rax, cpu->rbx, cpu->rcx, cpu->rdx,
               cpu->rsi, cpu->rdi, cpu->rbp, cpu->r8,
               cpu->r9, cpu->r10, cpu->r11, cpu->r12,
               cpu->r13, cpu->r14, cpu->r15, cpu->ss,
               cpu->rsp, cpu->rflags, cpu->cs, cpu->rip);

        // printf("ERROR");
        fb_swap();

        // clear interrupts and halt forever
        while (1)
            asm volatile("cli; hlt");
    }
    // handle IRQ's / hardware interrupts
    else if (cpu->isr_number >= 32 && cpu->isr_number <= 47)
    {
        // keyboard IRQ check -> call handler
        if (cpu->isr_number == 34)
        {
            printf("syscall\n");

            printf("ℹ Register dump:\n\n");

            // asm("pop %rax");

            printf("⤷ rax: 0x%.16llx, rbx:    0x%.16llx, rcx: 0x%.16llx, rdx: 0x%.16llx\n"
                   "⤷ rsi: 0x%.16llx, rdi:    0x%.16llx, rbp: 0x%.16llx, r8 : 0x%.16llx\n"
                   "⤷ r9 : 0x%.16llx, r10:    0x%.16llx, r11: 0x%.16llx, r12: 0x%.16llx\n"
                   "⤷ r13: 0x%.16llx, r14:    0x%.16llx, r15: 0x%.16llx, ss : 0x%.16llx\n"
                   "⤷ rsp: 0x%.16llx, rflags: 0x%.16llx, cs : 0x%.16llx, rip: 0x%.16llx\n",
                   cpu->rax, cpu->rbx, cpu->rcx, cpu->rdx,
                   cpu->rsi, cpu->rdi, cpu->rbp, cpu->r8,
                   cpu->r9, cpu->r10, cpu->r11, cpu->r12,
                   cpu->r13, cpu->r14, cpu->r15, cpu->ss,
                   cpu->rsp, cpu->rflags, cpu->cs, cpu->rip);
        }

        // fb_clear(0);
        // fb_cursor_reset();
        // printf("interrupt %d happened\n", cpu->isr_number);
    }
    else if (cpu->isr_number == 255)
    {
        // apic spurious interrupt
        printf("apic spurious interrupt");
    }

    fb_swap();

    pic_signal_EOI(cpu->isr_number);

    return rsp;
}