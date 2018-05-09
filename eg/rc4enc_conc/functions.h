#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <openssl/rc4.h>
#include "mbedtls/config.h"
#include "mbedtls/arc4.h"

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

#define ARR_LEN 256
#define CRYPT_LEN 1
unsigned char g_input[CRYPT_LEN]="1";
// int f1( mbedtls_arc4_context *ctx, size_t length, const unsigned char *input,
//                 unsigned char *output )
long f2(mbedtls_arc4_context *ctx)
{
  size_t length=CRYPT_LEN;
  unsigned char *input=g_input;
  unsigned char output[CRYPT_LEN];
  long ret=0;
  int x, y, a, b;
  size_t i;
  unsigned char *m;
  
  x = ctx->x;
  y = ctx->y;
  m = ctx->m;
  
  for( i = 0; i < length; i++ )
    {
      x = ( x + 1 ) & (ARR_LEN - 1); a = m[x];
      y = ( y + a ) & (ARR_LEN - 1); b = m[y];
      
      m[x] = (unsigned char) b;
      m[y] = (unsigned char) a;
      
      output[i] = (unsigned char)
	( input[i] ^ m[ ( a + b ) & (ARR_LEN - 1) ] );
    }
  
  ctx->x = x;
  ctx->y = y;
  
  //return( 0 );
  ret+=output[0];
  // ret=ret<<8;

  // ret+=output[1];
  // ret=ret<<8;

  // ret+=output[2];
  // ret=ret<<8;

  // ret+=output[3];
  // ret=ret<<8;

  // ret+=output[4];
  // ret=ret<<8;

  // ret+=output[5];
  // ret=ret<<8;

  // ret+=output[6];
  // ret=ret<<8;

  // ret+=output[7];
  // ret=ret<<8;

  return ret;
}

// int f2(RC4_KEY *key, size_t len, const unsigned char *indata,
//          unsigned char *outdata)
long f1(RC4_KEY *key)
{
  size_t len = CRYPT_LEN;
  unsigned char *indata = g_input;
  unsigned char outdata_buf[CRYPT_LEN];
  unsigned char *outdata=outdata_buf;
  long ret=0;
  //register RC4_INT *d;
  //register RC4_INT x, y, tx, ty;
  RC4_INT *d;
  RC4_INT x, y, tx, ty;
  size_t i;
  
  x = key->x;
  y = key->y;
  d = key->data;
  
#define LOOP(in,out)		\
  x=((x+1)&(ARR_LEN - 1));		\
  tx=d[x];			\
  y=(tx+y)&(ARR_LEN - 1);		\
  d[x]=ty=d[y];			\
  d[y]=tx;					\
  (out) = d[(tx+ty)&(ARR_LEN - 1)]^ (in);
  
  i = len >> 3;
  if (i) {
    for (;;) {
      LOOP(indata[0], outdata[0]);
      LOOP(indata[1], outdata[1]);
      LOOP(indata[2], outdata[2]);
      LOOP(indata[3], outdata[3]);
      LOOP(indata[4], outdata[4]);
      LOOP(indata[5], outdata[5]);
      LOOP(indata[6], outdata[6]);
      LOOP(indata[7], outdata[7]);
      indata += 8;
      outdata += 8;
      if (--i == 0)
	break;
    }
  }
  i = len & 0x07;
  if (i) {
    for (;;) {
      LOOP(indata[0], outdata[0]);
      if (--i == 0)
	break;
      LOOP(indata[1], outdata[1]);
      if (--i == 0)
	break;
      LOOP(indata[2], outdata[2]);
      if (--i == 0)
	break;
      LOOP(indata[3], outdata[3]);
      if (--i == 0)
	break;
      LOOP(indata[4], outdata[4]);
      if (--i == 0)
	break;
      LOOP(indata[5], outdata[5]);
      if (--i == 0)
	break;
      LOOP(indata[6], outdata[6]);
      if (--i == 0)
	break;
    }
  }
  key->x = x;
  key->y = y;
  //return 0;
  ret+=outdata[0];
  // ret=ret<<8;
  // 
  // ret+=outdata[1];
  // ret=ret<<8;
  // 
  // ret+=outdata[2];
  // ret=ret<<8;

  // ret+=outdata[3];
  // ret=ret<<8;

  // ret+=outdata[4];
  // ret=ret<<8;

  // ret+=outdata[5];
  // ret=ret<<8;

  // ret+=outdata[6];
  // ret=ret<<8;

  // ret+=outdata[7];
  // ret=ret<<8;

  return ret;
}
#endif
