#include <asm/unistd_64.h>
long syscall(long number, ...);

void _start() {
    char hellow[] = "Hello, World!";
    syscall(__NR_write, 1, hellow, sizeof(hellow) - 1);
    syscall(__NR_exit, 0);
}
