#include <math.h>

bool mask_has_flag(unsigned int mask, unsigned int flag)
{
    return ((mask & flag) != 0);
}

bool is_context_filtered(int context, int CONTEXT_FM, int CONTEXT_WPS)
{
    return (context == CONTEXT_FM || context == CONTEXT_WPS);
}

bool is_action_normal(int action, int ACTION_REDRAW, int SYS_EVENT)
{
    return (action != ACTION_REDRAW && (action & SYS_EVENT) == 0);
}

int mul_s16_s16(short int op1, short int op2)
{
    return (int)(op1 * op2);
}

unsigned int mul_u16_u16(unsigned short int op1, unsigned short int op2)
{
    return (unsigned int)(op1 * op2);
}

bool rec_format_ok(int rec_format, int REC_NUM_FORMATS)
{
    return (unsigned)rec_format < REC_NUM_FORMATS;
}

unsigned addDispl( unsigned addr, unsigned char displ ) {
    return (unsigned)((int)addr + (int)(signed char)displ);
}

int get_margin(int width, int full_w) {
    return ((full_w - width) / 2);
}

int clamp_component_bits(int x, int bits)
{
    if ((unsigned)x > (1u << bits) - 1)
        x = x < 0 ? 0 : (1 << bits) - 1;
    return x;
}

int clip_sample16(int sample)
{
    if ((short int)sample != sample)
        sample = 0x7fff ^ (sample >> 31);
    return sample;
}

unsigned int myswap32(unsigned int val)
{
  const unsigned char* v = (const unsigned char*)&val;

  return ((unsigned int)v[0]<<24) | ((unsigned int)v[1]<<16) | ((unsigned int)v[2]<<8) | v[3];
}
unsigned int swapu32(unsigned int n)
{
    return (    ((n & 0xffU) << 24) |
                ((n & 0xff00U) << 8) |
                ((n & 0xff0000U) >> 8) |
                ((n & 0xff000000U) >> 24) );
}

int bound_motion_vector (const int vector, const int f_code)
{
    return ((int)vector << (27 - f_code)) >> (27 - f_code);
}

bool is_valid_cell(int x, int y, int GRID_W, int GRID_H) {
    return (x >= 0 && x < GRID_W
            && y >= 0 && y < GRID_H);
}

int SCALE(int x)
{
    return x == 1 ? x : x >> 1;
}

int clamp(int val, int min, int max)
{
    if (val < min)
        val = min;
    else if (val > max)
        val = max;
    return val;
}

unsigned int longent_char_next(unsigned int i)
{
    switch (i += 2)
    {
    case 26: i -= 1; /* return 28 */
    case 11: i += 3; /* return 14 */
    }

    return i < 32 ? i : 0;
}

int ep_index(int n, bool dir)
{
    return (n << 1) | dir;
}

bool epidx_dir(int idx)
{
    return idx & 1;
}

int epidx_n(int idx)
{
    return idx >> 1;
}

unsigned int encode_16_to_18(unsigned int a)
{
    return ((a & 0xff) << 1) | (((a >> 8) & 0xff) << 10);
}

unsigned int decode_18_to_16(unsigned int a)
{
    return ((a >> 1) & 0xff) | ((a >> 2) & 0xff00);
}

void *noncached(void *p)
{
    return (void *)(((unsigned long)p) & 0xffff);
}

unsigned int ad_s32(int a, int b)
{
    return (a >= b) ? (a - b) : (b - a);
}

int imx233_depth_3d_val2phys(int val)
{
    if(val == 0)
        return 0; /* 0dB */
    else
        return 15 * (val + 1); /* 3dB + 1.5dB per step */
}

bool my_isspace(char c)
{
    return (c == ' ') || (c == '\t') || (c == '\n');
}

bool my_isdigit(char c)
{
    return (c >= '0') && (c <= '9');
}

bool my_isxdigit(char c)
{
    return ((c >= '0') && (c <= '9'))
        || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'));
}

unsigned int swap_odd_even32_hw(unsigned int value)
    /*
     * result[31..24],[15.. 8] = value[23..16],[ 7.. 0]
     * result[23..16],[ 7.. 0] = value[31..24],[15.. 8]
     */
{
    unsigned int t = value & 0xff00ff00;
    return (t >> 8) | ((t ^ value) << 8);
}

int fifo_mod(int n, int SERIAL_BUF_SIZE)
{
    return (n >= SERIAL_BUF_SIZE) ? n - SERIAL_BUF_SIZE : n;
}

int ilog(register unsigned int v){
  register int ret=0;
  while(v){
    ret++;
    v>>=1;
  }
  return(ret);
}

int MULT32(int x, int y) {
  return (x >> 9) * y;  /* y preshifted >>23 */
}

