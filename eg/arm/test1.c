#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <boost/algorithm/clamp.hpp>

//#include "popCount.h"

#define MAX_FRAG_SIZE 1024

unsigned char g_code[MAX_FRAG_SIZE];
int g_code_ind=0;

extern "C" int f1(int _x1, int _x2, int _x3, int _x4, 
		  int a0, int a1, int a2, int a3, int a4, int a5) { 
		  // int a6, int a7, int a8, int a9,
		  // int a10, int a11, int a12) {
  // unsigned char code[] = {
  //   // 0x48, 0x00, 0x1b, 0xe5,  // ldr r0, [fp, #-56]  ; 0x38
  //   // 0x4c, 0x10, 0x1b, 0xe5,  // ldr r1, [fp, #-60]  ; 0x3c
  //   // 0x50, 0x20, 0x1b, 0xe5,  // ldr r2, [fp, #-64]  ; 0x40
  //   // 0x54, 0x30, 0x1b, 0xe5,  // ldr r3, [fp, #-68]  ; 0x44
  //   0x04, 0x00, 0x9b, 0xe5,  // ldr     r0, [fp, #4]
  //   0x08, 0x10, 0x9b, 0xe5,  // ldr     r1, [fp, #8]
  //   0x0c, 0x20, 0x9b, 0xe5,  // ldr     r2, [fp, #12]
  //   0x10, 0x30, 0x9b, 0xe5,  // ldr     r3, [fp, #16]
  //   0x14, 0x40, 0x9b, 0xe5,  // ldr     r4, [fp, #20]
  //   0x18, 0x50, 0x9b, 0xe5,  // ldr     r5, [fp, #24]
  //   // 0x04, 0x40, 0x9b, 0xe5,  // ldr r4, [fp, #4]
  //   // 0x08, 0x50, 0x9b, 0xe5,  // ldr r5, [fp, #8]
  //   //0x00, 0x40, 0xa0, 0xe1,  // mov r4, r0
  //   0xff, 0x00 ,0x54 ,0xe3,  // cmp     r4, #255        ; 0xff
  //   0x02, 0x00 ,0x00 ,0x9a,  // bls     0x3d650
  //   0x00, 0x00 ,0x54 ,0xe3,  // cmp     r4, #0
  //   0xff, 0x40 ,0xa0 ,0xa3,  // movge   r4, #255        ; 0xff
  //   0x00, 0x40 ,0xa0 ,0xb3,  // movlt   r4, #0
  //   0x04, 0x00, 0xa0, 0xe1,  // mov r0, r4
  //   0x1e, 0xff, 0x2f, 0xe1,  // bx lr
  //   0x00, 0x00, 0xa0, 0xe1,   // nop
  // };
  register int p0 __asm__("r0") = a0;
  register int p1 __asm__("r1") = a1;
  register int p2 __asm__("r2") = a2;
  register int p3 __asm__("r3") = a3;
  register int p4 __asm__("r4") = a4;
  register int p5 __asm__("r5") = a5;
  return ((int (*) ())g_code)();
	
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
extern "C" int f2(int val, int lo, int hi, int a, int b, int c) {
  return clamp32(val, lo, hi);
  // return clamp32(val, 0, 255);
  // return (val < lo) ? lo : ( hi < val) ? hi : val;
}

// long wrap_f2(long a0, long a1) {
//   return f2(a0, a1);
// }

extern "C" int compare(long *r1p, long *r2p,
		       int a0, int a1, int a2, int a3, int a4, int a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);
  
  long r1 = f1(0, 0, 0, 0, a0, a1, a2, a3, a4, a5);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  printf("Starting adapted_f1\n");
  fflush(stdout);
  
  register int p0 __asm__("r4") = a4;
  register int p1 __asm__("r5") = a5;
  long r2 = f2(a0, a1, a2, a3, a4, a5);
  
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

int global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;
extern "C" void fuzz_start() {}

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 6 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  // FILE *fh_ce;
  // if (argc == 5 && argv[3][0]=='g') {
  //   fh_ce = fopen(argv[4], "r");
  //   if (!fh_ce) {
  //     fprintf(stderr, "Failed to open %s for reading: %s\n",
  // 	      argv[4], strerror(errno));
  //     return 1;
  //   }
  // }

  for(int i=0; i < MAX_FRAG_SIZE; i+=4) {
    g_code[i] = 0x00;
    g_code[i+1] = 0x00;
    g_code[i+2] = 0xa0;
    g_code[i+3] = 0xe1;   // nop
  }
  // we assume the fragment file name will be the last argument
  char *file_name = argv[argc-1]; 
  FILE *frag;
  frag = fopen(file_name, "r");
  unsigned b1, b2, b3, b4;
  int g_code_ind = 0;
  while (fscanf(frag, "%x %x %x %x",
		&b1, &b2, &b3, &b4) != EOF) {
    //printf("0x%x 0x%x 0x%x 0x%x\n", b1, b2, b3, b4);
    g_code[g_code_ind++]=b1;
    g_code[g_code_ind++]=b2;
    g_code[g_code_ind++]=b3;
    g_code[g_code_ind++]=b4;
  }
  for(int i=0; i < g_code_ind; i+=4) {
    printf("0x%x 0x%x 0x%x 0x%x\n", 
	   g_code[i], g_code[i+1], g_code[i+2], g_code[i+3]);
  }
 
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: two-funcs <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> g\n");
	fprintf(stderr, "    or two-funcs <f1num> <f2num> f <fname or ->\n");
	exit(1);
    }
    if (argv[3][0] == 'a') {
	int args[6] = {0, 0, 0, 0, 0, 0};
	long r1, r2;
	int i;
	for (i = 0; i < 6 && i + 4 < argc - 1; i++) {
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
      int a, b, c, d, e, f;
      // fscanf(fh_ce, "%lx %lx %lx %lx %lx %lx",
      //        &a, &b, &c, &d, &e, &f); 
      // printf("read ce inputs\n");
      // fflush(stdout);
      // compare(0, 0, a, b, c, d, e, f);
      compare(0, 0,
      	      global_arg0, global_arg1, global_arg2,
      	      global_arg3, global_arg4, global_arg5);
    } else if (argv[3][0] == 'f') {
	int a, b, c, d, e, f;
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
	while (fscanf(fh, "%x %x %x %x %x %x",
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