/*
 gcc -static bn.c -Wl,-rpath,/export/scratch/vaibhav/opt_openssl/lib -g -o bn -lcrypto -I /export/scratch/vaibhav/mbedtls-install/include/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

#include <openssl/dh.h>
#include <openssl/bn.h>

#include "mbedtls/config.h"
#include "mbedtls/bignum.h"


long str_ce_addr;
//struct bignum_st {
typedef struct {
    BN_ULONG *d;                /* Pointer to an array of 'BN_BITS2' bit
                                 * chunks. */
    int top;                    /* Index of last used d +1. */
    /* The next are internal book keeping for bn_expand. */
    int dmax;                   /* Size of the d array. */
    int neg;                    /* one if the number is negative */
    int flags;
} s1;

typedef struct {
    int s;              /*!<  integer sign      */
    size_t n;           /*!<  total # of limbs  */
    mbedtls_mpi_uint *p;          /*!<  pointer to limbs  */
} s2;

long f1_s(s1 *s, char *hex_str) {
  s->d = 0x2; //to be mapped to s2->p
  s->top = 1; //to be ignored
  s->dmax = 1; //to be mapped to s2->n
  s->neg = 0; //to be mapped to s2->s = 1
  s->flags = 0; //to be ignored
  return 0;
}

long f2_s(s2 *s, int radix, char *hex_str) {
  //s->s = 0; //= 1; this is what it should really be
  s->s = 1; 
  s->n = 1;
  s->p = 0x2;
  return 0;
}

long f1_old(BIGNUM *h) {//, int len) {
  int len=1;
  int str_len = (len & 0x1) ? 32 : 31;
  char hex_str[40];
  for(int i=0;i<str_len;i++) 
    hex_str[i]='f';
  hex_str[str_len-2]='f';
  hex_str[str_len-1]='\0';
  
  //BIGNUM *h = BN_new();
  BN_hex2bn(&h, hex_str);
  //BN_mul(h, h, h, ctx);
  //printf("h->dmax = %d\n", h->dmax);
  //for(int i=0;i<h->dmax; i++) {
  //  printf("h->d[%d] = %d\n", i, h->d[i]);
  //}
  return h->d[0];
}

int my_OPENSSL_hexchar2int(unsigned char c)
{
#ifdef CHARSET_EBCDIC
    c = os_toebcdic[c];
#endif

    switch (c) {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
          return 4;
    case '5':
          return 5;
    case '6':
          return 6;
    case '7':
          return 7;
    case '8':
          return 8;
    case '9':
          return 9;
    case 'a': case 'A':
          return 0x0A;
    case 'b': case 'B':
          return 0x0B;
    case 'c': case 'C':
          return 0x0C;
    case 'd': case 'D':
          return 0x0D;
    case 'e': case 'E':
          return 0x0E;
    case 'f': case 'F':
          return 0x0F;
    }
    return -1;
}

