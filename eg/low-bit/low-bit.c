#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f1(int x, unsigned y) {
    return (x << 1) | (y % 2);
}

int f2(int a, int b, int c, int d) {
    return a + b + (c & d);
}

/* Values assigned to this structure represent an adaptor. */
struct adaptor {
    int a_is_const; /* a_is_const = 1: "a" is a constant with value a_val */
    int a_val;      /* a_is_const = 0: "a" is equal to the a_val'th arg */
    int b_is_const;
    int b_val;
    int c_is_const;
    int c_val;
    int d_is_const;
    int d_val;
} the_adaptor;

/* Adapted implementation of f1 using f2. Removing the assertions
   would make this faster, but if we don't check somewhere that the
   values are sensible, the search may generate non-sensible adaptors.
   The adapter implementation and the assertions are written in a
   weird way to show that they do not need any branches, though GCC
   doesn't oblige in compiling them that way with the default settings
   I used. */
int f1_with_f2(struct adaptor *ap, int x, int y) {
    int a, b, c, d;
    /*assert(!(ap->a_is_const & ~1));*/
    /*assert(ap->a_is_const | !(ap->a_val & ~1));*/
    a = ap->a_is_const ? ap->a_val : (ap->a_val ? y : x);
    /*assert(!(ap->b_is_const & ~1));*/
    /*assert(ap->b_is_const | !(ap->b_val & ~1));*/
    b = ap->b_is_const ? ap->b_val : (ap->b_val ? y : x);
    /*assert(!(ap->c_is_const & ~1));*/
    /*assert(ap->c_is_const | !(ap->c_val & ~1));*/
    c = ap->c_is_const ? ap->c_val : (ap->c_val ? y : x);
    /*assert(!(ap->d_is_const & ~1));*/
    /*assert(ap->d_is_const | !(ap->d_val & ~1));*/
    d = ap->d_is_const ? ap->d_val : (ap->d_val ? y : x);
    return f2(a, b, c, d);
}

/* An adaptor can be represented in ASCII as a comma-seperated
   sequence of fixed-width hex strings, as in:

   0,00000000,0,00000001,1,0000face,1,ffffffff
*/

/* I wrote this parser without branches, but that feature is currently
   not needed because we don't symbolically execute this code, we just
   make its output structure symbolic. */
#define is_hex(c) (((c) - '0' < 10u) | ((c) - 'a' < 6u))
#define parse_hex(c) (((c) - '0' < 10u) ? (c) - '0' : (c) - 'a' + 10)

void parse_adaptor(struct adaptor *ap, char *s) {
    assert(strlen(s) == 43);
    assert((s[0] & ~1) == '0');
    ap->a_is_const = (s[0] & 1);
    assert(s[1] == ',');
    assert(is_hex(s[2]) & is_hex(s[3]) & is_hex(s[4]) & is_hex(s[5]) &
	   is_hex(s[6]) & is_hex(s[7]) & is_hex(s[8]) & is_hex(s[9]));
    ap->a_val = (parse_hex(s[2]) << 28) | (parse_hex(s[3]) << 24) |
	        (parse_hex(s[4]) << 20) | (parse_hex(s[5]) << 16) |
	        (parse_hex(s[6]) << 12) | (parse_hex(s[7]) <<  8) |
         	(parse_hex(s[8]) <<  4) | (parse_hex(s[9]));
    assert(s[10] == ',');

    ap->b_is_const = (s[11] & 1);
    assert(s[12] == ',');
    assert(is_hex(s[13]) & is_hex(s[14]) & is_hex(s[15]) & is_hex(s[16]) &
	   is_hex(s[17]) & is_hex(s[18]) & is_hex(s[19]) & is_hex(s[20]));
    ap->b_val = (parse_hex(s[13]) << 28) | (parse_hex(s[14]) << 24) |
	        (parse_hex(s[15]) << 20) | (parse_hex(s[16]) << 16) |
	        (parse_hex(s[17]) << 12) | (parse_hex(s[18]) <<  8) |
         	(parse_hex(s[19]) <<  4) | (parse_hex(s[20]));
    assert(s[21] == ',');

    ap->c_is_const = (s[22] & 1);
    assert(s[23] == ',');
    assert(is_hex(s[24]) & is_hex(s[25]) & is_hex(s[26]) & is_hex(s[27]) &
	   is_hex(s[28]) & is_hex(s[29]) & is_hex(s[30]) & is_hex(s[31]));
    ap->c_val = (parse_hex(s[24]) << 28) | (parse_hex(s[25]) << 24) |
	        (parse_hex(s[26]) << 20) | (parse_hex(s[27]) << 16) |
	        (parse_hex(s[28]) << 12) | (parse_hex(s[29]) <<  8) |
         	(parse_hex(s[30]) <<  4) | (parse_hex(s[31]));
    assert(s[32] == ',');

    ap->d_is_const = (s[33] & 1);
    assert(s[34] == ',');
    assert(is_hex(s[35]) & is_hex(s[36]) & is_hex(s[37]) & is_hex(s[38]) &
	   is_hex(s[39]) & is_hex(s[40]) & is_hex(s[41]) & is_hex(s[42]));
    ap->d_val = (parse_hex(s[35]) << 28) | (parse_hex(s[36]) << 24) |
	        (parse_hex(s[37]) << 20) | (parse_hex(s[38]) << 16) |
	        (parse_hex(s[39]) << 12) | (parse_hex(s[40]) <<  8) |
         	(parse_hex(s[41]) <<  4) | (parse_hex(s[42]));
}

/* The arguments to the printf()s are omitted for symbolic execution
   purposes because concretizing the values to print them would cause
   a lot of excess branching. */
void compare(int x, int y) {
    int r1, r2;
    r1 = f1(x, y);
    r2 = f1_with_f2(&the_adaptor, x, y);
    if (r1 == r2) {
	/* printf("Match, both give 0x%x\n", r1); */
	printf("Match\n");
    } else {
	/*printf("Mismatch, f1 gives 0x%x, adaptor gives 0x%x\n", r1, r2);*/
	printf("Mismatch\n");
	exit(1);
    }
}

int main(int argc, char **argv) {
    int x, y;
    char *env;
    if (argc != 2 && argc != 3) {
	fprintf(stderr, "Usage: low-bit input_file or low-bit x y\n");
	return 10;
    }
    if ((env = getenv("ADAPTOR"))) {
	parse_adaptor(&the_adaptor, env);
    }
    if (argc == 3) {
	/* Compare the adapted and target implementations on one
	   input, and print the results. If you explore this with x
	   and y symbolic, you can check whether the adaptor works for
	   all inputs. */
	x = strtoul(argv[1], 0, 0);
	y = strtoul(argv[2], 0, 0);
	compare(x, y);
    } else {
	/* Try a sequence of tests from a file. This is the mode to
	   use when you want the adaptor to be symbolic, to try to
	   synthesize an adaptor that works over a whole test suite. */
	FILE *fh;
	if (argv[1][0] == '-' && argv[1][1] == 0) {
	    fh = stdin;
	} else {
	    fh = fopen(argv[1], "r");
	    if (!fh) {
		fprintf(stderr, "Failed to open %s for reading: %s\n",
			argv[1], strerror(errno));
		return 1;
	    }
	}
	while (fscanf(fh, "%x %x", &x, &y) != EOF) {
	    compare(x, y);
	}
	printf("All tests succeeded!\n");
    }
    return 0;
}
