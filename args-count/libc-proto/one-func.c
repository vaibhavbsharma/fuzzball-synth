#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int unused;
    char *addr_err1 = strerror(1);
    char *addr_fcvt = fcvt(1.0, 5, &unused, &unused);
    long diff;
    long offset;
    int (*puts_fp)(const char *);
    printf("Error '%s' is at %p\n", addr_err1, addr_err1);
    printf("Float '%s' is at %p\n", addr_fcvt, addr_fcvt);
    diff = addr_fcvt - addr_err1;
    printf("Difference is 0x%lx\n", diff);
    if (diff != 0x244a81) {
	printf("Using unexpected glibc version, aborting\n");
	exit(1);
    }
    offset = (long)addr_err1 - 0x17cd8f;
    printf("Libc load address is 0x%lx\n", offset);
    puts_fp = (int (*)(const char *))(offset + 0x6fdb0);
    (*puts_fp)("Hello, world!");
    return 0;
}
