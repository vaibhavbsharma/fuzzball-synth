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

int f1_sf(struct1 *s) {
  if(s) {
    // s->a = 1;
    //return s->a; // - s->b;
    return 3*(s->a) + 5*(s->b);
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
    // s->b = 1;
    //return s->b; // - s->a;
    return 3*(s->b) + 5*(s->a);
    //return 3*(s->c) + 5*(s->b) + 7*(s->a);
    //return s->c - s->b - s->a;
    //return s->d - s->c + s->b - s->a;
    //return 3*(s->d) + 5*(s->c) + 7*(s->b) + 11*(s->a);
    //return s->a;
  }
  return 0;
}

#define ARR_LEN 16

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

