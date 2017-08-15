#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <boost/algorithm/clamp.hpp>

//#include "popCount.h"

extern "C" int f1(int x) {
  char code[] = {
    0x00, 0x40, 0xa0, 0xe1   // mov r4, r0
    , 0xff, 0x00 ,0x54 ,0xe3 // cmp     r4, #255        ; 0xff
    , 0x02, 0x00 ,0x00 ,0x9a // bls     0x3d650
    , 0x00, 0x00 ,0x54 ,0xe3 // cmp     r4, #0
    , 0xff, 0x40 ,0xa0 ,0xa3 // movge   r4, #255        ; 0xff
    , 0x00, 0x40 ,0xa0 ,0xb3 // movlt   r4, #0
    , 0x04, 0x00, 0xa0, 0xe1 // mov r0, r4
    , 0x1e, 0xff, 0x2f, 0xe1 // bx lr
  };	
  return ((int (*) (int ))code)(x);
	
  // // int clamp_component(int x)
  // if ((unsigned) x > 255)
  //   x = x < 0 ? 0 : 255;
  // return x;
}

int clamp32(int x, int lo, int hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

short clamp16(short x, short lo, short hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

// inspired from boost
extern "C" int f2(int val, int lo, int hi) {
  return clamp32(val, lo, hi);
  // return clamp32(val, 0, 255);
  // return (val < lo) ? lo : ( hi < val) ? hi : val;
}

// long wrap_f2(long a0, long a1) {
//   return f2(a0, a1);
// }

extern "C" int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);
  
  long r1 = f1(a0);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  printf("Starting adapted_f1\n");
  fflush(stdout);
  
  long r2 = f2(a0, a1, a2);
  
  printf("Completed adapted_f1\n");
  fflush(stdout);
  
  if (r1 == r2) {
    printf("Match\n");
  } else {
    printf("Mismatch\n");
  }
  if (r1p)
    *r1p = r1;
  if (r2p)
    *r2p = r2;
  return r1 == r2;
}

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;
extern "C" void fuzz_start() {}

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 5 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  FILE *fh_ce;
  if (argc == 5 && argv[3][0]=='g') {
    fh_ce = fopen(argv[4], "r");
    if (!fh_ce) {
      fprintf(stderr, "Failed to open %s for reading: %s\n",
	      argv[4], strerror(errno));
      return 1;
    }
  }
 
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
	exit(1);
    }
    if (argv[3][0] == 'a') {
	long args[6] = {0, 0, 0, 0, 0, 0};
	long r1, r2;
	int i;
	for (i = 0; i < 6 && i + 4 < argc; i++) {
	    char *s = argv[i + 4];
	    if (isdigit(s[0])) {
		args[i] = atol(s);
	    } else {
		args[i] = (long)s;
	    }
	}
	compare(&r1, &r2,
		args[0], args[1], args[2], args[3], args[4], args[5]);
	if (r1 == r2) {
	    printf("Both %ld\n", r1);
	} else {
	    printf("Difference %ld vs. %ld\n", r1, r2);
	}
    } else if (argv[3][0] == 'g') {
      long a, b, c, d, e, f;
      // fscanf(fh_ce, "%lx %lx %lx %lx %lx %lx",
      //        &a, &b, &c, &d, &e, &f); 
      // printf("read ce inputs\n");
      // fflush(stdout);
      // compare(0, 0, a, b, c, d, e, f);
      compare(0, 0,
      	      global_arg0, global_arg1, global_arg2,
      	      global_arg3, global_arg4, global_arg5);
    } else if (argv[3][0] == 'f') {
	long a, b, c, d, e, f;
        if (argv[4][0] == '-' && argv[4][1] == 0) {
            fh = stdin;
        } else {
	  //fh = fopen(argv[4], "r");
            if (!fh) {
                fprintf(stderr, "Failed to open %s for reading: %s\n",
                        argv[4], strerror(errno));
                return 1;
            }
        }
	while (fscanf(fh, "%lx %lx %lx %lx %lx %lx",
		      &a, &b, &c, &d, &e, &f) != EOF) {
	  printf("read a test\n");
	  fflush(stdout);
	  int is_eq = compare(0, 0, a, b, c, d, e, f);
	    if (!is_eq)
		exit(1);
	}
	printf("All tests succeeded!\n");
    } else {
	fprintf(stderr, "Unhandled command argument\n");
	exit(1);
    }
    return 0;
}