int MULT31(int x, int y) {
  return (x >> 8) * y;  /* y preshifted >>23 */
}

int MULT31_SHIFT15(int x, int y) {
  return (x >> 6) * y;  /* y preshifted >>9 */
}

int get_pulses(int i)
{
   return i<8 ? i : (8 + (i&7)) << ((i>>3)-1);
}

int fixp_pow2(int x, int i)
{
  if (i < 0)
    return (x >> -i);
  else
    return x << i;              /* no check for overflow */
}

int fixp_mult_su(int a, int b)
{
    int hb = (a >> 16) * b;      
    unsigned int lb = (a & 0xffff) * b;      

    return hb + (lb >> 16) + ((lb & 0x8000) >> 15);      
}

int av_clip(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}
int mask_addr( int addr, int mask )
{
	#ifdef check
		check( addr <= mask );
	#endif
	return addr & mask;
}

inline int HIGHBITS(int c, int b)
{
	return c >> b;
}

inline int LOWBITS(int c, int b)
{
	return c & ((1<<b)-1);
}

inline int EXPAND_BITS(int x, int s, int d)
{
	return x << (d-s);
}

unsigned int rate_adjust(int x, int rate, int clk)
{
	unsigned int tmp = (long long)x * clk / 72 / rate;
//	assert (tmp <= 4294967295U);
	return tmp;
}


unsigned char get_bit(unsigned long val, unsigned char b)
{
    return (unsigned char) ((val >> b) & 1);
}

long long MULH(int a, int b){
    return ((long long)(a) * (long long)(b))>>32;
}

unsigned long long UMULH(unsigned a, unsigned b){
    return ((unsigned long long)(a) * (unsigned long long)(b))>>32;
}


int av_clip_c(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}

unsigned char av_clip_uint8_c(int a)
{
    if (a&(~0xFF)) return (-a)>>31;
    else           return a;
}

char av_clip_int8_c(int a)
{
    if ((a+0x80) & ~0xFF) return (a>>31) ^ 0x7F;
    else                  return a;
}

unsigned short int av_clip_uint16_c(int a)
{
    if (a&(~0xFFFF)) return (-a)>>31;
    else             return a;
}

short int av_clip_int16_c(int a)
{
    if ((a+0x8000) & ~0xFFFF) return (a>>31) ^ 0x7FFF;
    else                      return a;
}

#  define UINT64_C(c)	c ## ULL

long long av_clipl_int32_c(long long a)
{
    if ((a+0x80000000u) & ~UINT64_C(0xFFFFFFFF)) return (a>>63) ^ 0x7FFFFFFF;
    else                                         return a;
}

int av_ceil_log2_c(int x)
{
    //return av_log2((x - 1) << 1);
    return (int) log2((x - 1) << 1);
}

int SATURATE(int a, int b)
{
   if (a>b)
      a=b;
   if (a<-b)
      a = -b;
   return a;
}

int fixmulshift(int x, int y, int shamt)
{
    long temp;
    temp = x;
    temp *= y;

    temp >>= shamt;

    return (int)temp;
}

int fixmul31(int x, int y)
{
    long temp;
    temp = x;
    temp *= y;

    temp >>= 31;

    return (int)temp;
}

int fixmul24(int x, int y)
{
    long temp;
    temp = x;
    temp *= y;

    temp >>= 24;

    return (int)temp;
}

int fixmul16(int x, int y)
{
    long temp;
    temp = x;
    temp *= y;

    temp >>= 16;

    return (int)temp;
}

unsigned short int swap16_hw(unsigned short int value)
    /*
      result[15..8] = value[ 7..0];
      result[ 7..0] = value[15..8];
    */
{
    return (value >> 8) | (value << 8);
}

static inline unsigned int swaw32_hw(unsigned int value)
{
    /*
      result[31..16] = value[15.. 0];
      result[15.. 0] = value[31..16];
    */
#ifdef __thumb__
    asm (
        "ror %0, %1"
        : "+l"(value) : "l"(16));
    return value;
#else
    unsigned int retval;
    asm (
        "mov %0, %1, ror #16"
        : "=r"(retval) : "r"(value));
    return retval;
#endif

}

unsigned short int swap16(unsigned short int value)
{
    return (value >> 8) | (value << 8);
}

unsigned int swap32(unsigned int value)
{
    unsigned int hi = swap16(value >> 16);
    unsigned int lo = swap16(value & 0xffff);
    return (lo << 16) | hi;
}

unsigned short int av_bswap16(unsigned short int x)
{
    x= (x>>8) | (x<<8);
    return x;
}

unsigned int av_bswap32(unsigned int x)
{
    x= ((x<<8)&0xFF00FF00) | ((x>>8)&0x00FF00FF);
    x= (x>>16) | (x<<16);
    return x;
}

int main() { 
  return 0; 
}
