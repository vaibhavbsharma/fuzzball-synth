/*
 gcc -static struct_adaptor.c -Wl,-rpath,/export/scratch/vaibhav/opt_openssl/lib -g -o struct_adaptor -lcrypto -I /export/scratch/vaibhav/mbedtls-install/include/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include <openssl/rc4.h>
#include "mbedtls/config.h"
#include "mbedtls/arc4.h"

/* OpenSSL key structure

typedef struct rc4_key_st {
  unsigned int x, y;
  unsigned int data[256];
} RC4_KEY;

*/

/* mbedTLS key structure

typedef struct
{
    int x;                      //!< permutation index 
    int y;                      //!< permutation index
    unsigned char m[256];       //!< permutation table
} mbedtls_arc4_context;

*/

typedef struct _s1 {
  int a;
  int b;
  int c;
  int d;
} struct1;

typedef struct _s2 {
  int a;
  int b;
  int c;
  int d;
} struct2;

int f1_sf(struct1 *s) {
  if(s) {
    s->a = 1;
    //s->b = 2;
    //s->c = 3;
    //return s->a - s->b;
    //return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    //return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
  }
  return 0;
}

int f2_sf(struct2 *s) {
  if(s) {
    //s->c = 1;
    //s->a = 2;
    s->b = 1;
    //return s->b - s->a;
    //return 3*(s->b) + 5*(s->a);
    //return 3*(s->c) + 5*(s->b) + 7*(s->a);
    //return s->c - s->b - s->a;
    //return s->d - s->c + s->b - s->a;
    //return 3*(s->d) + 5*(s->c) + 7*(s->b) + 11*(s->a);
    //return s->a;
  }
  return 0;
}

#define ARR_LEN 256

//void mbedtls_arc4_setup( mbedtls_arc4_context *ctx, const unsigned char *key,
//                 unsigned int keylen ) {
int f1( mbedtls_arc4_context *ctx, const unsigned char *key, unsigned int keylen) {
  //const unsigned char key[1]="1";
  //unsigned int keylen = 1;
  int i, j, a;
  unsigned int k;
  unsigned char *m;
  
  ctx->x = 0;
  ctx->y = 0;
  m = ctx->m;
  
  //for( i = 0; i < 256; i++ )
  for( i = 0; i < ARR_LEN; i++ )
    m[i] = (unsigned char) i;

  j = k = 0;

  //for( i = 0; i < 256; i++, k++ )
  for( i = 0; i < ARR_LEN; i++, k++ )
    {
      if( k >= keylen ) k = 0;

      a = m[i];
      j = ( j + a + key[k] ) & (ARR_LEN - 1);
      m[i] = m[j];
      m[j] = (unsigned char) a;
    }
  return 0;
}

int f2(RC4_KEY *key, int len, const unsigned char *data)
//void RC4_set_key(RC4_KEY *key, int len, const unsigned char *data)
{
  //int len = 1;
  //const unsigned char data[1] = "1";
  register RC4_INT tmp;
  register int id1, id2;
  register RC4_INT *d;
  unsigned int i;

  d = &(key->data[0]);
  key->x = 0;
  key->y = 0;
  id1 = id2 = 0;

#define SK_LOOP(d,n) { \
                tmp=d[(n)]; \
                id2 = (data[id1] + tmp + id2) & (ARR_LEN - 1);	\
                if (++id1 == len) id1=0; \
                d[(n)]=d[id2]; \
                d[id2]=tmp; }

  //for (i = 0; i < 256; i++)
  for (i = 0; i < ARR_LEN; i++)
    d[i] = i;
  for (i = 0; i < ARR_LEN; i += 4) {
  //for (i = 0; i < 256; i += 4) {
    SK_LOOP(d, i + 0);
    SK_LOOP(d, i + 1);
    SK_LOOP(d, i + 2);
    SK_LOOP(d, i + 3);
  }
  return 0;
}

long wrap_f2(long a0, long a1, long a2) {
  return f2(a0, a1, a2);
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);

  long r1 = f1(a0, a1, a2);
  
  printf("Completed f1\n");
  fflush(stdout);
  
  printf("Starting adapted_f1\n");
  fflush(stdout);
  
  long r2 = wrap_f2(a0, a1, a2); 
  
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
      fscanf(fh_ce, "%lx %lx %lx %lx %lx %lx",
             &a, &b, &c, &d, &e, &f); 
      printf("read ce inputs\n");
      fflush(stdout);
      compare(0, 0, a, b, c, d, e, f);
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
