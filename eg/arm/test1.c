#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <boost/algorithm/clamp.hpp>
#include "test1.h"
#include "vlc_candidates_filtered.h"
//#include "popCount.h"

#define MAX_FRAG_SIZE 1024

unsigned char g_code[MAX_FRAG_SIZE];
int g_code_ind=0;


int *saved_sp;
int ret_val;
int a12_global;
extern "C" int f1(int _x1, int _x2, int _x3, int _x4, 
		  int a0, int a1, int a2, int a3, int a4, int a5,
		  int a6, int a7, int a8, int a9,
		  int a10, int a11, int a12) {
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
  
  // https://stackoverflow.com/questions/2114163/reading-a-register-value-into-a-c-variable
  asm ("mov %0, %%sp" : "=r" (saved_sp) );
  register int p0 __asm__("r0") = a0;
  register int p1 __asm__("r1") = a1;
  register int p2 __asm__("r2") = a2;
  register int p3 __asm__("r3") = a3;
  register int p4 __asm__("r4") = a4;
  register int p5 __asm__("r5") = a5;
  register int p6 __asm__("r6") = a6;
  register int p7 __asm__("r7") = a7;
  register int p8 __asm__("r8") = a8;
  register int p9 __asm__("r9") = a9;
  register int p10 __asm__("r10") = a10;
  register int p11 __asm__("r11") = a11;
  register int p12 __asm__("r12") = a12;
  
  ret_val = ((int (*) ())g_code)();
  register int *_sp __asm__("sp") = saved_sp;
  
  return ret_val;
	
  // // int clamp_component(int x)
  // if ((unsigned) x > 255)
  //   x = x < 0 ? 0 : 255;
  // return x;
}

