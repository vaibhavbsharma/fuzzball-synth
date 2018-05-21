#include <openssl/rc4.h>
#include "mbedtls/config.h"
#include "mbedtls/arc4.h"

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

//f1(c = 1, input[0] = 1) = 0
//f2(c = 0, input[0] = 0) =
// arg adapter is (0,1) (0,1) (0,0) (0,3)

//#define ARR_LEN 2
int f1_sf(struct1 *s, int len, unsigned char *input, unsigned char *output) {
    // s->a = 1;
    //return s->a; // - s->b;
    //return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    //return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
    int i = 0;
    int x, y, a, b;
    unsigned int *m = &(s->c);
    for (i = 0; i < len; i++) {
      x = ( x + 1 ) & (ARR_LEN - 1);
      a = s->a;
      y = ( y + a ) & (ARR_LEN - 1);
      b = s->b;
      s->a = (unsigned char) b;
      s->b = (unsigned char) a;
      
      // output[i] = (unsigned char)
      //  ( input[i] ^ m[ ( a + b ) & (ARR_LEN - 1) ] );
      // output[i] = input[i] + 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
      output[i] = input[i] ^ (s->c);
    }
    s->a=a;
    s->b=b;
    return 0;
    //return output[0];
}

int f2_sf(struct2 *s, int len, unsigned char *input, unsigned char *output) {
    // s->a = 1;
    //return s->a; // - s->b;
    //return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    //return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
    int i = 0;
    int x, y, a, b;
    unsigned int *m = &(s->c);
    for (i = 0; i < len; i++) {
      x = ( x + 1 ) & (ARR_LEN - 1);
      a = s->a;
      y = ( y + a ) & (ARR_LEN - 1);
      b = s->b;
      s->a = (unsigned char) b;
      s->b = (unsigned char) a;
      
      // output[i] = (unsigned char)
      //  ( input[i] ^ m[ ( a + b ) & (ARR_LEN - 1) ] );
      // output[i] = input[i] + 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
      output[i] = input[i] ^ (s->c);
    }
    s->a=a;
    s->b=b;
    return 0;
    //return output[0];
}

#ifdef MO_ADAPTER
long f1
#endif
#ifdef OM_ADAPTER
long f2
#endif
( mbedtls_arc4_context *ctx, size_t length, const unsigned char *input,
                unsigned char *output )
{
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
  
  return( 0 );
  //ret+=output[0];
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

  //return ret;
}

#ifdef MO_ADAPTER
long f2
#endif
#ifdef OM_ADAPTER
long f1
#endif
(RC4_KEY *key, size_t len, const unsigned char *indata,
         unsigned char *outdata)
{
  long ret=0;
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
  return 0;
  //ret+=outdata[0];
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

  //return ret;
}
