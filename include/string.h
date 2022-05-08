#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char *str);
char* strcpy(char* destination, const char* source);
char* strcat(char* destination, const char* source);
int strcmp(char* string1, char* string2);

#endif