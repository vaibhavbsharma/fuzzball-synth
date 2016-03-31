/* Examples of functions (with float input and outputs) that can be made 
   equivalent by adaptors that allow trees of arithmetic operations */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define AN for N arguments to f1, currently only account for 1-3 arguments
#define A2

// this allows us to read input as hex values using strtoul
union Data {
    int i;
    float f;
};

union Data a, b, c;

// distributive law: equivalent with x=(a*b) and y=(a*c)
/*float f1(float a, float b, float c) {
    return a * (b + c);
}
float f2(float x, float y) {
    return x + y;
}*/

float f1(float x, float y) { return x + y; }
//float f1(float x, float y) { return x - y; }
//float f1(float x, float y) { return x * y; }
float f2(float x) { return x; }

/* Compare the results of the two functions; note that the second call to f1()
   will be replaced by a call to f2() by FuzzBALL */
#ifdef A1
void compare(float a) {
    float r1, r2;
    r1 = f1(a);
    r2 = f1(a);
#elif defined(A2)
void compare(float a, float b) {
    float r1, r2;
    r1 = f1(a, b);
    r2 = f1(a, b);
#else
void compare(float a, float b, float c) {
    float r1, r2;
    r1 = f1(a, b, c);
    r2 = f1(a, b, c);
#endif
    if ((r1 == r2) || ((r1 != r1) && (r2 != r2))) {
        printf("Match\n");
    } else {
        printf("Mismatch\n");
        exit(1);
    }
}

int main(int argc, char **argv) {

    #ifdef A1
    if (argc != 1 && argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a\"\n", argv[0], argv[0]);
        return 10;
    }
    #elif defined(A2)
    if (argc != 1 && argc != 3) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a b\"\n", argv[0], argv[0]);
        return 10;
    }
    #else
    if (argc != 1 && argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: \"%s -f <input_file>\" or \"%s a b c\"\n", argv[0], argv[0]);
        return 10;
    }
    #endif
    
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
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
        while (fscanf(fh, "%x", &a.i) != EOF) {
            compare(a.f);
        }
        #elif defined(A2)
        while (fscanf(fh, "%x %x", &a.i, &b.i) != EOF) {
            compare(a.f, b.f);
        }
        #else
        while (fscanf(fh, "%x %x %x", &a.i, &b.i, &c.i) != EOF) {
            compare(a.f, b.f, c.f);
        }
        #endif
        printf("All tests succeeded!\n");
    } else if (argc == 1) {
        // here FuzzBALL should be running with a, b, c symbolic
        #ifdef A1
        compare(a.f);  
        #elif defined(A2)
        compare(a.f, b.f);  
        #else
        compare(a.f, b.f, c.f);  
        #endif
    } else {
        /* Compare the adapted and target implementations on one
           input, and print the results. If you explore this with x
           and y symbolic, you can check whether the adaptor works for
           all inputs. */
        #ifdef A1
        a.i = strtoul(argv[1], 0, 0);
        compare(a.f);  
        #elif defined(A2)
        a.i = strtoul(argv[1], 0, 0);
        b.i = strtoul(argv[2], 0, 0);
        compare(a.f, b.f);  
        #else
        a.i = strtoul(argv[1], 0, 0);
        b.i = strtoul(argv[2], 0, 0);
        c.i = strtoul(argv[3], 0, 0);
        compare(a.f, b.f, c.f);  
        #endif
    }
    return 0;
}



