#ifndef _RC4ENC_FUNCTIONS_H
#define _RC4ENC_FUNCTIONS_H
#ifdef RC4ENC
#ifdef OM_ADAPTER
int f2
#endif
#ifdef MO_ADAPTER
int f1
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
//  ret+=output[0];
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

//  return ret;
}

#ifdef OM_ADAPTER
int f1
#endif
#ifdef MO_ADAPTER
int f2
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
//  ret+=outdata[0];
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

//  return ret;
}
#endif

#endif
