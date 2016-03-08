/* Examples of functions (with integer input and outputs) that can be made 
   equivalent by adaptors that allow trees of arithmetic operations */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define AN for N arguments to f1, currently only account for 1-4 arguments
#define A2

/*
// absolute value: equivalent with x = (a ^ (a >> 31)) - (a >> 31)
// - but the synthesized adaptor might look more like: x = (a / (a >> (-1 & 31))),
//   which is the same as (a / 1) when a is positive and (a / -1) when a is negative
//   because of how division is implemented in the arithmetic adaptor
int f1(int a) {
    return abs(a);
}
int f2(int x) {
    return x;
}
*/

// turn off the rightmost 1 bit: equivalent with x = a & (a-1)
/*int f1(int a) {
    int i;
    
    if (a == 0) {
        return a;
    }
    
    for (i = 0; i < 8 * sizeof(a); i++) {
        if (a & (1 << i)) {
            break;
        }
    }
    return a ^= (1 << i);
}
int f2(int x) {
    return x;
}*/

/*
int f1(int a, int b) {
    return a + b;
}
int f2(int x) {
    return x;
}*/

// returns 1 if (x,y) is in the square with corners at (0,0), (1,1)
int f1(int x, int y) {
    return 0 <= x && x <= 1 && 0 <= y && y <= 1;
}

// returns 1 if (x,y) is in the square with corners at (2,1), (4,4)
int f2(int x, int y) {
    return 2 <= x && x <= 4 && 1 <= y && y <= 4;
}

/*
// returns 1 if (x,y) is in the square with corners at (3,4), (5,7)
int f2(int x, int y) {
    return 3 <= x && x <= 5 && 4 <= y && y <= 7;
}

int poly(x,y,a1,a2) {
    return x*a1 + y*a2;
}
*/
/* Compare the results of the two functions; note that the second call to f1()
   will be replaced by a call to f2() by FuzzBALL */
#ifdef A1
void compare(int a) {
    int r1, r2;
    r1 = f1(a);
    r2 = f1(a);
#elif defined(A2)
void compare(int a, int b) {
    int r1, r2;
    r1 = f1(a, b);
    r2 = f1(a, b);
#elif defined(A3)
void compare(int a, int b, int c) {
    int r1, r2;
    r1 = f1(a, b, c);
    r2 = f1(a, b, c);
#else
void compare(int a, int b, int c, int d) {
    int r1, r2;
    r1 = f1(a, b, c, d);
    r2 = f1(a, b, c, d);
#endif
    if (r1 == r2) {
        printf("Match\n");
    } else {
        printf("Mismatch\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    int a, b, c, d;

    #ifdef A1
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a\"\n", argv[0], argv[0]);
        return 10;
    }
    #elif defined(A2)
    if (argc != 3) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a b\"\n", argv[0], argv[0]);
        return 10;
    }
    #elif defined(A3)
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a b c\"\n", argv[0], argv[0]);
        return 10;
    }
    #else
    if (argc != 3 && argc != 5) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a b c d\"\n", argv[0], argv[0]);
        return 10;
    }
    #endif
    if (strcmp(argv[1], "-f") == 0) {
        /* Try a sequence of tests from a file. This is the mode to
           use when you want the adaptor to be symbolic, to try to
           synthesize an adaptor that works over a whole test suite. */
        FILE *fh;
        fh = fopen(argv[2], "r");
        if (!fh) {
            fprintf(stderr, "Failed to open %s for reading: %s\n",
                    argv[2], strerror(errno));
            return 1;
        }
        #ifdef A1
        while (fscanf(fh, "%x", &a) != EOF) {
            compare(a);
        }
        #elif defined(A2)
        while (fscanf(fh, "%x %x", &a, &b) != EOF) {
            //compare(a, b);
            printf("(%d,%d) -> %d\n", a, b, f1(a,b) == f2(b, 2));
        }
        #elif defined(A3)
        while (fscanf(fh, "%x %x %x", &a, &b, &c) != EOF) {
            compare(a, b, c);
        }
        #else
        while (fscanf(fh, "%x %x %x %x", &a, &b, &c, &d) != EOF) {
            compare(a, b, c, d);
        }
        #endif
        printf("All tests succeeded!\n");
    } else {
        /* Compare the adapted and target implementations on one
           input, and print the results. If you explore this with x
           and y symbolic, you can check whether the adaptor works for
           all inputs. */
        #ifdef A1
        a = strtoul(argv[1], 0, 0);
        compare(a);  
        #elif defined(A2)
        a = strtoul(argv[1], 0, 0);
        b = strtoul(argv[2], 0, 0);
        compare(a, b);  
        #elif defined(A3)
        a = strtoul(argv[1], 0, 0);
        b = strtoul(argv[2], 0, 0);
        c = strtoul(argv[3], 0, 0);
        compare(a, b, c);  
        #else
        a = strtoul(argv[1], 0, 0);
        b = strtoul(argv[2], 0, 0);
        c = strtoul(argv[3], 0, 0);
        c = strtoul(argv[4], 0, 0);
        compare(a, b, c, d);  
        #endif
    }
    return 0;
}



