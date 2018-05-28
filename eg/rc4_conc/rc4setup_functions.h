#ifndef _RC4SETUP_FUNCTIONS_H
#define _RC4SETUP_FUNCTIONS_H
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
#endif
