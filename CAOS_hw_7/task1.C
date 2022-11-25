#include <sys/syscall.h>

long syscall(long number, ...);

typedef enum constans {
    Size = 256
} size;

void _start(){
//лучший код на свете Земля
	char buf[Size];
	int n;

	while ((n = syscall(SYS_read, 0, buf, Size)) > 0)
	  syscall(SYS_write, 1, buf, n);
	
	syscall(SYS_exit, 0);

}

