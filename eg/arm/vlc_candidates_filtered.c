//small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: 
int IntegerCmp(int i0, int i1)
{
    return i0 < i1 ? -1 : i0 > i1 ? 1 : 0;
}

//small function from boost
extern "C" int boost_clamp(int val, int lo, int hi) {
  return clamp32(val, lo, hi);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
int clip_uint8_vlc( int a, int c_val1, int c_val2 )
{
    if( a&(~c_val1) ) return (-a)>>c_val2;
    else           return a;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/avi.c: 
int __EVEN( int i )
{
    return (i & 1) ? i + 1 : i;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/blend.cpp: 
unsigned div255(unsigned v)
{
    /* It is exact for 8 bits, and has a max error of 1 for 9 and 10 bits
     * while respecting full opacity/transparency */
    return ((v >> 8) + v + 1) >> 8;
    //return v / 255;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/langfromtelx.c: 
uint8_t bytereverse( int n )
{
    n = (((n >> 1) & 0x55) | ((n << 1) & 0xaa));
    n = (((n >> 2) & 0x33) | ((n << 2) & 0xcc));
    n = (((n >> 4) & 0x0f) | ((n << 4) & 0xf0));
    return n;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/compat/posix_memalign.c: 
int check_align (size_t align)
{
    for (size_t i = sizeof (void *); i != 0; i *= 2)
        if (align == i)
            return 0;
    return EINVAL;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/mmal.c: 
uint32_t align(uint32_t x, uint32_t y) {
    uint32_t mod = x % y;
    if (mod == 0)
        return x;
    else
        return x + y - mod;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: 
bool dirac_isEOS( uint32_t u_parse_code, uint32_t constant_val ) { 
  return constant_val == u_parse_code; 
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: 
bool dirac_PictureNbeforeM( uint32_t u_n, uint32_t u_m, uint32_t constant_val )
{
    /* specified as: u_n occurs before u_m if:
     *   (u_m - u_n) mod (1<<32) < D */
    return (uint32_t)(u_m - u_n) < (1u<<constant_val);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/events.c: 
bool isMouseEvent( int type, int constant_val1, int constant_val2)
{
    return type >= constant_val1 &&
           type <= constant_val2;
}


//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/image.c: 
bool IsPnmBlank(int v, int c_val1, int c_val2, int c_val3, int c_val4)
{
    return v == c_val1 || v == c_val2 || v == c_val3 || v == c_val4;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: 
bool AACCookieChkLen( int i_length, int i_size, int i_offset )
{
    return ( i_offset + i_length <= i_size );
}

//small function copy 
bool AACCookieChkLen1( int i_length, int i_size, int i_offset )
{
    return ( i_offset + i_length < i_size );
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ps.h: 
int ps_id_to_tk( unsigned i_id )
{
    if( i_id <= 0xff )
        return i_id - 0xc0;
    else if( (i_id & 0xff00) == 0xbd00 )
        return 256-0xC0 + (i_id & 0xff);
    else if( (i_id & 0xff00) == 0xfd00 )
        return 512-0xc0 + (i_id & 0xff);
    else
        return 768-0xc0 + (i_id & 0x07);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtp.c: 
uint32_t rtp_compute_ts( unsigned i_clock_rate, int64_t i_pts )
{
    /* This is an overflow-proof way of doing:
     * return i_pts * (int64_t)i_clock_rate / CLOCK_FREQ;
     *
     * NOTE: this plays nice with offsets because the (equivalent)
     * calculations are linear. */
    lldiv_t q = lldiv(i_pts, CLOCK_FREQ);
    return q.quot * (int64_t)i_clock_rate
          + q.rem * (int64_t)i_clock_rate / CLOCK_FREQ;
}


//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/visual/fft.c: 
int reverseBits(unsigned int initial)
{
    unsigned int reversed = 0, loop;
    for(loop = 0; loop < 32; loop++) {
        reversed <<= 1;
        reversed += (initial & 1);
        initial >>= 1;
    }
    return reversed;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: 
int metaToColumn( int _meta )
{
    int meta = 1, column = 0;
    while( meta != 0x0800)
    {
        if ( meta & _meta )
            break;
        meta <<= 1;
        column++;
    }
    return column;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/bezier.cpp: 
int Bezier::power( int x, int n )
{
    return n <= 0 ? 1 : x * power( x, n - 1 );
}

//small function from not sure where 
int MOD(int a, int b) {
    return ( ( a % b ) + b ) % b; 
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/colorthres.c:                        
static bool IsSimilar( int u, int v,
                       int refu, int refv, int reflength,
                       int i_satthres, int i_simthres )
{
    int length = sqrt(u * u + v * v);
    int diffu = refu * length - u * reflength;
    int diffv = refv * length - v * reflength;
    int64_t difflen2 = diffu * diffu + diffv * diffv;
    int64_t thres = length * reflength;
    thres *= thres;
    return length > i_satthres && (difflen2 * i_simthres < thres);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/deinterlace/algo_x.c: 
int median( int a, int b, int c )
{
    int min = a, max =a;
    if( b < min )
        min = b;
    else
        max = b;
    if( c < min )
        min = c;
    else if( c > max )
        max = c;
    return a + b + c - min - max;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/webservices/json.c: 
unsigned char hex_value (unsigned char c)
{
   if (c >= 'A' && c <= 'F')
      return (c - 'A') + 10;

   if (c >= 'a' && c <= 'f')
      return (c - 'a') + 10;

   if (c >= '0' && c <= '9')
      return c - '0';

   return 0xFF;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/macosx/prefs.m: - 
bool isSubCategoryGeneral(int category, int c_val1, int c_val2, int c_val3, int c_val4, int c_val5, int c_val6, int c_val7, int c_val8, int c_val9) 
{
    if (category == c_val1 ||
          category == c_val2 ||
          category == c_val3 ||
          category == c_val4 ||
          category == c_val5 ||
          category == c_val6 ||
          category == c_val7 ||
          category == c_val8 ||
          category == c_val9) {
        return true;
    }
    return false;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipstream.c: 
bool isAllowedChar( char c )
{
    return ( c >= 'a' && c <= 'z' )
           || ( c >= 'A' && c <= 'Z' )
           || ( c >= '0' && c <= '9' )
           || ( c == ':' ) || ( c == '/' )
           || ( c == '\\' ) || ( c == '.' )
           || ( c == ' ' ) || ( c == '_' );
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/scan.c: 
int scan_service_type( int service_type, int case1, int ret1,
		       int case2, int ret2,
		       int case3, int ret3,
		       int case4, int ret4, 
		       int ret5)
{
    switch( service_type )
    {
    case case1: return ret1; break;
    case case2: return ret2; break;
    case case3: return ret3; break;
    case case4: return ret4; break;
    default:   return ret5; break;
    }
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpeg/ts.c: 
uint32_t GetDescriptorLength24b( int i_length )
{
    uint32_t i_l1, i_l2, i_l3;

    i_l1 = i_length&0x7f;
    i_l2 = ( i_length >> 7 )&0x7f;
    i_l3 = ( i_length >> 14 )&0x7f;

    return( 0x808000 | ( i_l3 << 16 ) | ( i_l2 << 8 ) | i_l1 );
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cdg.c: 
uint32_t RenderRGB( int r, int g, int b )
{
    return ( r << CDG_COLOR_R_SHIFT ) | ( g << CDG_COLOR_G_SHIFT ) | ( b << CDG_COLOR_B_SHIFT );
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/qsv.c: 
int qsv_timestamp_to_mtime(int32 mfx_ts, int c_val1, int c_Val2)
{
    return mfx_ts / c_val1 * c_val2;
}


//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.h: 
int32_t fixmul32(int32_t x, int32_t y, int c_val)
{
    int64_t temp;
    temp = x;
    temp *= y;

    temp >>= c_val;

    return (int32_t)temp;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: 
int32_t Fixed32From64(int64_t x)
{
  return x & 0xFFFFFFFF;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: 
int64_t Fixed32To64(int32_t x)
{
  return (int64_t)x;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: 
int32_t fixdiv32(int32_t x, int32_t y, int c_val)
{
    int64_t temp;
    if(x == 0)
        return 0;
    if(y == 0)
        return 0x7fffffff;
    temp = x;
    temp <<= c_val;
    return (int32_t)(temp / y);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: 
int64_t fixdiv64(int64_t x, int64_t y, int c_val)
{
    int64_t temp;

    if(x == 0)
        return 0;
    if(y == 0)
        return 0x07ffffffffffffffLL;
    temp = x;
    temp <<= c_val;
    return (int64_t)(temp / y);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/qcom.c: 
size_t tile_pos(size_t x, size_t y, size_t w, size_t h)
{
    size_t flim = x + (y & ~1) * w;
    if (y & 1) {
        flim += (x & ~3) + 2;
    } else if ((h & 1) == 0 || y != (h - 1)) {
        flim += (x + 2) & ~3;
    }
    return flim;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/es_format.c: 
int BinaryLog( uint32_t i )
{
    int i_log = 0;
    if( i == 0 ) return -31337;
    if( i & 0xffff0000 ) i_log += 16;
    if( i & 0xff00ff00 ) i_log += 8;
    if( i & 0xf0f0f0f0 ) i_log += 4;
    if( i & 0xcccccccc ) i_log += 2;
    if( i & 0xaaaaaaaa ) i_log += 1;
    return i_log;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/es_format.c: 
int transform_FromBasicOps( unsigned angle, bool hflip, 
  int ret1, int ret2, int ret3, int ret4, int ret5, int ret6, int ret7, int ret8)
{
    switch ( angle )
    {
        case 90:
            return hflip ? ret1 : ret2;
        case 180:
            return hflip ? ret3 : ret4;
        case 270:
            return hflip ? ret5 : ret6;
        default:
            return hflip ? ret7: ret8;
    }
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
unsigned clz (unsigned x)
{
    unsigned i = sizeof (x) * 8;
    while (x)
    {
        x >>= 1;
        i--;
    }
    return i;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
unsigned ctz (unsigned x)
{
    unsigned i = sizeof (x) * 8;
    while (x)
    {
        x <<= 1;
        i--;
    }
    return i;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
unsigned popcount (unsigned x)
{
    unsigned count = 0;
    while (x)
    {
        count += x & 1;
        x = x >> 1;
    }
    return count;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
unsigned parity (unsigned x)
{
    for (unsigned i = 4 * sizeof (x); i > 0; i /= 2)
        x ^= x >> i;
    return x & 1;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
uint16_t bswap16 (uint16_t x)
{
    return (x << 8) | (x >> 8);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: 
uint32_t bswap32 (uint32_t x)
{
    return ((x & 0x000000FF) << 24)
         | ((x & 0x0000FF00) <<  8)
         | ((x & 0x00FF0000) >>  8)
         | ((x & 0xFF000000) >> 24);
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/lib/libvlc_internal.h: 
int from_mtime(int t, int c_val1, int c_val2)
{
    return (time + c_val1)/ c_val2;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/rawdv.h: 
uint16_t dv_audio_12to16( uint16_t sample )
{
    uint16_t shift, result;

    sample = (sample < 0x800) ? sample : sample | 0xf000;
    shift = (sample & 0xf00) >> 8;

    if (shift < 0x2 || shift > 0xd) {
        result = sample;
    } else if (shift < 0x8) {
        shift--;
        result = (sample - (256 * shift)) << shift;
    } else {
        shift = 0xe - shift;
        result = ((sample + ((256 * shift) + 1)) << shift) - 1;
    }

    return result;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/opengl.c: 
int GetAlignedSize(unsigned size)
{
    /* Return the smallest larger or equal power of 2 */
    unsigned align = 1 << (8 * sizeof (unsigned) - clz(size));
    return ((align >> 1) == size) ? size : align;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/scan.c: 
uint32_t decode_BCD( uint32_t input )
{
    uint32_t output = 0;
    for( short index=28; index >= 0 ; index -= 4 )
    {
        output *= 10;
        output += ((input >> index) & 0x0f);
    };
    return output;
}

//small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/decklink.cpp: 
int clip(int a, int c_val1, int c_val2)
{
    if      (a < c_val1) return c_val1;
    else if (a > c_val2) return c_val2;
    else               return a;
}
