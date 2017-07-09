#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

unsigned short f1(unsigned short v) {
  unsigned short c;
  for (c = 0; v; v >>= 1) {
    c += v & 1;
  }
  return c;
}

unsigned short popCountNaive_hex(unsigned short v) {
	char code[] = {
0x04, 0xb0, 0x2d, 0xe5,  
0x00, 0xb0, 0x8d, 0xe2,  
0x14, 0xd0, 0x4d, 0xe2,  
0x00, 0x30, 0xa0, 0xe1,  
0xbe, 0x30, 0x4b, 0xe1,  
0x00, 0x30, 0xa0, 0xe3,  
0xb6, 0x30, 0x4b, 0xe1,  
0x09, 0x00, 0x00, 0xea,  
0xbe, 0x30, 0x5b, 0xe1,  
0x01, 0x30, 0x03, 0xe2,  
0x03, 0x38, 0xa0, 0xe1,  
0x23, 0x28, 0xa0, 0xe1,  
0xb6, 0x30, 0x5b, 0xe1,  
0x03, 0x30, 0x82, 0xe0,  
0xb6, 0x30, 0x4b, 0xe1,  
0xbe, 0x30, 0x5b, 0xe1,  
0xa3, 0x30, 0xa0, 0xe1,  
0xbe, 0x30, 0x4b, 0xe1,  
0xbe, 0x30, 0x5b, 0xe1,  
0x00, 0x00, 0x53, 0xe3,  
0xf2, 0xff, 0xff, 0x1a,  
0xb6, 0x30, 0x5b, 0xe1,  
0x03, 0x00, 0xa0, 0xe1,  
0x00, 0xd0, 0x8b, 0xe2,  
0x00, 0x08, 0xbd, 0xe8,  
0x1e, 0xff, 0x2f, 0xe1  };
  return ((unsigned short (*) (unsigned short ))code)(v);
}

// unsigned short f2(unsigned short v) {
//   unsigned short c;
//   for (c = 0; v; v >>= 1) {
//     c += v & 1;
//   }
//   return c;
// }

unsigned short f2(unsigned short x, unsigned short f) {
  x= (x & 0x5555)+ ((x>> 1) & 0x5555); 
  x= (x & 0x3333)+ ((x>> 2) & 0x3333); 
  x= (x & 0x0077)+ ((x>> 8) & 0x0077); 
  x= (x & f)+ ((x>> 4) & f); 
  return x;
}

// long wrap_f2(long a0, long a1) {
//   return f2(a0, a1);
// }

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);

  long r1 = f1(a0);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  printf("Starting adapted_f1\n");
  fflush(stdout);
  
  long r2 = f2(a0, a1);
  
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
void fuzz_start() {}

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
