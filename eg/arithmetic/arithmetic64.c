/* Examples of functions (with integer input and outputs) that can be made 
   equivalent by adaptors that allow trees of arithmetic operations */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define AN for N arguments to f1, currently only account for 1-2 arguments
#define A1

///// General Synthesis Examples
// f2 should be the identity function
/*// absolute value: equivalent with x = (a ^ (a >> 31)) - (a >> 31)
int f1(int a) {
    return abs(a);
}
// average of unsigned integers: equivalent with  (x & y) + ((x ^ y) >> 1)$ 
int f1(int a, int b) {
    return ((unsigned int) a + (unsigned int) b) / 2;
}*/
// turn off the rightmost 1 bit: equivalent with x = a & (a-1)
long f1(long a) {
    long i;
    
    if (a == 0) {
        return a;
    }
    
    for (i = 0; i < 8 * sizeof(a); i++) {
        if (a & ((long) 1 << i)) {
            break;
        }
    }
    return a ^= (long) 1 << i;
}
long f2(long x) {
    return x;
}

/*
long f1(long a) {
    if ((a < 0) | (a  > 127)) {
        return 0;
    }
    if (islower(a)) {
        return 1;
    } else {
        return 0;
    }
}

long f2(long x) {
    if ((x < 0) | (x  > 127)) {
        return 0;
    }
    if (isupper(x)) {
        return 1;
    } else {
        return 0;
    }
}
*/
/*
// returns 1 if (x,y) is in the square with corners at (0,0), (1,1)
long f1(long x, long y) {
    //return 0 <= x & x <= 1 & 0 <= y & y <= 1;
    return 1 <= x & x <= 2 & 1 <= y & y <= 2;
}

// returns 1 if (x,y) is in the square with corners at (2,1), (4,4)
long f2(long x, long y) {
    //return 2 <= x & x <= 4 & 1 <= y & y <= 4;
    return 4 <= x & x <= 6 & 4 <= y & y <= 7;
}
*/
/* Compare the results of the two functions; note that the second call to f1()
   will be replaced by a call to f2() by FuzzBALL */
#ifdef A1
void compare(long a) {
    long r1, r2;
    r1 = f1(a);
    r2 = f1(a);
#else
void compare(long a, long b) {
    long r1, r2;
    r1 = f1(a, b);
    r2 = f1(a, b);
#endif
    if (r1 == r2) {
        printf("Match\n");
    } else {
        printf("Mismatch\n");
        exit(1);
    }
}

long global_a, global_b;

int main(int argc, char **argv) {

    if (argc != 1 && argc != 3) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s\"\n", argv[0], argv[0]);
        return 10;
    }
    if ((argc > 1) && (strcmp(argv[1], "-f") == 0)) {
        /* Try a sequence of tests from a file. This is the mode to
           use when you want the adaptor to be symbolic, to try to
           synthesize an adaptor that works over a whole test suite. */
        long a, b;
        FILE *fh;
        fh = fopen(argv[2], "r");
        if (!fh) {
            fprintf(stderr, "Failed to open %s for reading: %s\n",
                    argv[2], strerror(errno));
            return 1;
        }
        #ifdef A1
        while (fscanf(fh, "%lx", &a) != EOF) {
            compare(a);
            //long r1 = f1(a);
            //long r2 = f2(a & (a - 1));
            //printf("%lx\t->\t%d (%lx / %lx)\n", a, r1 == r2, r1, r2);
        }
        #else
        while (fscanf(fh, "%lx %lx", &a, &b) != EOF) {
            compare(a, b);
            //printf("(%d,%d) -> %d\n", a, b, f1(a,b) == f2(3-a, 2-b));
        }
        #endif
        printf("All tests succeeded!\n");
    } else {
        /* Compare the adapted and target implementations on one
           input, and print the results. If you explore this with x
           and y symbolic, you can check whether the adaptor works for
           all inputs. */
        #ifdef A1
        //global_a = strtoul(argv[1], 0, 0);
        compare(global_a);
        #else
        //global_a = strtoul(argv[1], 0, 0);
        //global_b = strtoul(argv[2], 0, 0);
        compare(global_a, global_b);  
        #endif
    }
    return 0;
}



