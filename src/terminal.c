#include <terminal.h>
#include <structs.h>
#include <printf.h>
#include <string.h>

struct limine_terminal *terminal;

void init_terminal()
{
    terminal = terminal_request.response->terminals[0];
}

void print(char *string)
{
    terminal_request.response->write(terminal, string, strlen(string));
}

void println(char *string)
{
    print(string);
    print("\n");
}

void set_color(char *color)
{
    print(color);
}

void cursor_up(int lines)
{
    printf("\033[%dA", lines);
}

void cursor_down(int lines)
{
    printf("\033[%dB", lines);
}

void cursor_right(int spaces)
{
    printf("\033[%dC", spaces);
}

void cursor_left(int space)
{
    printf("\033[%dD", space);
}

void print_status(char *text, int level, int go_up)
{
    switch (level)
    {
    case 0:
        if (go_up == 1)
            cursor_up(1);

        printf("%s[INFO]    %s                              \n", WHITE, text);
        break;
    case 1:
        if (go_up == 1)
            cursor_up(1);

        printf("%s[%sSUCCESS%s] %s                          \n", WHITE, GREEN, WHITE, text);
        break;
    case 2:
        if (go_up == 1)
            cursor_up(1);

        printf("%s[%sWARNING%s] %s                          \n", WHITE, YELLOW, WHITE, text);
        break;
    case 3:
        if (go_up == 1)
            cursor_up(1);

        printf("%s[%sERROR%s]   %s                          \n", WHITE, RED, WHITE, text);
        break;
    case 4:
        if (go_up == 1)
            cursor_up(1);

        printf("%s[PENDING] %s                              \n", WHITE, text);

        break;
    }
}

void putchar(char character)
{
    terminal_request.response->write(terminal, &character, 1);
}

void clear_terminal()
{
    print("\033[2J");
    cursor_up(terminal->columns);
}