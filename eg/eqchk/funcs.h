#ifndef _FUNCS_H
#define _FUNCS_H

#include <stdbool.h>

int _f0(int x, unsigned y) { return (x << 1) + (y % 2);}

int _f1(bool x) { return x ? 0 : 1; }

typedef long (func)(long, long, long, long, long, long);
struct func_info {
  const char *fname;
  func *fptr;
  int num_args;
  int is_varargs;
  int is_voidret;
};

int num_funcs = 2;
struct func_info funcs[] = {
    /*    0 */ {"_f0", (func*)&_f0, 2, 0, 0},
    /*    1 */ {"_f1", (func*)&_f1, 1, 0, 0},
};
#endif
