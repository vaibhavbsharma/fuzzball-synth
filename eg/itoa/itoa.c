#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int my_strlen(const char *s) {
    int i;
    for (i = 0; s[i]; i++)
        ;
    return i;
}

int my_streq(const char *s1, const char *s2) {
    int i;
    for (i = 0; ; i++) {
	if (s1[i] != s2[i])
	    return 0;
	else if (s1[i] == 0 && s2[i] == 0)
	    return 1;
	else if (s1[i] == 0 || s2[i] == 0)
	    return 0;
    }
}


/* From: CFAR_Apache_2.0.2/atds/apache/httpd-2.4.17/modules/echo/cromu_00001.c
 */

size_t itoa( char *out, size_t val, size_t max )
{
    size_t length = 0;
    size_t end = 0;
    size_t temp = 0;

    if ( out == NULL ) {
        goto end;
    }

    // Calculate the needed length
    temp = val;
    do {
        end++;
        temp >>= 3;
    } while ( temp );

    // ensure we have enough room
    if ( end >= max ) {
        goto end;
    }

    length = end;

    // Subtract one to skip the null
    end--;

    do {
        out[end] = (val & 7) + 0x30;
        val >>= 3;
        end--;
    } while ( val );

    out[length] = 0x00;
end:
    return length;
}

/* From:  https://stackoverflow.com/questions/190229/where-is-the-itoa-function-in-linux/192700#192700
 */
#define CHAR_BITS 8

const char *
my_itoa_buf(char *buf, size_t len, unsigned long /*int*/ num)
{
  static char loc_buf[sizeof(int) * CHAR_BITS]; /* not thread safe */

  if (len < 23)
      len = 23;
  if (len > 1000)
      return "";

  if (!buf)
  {
    buf = loc_buf;
    len = sizeof(loc_buf);
  }

  if (snprintf(buf, len, "%lo", num) == -1)
    return ""; /* or whatever */

  return buf;
}

size_t f1(char *buf, size_t val, size_t max) {
    if (max < 23)
	max = 23;
    if (max > 1000)
	return 0;
    return itoa(buf, val, max);
}

size_t f2(char *buf, size_t max, size_t val) {
    return (size_t)my_itoa_buf(buf, max, val);
}

size_t wrap_f2(char *buf, size_t max, size_t val) {
    return f2(buf, max, val);
}

void compare(char *buf, size_t val, size_t max) {
    long r1, r2;
    char *buf1 = malloc(100);
    char *buf2 = malloc(100);
    (void)buf;
    r1 = f1(buf1, val, max);
    printf("Completed f1\n");
    fflush(stdout);
    r2 = wrap_f2(buf2, val, max);
    if (r1 == r2 && my_streq(buf1, buf2)) {
	printf("Match\n");
	fflush(stdout);
    } else {
	printf("Mismatch\n");
	fflush(stdout);
	exit(1);
    }	
}

unsigned long global_arg0;
unsigned long global_arg1;
unsigned long global_arg2;

int main(int argc, char **argv) {
    unsigned long i, m;
    if (argc == 4 && argv[1][0] == 'c') {
	i = strtoul(argv[1], 0, 0);
	m = strtoul(argv[2], 0, 0);
	compare(0, i, m);
    } else if (argc == 2 && argv[1][0] == 'g') {
	compare((char *)global_arg0, global_arg1, global_arg2);
    } else if (argc == 3 && argv[1][0] == 'f') {
	FILE *fh;
        long a, b, c;
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
        while (fscanf(fh, "%lx %lx %lx",
                      &a, &b, &c) != EOF) {
            compare(0, b, c);
        }
        printf("All tests succeeded!\n");

    } else {
	fprintf(stderr, "Usage: itoa c <i> <max> | g\n");
	return 10;
    }
}
