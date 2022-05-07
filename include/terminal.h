#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>

#define BLACK "\e[0;30m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define CYAN "\e[0;36m"
#define WHITE "\e[0;37m"

#define INFO 0
#define SUCCESS 1
#define WARNING 2
#define ERROR 3
#define PENDING 4

void init_terminal();
void clear_terminal();
void print(char *string);
void println(char *string);
void cursor_up(int lines);
void cursor_down(int lines);
void cursor_left(int spaces);
void cursor_right(int spaces);
void putchar(char character);
void write(char *string, size_t length);
void print_status(char *text, int level, int go_up);

#endif