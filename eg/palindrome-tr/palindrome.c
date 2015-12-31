#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen(const char *s) {
    int i;
    for (i = 0; s[i]; i++)
	;
    return i;
}

char *my_memchr(const char *s, int c, size_t n) {
    const char *p;
    for (p = s; p < s + n; p++) {
	if (*p == c)
	    return (char *)p;
    }
    return 0;
}

char *my_strchr(const char *s, int c) {
    const char *p;
    for (p = s; *p; p++) {
	if (*p == c)
	    return (char *)p;
    }
    if (c == 0 && *p == 0)
	return (char *)p;
    return 0;
}

int ispalindrome(const char *bufferIn, size_t bufferInLen)
{
    int len = -1;
    int i;
    int pal = 1;
    const char *end;
    char string[64];

    memset(string, 0, sizeof(string));

    // Strip bad ending characters and store in string
    end = my_memchr(bufferIn, '\t', bufferInLen);
    if (end == NULL)
        end = my_strchr(bufferIn, '\0');
    len = end-bufferIn;
#ifdef PATCHED
    if (len > sizeof(string) - 1)
        return -1;
#endif
    memcpy(string, bufferIn, len);
    // Now palindrome check string
    for(i = 0; ((i <= len/2) && (pal==1)); i++) {
        if(string[i] != string[len-i-1])
            pal = 0;
    }
    return pal;
}

int f1(const char *s) {
//int ispalindrome_strlen(const char *s) {
    return ispalindrome(s, my_strlen(s));
}

/* http://stackoverflow.com/questions/16946115/reversing-a-string-with-strrev-c*/
int f2(const char *s)
//int ispal(const char *s)
{
    const char *p = s + my_strlen(s) - 1;
    while (s < p)
        if (*p-- != *s++)
            return 0;

    return 1;
}

struct adaptor {
    char table[256];
} the_adaptor;

int wrap_tr(struct adaptor *ap, int (*f)(const char *), const char *s) {
    char buf[64];
    int i;
    for (i = 0; i < sizeof(buf); i++) {
	buf[i] = s[i] + ap->table[(unsigned char)s[i]];
	if (!s[i])
	    break;
    }
    return f(buf);
}

void compare(char *s) {
    int r1, r2;
    r1 = f1(s);
    //r1 = ispalindrome_strlen(s);
    r2 = f1(s);
    //r2 = ispalindrome_strlen(s);
    //r2 = wrap_tr(&the_adaptor, ispal, s);
    if (r1 == r2) {
        /* printf("Match, both give %d\n", r1); */
        printf("Match\n");
    } else {
	/*printf("Mismatch, f1 gives %d, adaptor gives %d\n", r1, r2);*/
        printf("Mismatch\n");
        exit(1);
    }
}

char the_input[64];

int main(int argc, char **argv) {
    char buf[64];
    if (argv[1][0] == 'c' && argc == 3) {
      strncpy(the_input, argv[3], 64);
	the_input[63] = 0;
	compare(the_input);
    } else if (argv[1][0] == 's' && argc == 2) {
	the_input[63] = 0;
	compare(the_input);
    } else if (argv[1][0] == 'f' && argc == 3) {
        FILE *fh;
        if (argv[2][0] == '-' && argv[2][1] == 0) {
            fh = stdin;
        } else {
            fh = fopen(argv[2], "r");
            if (!fh) {
                fprintf(stderr, "Failed to open %s for reading: %s\n",
                        argv[2], strerror(errno));
                return 1;
            }
        }
	while (fread(buf, 1, 64, fh) == 64) {
	    buf[63] = 0;
	    compare(buf);
	}
	printf("All tests succeeded!\n");
    } else {
	fprintf(stderr, "Wrong number of arguments");
    }
    return 0;
}
