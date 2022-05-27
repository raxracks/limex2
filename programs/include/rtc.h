#ifndef RTC_H
#define RTC_H

#include <io.h>

static inline int bcdtobin(int value)
{
    return (value >> 4) * 10 + (value & 15);
}

static inline int rtc_year()
{
    outb(0x70, 0x09);
    return bcdtobin(inb(0x71));
}

static inline int rtc_month()
{
    outb(0x70, 0x08);
    return bcdtobin(inb(0x71));
}

static inline int rtc_day()
{
    outb(0x70, 0x07);
    return bcdtobin(inb(0x71));
}

static inline int rtc_hour()
{
    outb(0x70, 0x04);
    return bcdtobin(inb(0x71));
}

static inline int rtc_minute()
{
    outb(0x70, 0x02);
    return bcdtobin(inb(0x71));
}

static inline int rtc_second()
{
    outb(0x70, 0x00);
    return bcdtobin(inb(0x71));
}

#endif