#include <stdio.h>

#include <openssl/rc4.h>
#include <openssl/sha.h>

#include <openssl/ossl_typ.h>
#include <openssl/objects.h>

#include "mbedtls/config.h"
#include "mbedtls/arc4.h"

/*
gcc -shared -fPIC mhw.c -Wl,-rpath,/home/vaibhav/mbedtls-2.4.0/library -lmbedcrypto -g -lcrypto -I /home/vaibhav/mbedtls-2.4.0/include -L/home/vaibhav/mbedtls-2.4.0/library -o libhello.so
LD_PRELOAD=./libhello.so LD_LIBRARY_PATH=/home/vaibhav/mbedtls-2.4.0/library nmap -A 127.0.1.1
*/

typedef struct {
  RC4_KEY ks;                 /* working key */
} EVP_RC4_KEY;


# define data(ctx) ((EVP_RC4_KEY *)(ctx)->cipher_data)



struct my_evp_cipher_st {
  int a; int b; int c; int d; unsigned long e; 
  int (*init) (struct my_evp_cipher_ctx_st *v, const unsigned char *k, const unsigned char *iv, int enc);
  int (*do_cipher) (struct my_evp_cipher_ctx_st *v, unsigned char *o, const unsigned char *in, size_t inl);
  int (*cleanup) (void *);
  int i1;
  int (*set_asn1_parameters) (void *, void *);
  int (*get_asn1_paramters) (void *, void *);
  int (*ctrl) (void *, int, int, void *);
  void *app_data;
};

struct my_evp_cipher_ctx_st {
  const my_evp_cipher_st;
  void *engine; int encrypt; int buf_len; 
  unsigned char oiv[16]; 
  unsigned char iv[16];
  unsigned char buf[32];
  int num; void *app_data; int key_len; unsigned long flags;
  void *cipher_data;
  int final_used;
  int block_mask;
  unsigned char final[32];
};

int rc4_init_key(struct my_evp_cipher_ctx_st *ctx, const unsigned char *key,
                        const unsigned char *iv, int enc)
{
  /* printf( "--------------- my rc4_init ---------------\n"); 
  fflush(stdout); */
  RC4_set_key(&data(ctx)->ks, EVP_CIPHER_CTX_key_length(ctx), key);
  return 1;
}

int rc4_cipher(struct my_evp_cipher_ctx_st *ctx, unsigned char *out,
                      const unsigned char *in, size_t inl)
{
  /* printf( "--------------- my rc4_cipher ---------------\n"); 
  fflush(stdout); */
  RC4(&data(ctx)->ks, inl, in, out);
  return 1;
}


struct my_evp_cipher_st r4_cipher = { 
NID_rc4,
1, 16 /* EVP_RC4_KEY_SIZE */, 0,
0x8, /*EVP_CIPH_VARIABLE_LENGTH */
rc4_init_key,
rc4_cipher,
NULL,
sizeof(EVP_RC4_KEY),
NULL,
NULL,
NULL,
NULL
};


const struct my_evp_cipher_st * EVP_rc4() {
  printf( "--------------- my EVP_rc4 ---------------\n");
  return (&r4_cipher);
}


/* OpenSSL <-> mbedTLS RC4 key structure adaptors */

void mbedtls_arc4_context_to_RC4_KEY(mbedtls_arc4_context *ctx, RC4_KEY *RC4_KEY) {
  int i;
  for(i=0;i<256;i++) 
    RC4_KEY->data[i] = ctx->m[i];
  RC4_KEY->x = ctx->x;
  RC4_KEY->y = ctx->y;
}

void RC4_KEY_to_mbedtls_arc4_context(RC4_KEY *RC4_KEY, mbedtls_arc4_context *ctx) {
  int i;
  for(i=0;i<256;i++) 
    ctx->m[i] = RC4_KEY->data[i];
  ctx->x = RC4_KEY->x;
  ctx->y = RC4_KEY->y;
}

/* OpenSSL <- mbedTLS RC4 functions */

void RC4_set_key(RC4_KEY *RC4_KEY, int len, const unsigned char *data) {
  printf( "--------------- my RC4_set_key ---------------\n");
  mbedtls_arc4_context ctx;
  RC4_KEY_to_mbedtls_arc4_context(RC4_KEY, &ctx);
  mbedtls_arc4_setup(&ctx, data, len);
  mbedtls_arc4_context_to_RC4_KEY(&ctx, RC4_KEY);
}

void RC4(RC4_KEY *RC4_KEY, size_t len, const unsigned char *indata, unsigned char *outdata) {
  printf( "--------------- my RC4 ---------------\n");
  mbedtls_arc4_context ctx;
  RC4_KEY_to_mbedtls_arc4_context(RC4_KEY, &ctx);
  mbedtls_arc4_crypt(&ctx, len, indata, outdata);
  mbedtls_arc4_context_to_RC4_KEY(&ctx, RC4_KEY);
}
