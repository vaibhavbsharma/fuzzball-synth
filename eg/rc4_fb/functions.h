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


#ifdef RC4ENC
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
#endif

#ifdef RC4SETUP

#ifdef MO_ADAPTER
int f1
#endif
#ifdef OM_ADAPTER
int f2
#endif
( mbedtls_arc4_context *ctx, const unsigned char *key, unsigned int keylen) {
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
                                // i = 0      i = 1     i = 2     i = 3
      a = m[i];                 //(a = 0)    (a = 0)    a = 0     a = 0
      j = ( j + a + key[k] ) &
	(ARR_LEN - 1);          //(j = 1)    (j = 2)    j = 3     j = 0
      m[i] = m[j];              //(m[0] = 1) (m[1] = 2) m[2] = 3  m[3] = 1
      m[j] = (unsigned char) a; //(m[1] = 0) (m[2] = 0) m[3] = 0  m[0] = 0
    }                           //m[0] = 0, m[1] = 2, m[2] = 3, m[3] = 1
  return 0;
}


#ifdef MO_ADAPTER
int f2
#endif
#ifdef OM_ADAPTER
int f1
#endif
(RC4_KEY *key, int len, const unsigned char *data)
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
  for (i = 0; i < ARR_LEN; i += 1) {
  //for (i = 0; i < 256; i += 4) {
    SK_LOOP(d, i + 0);
    //SK_LOOP(d, i + 1);
    //SK_LOOP(d, i + 2);
    //SK_LOOP(d, i + 3);
  }
  return 0;
}
#endif
