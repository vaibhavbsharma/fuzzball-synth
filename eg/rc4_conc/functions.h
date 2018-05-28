#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <openssl/rc4.h>
#include "mbedtls/config.h"
#include "mbedtls/arc4.h"
#include "rc4enc_functions.h"
#include "rc4setup_functions.h"

/* target structure i want to achieve

typedef struct rc4_key_st {
  unsigned int x, y;
  unsigned int data[256];
} RC4_KEY;

*/

/* inner structure i want to achieve

typedef struct
{
    int x;                      //!< permutation index
    int y;                      //!< permutation index
    unsigned char m[256];       //!< permutation table
} mbedtls_arc4_context;

*/

unsigned char f0(mbedtls_arc4_context *ctx) {
    return ctx->m[255];
}

typedef struct {
    char c1;
    long l;
    short s1;
    char c2;
    int i;
    long long ll;
} all_sizes_struct;

void _f0(all_sizes_struct *s) {
    s->s1=42;
    s->c1='0';
    s->c2='0';
    s->i=1;
    s->l=2;
    s->ll=3;
}

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

int f1_simple_function(struct1 *s) {
  if(s) {
    // s->a = 1;
    return s->a; // - s->b;
//    return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
//    return 3*(s->a) + 5*(s->b) + 7*(s->c);
    //return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
  }
  return 0;
}

int f2_simple_function(struct2 *s) {
  if(s) {
    // s->b = 1;
    return s->b; // - s->a;
//    return 3*(s->b) + 5*(s->a);
//    return 3*(s->c) + 5*(s->b) + 7*(s->a);
    //return s->c - s->b - s->a;
    //return s->d - s->c + s->b - s->a;
    //return 3*(s->d) + 5*(s->c) + 7*(s->b) + 11*(s->a);
//    return s->b;
  }
  return 0;
}

#endif
