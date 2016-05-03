/* Examples of functions (with integer input and outputs) that can be made 
   equivalent by adaptors that allow trees of arithmetic operations */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define AN for N arguments to f1, currently only account for 1-4 arguments
#define A1

///// General Synthesis Examples (f2 should be the identity)
// absolute value: equivalent with x = (a ^ (a >> 31)) - (a >> 31)
/*int f1(int a) {
    return abs(a);
}
// average of unsigned integers: equivalent with  (x & y) + ((x ^ y) >> 1) 
int f1(int a, int b) {
    return ((unsigned int) a + (unsigned int) b) / 2;
}*/

// turn off the rightmost 1 bit: equivalent with x = a & (a-1)
int f1(int a) {
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
}

///// libc example
/*int f1(int a) {
    if (islower(a)) {
        return 1;
    } else {
        return 0;
    }
}
int f2(int x) {
    if (isupper(x)) {
        return 1;
    } else {
        return 0;
    }
}*/

///// boxes example
// returns 1 if (x,y) is in the square with corners at (1,1), (2,2)
/*int f1(int x, int y) {
    //return 0 <= x & x <= 1 & 0 <= y & y <= 1;
    return 1 <= x & x <= 2 & 1 <= y & y <= 2;
}
// returns 1 if (x,y) is in the square with corners at (4,4), (6,7)
int f2(int x, int y) {
    //return 2 <= x & x <= 4 & 1 <= y & y <= 4;
    return 4 <= x & x <= 6 & 4 <= y & y <= 7;
}*/

///// SKETCH examples
/*int f1(int x) {
    int i;
    if (x == -1) {
        // no rightmost 0-bit
        return 0;
    }
    for (i = 0; i < 8 * sizeof(x); i++) {
        if (!(x & (1 << i))) {
            break;
        }
    }
    return (1 << i);
}
int f2(int x, int q1, int q2) { 
    return ~(x + q1) & (x + q2); 
}*/
/*int poly(int n, int x, int q1, int q2) {
    if (n == 0) {
        return q1;
    } else {
        return x * poly(n-1, x, q1, q2) + q2;
    }
}
int f1(int x) {
    // x^4 + 6*x^3 + 11*x^2 + 6*x
    return x*x*x*x + 6*x*x*x + 11*x*x + 6*x;
}
int f2(int x, int q1, int q2) {
    return (x+1)*(x+2)*poly(2,x,q1,3);
}*/

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
            //int r1 = f1(a);
            //int r2 = f2(a, 0, 1);
            //printf("%x\t->\t%d (%x / %x)\n", a, r1 == r2, r1, r2);
        }
        #elif defined(A2)
        while (fscanf(fh, "%x %x", &a, &b) != EOF) {
            compare(a, b);
            //printf("(%d,%d) -> %d\n", a, b, f1(a,b) == f2(3-a, 2-b));
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
        //printf("%x -> %x\n", a, f1(a));
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



