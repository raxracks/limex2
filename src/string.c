#include <string.h>

size_t strlen(const char *s)
{
    size_t count = 0;
    while (*s != '\0')
    {
        count++;
        s++;
    }
    return count;
}

char *strcpy(char *destination, const char *source)
{
    if (destination == NULL)
        return NULL;
    char *ptr = destination;
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return ptr;
}

char *strcat(char *destination, const char *source)
{
    if (destination == NULL)
        return NULL;
    char *ptr = destination + strlen(destination);
    while (*source != '\0')
        *ptr++ = *source++;
    return destination;
}

int strcmp(char *string1, char *string2)
{
    for (int i = 0; i < strlen(string2); i++)
    {
        if (string1[i] != string2[i])
            return 0;
    }

    return 1;
}