long my_BN_hex2bn(BIGNUM *ret, const char *a) {
    // char a1[40];
    // int str_len=32;
    // for(int i=0;i<str_len;i++) 
    //   a1[i]='f';
    // a1[str_len-2]='f';
    // a1[str_len-1]='\0';
    //char *a=(char *) str_ce_addr;
    //BIGNUM *ret = NULL;
    BN_ULONG l = 0;
    int neg = 0, h, i, m, j, k, c;
    int num;
    char prod;
    if ((a == NULL) || (*a == '\0'))
        return (0);

    if (*a == '-') {
        neg = 1;
        a++;
    }

    for (i = 0; i <= (INT_MAX/4) && isxdigit((unsigned char)a[i]); i++)
        continue;

    //printf("1:i=%d\n",i);
    //fflush(stdout);
    // if (i == 0 || i > INT_MAX/4)
    //     goto err;

    //printf("2:i=%d\n",i);
    //fflush(stdout);
    num = i + neg;
    //if (bn == NULL)
    //    return (num);

    //printf("3:i=%d\n",i);
    //fflush(stdout);
    /* a is the start of the hex digits, and it is 'i' long */
    //if (*bn == NULL) {
    //    if ((ret = BN_new()) == NULL)
    //        return (0);
    //} else {
    //    ret = *bn;
        //BN_zero(ret);
    //}
    //printf("i=%d\n",i);
    /* i is the number of hex digits */
    prod = i*4;
    // if(prod < (i*4)) printf("Overflow!\n");
    // else printf("No overflow\n");
    // fflush(stdout);
    //printf("prod = %d\n", prod);
    if (bn_expand(ret, prod) == NULL)
    //if (bn_expand(ret, i*4) == NULL)
        goto err;

    j = i;                      /* least significant 'hex' */
    m = 0;
    h = 0;
    while (j > 0) {
        m = ((BN_BYTES * 2) <= j) ? (BN_BYTES * 2) : j;
        l = 0;
        for (;;) {
            c = a[j - m];
            k = my_OPENSSL_hexchar2int(c);
            if (k < 0)
                k = 0;          /* paranoia */
            l = (l << 4) | k;


            if (--m <= 0) {
              // if(ret->dmax <= h) printf("overflow dmax=%d h=%d\n", ret->dmax, h);
              // else printf("no overflow dmax=%d h=%d\n", ret->dmax, h);
	            ret->d[h++] = l;
	            break;
            }
            //OPENSSL_assert(((ret)->dmax) > h);
        }
        j -= (BN_BYTES * 2);
    }
    ret->top = h;
    bn_correct_top(ret);
    ret->neg = neg;

    //*bn = ret;
    //bn_check_top(ret);
    return (num);
    // return (0);
 err:
    //if (*bn == NULL)
    //    BN_free(ret);
    return (0);
}

//int BN_hex2bn(BIGNUM **bn, const char *a)
long f1(BIGNUM *ret, const char *a) {
  my_BN_hex2bn(ret, a);
  return 0;
}

long f2(mbedtls_mpi *h, int radix, const char *hex_str) {
  //int radix=16;
  // int str_len = 32 ;
  // char hex_str[40];
  // for(int i=0;i<str_len;i++) 
  //   hex_str[i]='f';
  // hex_str[str_len-2]='f';
  // hex_str[str_len-1]='\0';
  
  //mbedtls_mpi X;
  //mbedtls_mpi_init(&X);
  
  //mbedtls_mpi_grow(&X, h->dmax);
  //for(int i=0;i<h->dmax; i++)
    //X.p[i]=h->d[i];
  //char *hex_str = (char *) str_ce_addr;
  
  mbedtls_mpi_read_string(h, radix, hex_str);
  //mbedtls_mpi_mul_mpi(&X, &X, &X);
  //printf("X.n = %d\n", X.n);
  //for(int i=0;i<X.n; i++) {
  //  printf("X.p[%d] = %d\n", i, X.p[i]);
  //}
  // return h->p[0];
  return 0;
}


long wrap_f2(long a0, long a1, long a2) {
  return f2(a0, a1, a2);
}

int compare(long *r1p, long *r2p,
	    long a0, long a1, long a2, long a3, long a4, long a5) {
  
  printf("Starting f1\n");  
  fflush(stdout);

  BIGNUM *h = BN_new();
  
  long r1 = f1(a0, a1);
  
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

long global_arg0, global_arg1, global_arg2,
    global_arg3, global_arg4, global_arg5;


void fuzz_start() {}

int main(int argc, char **argv) { 
  FILE *fh;
  if (argc == 5 && argv[3][0]=='f') {
    fh = fopen(argv[4], "r");
  }
  FILE *fh_ce;
  long a, b, c, d, e, f;
  if (argc == 5 && argv[3][0]=='g') {
    fh_ce = fopen(argv[4], "r");
    if (!fh_ce) {
      fprintf(stderr, "Failed to open %s for reading: %s\n",
  	      argv[4], strerror(errno));
      return 1;
    }
    fscanf(fh_ce, "%lx %lx %lx %lx %lx %lx",
	   &a, &b, &c, &d, &e, &f); 
    printf("read ce inputs\n");
    fflush(stdout);
  }

  str_ce_addr = b;

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
      compare(0, 0, a, b, c, d, e, f);
      //compare(0, 0,
      //	      a, global_arg1, global_arg2,
      //	      //global_arg0, global_arg1, global_arg2,
      //	      global_arg3, global_arg4, global_arg5);
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
    str_ce_addr = b;
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
