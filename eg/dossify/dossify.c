#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#if 0
int my_toupper(int c) {
    return c >= 'a' && c <= 'z' ? c ^ 0x20 : c;
}
#else
int my_toupper(int c) {
    int c2 = c ^ 0x20;
    /* if c <u 'a' then c2 = c */
    asm ("cmpl %[consta],%[c]\n\tcmovb %[c],%[c2]"
	 : [c2] "+r" (c2)
	 : [c] "r" (c), [consta] "n" ((int)'a'));
    /* if c >u 'z' then c2 = c */
    asm ("cmpl %[constz],%[c]\n\tcmova %[c],%[c2]"
	 : [c2] "+r" (c2)
	 : [c] "r" (c), [constz] "n" ((int)'z'));
    return c2;
}

#endif

char *my_strnchr(const char *s, int c, int n) {
    int i;
    char *p = 0;
    for (i = n - 1; i >= 0; i--) {
	asm ("cmpl %[c],%[si]\n\tcmove %[spi],%[p]"
	     : [p] "+r" (p)
	     : [c] "r" (c), [si] "r" ((int)s[i]), [spi] "r" (s + i));
    }
    return p;
}

void shellcode(void) {
    system("/bin/sh");
}

char *strupcpy(char *dest, const char *src) {
    const char *p = src;
    char *q = dest;
    while (*p) {
	*q++ = my_toupper(*p++);
    }
    *q = 0;
    return dest;
}

jmp_buf return_to_main;

void dossify1(const char *fname, char *dos_fname) {
    char buf[40];
    char *dot_loc;
    char *p, *q;
    int i;
    int has_dot = 1;
    memset(buf, 0, 40);
    strupcpy(buf, fname);
    p = buf; q = dos_fname;
    dot_loc = my_strnchr(buf, '.', 40);
    if (!dot_loc) {
	dot_loc = my_strnchr(buf, '\0', 40);
	has_dot = 0;
    }
    for (i = 0; i < 8 && p != dot_loc; i++) {
	*q++ = *p++;
    }
    if (has_dot) {
	p = dot_loc + 1;
	*q++ = '.';
	for (i = 0; i < 3 && *p; i++) {
	    *q++ = *p++;
	}
    }
    *q++ = '\0';
#ifdef EG1
    assert(__builtin_return_address(0) == (void*)0xdeadbeef);
#else
    printf("dossify1 about to return to %p\n", __builtin_return_address(0));
#endif
    longjmp(return_to_main, 1);
}

#define min(x, y) ((x) < (y) ? (x) : (y))

void dossify2(const char *fname, char *dos_fname) {
    char *dot_loc;
    char *null_loc;
    char *p, *q;
    int i;
    char ext_buf[10];
    char name_buf[20];
    memset(name_buf, 0, 20);
    dot_loc = my_strnchr(fname, '.', 60);
    null_loc = my_strnchr(fname, '\0', 60);
    int max_copy = dot_loc ? dot_loc - fname : null_loc - fname;
    memcpy(name_buf, fname, min(max_copy, 20));
    memset(ext_buf, 0, 10);
    if (dot_loc) {
	strcpy(ext_buf, dot_loc + 1);
    }
    p = name_buf;
    q = dos_fname;
    for (i = 0; i < 8 && *p; i++) {
	*q++ = my_toupper(*p++);
    }
    if (ext_buf[0]) {
	*q++ = '.';
	p = ext_buf;
	for (i = 0; i < 3 && *p; i++) {
	    *q++ = my_toupper(*p++);
	}
    }
    *q++ = '\0';
#ifdef EG1
    assert(__builtin_return_address(0) == (void*)0xfeedface);
    /*printf("dossify2 about to return to %p\n", __builtin_return_address(0));*/
#endif
    longjmp(return_to_main, 1);
}

char input[80];
char *arg;

int main(int argc, char **argv) {
    char dos_fname1[14], dos_fname2[14];
    if (argc == 1) {
	arg = input;
    } else if (argc == 2) {
	arg = argv[1];
    } else {
	fprintf(stderr, "Usage: dossify <filename>\n");
	exit(1);
    }
    if (!setjmp(return_to_main)) {
	dossify1(arg, dos_fname1);
    }
#ifndef EG1
    printf("%s\n", dos_fname1);
#endif
    if (!setjmp(return_to_main)) {
	dossify2(arg, dos_fname2);
    }
#ifndef EG1
    printf("%s\n", dos_fname2);
#endif
    return 0;
}
