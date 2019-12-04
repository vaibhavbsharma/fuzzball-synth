#ifndef _FUNCS_H
#define _FUNCS_H

#include <stdbool.h>

int _f1(int x, unsigned y) { return (x << 1) + (y % 2);}

int _f2(int a, int b, int c, int d) { return c + d + (a & b); }

int sketch_f1( int x, short y ) {
    return 2*(x + (y*3)) + 7;
}

int sketch_f2( int a, int b, short c, char d ) {
    return c + d + (a * 6) + b; 
}

typedef long (func)(long, long, long, long, long, long);
struct func_info {
  const char *fname;
  func *fptr;
  int num_args;
  int is_varargs;
  int is_voidret;
};

int num_funcs = 3;
struct func_info funcs[] = {
    /*    0 */ {"_f1", (func*)&_f1, 2, 0, 0},
    /*    1 */ {"_f2", (func*)&_f2, 4, 0, 0},
    /*    2 */ {"sketch_f1", (func*)&sketch_f1, 2, 0, 0},
    /*    3 */ {"sketch_f2", (func*)&sketch_f2, 4, 0, 0},
};
#endif
