#include <rtc.h>
#include <io.h>
#include <printf.h>

int bcdtobin(int value)
{
    return (value >> 4) * 10 + (value & 15);
}

int rtc_year()
{
    outb(0x70, 0x09);
    return bcdtobin(inb(0x71));
}

int rtc_month()
{
    outb(0x70, 0x08);
    return bcdtobin(inb(0x71));
}

int rtc_day()
{
    outb(0x70, 0x07);
    return bcdtobin(inb(0x71));
}

int rtc_hour()
{
    outb(0x70, 0x04);
    return bcdtobin(inb(0x71));
}

int rtc_minute()
{
    outb(0x70, 0x02);
    return bcdtobin(inb(0x71));
}

int rtc_second()
{
    outb(0x70, 0x00);
    return bcdtobin(inb(0x71));
}

void rtc_print() {
    printf("%02d/%02d/2%03d %02d:%02d:%02d\n", rtc_day(), rtc_month(), rtc_year(), rtc_hour(), rtc_minute(), rtc_second());
}