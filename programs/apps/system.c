#include <syscall.h>

int main()
{
    syscall(0x1, 0, 0, 0, 0, 0, 0);
    return 0;
}