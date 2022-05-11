#include <terminal.h>
#include <structs.h>
#include <printf.h>
#include <string.h>

struct limine_terminal *terminal;

void init_terminal()
{
    terminal = terminal_request.response->terminals[0];
}

void tm_print(char *string)
{
    terminal_request.response->write(terminal, string, strlen(string));
}

void tm_printlen(char *string, int length)
{
    terminal_request.response->write(terminal, string, length);
}

void tm_println(char *string)
{
    tm_print(string);
    tm_print("\n");
}

void tm_set_color(char *color)
{
    tm_print(color);
}

void tm_cursor_up(int lines)
{
    printf("\033[%dA", lines);
}

void tm_cursor_down(int lines)
{
    printf("\033[%dB", lines);
}

void tm_cursor_right(int spaces)
{
    printf("\033[%dC", spaces);
}

void tm_cursor_left(int space)
{
    printf("\033[%dD", space);
}

void tm_print_status(char *text, int level, int go_up)
{
    switch (level)
    {
    case 0:
        if (go_up == 1)
            tm_cursor_up(1);

        printf("%s[INFO]    %s                              \n", WHITE, text);
        break;
    case 1:
        if (go_up == 1)
            tm_cursor_up(1);

        printf("%s[%sSUCCESS%s] %s                          \n", WHITE, GREEN, WHITE, text);
        break;
    case 2:
        if (go_up == 1)
            tm_cursor_up(1);

        printf("%s[%sWARNING%s] %s                          \n", WHITE, YELLOW, WHITE, text);
        break;
    case 3:
        if (go_up == 1)
            tm_cursor_up(1);

        printf("%s[%sERROR%s]   %s                          \n", WHITE, RED, WHITE, text);
        break;
    case 4:
        if (go_up == 1)
            tm_cursor_up(1);

        printf("%s[PENDING] %s                              \n", WHITE, text);

        break;
    }
}

void tm_putchar(char character)
{
    terminal_request.response->write(terminal, &character, 1);
}

void tm_clear()
{
    tm_print("\033[2J");
    tm_cursor_up(terminal->columns);
}