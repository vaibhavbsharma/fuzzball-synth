#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef EG2
/* Not equivalent, note signed modulo */
int f1(int x, int y) {
    return (x << 1) | (y % 2);
}

int f2(int a, int b, int c, int d) {
    return a + b + (c & d);
}
#elif defined(EG3)
/* A weird-bit-operation example that's more like synthesis, figuring
   out constants for a fast implementation of population count. One
   adaptor is 0,00000000,1,55555555,1,33333333,1,0f0f0f0f */

/* 
Final adaptor is 0,00000000,1,55555555,1,0x8001100033333333,
                 1,408244884fcf0f8f,1,0x00000000(had specified a 
		 5th argument to the inner function by mistake)
*/

int f1(unsigned x, int unused) {
    int count = 0, i;
    for (i = 0; i < 32; i++) {
	count += (x & 1);
	x >>= 1;
    }
    return count;
}

int f2(unsigned x, int c1, int c2, int c3) {
    x = x - ((x >> 1) & c1);
    x = (x & c2) + ((x >> 2) & c2);
    x = (x + (x >> 4)) & c3;
    x += x >> 8;
    x += x >> 16;
    return x & 0x3f;
}
#else
/* Equivalent with 0,00000000,0,00000000,0,00000001,1,00000001 */
int f1(int x, unsigned y){//, int z) {
    return (x << 1) + (y % 2);// + (z << 1);
}

int f2(int a, int b, int c, int d,int e){//, int f) {
    return c + d + (a & b) + e;// + f;
    //return a + b + (c & d);
}
#endif

/* The arguments to the printf()s are omitted for symbolic execution
   purposes because concretizing the values to print them would cause
   a lot of excess branching. */
void compare(int x, int y){//, int z) {
    int r1, r2;
    r1 = f1(x, y);//, z);
    r2 = f1(x, y);//, z);
    if (r1 == r2) {
	printf("Match\n");
    } else {
	printf("Mismatch\n");
	exit(1);
    }
}

int exp_args=2+1;
int main(int argc, char **argv) {
    int x, y, z;
    char *env;
    if (argc != 2 && argc != exp_args) {
	fprintf(stderr, "Usage: low-bit input_file or low-bit x y\n");
	return 10;
    }
    if (argc == exp_args) {
	/* Compare the adapted and target implementations on one
	   input, and print the results. If you explore this with x
	   and y symbolic, you can check whether the adaptor works for
	   all inputs. */
	/* Counter-example mode */
	x = strtoul(argv[1], 0, 0);
	y = strtoul(argv[2], 0, 0);
	//z = strtoul(argv[3], 0, 0);
	compare(x, y);//, z);
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
	    compare(x, y);//, z);
	}
	printf("All tests succeeded!\n");
    }
    return 0;
}
