#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "funcs.h"


int f1num, f2num;
bool void_flag=false;

long f1(long a, long b, long c, long d, long e, long f) {
    return (funcs[f1num].fptr)(a, b, c, d, e, f);
}

long f2(long a, long b, long c, long d, long e, long f) {
  return (funcs[f2num].fptr)(a, b, c, d, e, f);
}

long wrap_f2(long a, long b, long c, long d, long e, long f) {
    return f2(a, b, c, d, e, f);
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  printf("Starting f1\n");  
  fflush(stdout);
  long r1 = f1(a0, a1, a2, a3, a4, a5);
  printf("Completed f1\n");
  fflush(stdout);
  printf("Starting f2\n");
  fflush(stdout);
  long r2 = wrap_f2(a0, a1, a2, a3, a4, a5);
  printf("Completed f2\n");
  fflush(stdout);
  if (r1==r2) {
    printf("Match\n");
  } else {
    printf("Mismatch\n");
  }
  fflush(stdout);
  return r1 == r2;
}

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;

void fuzz_start() {}

void print_usage_and_exit() {
  fprintf(stderr, "Usage: two-funcs <fnum between 0 and %d> \n", num_funcs);
  exit(1);
}

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 5 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
	exit(1);
    }
    f1num = atoi(argv[1]);
    if (f1num < 0 || f1num >= sizeof(funcs)/sizeof(struct func_info)) {
	fprintf(stderr, "Error: f1num %d out of range\n", f1num);
    }
    f2num = atoi(argv[2]);
    if (f2num < 0 || f2num >= sizeof(funcs)/sizeof(struct func_info)) {
	fprintf(stderr, "Error: f2num %d out of range\n", f2num);
    }
    if((funcs[f1num].is_voidret==1) || (funcs[f2num].is_voidret==1) ) {
      void_flag=true;
    }
    if (argv[3][0] == 'g') {
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
