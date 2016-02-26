/* Examples of functions (with double input and outputs) that can be made 
   equivalent by adaptors that allow trees of arithmetic operations */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define AN for N arguments to f1, currently only account for 1-3 arguments
#define A3

// this allows us to read input as hex values using strtoul
union Data {
    unsigned long int ul;
    double d;
};

union Data a, b, c;

// distributive law: equivalent with x=(a*b) and y=(a*c)
double f1(double a, double b, double c) {
    return a * (b + c);
}
double f2(double x, double y) {
    return x + y;
}

//double f1(double x, double y) { return x + y; }
//double f1(double x, double y) { return x - y; }
//double f1(double x, double y) { return x * y; }
//double f2(double x) { return x; }

/* Compare the results of the two functions; note that the second call to f1()
   will be replaced by a call to f2() by FuzzBALL */
#ifdef A1
void compare(double a) {
    double r1, r2;
    r1 = f1(a);
    r2 = f1(a);
#elif defined(A2)
void compare(double a, double b) {
    double r1, r2;
    r1 = f1(a, b);
    r2 = f1(a, b);
#else
void compare(double a, double b, double c) {
    double r1, r2;
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
        while (fscanf(fh, "%lx", &a.ul) != EOF) {
            compare(a.d);
        }
        #elif defined(A2)
        while (fscanf(fh, "%lx %lx", &a.ul, &b.ul) != EOF) {
            compare(a.d, b.d);
        }
        #else
        while (fscanf(fh, "%lx %lx %lx", &a.ul, &b.ul, &c.ul) != EOF) {
            compare(a.d, b.d, c.d);
        }
        #endif
        printf("All tests succeeded!\n");
    } else if (argc == 1) {
        // here FuzzBALL should be running with a, b, c symbolic
        #ifdef A1
        compare(a.d);  
        #elif defined(A2)
        compare(a.d, b.d);  
        #else
        compare(a.d, b.d, c.d);  
        #endif
    } else {
        /* Compare the adapted and target implementations on one
           input, and print the results. If you explore this with x
           and y symbolic, you can check whether the adaptor works for
           all inputs. */
        #ifdef A1
        a.ul = strtoul(argv[1], 0, 0);
        compare(a.d);  
        #elif defined(A2)
        a.ul = strtoul(argv[1], 0, 0);
        b.ul = strtoul(argv[2], 0, 0);
        compare(a.d, b.d);  
        #else
        a.ul = strtoul(argv[1], 0, 0);
        b.ul = strtoul(argv[2], 0, 0);
        c.ul = strtoul(argv[3], 0, 0);
        compare(a.d, b.d, c.d);  
        #endif
    }
    return 0;
}