extern "C" int clamp32(int x, int lo, int hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

short clamp16(short x, short lo, short hi) {
    return boost::algorithm::clamp(x, lo, hi);
}

// inspired from boost
extern "C" int boost_clamp(int val, int lo, int hi, int a) {
  // R12 gets clobbered during funcs[f2num].fptr() call
  //register int p12 __asm__("r12") = a12_global;
  return clamp32(val, lo, hi);
  // return clamp32(val, 0, 255);
  // return (val < lo) ? lo : ( hi < val) ? hi : val;
}

int identity_fn(int val, int lo, int hi, int a) {
  register int p12 __asm__("r12") = a12_global;
  return val;
}

struct func_info funcs[] = {
  // must match types-no-float-1204.lst
  /* 0 */  {"identity_fn", (func*)&identity_fn, 4, 0, 0},
  /* 1 */  {"identity_fn", (func*)&identity_fn, 4, 0, 0},
  /* 2 */  {"boost_clamp", (func*)&boost_clamp, 4, 0, 0}, // placeholder
  /* 3 */  {"ref1",         (func*)&ref1,       3, 0, 0},
  /* 4 */  {"ref2",         (func*)&ref2,       3, 0, 0},
  /* 5 */  {"ref3",         (func*)&ref3,       3, 0, 0},
  /* 6 */  {"ref4",         (func*)&ref4,       3, 0, 0},
  /* 7 */  {"ref5",         (func*)&ref5,       3, 0, 0},
  /* 8 */  {"ref6",         (func*)&ref6,       3, 0, 0},
  /* 9 */  {"ref7",         (func*)&ref7,       3, 0, 0},
  /* 10 */ {"ref8",         (func*)&ref8,       3, 0, 0},
  /* 11 */ {"ref9",         (func*)&ref9,       3, 0, 0},
  /* 12 */ {"ref10",        (func*)&ref10,      3, 0, 0},
  /* 13 */ {"ref11",        (func*)&ref11,      3, 0, 0},
  /* 14 */ {"ref12",        (func*)&ref12,      3, 0, 0},
  /* 15 */ {"ref13",        (func*)&ref13,    3, 0, 0},
  /* 16 */ {"ref14",        (func*)&ref14,    3, 0, 0},
  /* 17 */ {"ref15",        (func*)&ref15,    3, 0, 0},
  /* 18 */ {"ref16",        (func*)&ref16,    3, 0, 0},
  /* 19 */ {"ref17",        (func*)&ref17,    3, 0, 0},
  /* 20 */ {"ref18",        (func*)&ref18,    3, 0, 0},
  /* 21 */ {"ref19",        (func*)&ref19,    3, 0, 0},
  /* 22 */ {"ref20",        (func*)&ref20,    3, 0, 0},
  /* 23 */ {"ref21",        (func*)&ref21,    3, 0, 0},
  /* 24 */ {"ref22",        (func*)&ref22,    3, 0, 0},
  /* 25 */ {"ref23",        (func*)&ref23,    3, 0, 0},
  /* 26 */ {"ref24",        (func*)&ref24,    3, 0, 0},
  /* 27 */ {"ref25",        (func*)&ref25,    3, 0, 0},
};
int f2num; 

extern "C" int f2(int a, int b, int c, int d,
		  int e, int f, int g, int h,
		  int i, int j, int k, int l,
		  int m) {
  asm ("mov %0, %%r4" : "=r" (e) );
  asm ("mov %0, %%r5" : "=r" (f) );
  asm ("mov %0, %%r6" : "=r" (g) );
  asm ("mov %0, %%r7" : "=r" (h) );
  asm ("mov %0, %%r8" : "=r" (i) );
  asm ("mov %0, %%r9" : "=r" (j) );
  asm ("mov %0, %%r10" : "=r" (k) );
  asm ("mov %0, %%r11" : "=r" (l) );
  asm ("mov %0, %%r12" : "=r" (m) );
  return (funcs[f2num].fptr)(a, b, c, d, e, f, g, h, i, j, k, l, m);
}

extern "C" int compare(long *r1p, long *r2p,
		       int a0, int a1, int a2, int a3, int a4, int a5,
		       int a6, int a7, int a8, int a9, int a10, int a11, 
		       int a12) {
  
  // printf("Starting f1\n");  
  // fflush(stdout);
 
  long r1 = f1(0, 0, 0, 0, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  // printf("Starting adapted_f1\n");
  // fflush(stdout);
  
  register int p4 __asm__("r4") = a4;
  register int p5 __asm__("r5") = a5;
  register int p6 __asm__("r6") = a6;
  register int p7 __asm__("r7") = a7;
  register int p8 __asm__("r8") = a8;
  register int p9 __asm__("r9") = a9;
  register int p10 __asm__("r10") = a10;
  register int p11 __asm__("r11") = a11;
  register int p12 __asm__("r12") = a12;
  a12_global = a12;
  long r2 = f2(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
  
  // printf("Completed adapted_f1\n");
  // fflush(stdout);
  
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
  global_arg3, global_arg4, global_arg5,
  global_arg6, global_arg7, global_arg8,
  global_arg9, global_arg10, global_arg11,
  global_arg12;

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
  // g_code[g_code_ind++] = 0x1c;
  // g_code[g_code_ind++] = 0x60;
  // g_code[g_code_ind++] = 0x9b;
  // g_code[g_code_ind++] = 0xe5;

  // g_code[g_code_ind++] = 0x20;
  // g_code[g_code_ind++] = 0x70;
  // g_code[g_code_ind++] = 0x9b;
  // g_code[g_code_ind++] = 0xe5;

  // g_code[g_code_ind++] = 0x24;
  // g_code[g_code_ind++] = 0x80;
  // g_code[g_code_ind++] = 0x9b;
  // g_code[g_code_ind++] = 0xe5;

  // g_code[g_code_ind++] = 0x28;
  // g_code[g_code_ind++] = 0x90;
  // g_code[g_code_ind++] = 0x9b;
  // g_code[g_code_ind++] = 0xe5;

  // g_code[g_code_ind++] = 0x2c;
  // g_code[g_code_ind++] = 0xa0;
  // g_code[g_code_ind++] = 0x9b;
  // g_code[g_code_ind++] = 0xe5;

  while (fscanf(frag, "%x %x %x %x",
		&b1, &b2, &b3, &b4) != EOF) {
    //printf("0x%x 0x%x 0x%x 0x%x\n", b1, b2, b3, b4);
    g_code[g_code_ind++]=b1;
    g_code[g_code_ind++]=b2;
    g_code[g_code_ind++]=b3;
    g_code[g_code_ind++]=b4;
  }
  // for(int i=0; i < g_code_ind; i+=4) {
  //   printf("0x%x 0x%x 0x%x 0x%x\n", 
	//    g_code[i], g_code[i+1], g_code[i+2], g_code[i+3]);
  // }
 
  fuzz_start();

    if (argc < 4) {
	fprintf(stderr, "Usage: test_arm <f1num> <f2num> a [0-6 args]\n");
	fprintf(stderr, "    or test_arm <f1num> <f2num> g <fragment-file-name>\n");
	fprintf(stderr, "    or test_arm <f1num> <f2num> f <tests file name or -> <fragment-file-name>\n");
	exit(1);
    }
    f2num = atoi(argv[2]);
    if (f2num < 1 || f2num > 27) {
	fprintf(stderr, "Error: f2num %d out of range\n", f2num);
    }
    if (argv[3][0] == 'a') {
      int args[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
		args[0], args[1], args[2], args[3], args[4], args[5],
		args[6], args[7], args[8], args[9], args[10], args[11],
		args[12]);
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
      	      global_arg3, global_arg4, global_arg5,
      	      global_arg6, global_arg7, global_arg8,
      	      global_arg9, global_arg10, global_arg11,
	      global_arg12);
    } else if (argv[3][0] == 'f') {
      int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12;
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
	while (fscanf(fh, "%x %x %x %x %x %x %x %x %x %x %x %x %x",
		      &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7,
		      &a8, &a9, &a10, &a11, &a12) != EOF) {
	  // printf("read a test\n");
	  // fflush(stdout);
	  int is_eq = compare(0, 0, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
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
