#ifndef MEMORY_H
#define MEMORY_H

static inline void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;

    while (n-- > 0)
    {
        *d++ = *s++;
    }

    return d;
}

#endif