small function in /export/scratch/vaibhav/vlc-2.2.6/compat/strsep.c: char *strsep( char **ppsz_string, const char *psz_delimiters )
{
    char *psz_string = *ppsz_string;
    if( !psz_string )
        return NULL;

    char *p = strpbrk( psz_string, psz_delimiters );
    if( !p )
    {
        *ppsz_string = NULL;
        return psz_string;
    }
    *p++ = '\0';

    *ppsz_string = p;
    return psz_string;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/strtof.c: float strtof (const char *str, char **end)
{
    return strtod (str, end);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/strnlen.c: size_t strnlen (const char *str, size_t max)
{
    const char *end = memchr (str, 0, max);
    return end ? (size_t)(end - str) : max;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/atof.c: double atof (const char *str)
{
    return strtod (str, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/lldiv.c: lldiv_t lldiv (long long num, long long denom)
{
    lldiv_t d = { num / denom, num % demon, };
    return d;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/posix_memalign.c: static int check_align (size_t align)
{
    for (size_t i = sizeof (void *); i != 0; i *= 2)
        if (align == i)
            return 0;
    return EINVAL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/posix_memalign.c: int posix_memalign (void **ptr, size_t align, size_t size)
{
    if (check_align (align))
        return EINVAL;

    int saved_errno = errno;
    void *p = memalign (align, size);
    if (p == NULL)
    {
        errno = saved_errno;
        return ENOMEM;
    }

    *ptr = p;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/posix_memalign.c: int posix_memalign (void **ptr, size_t align, size_t size)
{
    if (check_align (align))
        return EINVAL;

    *ptr = NULL;
    return size ? ENOMEM : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/dirfd.c: int (dirfd) (DIR *dir)
{
#ifdef dirfd
    return dirfd (dir);
#else
    (void) dir;
# ifdef ENOTSUP
    errno = ENOTSUP;
# endif
    return -1;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/flockfile.c: int ftrylockfile (FILE *stream)
{
    flockfile (stream); /* Move along people, there is nothing to see here. */
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/flockfile.c: int getc_unlocked (FILE *stream)
{
    return _getc_nolock (stream);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/flockfile.c: int putc_unlocked (int c, FILE *stream)
{
    return _putc_nolock (c, stream);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/flockfile.c: int putchar_unlocked (int c)
{
    return putc_unlocked (c, stdout);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/strlcpy.c: size_t strlcpy (char *tgt, const char *src, size_t bufsize)
{
    size_t length;

    for (length = 1; (length < bufsize) && *src; length++)
        *tgt++ = *src++;

    if (bufsize)
        *tgt = '\0';

    while (*src++)
        length++;

    return length - 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/fsync.c: int fsync (int fd)
{
#if defined(_WIN32)
    /* WinCE can use FlushFileBuffers() but it operates on file handles */
    return _commit (fd);
#else
# warning fsync() not implemented!
    return 0;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/getdelim.c:                  FILE *restrict stream)
{
    return getdelim (lineptr, n, '\n', stream);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/setenv.c: int unsetenv (const char *name)
{
    return setenv (name, "", 1);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/inet_pton.c: int inet_pton (int af, const char *src, void *dst)
{
    unsigned char *b = dst;

    switch (af)
    {
        case AF_INET:
            return sscanf (src, "%hhu.%hhu.%hhu.%hhu",
                           b + 0, b + 1, b + 2, b + 3) == 4;
    }
    errno = EAFNOSUPPORT;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/strdup.c: char *strdup (const char *str)
{
    size_t len = strlen (str) + 1;
    char *res = malloc (len);
    if (res)
        memcpy (res, str, len);
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/localtime_r.c: struct tm *localtime_r (const time_t *timep, struct tm *result)
{
    struct tm *s = localtime (timep);
    if (s == NULL)
        return NULL;

    *result = *s;
    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/atoll.c: long long atoll (const char *str)
{
    return strtoll (str, NULL, 10);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/test/libvlc/libvlc_additions.h: static void* media_list_add_file_path(libvlc_instance_t *vlc, libvlc_media_list_t *ml, const char * file_path)
{
    libvlc_media_t *md = libvlc_media_new_location (vlc, file_path);
    libvlc_media_list_add_media (ml, md);
    libvlc_media_release (md);
    return md;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/test/src/config/chain.c: int main( void )
{
    log( "Testing config chain escaping\n" );
    test_config_StringEscape();
    log( "Testing config chain un-escaping\n" );
    test_config_StringUnEscape();
    log( "Testing config_ChainCreate()\n" );
    test_config_ChainCreate();
    log( "Testing config_ChainDuplicate()\n" );
    test_config_ChainDuplicate();

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/test/src/misc/variables.c: int main( void )
{
    libvlc_instance_t *p_vlc;

    test_init();

    log( "Testing the core variables\n" );
    p_vlc = libvlc_new( test_defaults_nargs, test_defaults_args );
    assert( p_vlc != NULL );

    test_variables( p_vlc );

    libvlc_release( p_vlc );

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static dirac_block_encap_t *dirac_NewBlockEncap( block_t **pp_block )
{
    dirac_block_encap_t *p_dbe = calloc( 1, sizeof( *p_dbe ) );
    if( p_dbe ) dirac_AddBlockEncap( pp_block, p_dbe );
    return p_dbe;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: 
static bool dirac_isEOS( uint8_t u_parse_code ) { return 0x10 == u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static bool dirac_isSeqHdr( uint8_t u_parse_code ) { return 0 == u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static bool dirac_isPicture( uint8_t u_parse_code ) { return 0x08 & u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static int dirac_numRefs( uint8_t u_parse_code ) { return 0x3 & u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static inline bool dirac_PictureNbeforeM( uint32_t u_n, uint32_t u_m )
{
    /* specified as: u_n occurs before u_m if:
     *   (u_m - u_n) mod (1<<32) < D */
    return (uint32_t)(u_m - u_n) < (1u<<31);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static uint32_t dirac_uint( bs_t *p_bs )
{
    uint32_t u_count = 0, u_value = 0;
    while( !bs_eof( p_bs ) && !bs_read( p_bs, 1 ) )
    {
        u_count++;
        u_value <<= 1;
        u_value |= bs_read( p_bs, 1 );
    }
    return (1 << u_count) - 1 + u_value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static int dirac_bool( bs_t *p_bs )
{
    return bs_read( p_bs, 1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/h264.c: static int PacketizeValidate( void *p_private, block_t *p_au )
{
    VLC_UNUSED(p_private);
    VLC_UNUSED(p_au);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/h264.c: static inline int bs_read_se( bs_t *s )
{
    int val = bs_read_ue( s );

    return val&0x01 ? (val+1)/2 : -(val/2);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/hevc.c: static int PacketizeValidate( void *p_private, block_t *p_au )
{
    VLC_UNUSED(p_private);
    VLC_UNUSED(p_au);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/mpeg4audio.c: static int Mpeg4ReadAudioObjectType(bs_t *s)
{
    int i_type = bs_read(s, 5);
    if (i_type == 31)
        i_type = 32 + bs_read(s, 6);
    return i_type;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/mpeg4audio.c: static int LatmGetValue(bs_t *s)
{
    int i_bytes = bs_read(s, 2);
    int v = 0;
    for (int i = 0; i < i_bytes; i++)
        v = (v << 8) + bs_read(s, 8);

    return v;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/vc1.c: static block_t *PacketizeParse( void *p_private, bool *pb_ts_used, block_t *p_block )
{
    decoder_t *p_dec = p_private;

    return ParseIDU( p_dec, pb_ts_used, p_block );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_chroma/swscale.c: int OpenScaler( vlc_object_t *p_this )
{
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/mmal.c: 
static inline uint32_t align(uint32_t x, uint32_t y) {
    uint32_t mod = x % y;
    if (mod == 0)
        return x;
    else
        return x + y - mod;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/events.c: static inline bool isMouseEvent( WPARAM type )
{
    return type >= WM_MOUSEFIRST &&
           type <= WM_MOUSELAST;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/events.c: static inline bool isKeyEvent( WPARAM type )
{
    return type >= WM_KEYFIRST &&
           type <= WM_KEYLAST;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/events.c: static HCURSOR EmptyCursor( HINSTANCE instance )
{
    const int cw = GetSystemMetrics(SM_CXCURSOR);
    const int ch = GetSystemMetrics(SM_CYCURSOR);

    HCURSOR cursor = NULL;
    uint8_t *and = malloc(cw * ch);
    uint8_t *xor = malloc(cw * ch);
    if( and && xor )
    {
        memset(and, 0xff, cw * ch );
        memset(xor, 0x00, cw * ch );
        cursor = CreateCursor( instance, 0, 0, cw, ch, and, xor);
    }
    free( and );
    free( xor );

    return cursor;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/events.c: static HWND GetDesktopHandle(vout_display_t *vd)
{
    /* Find Program Manager */
    HWND hwnd = FindWindow( _T("Progman"), NULL );
    if( hwnd ) hwnd = FindWindowEx( hwnd, NULL, _T("SHELLDLL_DefView"), NULL );
    if( hwnd ) hwnd = FindWindowEx( hwnd, NULL, _T("SysListView32"), NULL );
    if( hwnd )
        return hwnd;

    msg_Dbg( vd, "Couldn't find desktop icon window,. Trying the hard way." );

    EnumWindows( enumWindowsProc, (LPARAM)&hwnd );
    return hwnd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/glwin32.c: static void *OurGetProcAddress(vlc_gl_t *gl, const char *name)
{
    VLC_UNUSED(gl);
    return wglGetProcAddress(name);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/wingdi.c: static int Control(vout_display_t *vd, int query, va_list args)
{
    switch (query) {
    case VOUT_DISPLAY_RESET_PICTURES:
        assert(0);
        return VLC_EGENERIC;
    default:
        return CommonControl(vd, query, args);
    }

}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/directx.c:                                       LPDIRECTDRAWSURFACE2 surface)
{
    if (DirectXLockSurface(front_surface, surface, NULL))
        return VLC_EGENERIC;

    DirectXUnlockSurface(front_surface, surface);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR\n"
    "{\n"
    "    return saturate(tex2D(screen, screenCoords.xy));\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR\n"
    "{\n"
    "    float4 color = tex2D(screen, screenCoords.xy);\n"
    "    color.r = 1.0 - color.r;\n"
    "    color.g = 1.0 - color.g;\n"
    "    color.b = 1.0 - color.b;\n"
    "    return color;\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D(screen, screenCoords.xy);\n"
    "    float gray = 0.2989 * color.r + 0.5870 * color.g + 0.1140 * color.b;\n"
    "    color.r = color.g = color.b = gray;\n"
    "    return color;\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 rgb_to_yuv601(float4 RGB)\n"
    "{\n"
    "    float Kr = 0.299;\n"
    "    float Kg = 0.587;\n"
    "    float Kb = 0.114;\n"
    "    float Y = Kr*RGB.r + Kg*RGB.g + Kb*RGB.b;\n"
    "    float V = (RGB.r-Y)/(1-Kr);\n"
    "    float U = (RGB.b-Y)/(1-Kb);\n"
    "    return float4(Y,U,V,1);\n"
    "}\n"

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 yuv709_to_rgb(float4 YUV)\n"
    "{\n"
    "    float Kr = 0.2125;\n"
    "    float Kg = 0.7154;\n"
    "    float Kb = 0.0721;\n"
    "    float Y = YUV.x;\n"
    "    float U = YUV.y;\n"
    "    float V = YUV.z;\n"
    "    float R = Y + V*(1-Kr);\n"
    "    float G = Y - U*(1-Kb)*Kb/Kg - V*(1-Kr)*Kr/Kg;\n"
    "    float B = Y + U*(1-Kb);\n"
    "    return float4(R,G,B,1);\n"
    "}\n"

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D(screen, screenCoords.xy);\n"
    "    return yuv709_to_rgb(rgb_to_yuv601(color));\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D( screen, screenCoords.xy);\n"
    "    color = pow(color,1.0/1.8);\n"
    "    return color;\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D( screen, screenCoords.xy);\n"
    "    color = pow(color,1.0/2.2);\n"
    "    return color;\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D(screen, screenCoords.xy);\n"
    "    if(color.r > 0.018)\n"
    "        color.r = 1.099 * pow(color.r,0.45) - 0.099;\n"
    "    else\n"
    "        color.r = 4.5138 * color.r;\n"
    "    if(color.g > 0.018)\n"
    "        color.g = 1.099 * pow(color.g,0.45) - 0.099;\n"
    "    else\n"
    "        color.g = 4.5138 * color.g;\n"
    "    if(color.b > 0.018)\n"
    "        color.b = 1.099 * pow(color.b,0.45) - 0.099;\n"
    "    else\n"
    "        color.b = 4.5138 * color.b;\n"
    "    return color;\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/builtin_shaders.h:     "float4 main(float2 screenCoords : TEXCOORD0) : COLOR0\n"
    "{\n"
    "    float4 color = tex2D(screen, screenCoords.xy);\n"
    "    color.r = max(color.r - 0.0627450980392157,0) * 1.164383561643836;\n"
    "    color.g = max(color.g - 0.0627450980392157,0) * 1.164383561643836;\n"
    "    color.b = max(color.b - 0.0627450980392157,0) * 1.164383561643836;\n"
    "    return saturate(color);\n"
    "}\n";

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/direct3d.c: static int ControlResetDevice(vout_display_t *vd)
{
    return Direct3DReset(vd);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/direct3d.c:                                char ***values, char ***descs)
{
    VLC_UNUSED(object);
    VLC_UNUSED(name);

    enum_context_t ctx = { NULL, NULL, 0 };

    ListShaders(&ctx);

    *values = ctx.values;
    *descs = ctx.descs;
    return ctx.count;

}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/direct2d.c: static int Control(vout_display_t *vd, int query, va_list args)
{
    return CommonControl(vd, query, args);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/decklink.cpp: static inline int clip(int a)
{
    if      (a < 4) return 4;
    else if (a > 1019) return 1019;
    else               return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/decklink.cpp: static int TimeGet(audio_output_t *, mtime_t* restrict)
{
    /* synchronization is handled by the card */
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/xcb/events.c: int XCB_Manage (vout_display_t *vd, xcb_connection_t *conn, bool *visible)
{
    xcb_generic_event_t *ev;

    while ((ev = xcb_poll_for_event (conn)) != NULL)
        ProcessEvent (vd, conn, visible, ev);

    if (xcb_connection_has_error (conn))
    {
        msg_Err (vd, "X server failure");
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/xcb/keys.c: static int keysymcmp (const void *pa, const void *pb)
{
    int a = *(const xcb_keysym_t *)pa;
    int b = *(const xcb_keysym_t *)pb;

    return a - b;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/xcb/keys.c:                                       xcb_connection_t *conn)
{
    msg_Err (obj, "X11 key press support not compiled-in");
    (void) conn;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/xcb/window.c: xcb_intern_atom_cookie_t intern_string (xcb_connection_t *c, const char *s)
{
    return xcb_intern_atom (c, 0, strlen (s), s);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/vdummy.c: static int OpenDummy(vlc_object_t *object)
{
    return Open(object, Display);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/vdummy.c: static int OpenStats(vlc_object_t *object)
{
    return Open(object, DisplayStat);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/vdummy.c: static int Control(vout_display_t *vd, int query, va_list args)
{
    VLC_UNUSED(vd);
    VLC_UNUSED(query);
    VLC_UNUSED(args);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/android/opaque.c: static int LockSurface(picture_t *picture)
{
    VLC_UNUSED(picture);

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/android/nativewindow.c: static int Control(vout_window_t *wnd, int cmd, va_list ap)
{
    switch (cmd)
    {
        case VOUT_WINDOW_SET_SIZE:
        {
            unsigned width = va_arg(ap, unsigned);
            unsigned height = va_arg(ap, unsigned);
            jni_SetAndroidSurfaceSize(width, height, width, height, 1, 1);
            break;
        }
        case VOUT_WINDOW_SET_STATE:
        case VOUT_WINDOW_SET_FULLSCREEN:
            return VLC_EGENERIC;
        default:
            msg_Err (wnd, "request %d not implemented", cmd);
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/fb.c: static void TextMode(int tty)
{
    /* return to text mode */
    if (-1 == ioctl(tty, KDSETMODE, KD_TEXT)) {
        /*msg_Err(vd, "failed ioctl KDSETMODE KD_TEXT");*/
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static bool CheckAPI (EGLDisplay dpy, const char *api)
{
    const char *apis = eglQueryString (dpy, EGL_CLIENT_APIS);
    return CheckToken(apis, api);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static bool CheckClientExt(const char *name)
{
    const char *exts = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    return CheckToken(exts, name);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static int OpenGLES2 (vlc_object_t *obj)
{
    static const struct gl_api api = {
        "OpenGL_ES", EGL_OPENGL_ES_API, 3, EGL_OPENGL_ES2_BIT,
        { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE },
    };
    return Open (obj, &api);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static int OpenGLES (vlc_object_t *obj)
{
    static const struct gl_api api = {
        "OpenGL_ES", EGL_OPENGL_ES_API, 0, EGL_OPENGL_ES_BIT,
        { EGL_CONTEXT_CLIENT_VERSION, 1, EGL_NONE },
    };
    return Open (obj, &api);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static int OpenGL (vlc_object_t *obj)
{
    static const struct gl_api api = {
        "OpenGL", EGL_OPENGL_API, 4, EGL_OPENGL_BIT,
        { EGL_NONE },
    };
    return Open (obj, &api);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/egl.c: static void *GetSymbol(vlc_gl_t *gl, const char *procname)
{
    (void) gl;
    return (void *)eglGetProcAddress (procname);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/opengl.c: static inline int GetAlignedSize(unsigned size)
{
    /* Return the smallest larger or equal power of 2 */
    unsigned align = 1 << (8 * sizeof (unsigned) - clz(size));
    return ((align >> 1) == size) ? size : align;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/opengl.c: static bool IsLuminance16Supported(int target)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(target, texture);
    glTexImage2D(target, 0, GL_LUMINANCE16,
                 64, 64, 0, GL_LUMINANCE, GL_UNSIGNED_SHORT, NULL);
    GLint size = 0;
    glGetTexLevelParameteriv(target, 0, GL_TEXTURE_LUMINANCE_SIZE, &size);

    glDeleteTextures(1, &texture);

    return size == 16;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/glx.c: static bool CheckGLX (vlc_object_t *vd, Display *dpy)
{
    int major, minor;
    bool ok = false;

    if (!glXQueryVersion (dpy, &major, &minor))
        msg_Dbg (vd, "GLX extension not available");
    else
    if (major != 1)
        msg_Dbg (vd, "GLX extension version %d.%d unknown", major, minor);
    else
    if (minor < 3)
        msg_Dbg (vd, "GLX extension version %d.%d too old", major, minor);
    else
    {
        msg_Dbg (vd, "using GLX extension version %d.%d", major, minor);
        ok = true;
    }
    return ok;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/glx.c: static bool CheckGLXext (Display *dpy, unsigned snum, const char *ext)
{
    const char *exts = glXQueryExtensionsString (dpy, snum);
    const size_t extlen = strlen (ext);

    while (*exts)
    {
        exts += strspn (exts, " ");

        size_t len = strcspn (exts, " ");
        if (len == extlen && !memcmp (exts, ext, extlen))
            return true;
        exts += len;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/glx.c: static void *GetSymbol(vlc_gl_t *gl, const char *procname)
{
    (void) gl;
#ifdef GLX_ARB_get_proc_address
    return glXGetProcAddressARB ((const GLubyte *)procname);
#else
    return NULL;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/drawable.c: static int Control (vout_window_t *wnd, int query, va_list ap)
{
    VLC_UNUSED( ap );

    switch (query)
    {
        case VOUT_WINDOW_SET_SIZE:   /* not allowed */
        case VOUT_WINDOW_SET_STATE: /* not allowed either, would be ugly */
            return VLC_EGENERIC;
        default:
            msg_Warn (wnd, "unsupported control query %d", query);
            return VLC_EGENERIC;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_splitter/panoramix.c: static inline int clip_accuracy( int a )
{
    return (a > ACCURACY) ? ACCURACY : (a < 0) ? 0 : a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_splitter/panoramix.c: static inline float clip_unit( float f )
{
    return f < 0.0 ? 0.0 : ( f > 1.0 ? 1.0 : f );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/text_renderer/freetype.c:                        const vlc_fourcc_t *p_chroma_list )
{
    return RenderCommon( p_filter, p_region_out, p_region_in, false, p_chroma_list );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/text_renderer/freetype.c:                        const vlc_fourcc_t *p_chroma_list )
{
    return RenderCommon( p_filter, p_region_out, p_region_in, true, p_chroma_list );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/text_renderer/tdummy.c:                        const vlc_fourcc_t *p_chroma_list )
{
    VLC_UNUSED(p_filter); VLC_UNUSED(p_region_out); VLC_UNUSED(p_region_in);
    VLC_UNUSED(p_chroma_list);
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/text_renderer/quartztext.c: static char *EliminateCRLF(char *psz_string)
{
    char *q;

    for (char * p = psz_string; p && *p; p++) {
        if ((*p == '\r') && (*(p+1) == '\n')) {
            for (q = p + 1; *q; q++)
                *(q - 1) = *q;

            *(q - 1) = '\0';
        }
    }
    return psz_string;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/smf.c: static int32_t ReadVarInt (stream_t *s)
{
    uint32_t val = 0;
    uint8_t byte;

    for (unsigned i = 0; i < 4; i++)
    {
        if (stream_Read (s, &byte, 1) < 1)
            return -1;

        val = (val << 7) | (byte & 0x7f);
        if ((byte & 0x80) == 0)
            return val;
    }

    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/podcast.c: static mtime_t strTimeToMTime( const char *psz )
{
    int h, m, s;
    switch( sscanf( psz, "%u:%u:%u", &h, &m, &s ) )
    {
    case 3:
        return (mtime_t)( ( h*60 + m )*60 + s ) * 1000000;
    case 2:
        return (mtime_t)( h*60 + m ) * 1000000;
        break;
    default:
        return -1;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/dvb.c: static int cmp(const void *k, const void *e)
{
    return strcmp(k, e);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/itml.c: int Import_iTML( vlc_object_t *p_this )
{
    DEMUX_BY_EXTENSION_OR_FORCED_MSG( ".xml", "itml",
                                      "using iTunes Media Library reader" );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/playlist.c: int Control(demux_t *demux, int query, va_list args)
{
    (void) demux; (void) query; (void) args;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/playlist.c: input_item_t * GetCurrentItem(demux_t *p_demux)
{
    input_thread_t *p_input_thread = demux_GetParentInput( p_demux );
    input_item_t *p_current_input = input_GetItem( p_input_thread );
    vlc_gc_incref(p_current_input);
    vlc_object_release(p_input_thread);
    return p_current_input;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/ram.c: static const char *SkipBlanks( const char *s, size_t i_strlen )
{
    while( i_strlen > 0 ) {
        switch( *s )
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                --i_strlen;
                ++s;
                break;
            default:
                i_strlen = 0;
        }
    }
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/b4s.c: static bool IsWhitespace( const char *psz_string )
{
    psz_string += strspn( psz_string, " \t\r\n" );
    return !*psz_string;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/m3u.c: static char *GuessEncoding (const char *str)
{
    return IsUTF8 (str) ? strdup (str) : FromLatin1 (str);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/m3u.c: static char *CheckUnicode (const char *str)
{
    return IsUTF8 (str) ? strdup (str): NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/m3u.c: static bool CheckContentType( stream_t * p_stream, const char * psz_ctype )
{
    char *psz_check = stream_ContentType( p_stream );
    if( !psz_check ) return false;

    int i_len = strlen( psz_check );
    if ( i_len == 0 )
    {
        free( psz_check );
        return false;
    }

    int i_res = strncasecmp( psz_check, psz_ctype, i_len );
    free( psz_check );

    return ( i_res == 0 ) ? true : false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/asx.c: static char *SkipBlanks(char *s, size_t i_strlen )
{
    while( i_strlen > 0 ) {
        switch( *s )
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                --i_strlen;
                ++s;
                break;
            default:
                i_strlen = 0;
        }
    }
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c: int Import_xspf(vlc_object_t *p_this)
{
    DEMUX_BY_EXTENSION_OR_MIMETYPE(".xspf", "application/xspf+xml",
                                      "using XSPF playlist reader");

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:     while ((i_node = xml_ReaderNextNode(p_xml_reader, &name)) > 0)
    {
        if (i_node == XML_READER_STARTELEM)
        {
            if (strcmp(name, "track"))
            {
                msg_Err(p_demux, "unexpected child of <trackList>: <%s>",
                         name);
                return false;
            }

            /* parse the track data in a separate function */
            if (parse_track_node(p_demux, p_input_node, p_xml_reader, "track"))
                i_ntracks++;
        }
        else if (i_node == XML_READER_ENDELEM)
            break;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:     if (i_node != XML_READER_ENDELEM)
    {
        msg_Err(p_demux, "there's a missing </trackList>");
        return false;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:     if (strcmp(name, "trackList"))
    {
        msg_Err(p_demux, "expected: </trackList>, found: </%s>", name);
        return false;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:                 switch (xml_ReaderNextNode(p_xml_reader, NULL))
                {
                    case XML_READER_STARTELEM: lvl++; break;
                    case XML_READER_ENDELEM:   lvl--; break;
                    case 0: case -1: return -1;
                }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:                 if (!*name)
                {
                    msg_Err(p_demux, "invalid xml stream");
                    FREE_VALUE();
                    if (b_release_input_item) vlc_gc_decref(p_new_input);
                    return false;
                }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:                 if (!p_handler)
                {
                    msg_Err(p_demux, "unexpected element <%s>", name);
                    FREE_VALUE();
                    if (b_release_input_item) vlc_gc_decref(p_new_input);
                    return false;
                }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:                 if (unlikely(!psz_value))
                {
                    FREE_VALUE();
                    if (b_release_input_item) vlc_gc_decref(p_new_input);
                    return false;
                }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/playlist/xspf.c:                 if (!strcmp(name, psz_element))
                {
                    FREE_VALUE();
                    if (b_release_input_item) vlc_gc_decref(p_new_input);
                    return true;
                }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/gme.c: static gme_err_t ReaderStream (void *data, void *buf, int length)
{
    stream_t *s = data;

    if (stream_Read (s, buf, length) < length)
        return "short read";
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/vobsub.h:                                      int *pi_original_frame_height )
{
    if( sscanf( psz_buf, "size: %dx%d",
                pi_original_frame_width, pi_original_frame_height ) == 2 )
    {
        return VLC_SUCCESS;
    }
    else
    {
        return VLC_EGENERIC;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/rawdv.h: static inline uint16_t dv_audio_12to16( uint16_t sample )
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/image.c: static bool IsPnmBlank(uint8_t v)
{
    return v == ' ' || v == '\t' || v == '\r' || v == '\n';
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avformat/demux.c: static vlc_fourcc_t CodecTagToFourcc( uint32_t codec_tag )
{
    // convert from little-endian avcodec codec_tag to VLC native-endian fourcc
#ifdef WORDS_BIGENDIAN
    return bswap32(codec_tag);
#else
    return codec_tag;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ogg.c:                                            uint64_t *pi_value )
{
    int i_shift = 0;
    int64_t i_read = 0;
    *pi_value = 0;

    while ( p_begin < p_end )
    {
        i_read = *p_begin & 0x7F; /* High bit is start of integer */
        *pi_value = *pi_value | ( i_read << i_shift );
        i_shift += 7;
        if ( (*p_begin++ & 0x80) == 0x80 ) break; /* see prev */
    }

    *pi_value = GetQWLE( pi_value );
    return p_begin;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/hevc.c:                               const uint8_t *src, int i_src )
{
    uint8_t *dst = malloc( i_src );
    if( !dst )
        return NULL;

    *pi_ret = nal_decode( src, dst, i_src );
    return dst;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static int MpgaCheckSync( const uint8_t *p_peek )
{
    uint32_t h = GetDWBE( p_peek );

    if( ((( h >> 21 )&0x07FF) != 0x07FF )   /* header sync */
        || (((h >> 19)&0x03) == 1 )         /* valid version ID ? */
        || (((h >> 17)&0x03) == 0 )         /* valid layer ?*/
        || (((h >> 12)&0x0F) == 0x0F )      /* valid bitrate ?*/
        || (((h >> 10) & 0x03) == 0x03 )    /* valide sampling freq ? */
        || ((h & 0x03) == 0x02 ))           /* valid emphasis ? */
    {
        return false;
    }
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static int MpgaGetFrameSamples( uint32_t h )
{
    const int i_layer = 3 - (((h)>>17)&0x03);
    switch( i_layer )
    {
    case 0:
        return 384;
    case 1:
        return 1152;
    case 2:
        return MPGA_VERSION(h) ? 576 : 1152;
    default:
        return 0;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static uint32_t MpgaXingGetDWBE( const uint8_t **pp_xing, int *pi_xing, uint32_t i_default )
{
    if( *pi_xing < 4 )
        return i_default;

    uint32_t v = GetDWBE( *pp_xing );

    MpgaXingSkip( pp_xing, pi_xing, 4 );

    return v;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static int EA52CheckSyncProbe( const uint8_t *p_peek, int *pi_samples )
{
    bool b_dummy;
    return A52CheckSync( p_peek, &b_dummy, pi_samples, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static int A52CheckSyncProbe( const uint8_t *p_peek, int *pi_samples )
{
    bool b_dummy;
    return A52CheckSync( p_peek, &b_dummy, pi_samples, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mpeg/es.c: static int DtsCheckSync( const uint8_t *p_peek, int *pi_samples )
{
    unsigned int i_sample_rate, i_bit_rate, i_frame_length, i_audio_mode;
    bool b_dts_hd;

    VLC_UNUSED(pi_samples);

    int i_frame_size = GetSyncInfo( p_peek,
                                    &b_dts_hd,
                                    &i_sample_rate,
                                    &i_bit_rate,
                                    &i_frame_length,
                                    &i_audio_mode );

    if( i_frame_size != VLC_EGENERIC && i_frame_size <= 8192 )
        return VLC_SUCCESS;
    else
        return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.h:     if( !( p_peek = p_buff = malloc( i_read ) ) ) \
    { \
        return( 0 ); \
    } \

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.h:     if( i_actually_read < 0 || (int64_t)i_actually_read < i_read )\
    { \
        msg_Warn( p_stream, "MP4_READBOX_ENTER: I got %i bytes, "\
        "but I requested %"PRId64"", i_actually_read, i_read );\
        free( p_buff ); \
        return( 0 ); \
    } \

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.h:     do \
    { \
        free( p_buff ); \
        if( i_read < 0 ) \
            msg_Warn( p_stream, "Not enough data" ); \
        return( i_code ); \
    } while (0)

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.h: static inline int CmpUUID( const UUID_t *u1, const UUID_t *u2 )
{
    return memcmp( u1, u2, 16 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/mp4.c: static int   Demux   ( demux_t * );
static int   DemuxRef( demux_t *p_demux ){ (void)p_demux; return 0;}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/mp4.c: static uint32_t stream_ReadU32( stream_t *s, void *p_read, uint32_t i_toread )
{
    uint32_t i_return = 0;
    if ( i_toread > INT32_MAX )
    {
        i_return = stream_Read( s, p_read, INT32_MAX );
        if ( i_return < INT32_MAX )
            return i_return;
        else
            i_toread -= INT32_MAX;
    }
    i_return += stream_Read( s, (uint8_t *)p_read + i_return, (int32_t) i_toread );
    return i_return;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/mp4.c: static bool MP4_stream_Tell( stream_t *s, uint64_t *pi_pos )
{
    int64_t i_pos = stream_Tell( s );
    if ( i_pos < 0 )
        return false;
    else
    {
        *pi_pos = (uint64_t) i_pos;
        return true;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.c: /* convert 16.16 fixed point to floating point */
static double conv_fx( int32_t fx ) {
    double fp = fx;
    fp /= 65536.;
    return fp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.c: static int MP4_ReadBoxContainerRaw( stream_t *p_stream, MP4_Box_t *p_container )
{
    return MP4_ReadBoxContainerChildren( p_stream, p_container, 0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.c: static int MP4_ReadLengthDescriptor( uint8_t **pp_peek, int64_t  *i_read )
{
    unsigned int i_b;
    unsigned int i_len = 0;
    do
    {
        i_b = **pp_peek;

        (*pp_peek)++;
        (*i_read)--;
        i_len = ( i_len << 7 ) + ( i_b&0x7f );
    } while( i_b&0x80 );
    return( i_len );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.c: static int MP4_ReadBox_drms( stream_t *p_stream, MP4_Box_t *p_box )
{
    VLC_UNUSED(p_box);
    /* ATOMs 'user', 'key', 'iviv', and 'priv' will be skipped,
     * so unless data decrypt itself by magic, there will be no playback,
     * but we never know... */
    msg_Warn( p_stream, "DRM protected streams are not supported." );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mp4/libmp4.c: MP4_Box_t *MP4_BoxGet( MP4_Box_t *p_box, const char *psz_fmt, ... )
{
    va_list args;
    MP4_Box_t *p_result;

    va_start( args, psz_fmt );
    MP4_BoxGet_Internal( &p_result, p_box, psz_fmt, args );
    va_end( args );

    return( p_result );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline double GetDBLBE( const uint8_t *p )
{
    union
    {
        uint64_t uint64;
        double dbl;
    } u_64;

    u_64.uint64 = GetQWBE( p );
    return u_64.dbl;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline int ReadBEInt32ToUInt32( const uint8_t *p, uint32_t *i_out )
{
    uint32_t i_value = GetDWBE( p );

    if( i_value > INT32_MAX ) return VLC_EGENERIC;

    *i_out = i_value;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline int ReadBEInt64ToUInt64( const uint8_t *p, uint64_t *i_out )
{
    uint64_t i_value = GetQWBE( p );

    if( i_value > INT64_MAX ) return VLC_EGENERIC;

    *i_out = i_value;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline bool AACCookieGetTag( uint8_t *p_tag, const uint8_t *p, uint64_t *p_offset, uint64_t i_size )
{
    if( *p_offset + 1 > i_size )
        return false;

    *p_tag = *( p + *p_offset );
    *p_offset += 1;

    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline bool AACCookieTagLen( uint64_t *p_tag_len, const uint8_t *p, uint64_t *p_offset, uint64_t i_size )
{
    uint32_t i_int_size;

    if( ParseVarLenInteger( p + *p_offset, i_size - *p_offset, p_tag_len, &i_int_size ))
        return false;

    *p_offset += i_int_size;

    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline bool AACCookieChkLen( int64_t i_length, uint64_t i_size, uint64_t i_offset )
{
    return ( i_offset + i_length <= i_size );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ps.c: static int OpenForce( vlc_object_t *p_this )
{
    return OpenCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ps.h: static inline int ps_id_to_tk( unsigned i_id )
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/xiph.h: static inline bool xiph_IsOldFormat( const void *extra, unsigned int i_extra )
{
    if ( i_extra >= 6 && GetWBE( extra ) == 30 )
        return true;
    else
        return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/voc.c: static unsigned int fix_voc_sr( unsigned int sr )
{
    switch( sr )
    {
        /*case 8000:
            return 8000;*/
        case 11111:
            return 11025;

        case 22222:
            return 22050;

        case 44444:
            return 44100;
    }
    return sr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c: static int  IODDescriptorLength( int *pi_data, uint8_t **pp_data )
{
    unsigned int i_b;
    unsigned int i_len = 0;
    do
    {
        i_b = **pp_data;
        (*pp_data)++;
        (*pi_data)--;
        i_len = ( i_len << 7 ) + ( i_b&0x7f );

    } while( i_b&0x80 && *pi_data > 0 );

    if (i_len > *pi_data)
        i_len = *pi_data;

    return i_len;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c: static int IODGetBytes( int *pi_data, uint8_t **pp_data, size_t bytes )
{
    uint32_t res = 0;
    while( *pi_data > 0 && bytes-- )
    {
        res <<= 8;
        res |= **pp_data;
        (*pp_data)++;
        (*pi_data)--;
    }

    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c: static char* IODGetURL( int *pi_data, uint8_t **pp_data )
{
    int len = IODGetBytes( pi_data, pp_data, 1 );
    if (len > *pi_data)
        len = *pi_data;
    char *url = strndup( (char*)*pp_data, len );
    *pp_data += len;
    *pi_data -= len;
    return url;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c:                                bool b_broken )
{
    /* Deal with no longer broken providers (no switch byte
      but sending ISO_8859-1 instead of ISO_6937) without
      removing them from the broken providers table
      (keep the entry for correctly handling recorded TS).
    */
    b_broken = b_broken && i_length && *psz_instring > 0x20;

    if( b_broken )
        return FromCharset( "ISO_8859-1", psz_instring, i_length );
    return vlc_from_EIT( psz_instring, i_length );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c: static int64_t EITConvertStartTime( uint64_t i_date )
{
    const int i_mjd = i_date >> 24;
    const int i_hour   = CVT_FROM_BCD(i_date >> 16);
    const int i_minute = CVT_FROM_BCD(i_date >>  8);
    const int i_second = CVT_FROM_BCD(i_date      );
    int i_year;
    int i_month;
    int i_day;

    /* if all 40 bits are 1, the start is unknown */
    if( i_date == UINT64_C(0xffffffffff) )
        return -1;

    EITDecodeMjd( i_mjd, &i_year, &i_month, &i_day );
    return vlc_timegm( i_year - 1900, i_month - 1, i_day, i_hour, i_minute, i_second );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/ts.c: static int EITConvertDuration( uint32_t i_duration )
{
    return CVT_FROM_BCD(i_duration >> 16) * 3600 +
           CVT_FROM_BCD(i_duration >> 8 ) * 60 +
           CVT_FROM_BCD(i_duration      );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/avi.c: static char *FromACP( const char *str )
{
    return FromCharset(vlc_pgettext("GetACP", "CP1252"), str, strlen(str));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/avi.c: static inline off_t __EVEN( off_t i )
{
    return (i & 1) ? i + 1 : i;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/avi.c: vlc_fourcc_t AVI_FourccGetCodec( unsigned int i_cat, vlc_fourcc_t i_codec )
{
    switch( i_cat )
    {
        case AUDIO_ES:
            wf_tag_to_fourcc( i_codec, &i_codec, NULL );
            return i_codec;
        case VIDEO_ES:
            return vlc_fourcc_GetCodec( i_cat, i_codec );
        default:
            return VLC_FOURCC( 'u', 'n', 'd', 'f' );
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/libavi.c:     if( i_read > 100000000 ) \
    { \
        msg_Err( s, "Big chunk ignored" ); \
        return VLC_EGENERIC; \
    } \

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/libavi.c:     if( !( p_read = p_buff = malloc(i_read ) ) ) \
    { \
        return VLC_EGENERIC; \
    } \

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/libavi.c: #define AVI_READ( res, func, size ) \
    if( i_read < size ) { \
        free( p_buff); \
        return VLC_EGENERIC; \
    } \

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/libavi.c: static inline uint8_t GetB( uint8_t *ptr )
{
    return *ptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/avi/libavi.c: static int AVI_ChunkRead_nothing( stream_t *s, avi_chunk_t *p_chk )
{
    return AVI_NextChunk( s, p_chk );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/asf/libasf.c: #define ASF_FUNCTION_READ_X(type, x, cmd ) \
static inline type AsfObjectHelperRead##x( const uint8_t *p_peek, int i_peek, uint8_t **pp_data ) { \
    uint8_t *p_data = *pp_data; \
    type i_ret = 0;  \
    if( ASF_HAVE(x) )   \
        i_ret = cmd;    \
    ASF_SKIP(x);        \
    *pp_data = p_data;  \
    return i_ret;   }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/asf/libasf.c: static inline char *get_wstring( const uint8_t *p_data, size_t i_size )
{
    char *psz_str = FromCharset( "UTF-16LE", p_data, i_size );
    if( psz_str )
        p_data += i_size;
    return psz_str;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/asf/libasf.c: static int ASF_ReadObject_Raw(stream_t *s, asf_object_t *p_obj)
{
    VLC_UNUSED(s);
    VLC_UNUSED(p_obj);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/Ebml_parser.cpp: int EbmlParser::GetLevel( void ) const
{
    return mi_user_level;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/mkv.hpp: class PrivateTrackData
{
public:
    virtual ~PrivateTrackData() {}
    virtual int32_t Init() { return 0; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/demux.cpp: void event_thread_t::ResetPci()
{
    if( !is_running )
        return;

    vlc_mutex_lock( &lock );
    b_abort = true;
    vlc_cond_signal( &wait );
    vlc_mutex_unlock( &lock );

    vlc_join( thread, NULL );
    is_running = false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/stream_io_callback.cpp: uint32 vlc_stream_io_callback::read( void *p_buffer, size_t i_size )
{
    if( i_size <= 0 || mb_eof )
        return 0;

    int i_ret = stream_Read( s, p_buffer, i_size );
    return i_ret < 0 ? 0 : i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/stream_io_callback.cpp: uint64 vlc_stream_io_callback::getFilePointer( void )
{
    if ( s == NULL )
        return 0;
    return stream_Tell( s );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/stream_io_callback.cpp: size_t vlc_stream_io_callback::write(const void *, size_t )
{
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/stream_io_callback.cpp: uint64 vlc_stream_io_callback::toRead( void )
{
    uint64_t i_size;

    if( s == NULL)
        return 0;

    i_size = stream_Size( s );

    if( i_size <= 0 )
        return UINT64_MAX;

    return (uint64) i_size - stream_Tell( s );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/chapters.cpp:                                     size_t i_cookie_size )
{
    VLC_UNUSED( codec_id );
    // this chapter
    std::vector<chapter_codec_cmds_c*>::const_iterator index = codecs.begin();
    while ( index != codecs.end() )
    {
        if ( match( **index ,p_cookie, i_cookie_size ) )
            return this;
        ++index;
    }
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/util.cpp: int32_t Cook_PrivateTrackData::Init()
{
    i_subpackets = (size_t) i_sub_packet_h * (size_t) i_frame_size / (size_t) i_subpacket_size;
    p_subpackets = (block_t**) calloc(i_subpackets, sizeof(block_t*));

    if( unlikely( !p_subpackets ) )
    {
        i_subpackets = 0;
        return 1;
    }

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/matroska_segment_parse.cpp: static inline char * ToUTF8( const UTFstring &u )
{
    return strdup( u.GetUTF8().c_str() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/nsc.c: static void DemuxClose( vlc_object_t *p_this )
{
    VLC_UNUSED( p_this );
    return;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/nsc.c: static int Control( demux_t *p_demux, int i_query, va_list args )
{
    VLC_UNUSED( p_demux ); VLC_UNUSED( i_query ); VLC_UNUSED( args );
    //FIXME
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/real.c: #define RX(name, type, size, code ) \
static type name( const uint8_t **pp_data, int *pi_data ) { \
    if( *pi_data < (size) )          \
        return 0;                    \
    type v = code;                   \
    RVoid( pp_data, pi_data, size ); \
    return v;                        \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/real.c: static int RLength( const uint8_t **pp_data, int *pi_data )
{
    const int v0 = R16( pp_data, pi_data ) & 0x7FFF;
    if( v0 >= 0x4000 )
        return v0 - 0x4000;
    return (v0 << 16) | R16( pp_data, pi_data );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/livehttp.c: static int Seek( sout_access_out_t *p_access, off_t i_pos )
{
    (void) i_pos;
    msg_Err( p_access, "livehttp sout access cannot seek" );
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/shout.c: static int Seek( sout_access_out_t *p_access, off_t i_pos )
{
    VLC_UNUSED(i_pos);
    msg_Err( p_access, "cannot seek on shout" );
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/dummy.c: static int Seek( sout_access_out_t *p_access, off_t i_pos )
{
    (void)p_access; (void)i_pos;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/http.c: static int Control( sout_access_out_t *p_access, int i_query, va_list args )
{
    (void)p_access;

    switch( i_query )
    {
        case ACCESS_OUT_CONTROLS_PACE:
            *va_arg( args, bool * ) = false;
            break;

        default:
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/http.c: static int Seek( sout_access_out_t *p_access, off_t i_pos )
{
    (void)i_pos;
    msg_Warn( p_access, "HTTP sout access cannot seek" );
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/udp.c: static int Control( sout_access_out_t *p_access, int i_query, va_list args )
{
    (void)p_access;

    switch( i_query )
    {
        case ACCESS_OUT_CONTROLS_PACE:
            *va_arg( args, bool * ) = false;
            break;

        default:
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access_output/udp.c: static int Seek( sout_access_out_t *p_access, off_t i_pos )
{
    (void) i_pos;
    msg_Err( p_access, "UDP sout access cannot seek" );
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtp.c: uint32_t rtp_compute_ts( unsigned i_clock_rate, int64_t i_pts )
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtp.c:                             const char *psz_vod_session )
{
    if (p_media == NULL || psz_vod_session == NULL)
        return mdate();

    uint64_t i_ts_init;
    /* As per RFC 2326, session identifiers are at least 8 bytes long */
    strncpy((char *)&i_ts_init, psz_vod_session, sizeof(uint64_t));
    i_ts_init ^= (uintptr_t)p_media;
    /* Limit the timestamp to 48 bits, this is enough and allows us
     * to stay away from overflows */
    i_ts_init &= 0xFFFFFFFFFFFF;
    return i_ts_init;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/raop.c:                                         unsigned int i_line )
{
    if ( i_gcrypt_err != GPG_ERR_NO_ERROR )
    {
        msg_Err( p_stream, "gcrypt error (line %d): %s", i_line,
                 gpg_strerror( i_gcrypt_err ) );
        return 1;
    }

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/raop.c:                         char **ppsz_value )
{
    /* Find semicolon (separator between assignments) */
    *ppsz_name = strsep( ppsz_next, psz_delim_semicolon );
    if ( *ppsz_name )
    {
        /* Skip spaces */
        *ppsz_name += strspn( *ppsz_name, psz_delim_space );

        /* Get value */
        *ppsz_value = *ppsz_name;
        strsep( ppsz_value, psz_delim_equal );
    }
    else
        *ppsz_value = NULL;

    return !!*ppsz_name;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/raop.c: static int SendTeardown( vlc_object_t *p_this )
{
    vlc_dictionary_t resp_headers;
    vlc_dictionary_t req_headers;
    int i_err = VLC_SUCCESS;

    vlc_dictionary_init( &req_headers, 0 );
    vlc_dictionary_init( &resp_headers, 0 );

    i_err = ExecRequest( p_this, "TEARDOWN", NULL, NULL,
                         &req_headers, &resp_headers );
    if ( i_err != VLC_SUCCESS )
        goto error;

error:
    vlc_dictionary_clear( &req_headers, NULL, NULL );
    vlc_dictionary_clear( &resp_headers, FreeHeader, NULL );

    return i_err;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/display.c: static int Del( sout_stream_t *p_stream, sout_stream_id_sys_t *id )
{
    (void) p_stream;
    input_DecoderDelete( (decoder_t *)id );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/langfromtelx.c: static uint8_t bytereverse( int n )
{
    n = (((n >> 1) & 0x55) | ((n << 1) & 0xaa));
    n = (((n >> 2) & 0x33) | ((n << 2) & 0xcc));
    n = (((n >> 4) & 0x0f) | ((n << 4) & 0xf0));
    return n;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/dummy.c: static sout_stream_id_sys_t *Add( sout_stream_t *p_stream, es_format_t *p_fmt )
{
    VLC_UNUSED(p_stream); VLC_UNUSED(p_fmt);
    return malloc( 1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/dummy.c: static int Del( sout_stream_t *p_stream, sout_stream_id_sys_t *id )
{
    VLC_UNUSED(p_stream);
    free( id );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/dummy.c:                  block_t *p_buffer )
{
    (void)p_stream; (void)id;
    block_ChainRelease( p_buffer );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/smem.c: static int Del( sout_stream_t *p_stream, sout_stream_id_sys_t *id )
{
    VLC_UNUSED( p_stream );
    free( id );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtsp.c: static int dup_socket(int oldfd)
{
    int newfd;
#ifndef _WIN32
    newfd = vlc_dup(oldfd);
#else
    WSAPROTOCOL_INFO info;
    WSADuplicateSocket (oldfd, GetCurrentProcessId (), &info);
    newfd = WSASocket (info.iAddressFamily, info.iSocketType,
                       info.iProtocol, &info, 0, 0);
#endif
    return newfd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtsp.c: static inline const char *transport_next( const char *str )
{
    /* Looks for comma */
    str = strchr( str, ',' );
    if( str == NULL )
        return NULL; /* No more transport options */

    str++; /* skips comma */
    while( strchr( "\r\n\t ", *str ) )
        str++;

    return (*str) ? str : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtsp.c: static inline const char *parameter_next( const char *str )
{
    while( strchr( ",;", *str ) == NULL )
        str++;

    return (*str == ';') ? (str + 1) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtsp.c: static int64_t ParseNPT (const char *str)
{
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t oldloc = uselocale (loc);
    unsigned hour, min;
    float sec;

    if (sscanf (str, "%u:%u:%f", &hour, &min, &sec) == 3)
        sec += ((hour * 60) + min) * 60;
    else
    if (sscanf (str, "%f", &sec) != 1)
        sec = -1;

    if (loc != (locale_t)0)
    {
        uselocale (oldloc);
        freelocale (loc);
    }
    return sec < 0 ? -1 : sec * CLOCK_FREQ;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtsp.c:                          const httpd_message_t *query )
{
    return RtspHandler( (rtsp_stream_t *)p_args, NULL, cl, answer, query );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/description.c: static int Del( sout_stream_t *p_stream, sout_stream_id_sys_t *id )
{
    msg_Dbg( p_stream, "Removing a stream" );

    free( id );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtpfmt.c: static int rtp_packetize_g726_16( sout_stream_id_sys_t *id, block_t *in )
{
    return rtp_packetize_g726( id, in, 4 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtpfmt.c: static int rtp_packetize_g726_24( sout_stream_id_sys_t *id, block_t *in )
{
    return rtp_packetize_g726( id, in, 8 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtpfmt.c: static int rtp_packetize_g726_32( sout_stream_id_sys_t *id, block_t *in )
{
    return rtp_packetize_g726( id, in, 2 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/rtpfmt.c: static int rtp_packetize_g726_40( sout_stream_id_sys_t *id, block_t *in )
{
    return rtp_packetize_g726( id, in, 8 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/main_interface.cpp: void MainInterface::toggleFSC()
{
   if( !fullscreenControls ) return;

   IMEvent *eShow = new IMEvent( IMEvent::FullscreenControlToggle );
   QApplication::postEvent( fullscreenControls, eShow );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/main_interface.cpp:                              unsigned int *pi_width, unsigned int *pi_height )
{
    if( !videoWidget )
        return 0;

    /* This is a blocking call signal. Results are returned through pointers.
     * Beware of deadlocks! */
    WId id;
    emit askGetVideo( &id, pi_x, pi_y, pi_width, pi_height );
    return id;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp: void RecentsMRL::clear()
{
    if ( recents.isEmpty() )
        return;

    recents.clear();
    times.clear();
    if( isActive ) VLCMenuBar::updateRecents( p_intf );
    save();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp: QStringList RecentsMRL::recentList()
{
    return recents;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp: int RecentsMRL::time( const QString &mrl )
{
    if( !isActive )
        return -1;

    int i_index = recents.indexOf( mrl );
    if( i_index != -1 )
        return times.value(i_index, "-1").toInt();
    else
        return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp:                     bool b_playlist)
{
    return openMRLwithOptions( p_intf, mrl, NULL, b_start, b_playlist );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/menus.cpp:         QVector<vlc_object_t *> &objects, QVector<const char *> &varnames )
{
    PUSH_INPUTVAR( "bookmark" );
    PUSH_INPUTVAR( "title" );
    PUSH_INPUTVAR( "chapter" );
    PUSH_INPUTVAR( "program" );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/menus.cpp:         QVector<vlc_object_t *> &objects, QVector<const char *> &varnames )
{
    PUSH_INPUTVAR( "spu-es" );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/menus.cpp:         QVector<vlc_object_t *> &objects, QVector<const char *> &varnames )
{
    audio_output_t *p_object = p_input ? input_GetAout( p_input ) : NULL;

    PUSH_INPUTVAR( "audio-es" );
    PUSH_VAR( "stereo-mode" );
    PUSH_VAR( "visual" );

    if( p_object )
        vlc_object_release( p_object );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/menus.cpp: QMenu *VLCMenuBar::InterfacesMenu( intf_thread_t *p_intf, QMenu *current )
{
    QVector<vlc_object_t *> objects;
    QVector<const char *> varnames;
    varnames.append( "intf-add" );
    objects.append( VLC_OBJECT(p_intf) );

    return Populate( p_intf, current, varnames, objects );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/menus.cpp: static bool CheckTitle( vlc_object_t *p_object, const char *psz_var )
{
    int i_title = 0;
    if( sscanf( psz_var, "title %2i", &i_title ) <= 0 )
        return true;

    int i_current_title = var_GetInteger( p_object, "title" );
    return ( i_title == i_current_title );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/vlm.cpp: bool VLMDialog::exportVLMConf()
{
    QString saveVLMConfFileName = QFileDialog::getSaveFileName( this,
                                        qtr( "Save VLM configuration as..." ),
                                        QVLCUserDir( VLC_DOCUMENTS_DIR ),
                                        qtr( "VLM conf (*.vlm);;All (*)" ) );

    if( !saveVLMConfFileName.isEmpty() )
    {
        vlm_message_t *message;
        QString command = "save \"" + saveVLMConfFileName + "\"";
        vlm_ExecuteCommand( p_vlm , qtu( command ) , &message );
        vlm_MessageDelete( message );
        return true;
    }

    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/extensions.hpp: class WidgetMapper : public QObject
{
    Q_OBJECT
private:
    extension_widget_t *p_widget;
public:
    WidgetMapper( extension_widget_t *_p_widget ) :
            QObject(NULL), p_widget(_p_widget) {}
    extension_widget_t* getWidget() { return p_widget; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/openurl.cpp: QString OpenUrlDialog::url() const
{
    return lastUrl;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/openurl.cpp: bool OpenUrlDialog::shouldEnqueue() const
{
    return bShouldEnqueue;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/playlist.cpp: bool PlaylistDialog::hasPlaylistWidget()
{
    return ( !! playlistWidget );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp: static QPixmap hueRotate( QImage image, const QColor &source, const QColor &target )
{
    int distance = target.hue() - source.hue();
    /* must be indexed as we alter palette, not a whole pic */
    Q_ASSERT( image.colorCount() );
    if ( target.isValid() )
    {
        /* color 1 = transparency */
        for ( int i=1; i < image.colorCount(); i++ )
        {
            QColor color = image.color( i );
            int newhue = color.hue() + distance;
            if ( newhue < 0 ) newhue += 255;
            color.setHsv( newhue, color.saturation(), color.value(), color.alpha() );
            image.setColor( i, color.rgba() );
        }
    }
    return QPixmap::fromImage( image );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp:                                        const QModelIndex& ) const
{
    if( column != 0 )
        return QModelIndex();
    if( row < 0 || row >= extensions.count() )
        return QModelIndex();

    return createIndex( row, 0, extensions.at( row ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp: bool AddonsListModel::Addon::operator==( const Addon & other ) const
{
    //return data( IDRole ) == other.data( IDRole );
    return p_entry == other.p_entry;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp: bool AddonsListModel::Addon::operator==( const addon_entry_t * p_other ) const
{
    return p_entry == p_other;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp: int AddonsListModel::rowCount( const QModelIndex & ) const
{
    return addons.count();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp: Qt::ItemFlags AddonsListModel::flags( const QModelIndex &index ) const
{
    Qt::ItemFlags i_flags = ExtensionListModel::flags( index );
    int i_state = data( index, StateRole ).toInt();

    if ( i_state == ADDON_UNINSTALLING || i_state == ADDON_INSTALLING )
    {
        i_flags &= !Qt::ItemIsEnabled;
    }

    i_flags |= Qt::ItemIsEditable;

    return i_flags;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp:                                        const QModelIndex& ) const
{
    if( column != 0 )
        return QModelIndex();
    if( row < 0 || row >= addons.count() )
        return QModelIndex();

    return createIndex( row, 0, addons.at( row ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp:                                        const QModelIndex &index ) const
{
    if ( index.isValid() )
    {
        return QSize( 200, 2 * option.fontMetrics.height()
                      + margins.top() + margins.bottom() );
    }
    else
        return QSize();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/plugins.cpp:                                    const QModelIndex &index ) const
{
    if ( index.isValid() )
    {
        return QSize( 200, 4 * option.fontMetrics.height()
                      + margins.top() + margins.bottom() );
    }
    else
        return QSize();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/dialogs/open.cpp: QStringList OpenDialog::getMRLs( bool b_with_options )
{
    if ( !b_with_options ) return itemsMRL;
    QStringList postfixedMRLs;
    foreach( const QString &mrl, itemsMRL )
        postfixedMRLs << QString( mrl ).append( getOptions() );
    return postfixedMRLs;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/adapters/seekpoints.cpp: QList<SeekPoint> const SeekPoints::getPoints()
{
    QList<SeekPoint> copy;
    if ( access() )
    {
        copy = pointsList;
        release();
    }
    return copy;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/adapters/seekpoints.cpp: bool SeekPoints::jumpTo( int i_chapterindex )
{
    vlc_value_t val;
    val.i_int = i_chapterindex;
    input_thread_t *p_input_thread = playlist_CurrentInput( THEPL );
    if( !p_input_thread ) return false;
    bool b_succ = var_Set( p_input_thread, "chapter", val );
    vlc_object_release( p_input_thread );
    return ( b_succ == VLC_SUCCESS );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/adapters/seekpoints.hpp: class SeekPoints : public QObject
{
    Q_OBJECT
public:
    SeekPoints( QObject *, intf_thread_t * );
    QList<SeekPoint> const getPoints();
    bool access() { return listMutex.tryLock( 100 ); }
    void release() { listMutex.unlock(); }
    bool jumpTo( int );

public slots:
    void update();

private:
    QList<SeekPoint> pointsList;
    QMutex listMutex;
    intf_thread_t *p_intf;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/qt4.hpp: static inline QString QVLCUserDir( vlc_userdir_t type )
{
    char *dir = config_GetUserDir( type );
    if( !dir )
        return "";
    QString res = qfu( dir );
    free( dir );
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/main_interface_win32.cpp: static HBITMAP qt_pixmapToWinHBITMAP(const QPixmap &p, int hbitmapFormat = 0)
{
    return p.toWinHBITMAP((enum QBitmap::HBitmapFormat)hbitmapFormat);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/main_interface_win32.cpp: bool MainInterface::nativeEvent(const QByteArray &, void *message, long *result)
{
    return winEvent( static_cast<MSG*>( message ), result );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/managers/addons_manager.cpp: QString AddonsManager::getAddonType( int i_type )
{
    switch ( i_type )
    {
    case ADDON_SKIN2:
        return qtr( "Skins" );
    case ADDON_PLAYLIST_PARSER:
        return qtr("Playlist parsers");
    case ADDON_SERVICE_DISCOVERY:
        return qtr("Service Discovery");
    case ADDON_INTERFACE:
        return qtr("Interfaces");
    case ADDON_META:
        return qtr("Art and meta fetchers");
    case ADDON_EXTENSION:
        return qtr("Extensions");
    default:
        return qtr("Unknown");
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp:                         vlc_value_t oldval, vlc_value_t newval, void *param )
{
    VLC_UNUSED( p_this ); VLC_UNUSED( psz_var ); VLC_UNUSED( oldval );

    InputManager *im = (InputManager*)param;
    input_item_t *p_item = static_cast<input_item_t *>(newval.p_address);

    IMEvent *event = new IMEvent( IMEvent::ItemChanged, p_item );
    QApplication::postEvent( im, event );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp:                      vlc_value_t, vlc_value_t, void *param )
{
    InputManager *im = (InputManager*)param;
    IMEvent *event = new IMEvent( IMEvent::ItemTeletextChanged );

    QApplication::postEvent( im, event );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: int InputManager::playingStatus()
{
    return i_old_playing_status;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: bool InputManager::hasAudio()
{
    if( hasInput() )
    {
        vlc_value_t val;
        var_Change( p_input, "audio-es", VLC_VAR_CHOICESCOUNT, &val, NULL );
        return val.i_int > 0;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: bool InputManager::hasVisualisation()
{
    if( !p_input )
        return false;

    audio_output_t *aout = input_GetAout( p_input );
    if( !aout )
        return false;

    char *visual = var_InheritString( aout, "visual" );
    vlc_object_release( aout );

    if( !visual )
        return false;

    free( visual );
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: void InputManager::UpdateCaching()
{
    if(!hasInput()) return;

    float f_newCache = var_GetFloat ( p_input, "cache" );
    if( f_newCache != f_cache )
    {
        f_cache = f_newCache;
        /* Update cache */
        emit cachingChanged( f_cache );
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: void InputManager::UpdateArt()
{
    QString url;

    if( hasInput() )
        url = decodeArtURL( input_GetItem( p_input ) );

    /* the art hasn't changed, no need to update */
    if(artUrl == url)
        return;

    /* Update Art meta */
    artUrl = url;
    emit artChanged( artUrl );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: vout_thread_t* MainInputManager::getVout()
{
    return p_input ? input_GetVout( p_input ) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: audio_output_t * MainInputManager::getAout()
{
    return playlist_GetAout( THEPL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: bool MainInputManager::getPlayExitState()
{
    return var_InheritBool( THEPL, "play-and-exit" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: bool MainInputManager::hasEmptyPlaylist()
{
    playlist_Lock( THEPL );
    bool b_empty = playlist_IsEmpty( THEPL );
    playlist_Unlock( THEPL );
    return b_empty;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp:                         vlc_value_t oldval, vlc_value_t val, void *param )
{
    VLC_UNUSED( p_this ); VLC_UNUSED( psz_var ); VLC_UNUSED( oldval );
    VLC_UNUSED( val );

    MainInputManager *mim = (MainInputManager*)param;

    IMEvent *event = new IMEvent( IMEvent::ItemChanged );
    QApplication::postEvent( mim, event );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp:                         vlc_value_t oldval, vlc_value_t newval, void *param )
{
    VLC_UNUSED( p_this ); VLC_UNUSED( psz_var ); VLC_UNUSED( oldval );
    MainInputManager *mim = (MainInputManager*)param;

    PLEvent *event = new PLEvent( PLEvent::LeafToParent, newval.i_int );

    QApplication::postEvent( mim, event );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/qt4.cpp: static int OpenIntf( vlc_object_t *p_this )
{
    return Open( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/qt4.cpp: static int OpenDialogs( vlc_object_t *p_this )
{
    return Open( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: QString formatTooltip(const QString & tooltip)
{
    QString text = tooltip;
    text.replace("\n", "<br/>");

    QString formatted =
    "<html><head><meta name=\"qrichtext\" content=\"1\" />"
    "<style type=\"text/css\"> p, li { white-space: pre-wrap; } </style></head>"
    "<body style=\" font-family:'Sans Serif'; "
    "font-style:normal; text-decoration:none;\">"
    "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; "
    "margin-right:0px; -qt-block-indent:0; text-indent:0px;\">" +
    text + "</p></body></html>";
    return formatted;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: 
int VStringConfigControl::getType() const { return CONFIG_ITEM_STRING; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: 
int VIntConfigControl::getType() const { return CONFIG_ITEM_INTEGER; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: 
int BoolConfigControl::getType() const { return CONFIG_ITEM_BOOL; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: int ColorConfigControl::getValue() const
{
    return i_color;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: 
int VFloatConfigControl::getType() const { return CONFIG_ITEM_FLOAT; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/preferences_widgets.cpp: 
int KeySelectorControl::getType() const { return CONFIG_ITEM_KEY; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: Qt::DropActions PLModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QStringList PLModel::mimeTypes() const
{
    QStringList types;
    types << "vlc/qt-input-items";
    return types;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp:         int row, int, const QModelIndex &parent )
{
    bool copy = action == Qt::CopyAction;
    if( !copy && action != Qt::MoveAction )
        return true;

    const PlMimeData *plMimeData = qobject_cast<const PlMimeData*>( data );
    if( plMimeData )
    {
        if( copy )
            dropAppendCopy( plMimeData, getItem( parent ), row );
        else
            dropMove( plMimeData, getItem( parent ), row );
    }
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: bool PLModel::isParent( const QModelIndex &index, const QModelIndex &current ) const
{
    if( !index.isValid() )
        return false;

    if( index == current )
        return true;

    if( !current.isValid() || !current.parent().isValid() )
        return false;

    return isParent( index, current.parent() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: PLItem* PLModel::getItem( const QModelIndex & index ) const
{
    PLItem *item = static_cast<PLItem *>( VLCModel::getItem( index ) );
    if ( item == NULL ) item = rootItem;
    return item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QModelIndex PLModel::indexByPLID( const int i_plid, const int c ) const
{
    return index( findByPLId( rootItem, i_plid ), c );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QModelIndex PLModel::indexByInputItemID( const int i_inputitem_id, const int c ) const
{
    return index( findByInputId( rootItem, i_inputitem_id ), c );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: PLItem *PLModel::findByPLId( PLItem *root, int i_plitemid ) const
{
    return findInner( root, i_plitemid, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: PLItem *PLModel::findByInputId( PLItem *root, int i_input_itemid ) const
{
    PLItem *result = findInner( root, i_input_itemid, true );
    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: void PLModel::processItemRemoval( int i_pl_itemid )
{
    if( i_pl_itemid <= 0 ) return;
    removeItem( findByPLId( rootItem, i_pl_itemid ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: void PLModel::updateTreeItem( PLItem *item )
{
    if( !item ) return;
    emit dataChanged( index( item, 0 ) , index( item, columnCount( QModelIndex() ) - 1 ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: void PLModel::removeAll()
{
    if( rowCount() < 1 ) return;

    QModelIndexList l;
    for( int i = 0; i < rowCount(); i++)
    {
        QModelIndex indexrecord = index( i, 0, QModelIndex() );
        l.append( indexrecord );
    }
    doDelete(l);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: void PLModel::createNode( QModelIndex index, QString name )
{
    if( name.isEmpty() || !index.isValid() ) return;

    PL_LOCK;
    index = index.parent();
    if ( !index.isValid() ) index = rootIndex();
    playlist_item_t *p_item = playlist_ItemGetById( p_playlist, itemId( index, PLAYLIST_ID ) );
    if( p_item )
        playlist_NodeCreate( p_playlist, qtu( name ), p_item, PLAYLIST_END, 0, NULL );
    PL_UNLOCK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QList<input_item_t*> PlMimeData::inputItems() const
{
    return _inputItems;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QStringList PlMimeData::formats () const
{
    QStringList fmts;
    fmts << "vlc/qt-input-items";
    return fmts;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: int VLCModelSubInterface::columnFromMeta( int meta_col )
{
    int meta = 1, column = 0;

    while( meta != meta_col && meta != COLUMN_END )
    {
        meta <<= 1;
        column++;
    }

    return column;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp:                               int role ) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    int meta_col = columnToMeta( section );

    if( meta_col == COLUMN_END ) return QVariant();

    return QVariant( qfu( psz_column_title( meta_col ) ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: int VLCModel::columnToMeta( int _column )
{
    int meta = 1, column = 0;

    while( column != _column && meta != COLUMN_END )
    {
        meta <<= 1;
        column++;
    }

    return meta;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: int VLCModel::metaToColumn( int _meta )
{
    int meta = 1, column = 0;

    while( meta != COLUMN_END )
    {
        if ( meta & _meta )
            break;
        meta <<= 1;
        column++;
    }

    return column;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: AbstractPLItem *VLCModel::getItem( const QModelIndex &index ) const
{
    if( index.isValid() )
        return static_cast<AbstractPLItem*>( index.internalPointer() );
    else return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: int VLCModel::columnCount( const QModelIndex & ) const
{
    return columnFromMeta( COLUMN_END );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: QSize PlIconViewItemDelegate::sizeHint ( const QStyleOptionViewItem &, const QModelIndex & index ) const
{
    QFont f( index.data( Qt::FontRole ).value<QFont>() );
    f.setPointSize( __MAX( f.pointSize() + i_zoom, 4 ) );
    f.setBold( true );
    QFontMetrics fm( f );
    int textHeight = fm.height();
    int averagewidth = fm.averageCharWidth();
    QSize sz ( averagewidth * ICON_SCALER + 4 * SPACER,
               averagewidth * ICON_SCALER + 4 * SPACER + 2 * textHeight + 1 );
    return sz;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: QSize PlListViewItemDelegate::sizeHint ( const QStyleOptionViewItem &, const QModelIndex & ) const
{
    QFont f;
    f.setBold( true );
    QFontMetrics fm( f );
    int height = qMax( LISTVIEW_ART_SIZE, 2 * fm.height() + 4 ) + 6;
    return QSize( 0, height );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: int PicFlowView::horizontalOffset() const
{
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: int PicFlowView::verticalOffset() const
{
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: QModelIndex PicFlowView::indexAt(const QPoint &) const
{
    return QModelIndex();
    // No idea, PictureFlow doesn't provide anything to help this
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: QModelIndex PicFlowView::moveCursor(QAbstractItemView::CursorAction, Qt::KeyboardModifiers)
{
    return QModelIndex();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/views.cpp: QRegion PicFlowView::visualRegionForSelection(const QItemSelection &) const
{
    return QRect();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_item.cpp: QString PLItem::getTitle() const
{
    QString title;
    char *fb_name = input_item_GetTitle( p_input );
    if( EMPTY_STR( fb_name ) )
    {
        free( fb_name );
        fb_name = input_item_GetName( p_input );
    }
    title = qfu(fb_name);
    free(fb_name);
    return title;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/standardpanel.cpp: int StandardPLPanel::currentViewIndex() const
{
    if( currentView == treeView )
        return TREE_VIEW;
    else if( currentView == iconView )
        return ICON_VIEW;
    else if( currentView == listView )
        return LIST_VIEW;
    else
        return PICTUREFLOW_VIEW;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist.cpp: QSize LocationButton::sizeHint() const
{
    QSize s( fontMetrics().boundingRect( text() ).size() );
    /* Add two pixels to width: font metrics are buggy, if you pass text through elidation
       with exactly the width of its bounding rect, sometimes it still elides */
    s.setWidth( s.width() + ( 2 * PADDING ) + ( b_arrow ? 10 : 0 ) + 2 );
    s.setHeight( s.height() + 2 * PADDING );
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist.cpp: QSplitterHandle *PlaylistSplitter::createHandle()
{
    return new SplitterHandle( orientation(), this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist.cpp: QSize SplitterHandle::sizeHint() const
{
    return (orientation() == Qt::Horizontal) ? QSize( 1, height() ) : QSize( width(), 1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/sorting.h: static inline const char * psz_column_title( uint32_t i_column )
{
    switch( i_column )
    {
    case COLUMN_NUMBER:          return _("ID");
    case COLUMN_TITLE:           return VLC_META_TITLE;
    case COLUMN_DURATION:        return _("Duration");
    case COLUMN_ARTIST:          return VLC_META_ARTIST;
    case COLUMN_GENRE:           return VLC_META_GENRE;
    case COLUMN_ALBUM:           return VLC_META_ALBUM;
    case COLUMN_TRACK_NUMBER:    return VLC_META_TRACK_NUMBER;
    case COLUMN_DESCRIPTION:     return VLC_META_DESCRIPTION;
    case COLUMN_URI:             return _("URI");
    case COLUMN_RATING:          return VLC_META_RATING;
    case COLUMN_COVER:           return _("Cover");
    default: abort();
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/sorting.h: static inline int i_column_sorting( uint32_t i_column )
{
    switch( i_column )
    {
    case COLUMN_NUMBER:         return SORT_ID;
    case COLUMN_TITLE:          return SORT_TITLE_NODES_FIRST;
    case COLUMN_DURATION:       return SORT_DURATION;
    case COLUMN_ARTIST:         return SORT_ARTIST;
    case COLUMN_GENRE:          return SORT_GENRE;
    case COLUMN_ALBUM:          return SORT_ALBUM;
    case COLUMN_TRACK_NUMBER:   return SORT_TRACK_NUMBER;
    case COLUMN_DESCRIPTION:    return SORT_DESCRIPTION;
    case COLUMN_URI:            return SORT_URI;
    case COLUMN_RATING:         return SORT_RATING;
    default: abort();
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/sorting.h: static inline ml_select_e meta_to_mlmeta( uint32_t i_column )
{
    switch( i_column )
    {
    case COLUMN_NUMBER:         return ML_ID;
    case COLUMN_TITLE:          return ML_TITLE;
    case COLUMN_DURATION:       return ML_DURATION;
    case COLUMN_ARTIST:         return ML_ARTIST;
    case COLUMN_GENRE:          return ML_GENRE;
    case COLUMN_ALBUM:          return ML_ALBUM;
    case COLUMN_TRACK_NUMBER:   return ML_TRACK_NUMBER;
    case COLUMN_DESCRIPTION:    return ML_EXTRA;
    case COLUMN_URI:            return ML_URI;
    case COLUMN_RATING:         return ML_VOTE;
    case COLUMN_COVER:          return ML_COVER;
    default: abort();
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/info_panels.cpp: bool MetaPanel::isInEditMode()
{
    return b_inEditMode;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGView.cpp: const QDateTime& EPGView::startTime() const
{
    return m_startTime;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGView.cpp: const QDateTime& EPGView::baseTime() const
{
    return m_baseTime;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGView.cpp: bool EPGView::hasValidData() const
{
    return !epgitemsByChannel.isEmpty();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: QRectF EPGItem::boundingRect() const
{
    return m_boundingRect;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: const QDateTime& EPGItem::start() const
{
    return m_start;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: QDateTime EPGItem::end() const
{
    return QDateTime( m_start ).addSecs( m_duration );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: int EPGItem::duration() const
{
    return m_duration;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: bool EPGItem::endsBefore( const QDateTime &ref ) const
{
    return m_start.addSecs( m_duration ) < ref;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: bool EPGItem::playsAt( const QDateTime & ref ) const
{
    return (m_start <= ref) && !endsBefore( ref );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: QString EPGItem::description() const
{
    if( m_description.isEmpty() )
        return m_shortDescription;

    QString text( m_description );
    if( !m_shortDescription.isEmpty() )
        text += QString(" - ") += m_shortDescription;
    return text;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/interface_widgets.cpp: void TimeLabel::setDisplayPosition( float pos )
{
    if( pos == -1.f || cachedLength == 0 )
    {
        setText( " --:--/--:-- " );
        return;
    }

    int time = pos * cachedLength;
    secstotimestr( psz_time,
                   ( b_remainingTime && cachedLength ?
                   cachedLength - time : time ) );
    QString timestr = QString( "%1%2/%3" )
        .arg( QString( (b_remainingTime && cachedLength) ? "-" : "" ) )
        .arg( QString( psz_time ) )
        .arg( QString( ( !cachedLength && time ) ? "--:--" : psz_length ) );

    setText( timestr );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/extended_panels.cpp: static void ChangeAFiltersString( struct intf_thread_t *p_intf, const char *psz_name, bool b_add )
{
    char *psz_string;

    module_t *p_obj = module_find( psz_name );
    if( !p_obj )
    {
        msg_Err( p_intf, "Unable to find filter module \"%s\".", psz_name );
        return;
    }

    psz_string = ChangeFiltersString( p_intf, "audio-filter", psz_name, b_add );
    if( !psz_string )
        return;

    config_PutPsz( p_intf, "audio-filter", psz_string );

    free( psz_string );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/extended_panels.cpp: int ExtVideo::getPostprocessing( struct intf_thread_t *p_intf)
{
    char *psz_config = config_GetPsz(p_intf, "video-filter");
    int i_q = -1;
    if (psz_config) {
        if (strstr(psz_config, "postproc"))
            i_q = config_GetInt(p_intf, "postproc-q");
        free(psz_config);
    }
    return i_q;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/customwidgets.cpp: QString VLCKeyToString( unsigned val, bool locale )
{
    char *base = vlc_keycode2str (val, locale);
    if (base == NULL)
        return qtr( "Unset" );

    QString r = qfu( base );

    free( base );
    return r;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/animators.hpp: class BasicAnimator : public QAbstractAnimation
{
    Q_OBJECT

public:
    BasicAnimator( QObject *parent = 0 );
    void setFps( int _fps ) { fps = _fps; interval = 1000.0 / fps; }
    virtual int duration() const { return 1000; }

signals:
    void frameChanged();

protected:
    virtual void updateCurrentTime ( int msecs );
    int fps;
    int interval;
    int current_frame;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/animators.hpp: class PixmapAnimator : public BasicAnimator
{
    Q_OBJECT

public:
    PixmapAnimator( QWidget *parent, QList<QString> _frames );
    virtual int duration() const { return interval * pixmaps.count(); }
    virtual ~PixmapAnimator();
    QPixmap *getPixmap() { return currentPixmap; }
protected:
    virtual void updateCurrentTime ( int msecs );
    QList<QPixmap *> pixmaps;
    QPixmap *currentPixmap;
signals:
    void pixmapReady( const QPixmap & );
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.hpp: inline PFreal fmul(PFreal a, PFreal b)
{
    return ((long long)(a))*((long long)(b)) >> PFREAL_SHIFT;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.hpp: inline PFreal fdiv(PFreal num, PFreal den)
{
    long long p = (long long)(num) << (PFREAL_SHIFT * 2);
    long long q = p / (long long)den;
    long long r = q >> PFREAL_SHIFT;

    return r;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.hpp: inline PFreal fcos(int iangle)
{
    return fsin(iangle + (IANGLE_MAX >> 2));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/validators.cpp: QValidator::State UrlValidator::validate( QString& str, int& ) const
{
    if( str.startsWith( ' ' ) )
        return QValidator::Invalid;

    if ( str.isEmpty() )
        return QValidator::Intermediate;

    QUrl url( str );
    if ( url.scheme().isEmpty() )
        return QValidator::Intermediate;

    return ( url.isValid() ) ? QValidator::Acceptable : QValidator::Intermediate;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/customwidgets.hpp: class QFramelessButton : public QPushButton
{
    Q_OBJECT
public:
    QFramelessButton( QWidget *parent = NULL );
    virtual QSize sizeHint() const { return iconSize(); }
protected:
    virtual void paintEvent( QPaintEvent * event );
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/customwidgets.hpp: class QVLCDebugLevelSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    QVLCDebugLevelSpinBox( QWidget *parent ) : QSpinBox( parent ) { };
protected:
    virtual QString textFromValue( int ) const;
    /* QVLCDebugLevelSpinBox is read-only */
    virtual int valueFromText( const QString& ) const { return -1; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/input_slider.cpp: QSize SeekSlider::sizeHint() const
{
    if ( b_classic )
        return QSlider::sizeHint();
    return ( orientation() == Qt::Horizontal ) ? QSize( 100, 18 )
                                               : QSize( 18, 100 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/input_slider.cpp: qreal SeekSlider::handleOpacity() const
{
    return mHandleOpacity;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/searchlineedit.cpp: void SearchLineEdit::setMessageVisible( bool on )
{
    message = on;
    repaint();
    return;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/DeckButtonsLayout.cpp: int DeckButtonsLayout::count() const
{
    return 3;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/DeckButtonsLayout.cpp: QLayoutItem* DeckButtonsLayout::itemAt( int index ) const
{
    switch ( index ) {
        case 0:
            return backwardItem;
        case 1:
            return goItem;
        case 2:
            return forwardItem;
    }

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/DeckButtonsLayout.cpp: void DeckButtonsLayout::setBackwardButton( QAbstractButton* button )
{
    if ( backwardButton && button == backwardButton ) {
        return;
    }

    if ( backwardItem ) {
        delete takeAt( 0 );
    }

    if ( button ) {
        addChildWidget( button );
    }

    backwardItem = new QWidgetItem( button );
    backwardButton = button;

    update();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/DeckButtonsLayout.cpp: void DeckButtonsLayout::setRoundButton( QAbstractButton* button )
{
    if ( RoundButton && button == RoundButton ) {
        return;
    }

    if ( goItem ) {
        delete takeAt( 1 );
    }

    if ( button ) {
        addChildWidget( button );
    }

    goItem = new QWidgetItem( button );
    RoundButton = button;

    update();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/DeckButtonsLayout.cpp: void DeckButtonsLayout::setForwardButton( QAbstractButton* button )
{
    if ( forwardButton && button == forwardButton ) {
        return;
    }

    if ( forwardItem ) {
        delete takeAt( 2 );
    }

    if ( button ) {
        addChildWidget( button );
    }

    forwardItem = new QWidgetItem( button );
    forwardButton = button;

    update();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/BrowseButton.cpp: BrowseButton::Type BrowseButton::type() const
{
    return mType;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/BrowseButton.cpp: QSize BrowseButton::sizeHint() const
{
    return QSize( 50, 26 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/buttons/RoundButton.cpp: QSize RoundButton::sizeHint() const
{
    return QSize( 38, 38 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/registry.cpp: bool QVLCRegistry::RegistryKeyExists( const char *path )
{
    HKEY keyHandle;
    if( RegOpenKeyExA( m_RootKey, path, 0, KEY_READ, &keyHandle ) == ERROR_SUCCESS )
    {
        RegCloseKey( keyHandle );
        return true;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/registry.cpp: bool QVLCRegistry::RegistryValueExists( const char *path, const char *valueName )
{
    HKEY keyHandle;
    bool temp = false;
    DWORD size1;
    DWORD valueType;

    if( RegOpenKeyExA( m_RootKey, path, 0, KEY_READ, &keyHandle ) == ERROR_SUCCESS )
    {
        if( RegQueryValueExA( keyHandle, valueName, NULL,
                             &valueType, NULL, &size1 ) == ERROR_SUCCESS )
        {
           temp = true;
        }
        RegCloseKey( keyHandle );
    }
    return temp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/registry.cpp: int QVLCRegistry::DeleteValue( const char *path, const char *valueName )
{
    HKEY keyHandle;
    long result;
    if( (result = RegOpenKeyExA(m_RootKey, path, 0, KEY_WRITE, &keyHandle)) == ERROR_SUCCESS)
    {
        result = RegDeleteValueA(keyHandle, valueName);
        RegCloseKey(keyHandle);
    }
    //ERROR_SUCCESS = ok everything else you have a problem*g*,
    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/registry.cpp: long QVLCRegistry::DeleteKey( const char *path, const char *keyName )
{
    HKEY keyHandle;
    long result;
    if( (result = RegOpenKeyExA(m_RootKey, path, 0, KEY_WRITE, &keyHandle)) == ERROR_SUCCESS)
    {
         // be warned the key "keyName" will not be deleted if there are subkeys below him, values
        // I think are ok and will be recusively deleted, but not keys...
        // for this case we have to do a little bit more work!
        result = RegDeleteKeyA(keyHandle, keyName);
        RegCloseKey(keyHandle);
    }
    //ERROR_SUCCESS = ok everything else you have a problem*g*,
    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.cpp: static QRgb blendColor(QRgb c1, QRgb c2, int blend)
{
    unsigned int a,r,g,b,as,ad;
    if(blend>255)
        blend=255;
    as=(qAlpha(c1)*blend)/256;
    ad=qAlpha(c2);
    a=as+((255-as)*ad)/256;
    if(a>0)
    {
        r=(as*qRed(c1)+((255-as)*ad*qRed(c2))/256)/a;
        g=(as*qGreen(c1)+((255-as)*ad*qGreen(c2))/256)/a;
        b=(as*qBlue(c1)+((255-as)*ad*qBlue(c2))/256)/a;
    }
    else
    {
        r=g=b=0;
    }
    return qRgba(r, g, b, a);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.cpp: void PictureFlowPrivate::rowsRemoved(const QModelIndex & parent, int start, int end)
{
    if (rootindex != parent)
        return;
    for (int i = start;i <= end;i++)
    {
        removeSlide(i);
        modelmap.removeAt(i);
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/qt_dirs.cpp: QString toURI( const QString& s )
{
    if( s.contains( qfu("://") ) )
        return s;

    char *psz = vlc_path2uri( qtu(s), NULL );
    if( psz == NULL )
        return qfu("");

    QString uri = qfu( psz );
    free( psz );
    return uri;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/qt_dirs.hpp: static inline QString colon_escape( QString s )
{
    return s.replace( ":", "\\:" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/qt_dirs.hpp: static inline QString colon_unescape( QString s )
{
    return s.replace( "\\:", ":" ).trimmed();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/animators.cpp: const QPersistentModelIndex & DelegateAnimationHelper::getIndex() const
{
    return index;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/searchlineedit.hpp: class ClickLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY( QString clickMessage READ placeholderText WRITE setPlaceholderText )
public:
    ClickLineEdit( const QString &msg, QWidget *parent );
    void setPlaceholderText( const QString &msg );
    const QString& placeholderText() const { return mClickMessage; }
    virtual void setText( const QString& txt );
protected:
    virtual void paintEvent( QPaintEvent *e );
    virtual void dropEvent( QDropEvent *ev );
    virtual void focusInEvent( QFocusEvent *ev );
    virtual void focusOutEvent( QFocusEvent *ev );
private:
    QString mClickMessage;
    bool mDrawClickMsg;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/searchlineedit.hpp: class SearchLineEdit : public QMacCocoaViewContainer
{
    Q_OBJECT

public:
    SearchLineEdit(QWidget *parent = 0);
    virtual ~SearchLineEdit() {}

    virtual QSize sizeHint() const { return QSize(150, 40); }

public slots:
    void clear() {}

signals:
    void searchDelayedChanged( const QString& );
    void textEdited( const QString& );
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_scroll.cpp: const string EvtScroll::getAsString() const
{
    string event = "scroll";

    // Add the direction
    if( m_direction == kUp )
        event += ":up";
    else if( m_direction == kDown )
        event += ":down";
    else
        msg_Warn( getIntf(), "unknown scrolling direction" );

    // Add the modifier
    addModifier( event );

    return event;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_focus.hpp: class EvtFocus: public EvtGeneric
{
public:
    EvtFocus( intf_thread_t *pIntf, bool focus )
            : EvtGeneric( pIntf ), m_focus( focus ) { }
    virtual ~EvtFocus() { }

    virtual const string getAsString() const
    {
        return ( m_focus ? "focus:in" : "focus:out" );
    }

private:
    /// true for a focus in, and false for a focus out
    bool m_focus;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_leave.hpp: class EvtLeave: public EvtInput
{
public:
    EvtLeave( intf_thread_t *pIntf ): EvtInput( pIntf ) { }
    virtual ~EvtLeave() { }
    virtual const string getAsString() const { return "leave"; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_menu.hpp: class EvtMenu: public EvtGeneric
{
public:
    EvtMenu( intf_thread_t *pIntf, int itemId )
           : EvtGeneric( pIntf ), m_itemId( itemId ) { }
    virtual ~EvtMenu() { }
    virtual const string getAsString() const { return "menu"; }

    int getItemId() const { return m_itemId; }

private:
    /// Coordinates of the mouse (absolute or relative)
    int m_itemId;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_enter.hpp: class EvtEnter: public EvtInput
{
public:
    EvtEnter( intf_thread_t *pIntf ): EvtInput( pIntf ) { }
    virtual ~EvtEnter() { }
    virtual const string getAsString() const { return "enter"; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_dragndrop.hpp: class EvtDrag: public EvtGeneric
{
public:
    EvtDrag( intf_thread_t *pIntf ): EvtGeneric( pIntf ) { }
    virtual ~EvtDrag() { }
    virtual const string getAsString() const { return "drag"; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_dragndrop.hpp: class EvtDragEnter: public EvtDrag
{
public:
    EvtDragEnter( intf_thread_t *pIntf ): EvtDrag( pIntf ) { }
    virtual ~EvtDragEnter() { }
    virtual const string getAsString() const { return "drag:enter"; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_dragndrop.hpp: class EvtDragLeave: public EvtDrag
{
public:
    EvtDragLeave( intf_thread_t *pIntf ): EvtDrag( pIntf ) { }
    virtual ~EvtDragLeave() { }
    virtual const string getAsString() const { return "drag:leave"; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_dragndrop.hpp: class EvtDragOver: public EvtDrag
{
public:
    EvtDragOver( intf_thread_t *pIntf, int x, int y )
        : EvtDrag( pIntf ), m_xPos( x ), m_yPos( y ) { }
    virtual ~EvtDragOver() { }
    virtual const string getAsString() const { return "drag:over"; }
    // Return the event coordinates
    int getXPos() const { return m_xPos; }
    int getYPos() const { return m_yPos; }
private:
    int m_xPos;
    int m_yPos;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_dragndrop.hpp: class EvtDragDrop: public EvtDrag
{
public:
    EvtDragDrop( intf_thread_t *pIntf, int x, int y, const list<string>& files )
        : EvtDrag( pIntf ), m_files( files ), m_xPos( x ), m_yPos( y ) { }
    virtual ~EvtDragDrop() { }
    virtual const string getAsString() const { return "drag:drop"; }
    // Return the event coordinates
    int getXPos() const { return m_xPos; }
    int getYPos() const { return m_yPos; }
    const list<string>& getFiles() const { return m_files; }
private:
    list<string> m_files;
    int m_xPos;
    int m_yPos;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/events/evt_special.cpp: const string EvtSpecial::getAsString() const
{
    string event = "special";

    // Add the action
    if( m_action == kShow )
        event += ":show";
    else if( m_action == kHide )
        event += ":hide";
    else if( m_action == kEnable )
        event += ":enable";
    else if( m_action == kDisable )
        event += ":disable";
    else
        msg_Warn( getIntf(), "unknown action type" );

    return event;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_graphics.cpp: bool MacOSXGraphics::hit( int x, int y ) const
{
    // TODO
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: bool MacOSXFactory::init()
{
    // TODO
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: OSGraphics *MacOSXFactory::createOSGraphics( int width, int height )
{
    return new MacOSXGraphics( getIntf(), width, height );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: OSLoop *MacOSXFactory::getOSLoop()
{
    return MacOSXLoop::instance( getIntf() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: OSTimer *MacOSXFactory::createOSTimer( CmdGeneric &rCmd )
{
    return new MacOSXTimer( getIntf(), rCmd );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp:                                       bool playOnDrop, OSWindow *pParent )
{
    return new MacOSXWindow( getIntf(), rWindow, dragDrop,
                             playOnDrop, (MacOSXWindow*)pParent );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: OSTooltip *MacOSXFactory::createOSTooltip()
{
    return new MacOSXTooltip( getIntf() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: OSPopup *MacOSXFactory::createOSPopup()
{
    return new MacOSXPopup( getIntf() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: int MacOSXFactory::getScreenWidth() const
{
    // TODO
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: int MacOSXFactory::getScreenHeight() const
{
    // TODO
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/macosx/macosx_factory.cpp: SkinsRect MacOSXFactory::getWorkArea() const
{
    // XXX
    return SkinsRect( 0, 0, getScreenWidth(), getScreenHeight() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_resize.cpp: bool CtrlResize::mouseOver( int x, int y ) const
{
    return m_rCtrl.mouseOver( x, y );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_resize.cpp: const Position *CtrlResize::getPosition() const
{
    return m_rCtrl.getPosition();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_radialslider.cpp: void CtrlRadialSlider::onUpdate( Subject<VarPercent> &rVariable, void *arg )
{
    (void)arg;
    if( &rVariable == &m_rVariable )
    {
        int position = (int)( m_rVariable.get() * ( m_numImg - 1 ) );
        if( position == m_position )
            return;

        m_position = position;
        notifyLayout( m_width, m_height );
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_slider.cpp: static inline float scroll( bool up, float pct, float step )
{
    return pct + ( up ? step : -step );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_slider.cpp: void CtrlSliderBg::onUpdate( Subject<VarPercent> &rVariable, void*arg )
{
    (void)rVariable; (void)arg;
    int position = (int)( m_rVariable.get() * (m_nbHoriz * m_nbVert - 1) );
    if( position == m_position )
        return;

    m_position = position;

    // redraw the entire control
    notifyLayout();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_tree.cpp: CtrlTree::Iterator CtrlTree::findItemAtPos( int pos )
{
    // The first item is m_firstPos.
    // We decrement pos as we try the other items, until pos == 0.
    Iterator it = m_firstPos;
    for( ; it != m_rTree.end() && pos != 0; ++it, pos-- );

    return it;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_tree.cpp: CtrlTree::Iterator CtrlTree::getFirstFromSlider()
{
    // a simple (int)(...) causes rounding errors !
#ifdef _MSC_VER
#       define lrint (int)
#endif
    VarPercent &rVarPos = m_rTree.getPositionVar();
    double percentage = rVarPos.get();

    int excessItems = m_flat ? (m_rTree.countLeafs() - (int)m_capacity)
                             : (m_rTree.visibleItems() - (int)m_capacity);

    int index = (excessItems > 0 ) ?
        lrint( (1.0 - percentage)*(double)excessItems ) :
        0;

    Iterator it_first = m_rTree.getItem( index );

    return it_first;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_tree.cpp: bool CtrlTree::ensureVisible( const Iterator& item )
{
    Iterator it = m_firstPos;
    int max = (int)m_capacity;
    for( int i = 0; i < max && it != m_rTree.end(); ++it, i++ )
    {
        if( it == item )
            return false;
    }

    m_rTree.setSliderFromItem( item );
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_tree.cpp: CtrlTree::Iterator CtrlTree::getNearestItem( const Iterator& item )
{
    // return the previous item if it exists
    Iterator newItem = item;
    if( --newItem != m_rTree.end() && newItem != item )
        return newItem;

    // return the next item if no previous item found
    newItem = item;
    return ++newItem;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_text.cpp: void CtrlText::setPictures( const UString &rText )
{
    // reset the images ('normal' and 'double') from the text
    // 'Normal' image
    delete m_pImg;
    m_pImg = m_rFont.drawString( rText, m_color );
    if( !m_pImg )
        return;

    // 'Double' image
    const UString doubleStringWithSep = rText + SEPARATOR_STRING + rText;
    delete m_pImgDouble;
    m_pImgDouble = m_rFont.drawString( doubleStringWithSep, m_color );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_video.cpp: bool CtrlVideo::mouseOver( int x, int y ) const
{
    (void)x; (void)y;
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_video.cpp: bool CtrlVideo::isUsed( ) const
{
    return m_pVoutWindow ? true : false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_move.cpp: bool CtrlMove::mouseOver( int x, int y ) const
{
    return m_rCtrl.mouseOver( x, y );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_move.cpp: const Position *CtrlMove::getPosition() const
{
    return m_rCtrl.getPosition();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/skin_parser.cpp:                                      const char *a )
{
    if( attr.find(a) == attr.end() )
    {
        msg_Err( getIntf(), "bad theme (element: %s, missing attribute: %s)",
                 name.c_str(), a );
        m_errors = true; return true;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/skin_parser.cpp: bool SkinParser::convertBoolean( const char *value ) const
{
    return strcmp( value, "true" ) == 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/skin_parser.cpp: int SkinParser::convertColor( const char *transcolor )
{
    // TODO: move to the builder
    unsigned long iRed, iGreen, iBlue;
    iRed = iGreen = iBlue = 0;
    sscanf( transcolor, "#%2lX%2lX%2lX", &iRed, &iGreen, &iBlue );
    return ( iRed << 16 | iGreen << 8 | iBlue );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/skin_parser.cpp: int SkinParser::getDimension( string value, int refDimension )
{
    string::size_type leftPos;

    leftPos = value.find( "%" );
    if( leftPos != string::npos )
    {
        int val = atoi( value.substr( 0, leftPos ).c_str() );
        return  val * refDimension / 100;
    }

    leftPos = value.find( "px" );
    if( leftPos != string::npos )
    {
        int val = atoi( value.substr( 0, leftPos ).c_str() );
        return val;
    }

    return atoi( value.c_str() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/expr_evaluator.cpp: string ExprEvaluator::getToken()
{
    if( !m_stack.empty() )
    {
        string token = m_stack.front();
        m_stack.pop_front();
        return token;
    }
    return "";
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/expr_evaluator.cpp: bool ExprEvaluator::hasPrecedency( const string &op1, const string &op2 ) const
{
    // FIXME
    if( op1 == "(" )
    {
        return true;
    }
    if( op1 == "and" )
    {
        return (op2 == "or") || (op2 == "not" );
    }
    if( op1 == "or" )
    {
        return (op2 == "not" );
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/builder.cpp:     else if( abort )\
    { \
        msg_Err( getIntf(), "bitmap required for id: %s", rData.m_id.c_str() ); \
        return; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/parser/builder.cpp: void Builder::addIniFile( const BuilderData::IniFile &rData )
{
    // Parse the INI file
    string full_path = getFilePath( rData.m_file );
    if( !full_path.size() )
        return;

    IniFile iniFile( getIntf(), rData.m_id, full_path );
    iniFile.parseFile();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_window.cpp: bool OS2Window::invalidateRect( int x, int y, int w, int h ) const
{
    RECTL rcl;
    WinQueryWindowRect( m_hWnd, &rcl );

    // Find bottom and invert it
    y = ( rcl.yTop - 1 ) - ( y + h - 1 );
    WinSetRect( 0, &rcl, x, y, x + w, y + h );
    WinInvalidateRect( m_hWndClient, &rcl, TRUE );
    WinUpdateWindow( m_hWndClient );

    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_popup.cpp:     : OSPopup( pIntf ), m_hWnd( hAssociatedWindow )
{
    // Create the popup menu
    m_hMenu = WinCreateWindow( m_hWnd,          // parent
                               WC_MENU,         // menu
                               "",              // title
                               0,               // style
                               0, 0,            // x, y
                               0, 0,            // cx, cy
                               m_hWnd,          // owner
                               HWND_TOP,        // z-order
                               1,               // id
                               NULL, NULL );    // ctrl data, pres params

    if( !m_hMenu )
    {
        msg_Err( getIntf(), "CreatePopupMenu failed" );
        return;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_popup.cpp: unsigned int OS2Popup::findInsertionPoint( unsigned int pos ) const
{
    int nCount = LONGFROMMR( WinSendMsg( m_hMenu, MM_QUERYITEMCOUNT, 0, 0 ));

    // For this simple algorithm, we rely on the fact that in the final state
    // of the menu, the ID of each item is equal to its position in the menu
    int i = 0;
    while( i < nCount &&
           SHORT1FROMMR( WinSendMsg( m_hMenu, MM_ITEMIDFROMPOSITION,
                                     MPFROMLONG( i ), 0 )) < pos )
    {
        i++;
    }
    return i;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_loop.cpp: int OS2Loop::getMod( MPARAM mp ) const
{
    int mod = EvtInput::kModNone;
    if( SHORT2FROMMP( mp ) & KC_CTRL )
        mod |= EvtInput::kModCtrl;
    if( SHORT2FROMMP( mp ) & KC_SHIFT )
        mod |= EvtInput::kModShift;

    return mod;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: OSGraphics *OS2Factory::createOSGraphics( int width, int height )
{
    return new OS2Graphics( getIntf(), width, height );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: OSLoop *OS2Factory::getOSLoop()
{
    return OS2Loop::instance( getIntf() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: OSTimer *OS2Factory::createOSTimer( CmdGeneric &rCmd )
{
    return new OS2Timer( getIntf(), rCmd, m_hParentClientWindow );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp:                                       GenericWindow::WindowType_t type )
{
    return new OS2Window( getIntf(), rWindow, m_hInst, m_hParentClientWindow,
                          dragDrop, playOnDrop, (OS2Window*)pParent, type );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: OSTooltip *OS2Factory::createOSTooltip()
{
    return new OS2Tooltip( getIntf(), m_hInst, m_hParentClientWindow );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: int OS2Factory::getScreenWidth() const
{
    return WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: int OS2Factory::getScreenHeight() const
{
    return WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_factory.cpp: SkinsRect OS2Factory::getWorkArea() const
{
    // TODO : calculate Desktop Workarea excluding WarpCenter

    // Fill a Rect object
    return  SkinsRect( 0, 0, getScreenWidth(), getScreenHeight());
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_timer.cpp: void OS2Timer::stop()
{
    if( !m_hwndTimer )
        return;

    WinStopTimer( 0, m_hwndTimer, ID_TIMER );

    WinDestroyWindow( m_hwndTimer );

    m_hwndTimer = NULLHANDLE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_graphics.cpp: bool OS2Graphics::hit( int x, int y ) const
{
    POINTL ptl = { x, invertPointY( y )};
    return GpiPtInRegion( m_hps, m_mask, &ptl ) == PRGN_INSIDE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/os2/os2_graphics.cpp:                                    int& w_target, int& h_target )
{
    // set valid width and height
    w_target = (w_target > 0) ? w_target : w_src;
    h_target = (h_target > 0) ? h_target : h_src;

    // clip source if needed
    rect srcRegion( x_src, y_src, w_src, h_src );
    rect targetRegion( x_target, y_target, w_target, h_target );
    rect inter;
    if( rect::intersect( srcRegion, targetRegion, &inter ) )
    {
        x_target = inter.x;
        y_target = inter.y;
        w_target = inter.width;
        h_target = inter.height;
        return true;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_graphics.cpp: bool X11Graphics::hit( int x, int y ) const
{
    return XPointInRegion( m_mask, x, y );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_graphics.cpp:                                    int& w_target, int& h_target )
{
    // set valid width and height
    w_target = (w_target > 0) ? w_target : w_src;
    h_target = (h_target > 0) ? h_target : h_src;

    // clip source if needed
    rect srcRegion( x_src, y_src, w_src, h_src );
    rect targetRegion( x_target, y_target, w_target, h_target );
    rect inter;
    if( rect::intersect( srcRegion, targetRegion, &inter ) )
    {
        x_target = inter.x;
        y_target = inter.y;
        w_target = inter.width;
        h_target = inter.height;
        return true;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_loop.cpp: inline int X11Loop::X11ModToMod( unsigned state )
{
    int mod = EvtInput::kModNone;
    if( state & Mod1Mask )
        mod |= EvtInput::kModAlt;
    if( state & ControlMask )
        mod |= EvtInput::kModCtrl;
    if( state & ShiftMask )
        mod |= EvtInput::kModShift;
    return mod;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_popup.cpp: int X11Popup::getPosFromId( int id ) const
{
    // TODO
    (void)id;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_window.cpp: void X11Window::setOpacity( uint8_t value ) const
{
    if( NET_WM_WINDOW_OPACITY == None )
        return;

    if( 255==value )
        XDeleteProperty(XDISPLAY, m_wnd, NET_WM_WINDOW_OPACITY);
    else
    {
        uint32_t opacity = value * ((uint32_t)-1/255);
        XChangeProperty(XDISPLAY, m_wnd, NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned char *) &opacity, 1L);
    }
    XSync( XDISPLAY, False );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_window.cpp: bool X11Window::invalidateRect( int x, int y, int w, int h ) const
{
    XClearArea( XDISPLAY, m_wnd, x, y, w, h, True );
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: OSGraphics *X11Factory::createOSGraphics( int width, int height )
{
    return new X11Graphics( getIntf(), *m_pDisplay, width, height );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: OSLoop *X11Factory::getOSLoop()
{
    return X11Loop::instance( getIntf(), *m_pDisplay );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: OSTimer *X11Factory::createOSTimer( CmdGeneric &rCmd )
{
    return new X11Timer( getIntf(), rCmd );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp:                                       GenericWindow::WindowType_t type )
{
    return new X11Window( getIntf(), rWindow, *m_pDisplay, dragDrop,
                          playOnDrop, (X11Window*)pParent, type );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: OSTooltip *X11Factory::createOSTooltip()
{
    return new X11Tooltip( getIntf(), *m_pDisplay );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: OSPopup *X11Factory::createOSPopup()
{
    return new X11Popup( getIntf(), *m_pDisplay );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: int X11Factory::getScreenWidth() const
{
    return m_screenWidth;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: int X11Factory::getScreenHeight() const
{
    return m_screenHeight;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_factory.cpp: SkinsRect X11Factory::getWorkArea() const
{
    // XXX
    return SkinsRect( 0, 0, getScreenWidth(), getScreenHeight() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_timer.cpp: mtime_t X11Timer::getNextDate() const
{
    return m_nextDate;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_timer.cpp: bool X11Timer::execute()
{
    m_nextDate += m_interval;
    // Execute the callback
    m_rCommand.execute();

    return !m_oneShot;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_timer.cpp: bool X11TimerLoop::sleep( int delay )
{
    struct pollfd ufd;
    memset( &ufd, 0, sizeof (ufd) );
    ufd.fd = m_connectionNumber;
    ufd.events = POLLIN;

    // Wait for an X11 event, or timeout
    return poll( &ufd, 1, delay ) > 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_display.cpp: template<class type> type X11Display::putPixel(type r, type g, type b) const
{
    return ( (r >> m_redRightShift)   << m_redLeftShift   ) |
           ( (g >> m_greenRightShift) << m_greenLeftShift ) |
           ( (b >> m_blueRightShift)  << m_blueLeftShift  );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_display.cpp: type X11Display::blendPixel(type v,type r, type g, type b, type a) const
{
    uint16_t temp;

    temp = ((uint8_t)((v >> m_redLeftShift) << m_redRightShift));
    uint8_t red = r + ( temp * (255 - a) ) / 255;
    temp = ((uint8_t)((v >> m_greenLeftShift) << m_greenRightShift));
    uint8_t green = g + ( temp * (255 - a) ) / 255;
    temp = ((uint8_t)((v >> m_blueLeftShift) << m_blueRightShift));
    uint8_t blue = b + ( temp * (255 - a) ) / 255;

    return putPixel<type>(red,green,blue);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_display.cpp:     const
{
    unsigned long value = putPixel<unsigned long>(r,g,b);

    return m_pixelSize==1 ? 255 - value : value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_muxer.hpp: class CmdMuxer: public CmdGeneric
{
public:
    CmdMuxer( intf_thread_t *pIntf, const list<CmdGeneric*> &rList )
        : CmdGeneric( pIntf ), m_list( rList ) { }
    virtual ~CmdMuxer() { }
    virtual void execute();
    virtual string getType() const { return "muxer"; }

private:
    /// List of commands we will execute sequentially
    typedef std::list<CmdGeneric*> cmdList_t;
    cmdList_t m_list;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_generic.hpp: class Cmd##name: public CmdGeneric                             \
{   public:                                                    \
    Cmd##name( intf_thread_t *pIntf ): CmdGeneric( pIntf ) { } \
    virtual ~Cmd##name() { }                                   \
    virtual void execute();                                    \
    virtual string getType() const { return type; }            \
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_generic.hpp: class CmdGeneric: public SkinObject
{
public:
    virtual ~CmdGeneric() { }

    /// This method does the real job of the command
    virtual void execute() = 0;

    /// Return the type of the command
    virtual string getType() const { return ""; }

    /// During queue reductions, check if we really want to remove
    /// this command.
    virtual bool checkRemove( CmdGeneric * ) const { return true; }

protected:
    CmdGeneric( intf_thread_t *pIntf ): SkinObject( pIntf ) { }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_minimize.hpp: class CmdMaximize: public CmdGeneric
{
public:
    /// Maximize the given layout
    CmdMaximize( intf_thread_t *pIntf, WindowManager &rWindowManager,
                 TopWindow &rWindow );
    virtual ~CmdMaximize() { }
    virtual void execute();
    virtual string getType() const { return "maximize"; }

private:
    WindowManager &m_rWindowManager;
    TopWindow &m_rWindow;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_minimize.hpp: class CmdUnmaximize: public CmdGeneric
{
public:
    /// Unmaximize the given layout
    CmdUnmaximize( intf_thread_t *pIntf, WindowManager &rWindowManager,
                 TopWindow &rWindow );
    virtual ~CmdUnmaximize() { }
    virtual void execute();
    virtual string getType() const { return "unmaximize"; }

private:
    WindowManager &m_rWindowManager;
    TopWindow &m_rWindow;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_on_top.hpp: class CmdSetOnTop: public CmdGeneric
{
public:
    CmdSetOnTop( intf_thread_t *pIntf, bool b_ontop )
        : CmdGeneric( pIntf ), m_ontop( b_ontop ) { }
    virtual ~CmdSetOnTop() { }
    virtual void execute();
    virtual string getType() const { return "set on top"; }

private:
    bool m_ontop;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playtree.hpp: class CmdPlaytreeDel: public CmdGeneric
{
public:
    CmdPlaytreeDel( intf_thread_t *pIntf, VarTree &rTree )
                  : CmdGeneric( pIntf ), m_rTree( rTree ) { }
    virtual ~CmdPlaytreeDel() { }
    virtual void execute();
    virtual string getType() const { return "playtree del"; }

private:
    /// Tree
    VarTree &m_rTree;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_audio.hpp: class CmdSetEqualizer: public CmdGeneric
{
public:
    CmdSetEqualizer( intf_thread_t *pIntf, bool iEnable )
                   : CmdGeneric( pIntf ), m_enable( iEnable ) { }
    virtual ~CmdSetEqualizer() { }
    virtual void execute();
    virtual string getType() const { return "set equalizer"; }

private:
    /// Enable or disable the equalizer
    bool m_enable;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_resize.hpp: class CmdResize: public CmdGeneric
{
public:
    /// Resize the given layout
    CmdResize( intf_thread_t *pIntf, const WindowManager &rWindowManager,
               GenericLayout &rLayout, int width, int height );
    virtual ~CmdResize() { }
    virtual void execute();
    virtual string getType() const { return "resize"; }

private:
    const WindowManager &m_rWindowManager;
    GenericLayout &m_rLayout;
    int m_width, m_height;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_resize.hpp: class CmdResizeVout: public CmdGeneric
{
public:
    /// Resize the given layout
    CmdResizeVout( intf_thread_t *pIntf, vout_window_t* pWnd,
                   int width, int height );
    virtual ~CmdResizeVout() { }
    virtual void execute();
    virtual string getType() const { return "resize vout"; }

private:
    vout_window_t* m_pWnd;
    int m_width, m_height;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_resize.hpp: class CmdSetFullscreen: public CmdGeneric
{
public:
    /// Resize the given layout
    CmdSetFullscreen( intf_thread_t *pIntf, vout_window_t* pWnd,
                      bool fullscreen );
    virtual ~CmdSetFullscreen() { }
    virtual void execute();
    virtual string getType() const { return "toogle fullscreen"; }

private:
    vout_window_t* m_pWnd;
    bool m_bFullscreen;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistDel: public CmdGeneric
{
public:
    CmdPlaylistDel( intf_thread_t *pIntf, VarList &rList )
                  : CmdGeneric( pIntf ), m_rList( rList ) { }
    virtual ~CmdPlaylistDel() { }
    virtual void execute();
    virtual string getType() const { return "playlist del"; }

private:
    /// List
    VarList &m_rList;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistRandom: public CmdGeneric
{
public:
    CmdPlaylistRandom( intf_thread_t *pIntf, bool value )
                     : CmdGeneric( pIntf ), m_value( value ) { }
    virtual ~CmdPlaylistRandom() { }
    virtual void execute();
    virtual string getType() const { return "playlist random"; }

private:
    /// Random state
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistLoop: public CmdGeneric
{
public:
    CmdPlaylistLoop( intf_thread_t *pIntf, bool value )
                   : CmdGeneric( pIntf ), m_value( value ) { }
    virtual ~CmdPlaylistLoop() { }
    virtual void execute();
    virtual string getType() const { return "playlist loop"; }

private:
    /// Loop state
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistRepeat: public CmdGeneric
{
public:
    CmdPlaylistRepeat( intf_thread_t *pIntf, bool value )
                     : CmdGeneric( pIntf ), m_value( value ) { }
    virtual ~CmdPlaylistRepeat() { }
    virtual void execute();
    virtual string getType() const { return "playlist repeat"; }

private:
    /// Repeat state
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistLoad: public CmdGeneric
{
public:
    CmdPlaylistLoad( intf_thread_t *pIntf, const string& rFile )
                   : CmdGeneric( pIntf ), m_file( rFile ) { }
    virtual ~CmdPlaylistLoad() { }
    virtual void execute();
    virtual string getType() const { return "playlist load"; }

private:
    /// Playlist file to load
    string m_file;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_playlist.hpp: class CmdPlaylistSave: public CmdGeneric
{
public:
    CmdPlaylistSave( intf_thread_t *pIntf, const string& rFile )
                   : CmdGeneric( pIntf ), m_file( rFile ) { }
    virtual ~CmdPlaylistSave() { }
    virtual void execute();
    virtual string getType() const { return "playlist save"; }

private:
    /// Playlist file to save
    string m_file;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_vars.hpp: class CmdPlaytreeDelete: public CmdGeneric
{
public:
    CmdPlaytreeDelete( intf_thread_t *pIntf, int i_id ):
        CmdGeneric( pIntf ), m_id( i_id ) { }
    virtual ~CmdPlaytreeDelete() { }
    virtual void execute();
    virtual string getType() const { return "playtree append"; }

private:
    int m_id;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_vars.hpp: class CmdSetText: public CmdGeneric
{
public:
    CmdSetText( intf_thread_t *pIntf, VarText &rText, const UString &rValue ):
        CmdGeneric( pIntf ), m_rText( rText ), m_value( rValue ) { }
    virtual ~CmdSetText() { }
    virtual void execute();
    virtual string getType() const { return "set text"; }

private:
    /// Text variable to set
    VarText &m_rText;
    /// Value to set
    const UString m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_vars.hpp: class CmdSetEqPreamp: public CmdGeneric
{
public:
    CmdSetEqPreamp( intf_thread_t *I, EqualizerPreamp &P, float v )
                  : CmdGeneric( I ), m_rPreamp( P ), m_value( v ) { }
    virtual ~CmdSetEqPreamp() { }
    virtual void execute();
    virtual string getType() const { return "set equalizer preamp"; }

private:
    /// Preamp variable to set
    EqualizerPreamp &m_rPreamp;
    /// Value to set
    float m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_vars.hpp: class CmdSetEqBands: public CmdGeneric
{
public:
    CmdSetEqBands( intf_thread_t *I, EqualizerBands &B, const string &V )
                 : CmdGeneric( I ), m_rEqBands( B ), m_value( V ) { }
    virtual ~CmdSetEqBands() { }
    virtual void execute();
    virtual string getType() const { return "set equalizer bands"; }

private:
    /// Equalizer variable to set
    EqualizerBands &m_rEqBands;
    /// Value to set
    const string m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_show_window.hpp: class CmdShowWindow: public CmdGeneric
{
public:
    CmdShowWindow( intf_thread_t *pIntf, WindowManager &rWinManager,
                   TopWindow &rWin ):
        CmdGeneric( pIntf ), m_rWinManager( rWinManager ), m_rWin( rWin ) { }
    virtual ~CmdShowWindow() { }
    virtual void execute() { m_rWinManager.show( m_rWin ); }
    virtual string getType() const { return "show window"; }

private:
    /// Reference to the window manager
    WindowManager &m_rWinManager;
    /// Reference to the window
    TopWindow &m_rWin;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_show_window.hpp: class CmdHideWindow: public CmdGeneric
{
public:
    CmdHideWindow( intf_thread_t *pIntf, WindowManager &rWinManager,
                   TopWindow &rWin ):
        CmdGeneric( pIntf ), m_rWinManager( rWinManager ), m_rWin( rWin ) { }
    virtual ~CmdHideWindow() { }
    virtual void execute() { m_rWinManager.hide( m_rWin ); }
    virtual string getType() const { return "hide window"; }

private:
    /// Reference to the window manager
    WindowManager &m_rWinManager;
    /// Reference to the window
    TopWindow &m_rWin;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_show_window.hpp: class CmdRaiseAll: public CmdGeneric
{
public:
    CmdRaiseAll( intf_thread_t *pIntf, WindowManager &rWinManager ):
        CmdGeneric( pIntf ), m_rWinManager( rWinManager ) { }
    virtual ~CmdRaiseAll() { }
    virtual void execute() { m_rWinManager.raiseAll(); }
    virtual string getType() const { return "raise all windows"; }

private:
    /// Reference to the window manager
    WindowManager &m_rWinManager;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_layout.hpp: class CmdLayout: public CmdGeneric
{
public:
    CmdLayout( intf_thread_t *pIntf, TopWindow &rWindow,
               GenericLayout &rLayout );
    virtual ~CmdLayout() { }
    virtual void execute();
    virtual string getType() const { return "change layout"; }

private:
    TopWindow &m_rWindow;
    GenericLayout &m_rLayout;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_add_item.hpp: class CmdAddItem: public CmdGeneric
{
public:
    CmdAddItem( intf_thread_t *pIntf, const string &rName, bool playNow )
              : CmdGeneric( pIntf ), m_name( rName ), m_playNow( playNow ) { }
    virtual ~CmdAddItem() { }
    virtual void execute();
    virtual string getType() const { return "add item"; }

private:
    /// Name of the item to enqueue
    string m_name;
    /// Should we play the item immediately?
    bool m_playNow;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/commands/cmd_change_skin.hpp: class CmdChangeSkin: public CmdGeneric
{
public:
    CmdChangeSkin( intf_thread_t *pIntf, const string &rFile ):
        CmdGeneric( pIntf ), m_file( rFile ) { }
    virtual ~CmdChangeSkin() { }
    virtual void execute();
    virtual string getType() const { return "change skin"; }

private:
    /// Skin file to load
    string m_file;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/generic_layout.cpp: const list<LayeredControl> &GenericLayout::getControlList() const
{
    return m_controlList;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/generic_layout.cpp: const list<Anchor*>& GenericLayout::getAnchorList() const
{
    return m_anchorList;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/generic_layout.cpp: bool GenericLayout::isTightlyCoupledWith( const GenericLayout& otherLayout ) const
{
    return m_original_width == otherLayout.m_original_width &&
           m_original_height == otherLayout.m_original_height &&
           m_minWidth == otherLayout.m_minWidth &&
           m_maxWidth == otherLayout.m_maxWidth &&
           m_minHeight == otherLayout.m_minHeight &&
           m_maxHeight == otherLayout.m_maxHeight;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/top_window.cpp: const GenericLayout& TopWindow::getActiveLayout() const
{
    return *m_pActiveLayout;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/art_manager.hpp: class ArtBitmap: public FileBitmap
{
public:

    string getUriName() { return m_uriName; }

    /// Constructor/destructor
    ArtBitmap( intf_thread_t *pIntf, image_handler_t *pImageHandler,
               string uriName ) :
        FileBitmap( pIntf, pImageHandler, uriName, -1 ),
        m_uriName( uriName ) {}
    virtual ~ArtBitmap() {}

private:
    /// uriName
    string m_uriName;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/anchor.cpp: bool Anchor::isHanging( const Anchor &rOther ) const
{
    if( m_priority <= rOther.m_priority )
        return false;

    // Compute delta coordinates between anchors, since the Bezier class
    // uses coordinates relative to (0;0)
    int deltaX = getXPosAbs() - rOther.getXPosAbs();
    int deltaY = getYPosAbs() - rOther.getYPosAbs();

    // One of the anchors (at least) must be a point, else it has no meaning
    return (isPoint() && rOther.m_rCurve.getMinDist( deltaX, deltaY ) == 0) ||
           (rOther.isPoint() && m_rCurve.getMinDist( -deltaX, -deltaY ) == 0);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/vlcproc.cpp:                          vlc_value_t oldval, vlc_value_t newval, void *pParam )
{
    (void)pObj; (void)pVariable; (void)oldval;
    VlcProc *pThis = (VlcProc*)pParam;
    input_thread_t *pInput = static_cast<input_thread_t*>(newval.p_address);

    var_AddCallback( pInput, "intf-event", onGenericCallback2, pThis );
    var_AddCallback( pInput, "bit-rate", onGenericCallback, pThis );
    var_AddCallback( pInput, "sample-rate", onGenericCallback, pThis );
    var_AddCallback( pInput, "can-record", onGenericCallback, pThis );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme.cpp: GenericBitmap *Theme::getBitmapById( const string &id ) const
{
    return m_bitmaps.find_first_object( id );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme.cpp: GenericFont *Theme::getFontById( const string &id ) const
{
    return m_fonts.find_first_object( id );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme_loader.cpp: static voidpf ZCALLBACK open_vlc( voidpf opaque, const char *filename, int mode)
{
    (void)mode;
    intf_thread_t *pIntf = (intf_thread_t *)opaque;

    FILE *stream = vlc_fopen( filename, "rb" );
    if( stream == NULL )
        msg_Dbg( pIntf, "vlc_fopen failed for %s", filename );
    return stream;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme_loader.cpp: int getoct( char *p, int width )
{
    int result = 0;
    char c;

    while( width-- )
    {
        c = *p++;
        if( c == ' ' )
            continue;
        if( c == 0 )
            break;
        result = result * 8 + (c - '0');
    }
    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme_loader.cpp: int gzclose_frontend( int fd )
{
    if( currentGzVp != NULL && fd != -1 )
    {
        void *toClose = currentGzVp;
        currentGzVp = NULL;  currentGzFd = -1;
        return gzclose( (gzFile) toClose );
    }
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme_loader.cpp: int gzread_frontend( int fd, void *p_buffer, size_t i_length )
{
    if( currentGzVp != NULL && fd != -1 )
    {
        return gzread( (gzFile) currentGzVp, p_buffer, i_length );
    }
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/theme_loader.cpp: int gzwrite_frontend( int fd, const void * p_buffer, size_t i_length )
{
    if( currentGzVp != NULL && fd != -1 )
    {
        return gzwrite( (gzFile) currentGzVp, const_cast<void*>(p_buffer), i_length );
    }
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/skin_common.hpp: static inline string sFromLocale( const string &rLocale )
{
    const char *s = FromLocale( rLocale.c_str() );
    string res = s;
    LocaleFree( s );
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/skin_common.hpp: static inline string sFromWide( const wstring &rWide )
{
    char *s = FromWide( rWide.c_str() );
    string res = s;
    free( s );
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/skin_common.hpp: static inline string sToLocale( const string &rUTF8 )
{
    const char *s = ToLocale( rUTF8.c_str() );
    string res = s;
    LocaleFree( s );
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/skin_common.hpp: class SkinObject
{
public:
    SkinObject( intf_thread_t *pIntf ): m_pIntf( pIntf ) { }
    virtual ~SkinObject() { }

    /// Getter (public because it is used in C callbacks in the win32
    /// interface)
    intf_thread_t *getIntf() const { return m_pIntf; }

private:
    intf_thread_t *m_pIntf;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/anim_bitmap.cpp: bool AnimBitmap::operator ==( const AnimBitmap& rOther ) const
{
    return &m_rBitmap == &rOther.m_rBitmap
        && m_nbFrames == rOther.m_nbFrames
        && m_frameRate == rOther.m_frameRate
        && m_nbLoops == rOther.m_nbLoops;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/file_bitmap.cpp: uint8_t *FileBitmap::getData() const
{
    if( m_pData == NULL )
    {
        msg_Warn( getIntf(), "FileBitmap::getData() returns NULL" );
    }
    return m_pData;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: bool UString::operator !=( const UString &rOther ) const
{
    return !(*this == rOther);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: bool UString::operator <=( const UString &rOther ) const
{
    return !( rOther < *this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: bool UString::operator >( const UString &rOther ) const
{
    return ( rOther < *this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: bool UString::operator >=( const UString &rOther ) const
{
    return !( *this < rOther );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: const UString UString::operator +( const UString &rOther ) const
{
    UString result( *this );
    result += rOther;

    return result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: const UString UString::operator +( const char *pString ) const
{
    UString temp( getIntf(), pString );
    return (*this + temp );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: uint32_t UString::find( const char *pString, uint32_t position ) const
{
    UString tmp( getIntf(), pString );
    return find( tmp, position );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/ustring.cpp: UString UString::fromInt( intf_thread_t *pIntf, int number)
{
    stringstream ss;
    ss << number;
    return UString( pIntf, ss.str().c_str() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/bezier.cpp:         __inline long int lrintf( float x )
        {
            int i;
            _asm fld x __asm fistp i
            return i;
        }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/bezier.cpp: inline float Bezier::power( float x, int n )
{
#if 0
    return n <= 0 ? 1 : x * power( x, n - 1 );
#else
    return powf( x, n );
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/position.cpp: int Position::getWidth() const
{
    return getRight() - getLeft() + 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/position.cpp: int Position::getHeight() const
{
    return getBottom() - getTop() + 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/position.cpp: int VarBox::getWidth() const
{
    return m_width;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/position.cpp: int VarBox::getHeight() const
{
    return m_height;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_string.hpp: class VarString: public Variable, public Subject<VarString>
{
public:
    VarString( intf_thread_t *pIntf ): Variable( pIntf ) { }
    virtual ~VarString() { }

    /// Get the variable type
    virtual const string &getType() const { return m_type; }

    /// Set the internal value
    virtual void set( string str );
    virtual string get() const { return m_value; }

private:
    /// Variable type
    static const string m_type;
    /// string value
    string m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBool: public Variable, public Subject<VarBool>
{
public:
    /// Get the variable type
    virtual const string &getType() const { return m_type; }

    /// Get the boolean value
    virtual bool get() const = 0;

protected:
    VarBool( intf_thread_t *pIntf ): Variable( pIntf ) { }
    virtual ~VarBool() { }

private:
    /// Variable type
    static const string m_type;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBoolTrue: public VarBool
{
public:
    VarBoolTrue( intf_thread_t *pIntf ): VarBool( pIntf ) { }
    virtual ~VarBoolTrue() { }
    virtual bool get() const { return true; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBoolFalse: public VarBool
{
public:
    VarBoolFalse( intf_thread_t *pIntf ): VarBool( pIntf ) { }
    virtual ~VarBoolFalse() { }
    virtual bool get() const { return false; }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBoolImpl: public VarBool
{
public:
    VarBoolImpl( intf_thread_t *pIntf );
    virtual ~VarBoolImpl() { }

    // Get the boolean value
    virtual bool get() const { return m_value; }

    /// Set the internal value
    virtual void set( bool value );

private:
    /// Boolean value
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBoolAndBool: public VarBool, public Observer<VarBool>
{
public:
    VarBoolAndBool( intf_thread_t *pIntf, VarBool &rVar1, VarBool &rVar2 );
    virtual ~VarBoolAndBool();
    virtual bool get() const { return m_value; }

    // Called when one of the observed variables is changed
    void onUpdate( Subject<VarBool> &rVariable, void* );

private:
    /// Boolean variables
    VarBool &m_rVar1, &m_rVar2;
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarBoolOrBool: public VarBool, public Observer<VarBool>
{
public:
    VarBoolOrBool( intf_thread_t *pIntf, VarBool &rVar1, VarBool &rVar2 );
    virtual ~VarBoolOrBool();
    virtual bool get() const { return m_value; }

    // Called when one of the observed variables is changed
    void onUpdate( Subject<VarBool> &rVariable, void* );

private:
    /// Boolean variables
    VarBool &m_rVar1, &m_rVar2;
    bool m_value;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_bool.hpp: class VarNotBool: public VarBool, public Observer<VarBool>
{
public:
    VarNotBool( intf_thread_t *pIntf, VarBool &rVar );
    virtual ~VarNotBool();
    virtual bool get() const { return !m_rVar.get(); }

    // Called when the observed variable is changed
    void onUpdate( Subject<VarBool> &rVariable, void* );

private:
    /// Boolean variable
    VarBool &m_rVar;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_tree.cpp:                   int pos )
{
    Iterator it;
    if( pos == -1 )
    {
        it = m_children.end();
    }
    else
    {
        it = m_children.begin();
        for( int i = 0; i < pos && it != m_children.end(); ++it, i++ );
    }

    return m_children.insert( it,
                              VarTree( getIntf(), this, id, rcString,
                                       selected, playing,
                                       expanded, readonly ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_tree.cpp: int VarTree::getIndex( const Iterator& item )
{
    int index = 0;
    Iterator it;
    for( it = m_flat ? firstLeaf() : m_children.begin();
         it != m_children.end();
         it = m_flat ? getNextLeaf( it ) : getNextVisibleItem( it ) )
    {
        if( it == item )
            break;
        index++;
    }
    return (it == item) ? index : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_tree.cpp: VarTree::Iterator VarTree::getItemFromSlider()
{
    // a simple (int)(...) causes rounding errors !
#ifdef _MSC_VER
#       define lrint (int)
#endif
    VarPercent &rVarPos = getPositionVar();
    double percentage = rVarPos.get();

    int indexMax = m_flat ? (countLeafs() - 1)
                          : (visibleItems() - 1);

    int index = lrint( (1.0 - percentage)*(double)indexMax );

    Iterator it_first = m_flat ? getLeaf( index + 1 )
                               : getVisibleItem( index + 1 );
    return it_first;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_tree.cpp: VarTree::IteratorVisible VarTree::getItem( int index )
{
   Iterator it =
        m_flat ? getLeaf( index + 1 )
               : getVisibleItem( index + 1 );

   return IteratorVisible( it, this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/fsm.cpp: void FSM::setState( const string &state )
{
    if( m_states.find( state ) == m_states.end() )
    {
        msg_Warn( getIntf(), "FSM: trying to set an invalid state" );
        return;
    }
    m_currentState = state;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/position.hpp: class SkinsRect: public GenericRect
{
public:
    SkinsRect( int left, int top, int right, int bottom );

    virtual int getLeft() const { return m_left; }
    virtual int getTop() const { return m_top; }
    virtual int getRight() const { return m_right; }
    virtual int getBottom() const { return m_bottom; }
    virtual int getWidth() const { return m_right - m_left; }
    virtual int getHeight() const { return m_bottom - m_top; }

private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/vars/playtree.cpp: UString* Playtree::getTitle( input_item_t *pItem )
{
    char *psz_name = input_item_GetTitleFbName( pItem );
    UString *pTitle = new UString( getIntf(), psz_name );
    free( psz_name );
    return pTitle;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_dragdrop.cpp: STDMETHODIMP Win32DragDrop::QueryInterface( REFIID iid, void FAR* FAR* ppv )
{
    // Tell other objects about our capabilities
    if( iid == IID_IUnknown || iid == IID_IDropTarget )
    {
        *ppv = this;
        AddRef();
        return S_OK;
    }
    *ppv = NULL;
    return ResultFromScode( E_NOINTERFACE );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_dragdrop.cpp: STDMETHODIMP_(ULONG) Win32DragDrop::AddRef()
{
    return ++m_references;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_dragdrop.cpp: STDMETHODIMP_(ULONG) Win32DragDrop::Release()
{
    if( --m_references == 0 )
    {
        delete this;
        return 0;
    }
    return m_references;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_loop.cpp: int Win32Loop::getMod( WPARAM wParam ) const
{
    int mod = EvtInput::kModNone;
    if( wParam & MK_CONTROL )
        mod |= EvtInput::kModCtrl;
    if( wParam & MK_SHIFT )
        mod |= EvtInput::kModShift;

    return mod;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_window.cpp: bool Win32Window::invalidateRect( int x, int y, int w, int h) const
{
    RECT rect = { x, y, x + w , y + h };
    InvalidateRect( m_hWnd, &rect, FALSE );
    UpdateWindow( m_hWnd );

    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_popup.cpp:     : OSPopup( pIntf ), m_hWnd( hAssociatedWindow )
{
    // Create the popup menu
    m_hMenu = CreatePopupMenu();

    if( !m_hMenu )
    {
        msg_Err( getIntf(), "CreatePopupMenu failed" );
        return;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_popup.cpp: unsigned int Win32Popup::findInsertionPoint( unsigned int pos ) const
{
    // For this simple algorithm, we rely on the fact that in the final state
    // of the menu, the ID of each item is equal to its position in the menu
    int i = 0;
    while( i < GetMenuItemCount( m_hMenu ) &&
           GetMenuItemID( m_hMenu, i ) < pos )
    {
        i++;
    }
    return i;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: OSGraphics *Win32Factory::createOSGraphics( int width, int height )
{
    return new Win32Graphics( getIntf(), width, height );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: OSLoop *Win32Factory::getOSLoop()
{
    return Win32Loop::instance( getIntf() );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: OSTimer *Win32Factory::createOSTimer( CmdGeneric &rCmd )
{
    return new Win32Timer( getIntf(), rCmd, m_hParentWindow );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp:                                         GenericWindow::WindowType_t type )
{
    return new Win32Window( getIntf(), rWindow, m_hInst, m_hParentWindow,
                            dragDrop, playOnDrop, (Win32Window*)pParent, type );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: OSTooltip *Win32Factory::createOSTooltip()
{
    return new Win32Tooltip( getIntf(), m_hInst, m_hParentWindow );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: int Win32Factory::getScreenWidth() const
{
    return GetSystemMetrics(SM_CXSCREEN);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: int Win32Factory::getScreenHeight() const
{
    return GetSystemMetrics(SM_CYSCREEN);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: SkinsRect Win32Factory::getWorkArea() const
{
    RECT r;
    SystemParametersInfo( SPI_GETWORKAREA, 0, &r, 0 );
    // Fill a Rect object
    return  SkinsRect( r.left, r.top, r.right, r.bottom );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_graphics.cpp: bool Win32Graphics::hit( int x, int y ) const
{
    return PtInRegion( m_mask, x, y ) != 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_graphics.cpp:                                      int& w_target, int& h_target )
{
    // set valid width and height
    w_target = (w_target > 0) ? w_target : w_src;
    h_target = (h_target > 0) ? h_target : h_src;

    // clip source if needed
    rect srcRegion( x_src, y_src, w_src, h_src );
    rect targetRegion( x_target, y_target, w_target, h_target );
    rect inter;
    if( rect::intersect( srcRegion, targetRegion, &inter ) )
    {
        x_target = inter.x;
        y_target = inter.y;
        w_target = inter.width;
        h_target = inter.height;
        return true;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/ncurses.c: static void DrawEmptyLine(int y, int x, int w)
{
    if (w <= 0) return;

    mvhline(y, x, ' ', w);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/ncurses.c: static void DrawLine(int y, int x, int w)
{
    if (w <= 0) return;

    attrset(A_REVERSE);
    mvhline(y, x, ' ', w);
    attroff(A_REVERSE);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/rc.c:                  vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    intf_thread_t *intf = (intf_thread_t *)p_this;

    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);
    return intf_Create(pl_Get(intf), newval.psz_string );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus.c: int DemarshalSetPropertyValue( DBusMessage *p_msg, void *p_arg )
{
    int  i_type;
    bool b_valid_input = FALSE;
    DBusMessageIter in_args, variant;
    dbus_message_iter_init( p_msg, &in_args );

    do
    {
        i_type = dbus_message_iter_get_arg_type( &in_args );
        if( DBUS_TYPE_VARIANT == i_type )
        {
            dbus_message_iter_recurse( &in_args, &variant );
            dbus_message_iter_get_basic( &variant, p_arg );
            b_valid_input = TRUE;
        }
    } while( dbus_message_iter_next( &in_args ) );

    return b_valid_input ? VLC_SUCCESS : VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalPosition( intf_thread_t *p_intf, DBusMessageIter *container )
{
    /* returns position in microseconds */
    dbus_int64_t i_pos;
    input_thread_t *p_input = pl_CurrentInput( p_intf );

    if( !p_input )
        i_pos = 0;

    else
    {
        i_pos = var_GetTime( p_input, "time" );
        vlc_object_release( p_input );
    }

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_INT64, &i_pos ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: DBUS_METHOD( VolumeSet )
{
    REPLY_INIT;
    double d_dbus_vol;

    if( VLC_SUCCESS != DemarshalSetPropertyValue( p_from, &d_dbus_vol ) )
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    playlist_VolumeSet( PL, fmaxf( d_dbus_vol, 0.f ) );

    REPLY_SEND;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalCanGoNext( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );

    dbus_bool_t b_can_go_next = TRUE;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_go_next ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalCanGoPrevious( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );

    dbus_bool_t b_can_go_previous = TRUE;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_go_previous ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalCanPause( intf_thread_t *p_intf, DBusMessageIter *container )
{
    dbus_bool_t b_can_pause = FALSE;
    input_thread_t *p_input = pl_CurrentInput( p_intf );

    if( p_input )
    {
        b_can_pause = var_GetBool( p_input, "can-pause" );
        vlc_object_release( p_input );
    }

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_pause ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalCanControl( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    dbus_bool_t b_can_control = TRUE;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_control ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalCanSeek( intf_thread_t *p_intf, DBusMessageIter *container )
{
    dbus_bool_t b_can_seek = FALSE;
    input_thread_t *p_input = pl_CurrentInput( p_intf );

    if( p_input )
    {
        b_can_seek = var_GetBool( p_input, "can-seek" );
        vlc_object_release( p_input );
    }

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_seek ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: DBUS_METHOD( ShuffleSet )
{
    REPLY_INIT;
    dbus_bool_t b_shuffle;

    if( VLC_SUCCESS != DemarshalSetPropertyValue( p_from, &b_shuffle ) )
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    var_SetBool( PL, "random", ( b_shuffle == TRUE ) );

    REPLY_SEND;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalRate( intf_thread_t *p_intf, DBusMessageIter *container )
{
    double d_rate;
    input_thread_t *p_input = pl_CurrentInput( p_intf );

    if( p_input != NULL )
    {
        d_rate = var_GetFloat( p_input, "rate" );
        vlc_object_release( (vlc_object_t*) p_input );
    }
    else
        d_rate = 1.0;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_DOUBLE,
                                         &d_rate ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: DBUS_METHOD( RateSet )
{
    REPLY_INIT;

    double d_rate;

    if( VLC_SUCCESS != DemarshalSetPropertyValue( p_from, &d_rate ) )
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    input_thread_t *p_input = pl_CurrentInput( p_this );
    if( p_input != NULL )
    {
        var_SetFloat( p_input, "rate", (float) d_rate );
        vlc_object_release( (vlc_object_t*) p_input );
    }
    else
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    REPLY_SEND;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalMinimumRate( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    double d_min_rate = (double) INPUT_RATE_MIN / INPUT_RATE_DEFAULT;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_DOUBLE, &d_min_rate ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: MarshalMaximumRate( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    double d_max_rate = (double) INPUT_RATE_MAX / INPUT_RATE_DEFAULT;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_DOUBLE, &d_max_rate ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: #define PROPERTY_GET_FUNC( prop, signature ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        if( !dbus_message_iter_open_container( &args, DBUS_TYPE_VARIANT, signature, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        if( VLC_SUCCESS != Marshal##prop( p_this, &v ) ) { \
            dbus_message_iter_abandon_container( &args, &v ); \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        } \
        if( !dbus_message_iter_close_container( &args, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: #define PROPERTY_SET_FUNC( prop ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        return prop##Set( p_conn, p_from, p_this ); \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: #define PROPERTY_MAPPING_END else { return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c:     if( VLC_SUCCESS != AddProperty( (intf_thread_t*) p_this, \
                &dict, #prop, signature, Marshal##prop ) ) { \
        dbus_message_iter_abandon_container( &args, &dict ); \
        return VLC_ENOMEM; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: #define PROPERTY_MAPPING_END else { return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: MarshalIdentity( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const char *psz_id = _("VLC media player");

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_STRING, &psz_id ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: MarshalCanQuit( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const dbus_bool_t b_ret = TRUE;

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN, &b_ret ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: MarshalCanRaise( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const dbus_bool_t b_ret = FALSE;

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN, &b_ret ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: MarshalHasTrackList( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const dbus_bool_t b_ret = FALSE;

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN, &b_ret ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: MarshalDesktopEntry( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const char* psz_ret = PACKAGE;

    if (!dbus_message_iter_append_basic( container, DBUS_TYPE_STRING, &psz_ret ))
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: #define PROPERTY_GET_FUNC( prop, signature ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        if( !dbus_message_iter_open_container( &args, DBUS_TYPE_VARIANT, signature, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        if( VLC_SUCCESS != Marshal##prop( p_this, &v ) ) { \
            dbus_message_iter_abandon_container( &args, &v ); \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        } \
        if( !dbus_message_iter_close_container( &args, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: #define PROPERTY_SET_FUNC( prop ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        return prop##Set( p_conn, p_from, p_this ); \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c: #define PROPERTY_MAPPING_END else { return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_root.c:     if( VLC_SUCCESS != AddProperty( (intf_thread_t*) p_this, \
                &dict, #prop, signature, Marshal##prop ) ) { \
        dbus_message_iter_abandon_container( &args, &dict ); \
        return VLC_ENOMEM; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c: MarshalCanEditTracks( intf_thread_t *p_intf, DBusMessageIter *container )
{
    VLC_UNUSED( p_intf );
    const dbus_bool_t b_ret = TRUE;

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN, &b_ret ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c: #define PROPERTY_GET_FUNC( prop, signature ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        if( !dbus_message_iter_open_container( &args, DBUS_TYPE_VARIANT, signature, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        if( VLC_SUCCESS != Marshal##prop( p_this, &v ) ) { \
            dbus_message_iter_abandon_container( &args, &v ); \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
        } \
        if( !dbus_message_iter_close_container( &args, &v ) ) \
            return DBUS_HANDLER_RESULT_NEED_MEMORY; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c: #define PROPERTY_SET_FUNC( prop ) \
    else if( !strcmp( psz_property_name,  #prop ) ) { \
        return prop##Set( p_conn, p_from, p_this ); \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c: #define PROPERTY_MAPPING_END else { return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c:     if( VLC_SUCCESS != AddProperty( (intf_thread_t*) p_this, \
                &dict, #prop, signature, Marshal##prop ) ) { \
        dbus_message_iter_abandon_container( &args, &dict ); \
        return VLC_ENOMEM; \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_tracklist.c: handle_tracklist ( DBusConnection *p_conn, DBusMessage *p_from, void *p_this )
{
    if(0);

    METHOD_FUNC( DBUS_INTERFACE_PROPERTIES, "Get",    GetProperty );
    METHOD_FUNC( DBUS_INTERFACE_PROPERTIES, "GetAll", GetAllProperties );

    /* here D-Bus method names are associated to an handler */

    METHOD_FUNC( DBUS_MPRIS_TRACKLIST_INTERFACE, "GoTo",        GoTo );
    METHOD_FUNC( DBUS_MPRIS_TRACKLIST_INTERFACE, "AddTrack",    AddTrack );
    METHOD_FUNC( DBUS_MPRIS_TRACKLIST_INTERFACE, "RemoveTrack", RemoveTrack );
    METHOD_FUNC( DBUS_MPRIS_TRACKLIST_INTERFACE, "GetTracksMetadata",
                                                  GetTracksMetadata );

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dummy.c: static int Open( vlc_object_t *p_this )
{
    intf_thread_t *p_intf = (intf_thread_t*) p_this;

#ifdef _WIN32
    bool b_quiet;
    b_quiet = var_InheritBool( p_intf, "dummy-quiet" );
    if( !b_quiet )
        CONSOLE_INTRO_MSG;
#endif

    msg_Info( p_intf, "using the dummy interface module..." );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/globalhotkeys/xcb.c:         xcb_key_symbols_t *p_symbols, unsigned i_vlc )
{
    unsigned i_mask = 0;

    if( i_vlc & KEY_MODIFIER_ALT )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Alt_L ) |
                  GetModifier( p_connection, p_symbols, XK_Alt_R );
    if( i_vlc & KEY_MODIFIER_SHIFT )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Shift_L ) |
                  GetModifier( p_connection, p_symbols, XK_Shift_R );
    if( i_vlc & KEY_MODIFIER_CTRL )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Control_L ) |
                  GetModifier( p_connection, p_symbols, XK_Control_R );
    if( i_vlc & KEY_MODIFIER_META )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Meta_L ) |
                  GetModifier( p_connection, p_symbols, XK_Meta_R ) |
                  GetModifier( p_connection, p_symbols, XK_Super_L ) |
                  GetModifier( p_connection, p_symbols, XK_Super_R );
    return i_mask;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/unimotion.c: int detect_sms()
{
    int kernFunc;
    char *servMatch;
    int dataType;
    union motion_data data;
    int i;

    for ( i = 1; ; i++ ) {
        if ( !set_values(i, &kernFunc, &servMatch, &dataType) )
            break;
        if ( probe_sms(kernFunc, servMatch, dataType, &data) )
            return i;
    }

    return unknown;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/netsync.c: static mtime_t GetPcrSystem(input_thread_t *input)
{
    int canc = vlc_savecancel();
    /* TODO use the delay */
    mtime_t system;
    if (input_GetPcrSystem(input, &system, NULL))
        system = -1;
    vlc_restorecancel(canc);

    return system;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/gestures.c: static inline unsigned gesture( unsigned i_pattern, unsigned i_num )
{
    return ( i_pattern >> ( i_num * 4 ) ) & 0xF;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/hotkeys.c:                         vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    intf_thread_t *p_intf = (intf_thread_t *)p_data;

    (void)libvlc;
    (void)psz_var;
    (void)oldval;

    return PutAction( p_intf, newval.i_int );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/hotkeys.c: static float AdjustRateFine( vlc_object_t *p_obj, const int i_dir )
{
    const float f_rate_min = (float)INPUT_RATE_DEFAULT / INPUT_RATE_MAX;
    const float f_rate_max = (float)INPUT_RATE_DEFAULT / INPUT_RATE_MIN;
    float f_rate = var_GetFloat( p_obj, "rate" );

    int i_sign = f_rate < 0 ? -1 : 1;

    f_rate = floor( fabs(f_rate) / 0.1 + i_dir + 0.05 ) * 0.1;

    if( f_rate < f_rate_min )
        f_rate = f_rate_min;
    else if( f_rate > f_rate_max )
        f_rate = f_rate_max;
    f_rate *= i_sign;

    return f_rate;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/logo.c: static int OpenSub( vlc_object_t *p_this )
{
    return OpenCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/logo.c: static int OpenVideo( vlc_object_t *p_this )
{
    return OpenCommon( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/rotate.c:                            vlc_value_t oldval, vlc_value_t newval, void *data )
{
    filter_sys_t *p_sys = data;

    store_trigo( p_sys, newval.f_float );
    (void) p_this; (void) psz_var; (void) oldval;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/vhs.c: 
static inline int64_t MOD(int64_t a, int64_t b) {
    return ( ( a % b ) + b ) % b; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/ball.c: static int getBallColor( vlc_object_t *p_this, char const *psz_newval )
{
    int ret;
    if( !strcmp( psz_newval, "red" ) )
        ret = RED;
    else if( !strcmp( psz_newval, "blue" ) )
        ret = BLUE;
    else if( !strcmp( psz_newval, "green" ) )
        ret = GREEN;
    else if( !strcmp( psz_newval, "white" ) )
        ret = WHITE;
    else
    {
        msg_Err( p_this, "no valid ball color provided (%s)", psz_newval );
        ret = RED;
    }
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/puzzle_lib.h: void puzzle_fill_rectangle(picture_t *p_pic_out, int32_t x, int32_t y, int32_t i_w, int32_t i_h, uint8_t Y, uint8_t U, uint8_t V );
static inline int32_t init_countdown(int32_t init_val) {
    return ( ( __MAX( 1, 30000 - init_val)/20 ) / 2 + ((unsigned) vlc_mrand48() ) % ( __MAX( 1, ((30000 - init_val)/20) ) ) ); }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/MoMoConnection.cpp: 
ATMO_BOOL CMoMoConnection::isOpen(void) {
	 return (m_hComport != INVALID_HANDLE_VALUE);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoClassicConnection.cpp: 
ATMO_BOOL CAtmoClassicConnection::isOpen(void) {
	 return (m_hComport != INVALID_HANDLE_VALUE);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoDmxSerialConnection.cpp: 
ATMO_BOOL CAtmoDmxSerialConnection::isOpen(void) {
	 return (m_hComport != INVALID_HANDLE_VALUE);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoConfig.cpp: int CAtmoConfig::getZoneCount()
{
    return(m_computed_zones_count);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoConnection.cpp: ATMO_BOOL CAtmoConnection::ShowConfigDialog(HINSTANCE hInst, HWND parent, CAtmoConfig *cfg)
{
    MessageBox(parent, "This device doesn't have a special config dialog", "Info", 0);
    return ATMO_FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoZoneDefinition.cpp: int CAtmoZoneDefinition::getZoneNumber()
{
    return m_zonenumber;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoDynData.cpp: char *CAtmoDynData::getWorkDir()
{
    return m_WorkDir;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoInput.h: */
class CAtmoInput : public CThread {

protected:
    CAtmoDynData         *m_pAtmoDynData;
    CAtmoColorCalculator *m_pAtmoColorCalculator;

public:
    CAtmoInput(CAtmoDynData *pAtmoDynData);
    virtual ~CAtmoInput(void);

    // Opens the input-device.
    // Returns true if the input-device was opened successfully.
    virtual ATMO_BOOL Open(void) { return ATMO_FALSE; }

    // Closes the input-device.
    // Returns true if the input-device was closed successfully.
    virtual ATMO_BOOL Close(void) { return ATMO_FALSE; }

};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/FnordlichtConnection.cpp: ATMO_BOOL CFnordlichtConnection::reset(unsigned char addr)
{
    if(m_hComport == INVALID_HANDLE_VALUE)
        return ATMO_FALSE;

    stop(255);

    if ( sync() && start_bootloader(addr) )
    {
#if defined(_ATMO_VLC_PLUGIN_)
        do_sleep(200000); // wait 200ms
#else
        do_sleep(200); // wait 200ms
#endif
        if ( sync() && boot_enter_application(addr) )
                return ATMO_TRUE;
    }

    return ATMO_FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoThread.cpp: ATMO_BOOL CThread::ThreadSleep(DWORD millisekunden)
{
#if defined(_ATMO_VLC_PLUGIN_)
     ATMO_BOOL temp;
     vlc_mutex_lock( &m_TerminateLock );
     vlc_cond_timedwait(&m_TerminateCond,
                        &m_TerminateLock,
                        mdate() + (mtime_t)(millisekunden * 1000));
     temp = m_bTerminated;
     vlc_mutex_unlock( &m_TerminateLock );
     return !temp;

#else
     DWORD res = WaitForSingleObject(m_hTerminateEvent,millisekunden);
	 return (res == WAIT_TIMEOUT);
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/blend.cpp: static inline unsigned div255(unsigned v)
{
    /* It is exact for 8 bits, and has a max error of 1 for 9 and 10 bits
     * while respecting full opacity/transparency */
    return ((v >> 8) + v + 1) >> 8;
    //return v / 255;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/yuvp.c: static inline uint8_t vlc_uint8( int v )
{
    if( v > 255 )
        return 255;
    else if( v < 0 )
        return 0;
    return v;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/scene.c: static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    /* TODO: think of some funky algorithm to detect scene changes. */
    SnapshotRatio( p_filter, p_pic );
    return p_pic;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/colorthres.c:                        int i_satthres, int i_simthres )
{
    int length = sqrt(u * u + v * v);

    int diffu = refu * length - u * reflength;
    int diffv = refv * length - v * reflength;
    int64_t difflen2 = diffu * diffu + diffv * diffv;
    int64_t thres = length * reflength;
    thres *= thres;
    return length > i_satthres && (difflen2 * i_simthres < thres);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/gradient.c:     if( !p_smooth )
    {
        free( p_hough );
        return;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/sharpen.c: inline static int32_t clip( int32_t a )
{
    return (a > 255) ? 255 : (a < 0) ? 0 : a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/deinterlace/algo_x.c:  */
static inline int ssd( int a ) { return a*a; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/deinterlace/algo_x.c: static inline int median( int a, int b, int c )
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/subsdelay.c: static bool SubsdelayIsTextEmpty( char *psz_text )
{
    if( !psz_text )
    {
        return false;
    }

    psz_text += strspn( psz_text, " " );
    return !( *psz_text );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/grain.c: static uint32_t urand(uint32_t *seed)
{
    uint32_t s = *seed;
    s ^= s << 13;
    s ^= s >> 17;
    s ^= s << 5;
    return *seed = s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/grain.c: static double drand(uint32_t *seed)
{
    return urand(seed) / (double)UINT32_MAX;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/oldmovie.c: 
static inline int64_t MOD(int64_t a, int64_t b) {
    return ( ( a % b ) + b ) % b; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/remoteosd.c:                         int i_bytes )
{
    return i_bytes == net_Read( p_filter, i_socket, NULL,
                                  (unsigned char*)p_readbuf,
                                  i_bytes, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/remoteosd.c:                          int i_bytes )
{
    return i_bytes == net_Write( p_filter, i_socket, NULL,
                                  (unsigned char*)p_writebuf, i_bytes );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/puzzle_bezier.c: point_t *puzzle_H_2_scale_curve_V(int32_t i_width, int32_t i_lines, uint8_t i_pts_nbr, point_t *ps_pt, int32_t i_shape_size)
{
    if (ps_pt == NULL)
        return NULL;

    point_t *ps_bezier_scale_H = puzzle_scale_curve_H(i_lines, i_width, i_pts_nbr, ps_pt, i_shape_size);
    point_t *ps_pts_V = puzzle_curve_H_2_V(i_pts_nbr, ps_bezier_scale_H);
    free(ps_bezier_scale_H);

    return ps_pts_V;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/audiobargraph_v.c: static float iec_scale(float dB)
{
    if (dB < -70.0f)
        return 0.0f;
    if (dB < -60.0f)
        return (dB + 70.0f) * 0.0025f;
    if (dB < -50.0f)
        return (dB + 60.0f) * 0.005f + 0.025f;
    if (dB < -40.0)
        return (dB + 50.0f) * 0.0075f + 0.075f;
    if (dB < -30.0f)
        return (dB + 40.0f) * 0.015f + 0.15f;
    if (dB < -20.0f)
        return (dB + 30.0f) * 0.02f + 0.3f;
    if (dB < -0.001f || dB > 0.001f)  /* if (dB < 0.0f) */
        return (dB + 20.0f) * 0.025f + 0.5f;
    return 1.0f;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/audiobargraph_v.c: static int OpenSub(vlc_object_t *p_this)
{
    return OpenCommon(p_this, true);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/audiobargraph_v.c: static int OpenVideo(vlc_object_t *p_this)
{
    return OpenCommon(p_this, false);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/filter_picture.h: static inline uint8_t vlc_uint8( int v )
{
    if( v > 255 )
        return 255;
    else if( v < 0 )
        return 0;
    return v;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/filter_picture.h: static inline picture_t *CopyInfoAndRelease( picture_t *p_outpic, picture_t *p_inpic )
{
    picture_CopyProperties( p_outpic, p_inpic );

    picture_Release( p_inpic );

    return p_outpic;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/dynamicoverlay/dynamicoverlay_commands.c: static int skip_space( char **psz_command )
{
    char *psz_temp = *psz_command;

    while( isspace( (unsigned char)*psz_temp ) )
    {
        ++psz_temp;
    }
    if( psz_temp == *psz_command )
    {
        return VLC_EGENERIC;
    }
    *psz_command = psz_temp;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/dynamicoverlay/dynamicoverlay_commands.c: static int parse_digit( char **psz_command, int32_t *value )
{
    char *psz_temp;
    *value = strtol( *psz_command, &psz_temp, 10 );
    if( psz_temp == *psz_command )
    {
        return VLC_EGENERIC;
    }
    *psz_command = psz_temp;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/dynamicoverlay/dynamicoverlay_commands.c:                        int count, char *psz_value )
{
    if( *psz_end - *psz_command < count )
    {
        return VLC_EGENERIC;
    }
    memcpy( psz_value, *psz_command, count );
    *psz_command += count;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/dynamicoverlay/dynamicoverlay_commands.c:                         commandparams_t *p_params )
{
    VLC_UNUSED(psz_command);
    VLC_UNUSED(psz_end);
    VLC_UNUSED(p_params);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/dynamicoverlay/dynamicoverlay_commands.c:                             buffer_t *p_output )
{
    VLC_UNUSED(p_results);
    VLC_UNUSED(p_output);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/postproc.c:                         vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    VLC_UNUSED(psz_var); VLC_UNUSED(oldval); VLC_UNUSED(p_data);
    filter_t *p_filter = (filter_t *)p_this;

    char *psz_name = var_GetNonEmptyString( p_filter, FILTER_PREFIX "name" );
    PPChangeMode( p_filter, psz_name, newval.i_int );
    free( psz_name );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/postproc.c:                            vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    VLC_UNUSED(psz_var); VLC_UNUSED(oldval); VLC_UNUSED(p_data);
    filter_t *p_filter = (filter_t *)p_this;

    int i_quality = var_GetInteger( p_filter, FILTER_PREFIX "q" );
    PPChangeMode( p_filter, *newval.psz_string ? newval.psz_string : NULL,
                  i_quality );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/gnutls.c: static int gnutls_Init (vlc_object_t *obj)
{
    const char *version = gnutls_check_version ("3.3.0");
    if (version == NULL)
    {
        msg_Err (obj, "unsupported GnuTLS version");
        return -1;
    }
    msg_Dbg (obj, "using GnuTLS version %s", version);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/gnutls.c: gnutls_SessionPrioritize (vlc_object_t *obj, gnutls_session_t session)
{
    char *priorities = var_InheritString (obj, "gnutls-priorities");
    if (unlikely(priorities == NULL))
        return VLC_ENOMEM;

    const char *errp;
    int val = gnutls_priority_set_direct (session, priorities, &errp);
    if (val < 0)
    {
        msg_Err (obj, "cannot set TLS priorities \"%s\": %s", errp,
                 gnutls_strerror (val));
        val = VLC_EGENERIC;
    }
    else
        val = VLC_SUCCESS;
    free (priorities);
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/stats.c: static block_t *EncodeAudio( encoder_t *p_enc, block_t *p_abuff )
{
    (void)p_abuff;
    (void)p_enc;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/playlist/xspf.c: static char *input_xml( input_item_t *p_item, char *(*func)(input_item_t *) )
{
    char *tmp = func( p_item );
    if( tmp == NULL )
        return NULL;
    char *ret = convert_xml_special_chars( tmp );
    free( tmp );
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/xml/libxml.c: static void Close( vlc_object_t *p_this )
{
#ifdef LIBXML_GETS_A_CLUE_ABOUT_REENTRANCY_AND_MEMORY_LEAKS
    vlc_mutex_lock( &lock );
    xmlCleanupParser();
    vlc_mutex_unlock( &lock );
#endif
    VLC_UNUSED(p_this);
    return;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/xml/libxml.c: static int StreamRead( void *p_context, char *p_buffer, int i_buffer )
{
    stream_t *s = (stream_t*)p_context;
    return stream_Read( s, p_buffer, i_buffer );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/webservices/json.c: static unsigned char hex_value (json_char c)
{
   if (c >= 'A' && c <= 'F')
      return (c - 'A') + 10;

   if (c >= 'a' && c <= 'f')
      return (c - 'a') + 10;

   if (c >= '0' && c <= '9')
      return c - '0';

   return 0xFF;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/webservices/json.c: json_value * json_parse (const json_char * json)
{
   json_settings settings;
   memset (&settings, 0, sizeof (json_settings));

   return json_parse_ex (&settings, json, 0);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/rtsp.c: static int64_t ParseNPT (const char *str)
{
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t oldloc = uselocale (loc);
    unsigned hour, min;
    float sec;

    if (sscanf (str, "%u:%u:%f", &hour, &min, &sec) == 3)
        sec += ((hour * 60) + min) * 60;
    else
    if (sscanf (str, "%f", &sec) != 1)
        sec = 0.;

    if (loc != (locale_t)0)
    {
        uselocale (oldloc);
        freelocale (loc);
    }
    return sec * CLOCK_FREQ;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/logger.c: static bool IgnoreMessage( intf_thread_t *p_intf, int type )
{
    /* TODO: cache value... */
    int verbosity = var_InheritInteger( p_intf, "log-verbose" );
    if (verbosity == -1)
        verbosity = var_InheritInteger( p_intf, "verbose" );

    return verbosity < 0 || verbosity < (type - VLC_MSG_ERR);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/securetransport.c: static int st_Error (vlc_tls_t *obj, int val)
{
    switch (val)
    {
        case errSSLWouldBlock:
            errno = EAGAIN;
            break;

        case errSSLClosedGraceful:
        case errSSLClosedAbort:
            msg_Dbg(obj, "Connection closed with code %d", val);
            errno = ECONNRESET;
            break;
        default:
            msg_Err(obj, "Found error %d", val);
            errno = ECONNRESET;
    }
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/addons/fsstorage.c: static int ListSkin_filter( const char * psz_filename )
{
    int i_len = strlen( psz_filename );
    if ( i_len  <= 4 )
        return 0;
    else
        return ! strcmp( psz_filename + i_len - 4, ".vlt" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/misc/addons/fsstorage.c: static int ListScript_filter( const char * psz_filename )
{
    int i_len = strlen( psz_filename );
    if ( i_len  <= 4 )
        return 0;
    else
        return ! strcmp( psz_filename + i_len - 4, ".lua" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/stereo_widen.c:                            float **pp_write, float f_delay, unsigned i_rate )
{
    const size_t i_size = (2 * (size_t)(1 + f_delay * i_rate / 1000));

    if( unlikely(SIZE_MAX / sizeof(float) < i_size) )
        return VLC_EGENERIC;

    float *p_realloc = realloc( *pp_buffer, i_size * sizeof(float) );
    if( !p_realloc )
        return VLC_ENOMEM;

    memset( p_realloc, 0, i_size * sizeof(float) );
    *pp_write = *pp_buffer = p_realloc;
    *pi_buffer = i_size;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/chorus_flanger.c: static inline float small_value()
{
    /* allows for 2^-24, should be enough for 24-bit DACs at least */
    return ( 1.0 / 16777216.0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/denormals.c: float undenormalise( float f )
{
    if( fpclassify( f ) == FP_SUBNORMAL  )
        return 0.0;
    return f;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/revmodel.cpp: float revmodel::getroomsize()
{
    return (roomsize-offsetroom)/scaleroom;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/revmodel.cpp: float revmodel::getdamp()
{
    return damp/scaledamp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/revmodel.cpp: float revmodel::getwet()
{
    return wet/scalewet;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/revmodel.cpp: float revmodel::getdry()
{
    return dry/scaledry;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/revmodel.cpp: float revmodel::getwidth()
{
    return width;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/comb.cpp: float comb::getdamp()
{
    return damp1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/comb.cpp: float comb::getfeedback()
{
    return feedback;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/spatializer/allpass.cpp: float allpass::getfeedback()
{
    return feedback;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/compressor.c:                                            const float f_inp2 )
{
    return f_in + 0.5f * f_fr * ( f_inp1 - f_inm1 +
         f_fr * ( 4.0f * f_inp1 + 2.0f * f_inm1 - 5.0f * f_in - f_inp2 +
         f_fr * ( 3.0f * ( f_in - f_inp1 ) - f_inm1 + f_inp2 ) ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/compressor.c: static float Max( float f_x, float f_a )
{
    f_x -= f_a;
    f_x += fabs( f_x );
    f_x *= 0.5;
    f_x += f_a;

    return f_x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/compressor.c: static float Clamp( float f_x, float f_a, float f_b )
{
    const float f_x1 = fabs( f_x - f_a );
    const float f_x2 = fabs( f_x - f_b );

    f_x = f_x1 + f_a + f_b;
    f_x -= f_x2;
    f_x *= 0.5;

    return f_x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_filter/compressor.c: static int Round( float f_x )
{
    ls_pcast32 p;

    p.f = f_x;
    p.f += ( 3 << 22 );

    return p.i - 0x4b400000;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/sap.c: static inline int min_int( int a, int b )
{
    return a > b ? b : a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/sap.c: static bool IsWellKnownPayload (int type)
{
    switch (type)
    {   /* Should be in sync with modules/demux/rtp.c */
        case  0: /* PCMU/8000 */
        case  3:
        case  8: /* PCMA/8000 */
        case 10: /* L16/44100/2 */
        case 11: /* L16/44100 */
        case 12:
        case 14: /* MPA/90000 */
        case 32: /* MPV/90000 */
        case 33: /* MP2/90000 */
            return true;
   }
   return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/sap.c: static int Control( demux_t *p_demux, int i_query, va_list args )
{
    VLC_UNUSED(p_demux); VLC_UNUSED(i_query); VLC_UNUSED(args);
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/xcb_apps.c: static int vlc_sd_probe_Open (vlc_object_t *obj)
{
    vlc_probe_t *probe = (vlc_probe_t *)obj;

    char *display = var_InheritString (obj, "x11-display");
    xcb_connection_t *conn = xcb_connect (display, NULL);
    free (display);
    if (xcb_connection_has_error (conn))
        return VLC_PROBE_CONTINUE;
    xcb_disconnect (conn);
    return vlc_sd_probe_Add (probe, "xcb_apps{longname=\"Screen capture\"}",
                             N_("Screen capture"), SD_CAT_DEVICES);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/xcb_apps.c: static int cmpapp (const void *a, const void *b)
{
    xcb_window_t wa = *(xcb_window_t *)a;
    xcb_window_t wb = *(xcb_window_t *)b;

    if (wa > wb)
        return 1;
    if (wa < wb)
        return -1;
    return 0;
} 

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/xcb_apps.c: static void AddDesktop(services_discovery_t *sd)
{
    input_item_t *item;

    item = input_item_NewWithType ("screen://", _("Desktop"),
                                   0, NULL, 0, -1, ITEM_TYPE_CARD);
    if (item == NULL)
        return;

    services_discovery_AddItem (sd, item, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static int cmpdev (const void *a, const void *b)
{
    const dev_t *da = a, *db = b;
    dev_t delta = *da - *db;

    if (sizeof (delta) > sizeof (int))
        return delta ? (((signed)delta > 0) ? 1 : -1) : 0;
    return (signed)delta;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static int hex (char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c + 10 - 'A';
    if (c >= 'a' && c <= 'f')
        return c + 10 - 'a';
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static char *decode_property (struct udev_device *dev, const char *name)
{
    return decode (udev_device_get_property_value (dev, name));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static bool v4l_is_legacy (struct udev_device *dev)
{
    const char *version;

    version = udev_device_get_property_value (dev, "ID_V4L_VERSION");
    return (version != NULL) && !strcmp (version, "1");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static bool v4l_can_capture (struct udev_device *dev)
{
    const char *caps;

    caps = udev_device_get_property_value (dev, "ID_V4L_CAPABILITIES");
    return (caps != NULL) && (strstr (caps, ":capture:") != NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: static char *v4l_get_name (struct udev_device *dev)
{
    const char *prd = udev_device_get_property_value (dev, "ID_V4L_PRODUCT");
    return prd ? strdup (prd) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: int OpenV4L (vlc_object_t *obj)
{
    static const struct subsys subsys = {
        "video4linux", v4l_get_mrl, v4l_get_name, ITEM_TYPE_CARD,
    };

    return Open (obj, &subsys);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c:                             unsigned *restrict pdevice)
{
    const char *node = udev_device_get_devpath (dev);
    char type;

    node = strrchr (node, '/');
    if (node == NULL)
        return -1;
    if (sscanf (node, "/pcmC%uD%u%c", pcard, pdevice, &type) < 3)
        return -1;
    if (type != 'c')
        return -1;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: int OpenALSA (vlc_object_t *obj)
{
    static const struct subsys subsys = {
        "sound", alsa_get_mrl, alsa_get_name, ITEM_TYPE_CARD,
    };

    return Open (obj, &subsys);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/udev.c: int OpenDisc (vlc_object_t *obj)
{
    static const struct subsys subsys = {
        "block", disc_get_mrl, disc_get_name, ITEM_TYPE_DISC,
    };

    return Open (obj, &subsys);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/pulse.c: static int cmpsrc (const void *a, const void *b)
{
    const uint32_t *pa = a, *pb = b;
    uint32_t idxa = *pa, idxb = *pb;

    return (idxa != idxb) ? ((idxa < idxb) ? -1 : +1) : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/pulse.c:                            void *userdata)
{
    services_discovery_t *sd = userdata;

    if (eol)
        return;
    AddSource (sd, i);
    (void) ctx;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/mediadirs.c: static int Open##type( vlc_object_t *p_this )      \
{                                                  \
    msg_Dbg( p_this, "Starting " #type );          \
    return Open( p_this, type );                   \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/mediadirs.c: void formatSnapshotItem( input_item_t *p_item )
{
    if( !p_item )
        return;

    char* psz_uri = input_item_GetURI( p_item );

    /* copy the snapshot mrl as a ArtURL */
    if( psz_uri )
        input_item_SetArtURL( p_item, psz_uri );

    free( psz_uri );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/mediadirs.c: static int vlc_sd_probe_Open( vlc_object_t *obj )
{
    vlc_probe_t *probe = (vlc_probe_t *)obj;

    vlc_sd_probe_Add( probe, "video_dir{longname=\"My Videos\"}",
                      N_("My Videos"), SD_CAT_MYCOMPUTER );
    vlc_sd_probe_Add( probe, "audio_dir{longname=\"My Music\"}",
                      N_("My Music"), SD_CAT_MYCOMPUTER );
    vlc_sd_probe_Add( probe, "picture_dir{longname=\"My Pictures\"}",
                      N_("My Pictures"), SD_CAT_MYCOMPUTER );
    return VLC_PROBE_CONTINUE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp:                                       const char*   psz_tag_name )
{
    assert( p_parent );
    assert( psz_tag_name );

    IXML_NodeList* p_node_list;
    p_node_list = ixmlElement_getElementsByTagName( p_parent, psz_tag_name );
    if ( !p_node_list ) return NULL;

    IXML_Node* p_element = ixmlNodeList_item( p_node_list, 0 );
    ixmlNodeList_free( p_node_list );
    if ( !p_element )   return NULL;

    IXML_Node* p_text_node = ixmlNode_getFirstChild( p_element );
    if ( !p_text_node ) return NULL;

    return ixmlNode_getNodeValue( p_text_node );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp:                                         const char* psz_attribute )
{
    assert( p_parent );
    assert( psz_tag_name );
    assert( psz_attribute );

    IXML_NodeList* p_node_list;
    p_node_list = ixmlElement_getElementsByTagName( p_parent, psz_tag_name );
    if ( !p_node_list )   return NULL;

    IXML_Node* p_element = ixmlNodeList_item( p_node_list, 0 );
    ixmlNodeList_free( p_node_list );
    if ( !p_element )     return NULL;

    return ixmlElement_getAttribute( (IXML_Element*) p_element, psz_attribute );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp:                                       const char*     psz_tag_name )
{
    assert( p_doc );
    assert( psz_tag_name );

    IXML_NodeList* p_node_list;
    p_node_list = ixmlDocument_getElementsByTagName( p_doc, psz_tag_name );
    if ( !p_node_list )  return NULL;

    IXML_Node* p_element = ixmlNodeList_item( p_node_list, 0 );
    ixmlNodeList_free( p_node_list );
    if ( !p_element )    return NULL;

    IXML_Node* p_text_node = ixmlNode_getFirstChild( p_element );
    if ( !p_text_node )  return NULL;

    return ixmlNode_getNodeValue( p_text_node );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp:                    const char* psz_tag_name )
{
    assert( p_doc );
    assert( psz_tag_name );

    const char* psz = xml_getChildElementValue( p_doc, psz_tag_name );

    if( !psz )
        return 0;

    char *psz_end;
    long l = strtol( psz, &psz_end, 10 );

    if( *psz_end || l < 0 || l > INT_MAX )
        return 0;

    return (int)l;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* MediaServer::getUDN() const
{
    return _UDN.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* MediaServer::getFriendlyName() const
{
    return _friendly_name.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* MediaServer::getContentDirectoryEventURL() const
{
    return _content_directory_event_url.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* MediaServer::getContentDirectoryControlURL() const
{
    return _content_directory_control_url.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: void MediaServer::setInputItem( input_item_t* p_input_item )
{
    if( _p_input_item == p_input_item )
        return;

    if( _p_input_item )
        vlc_gc_decref( _p_input_item );

    vlc_gc_incref( p_input_item );
    _p_input_item = p_input_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: input_item_t* MediaServer::getInputItem() const
{
    return _p_input_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: bool MediaServer::compareSID( const char* psz_sid )
{
    return ( strncmp( _subscription_id, psz_sid, sizeof( Upnp_SID ) ) == 0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Item::getObjectID() const
{
    return _objectID.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Item::getTitle() const
{
    return _title.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Item::getResource() const
{
    return _resource.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Item::getSubtitles() const
{
    if( !_subtitles.size() )
        return NULL;

    return _subtitles.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: mtime_t Item::getDuration() const
{
    return _duration;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: char* Item::buildSubTrackIdOption() const
{
    return strdup( ":sub-track-id=2" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: void Item::setInputItem( input_item_t* p_input_item )
{
    if( _p_input_item == p_input_item )
        return;

    if( _p_input_item )
        vlc_gc_decref( _p_input_item );

    vlc_gc_incref( p_input_item );
    _p_input_item = p_input_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Container::getObjectID() const
{
    return _objectID.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: const char* Container::getTitle() const
{
    return _title.c_str();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: unsigned int Container::getNumItems() const
{
    return _items.size();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: unsigned int Container::getNumContainers() const
{
    return _containers.size();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: Container* Container::getParent()
{
    return _parent;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: void Container::setInputItem( input_item_t* p_input_item )
{
    if( _p_input_item == p_input_item )
        return;

    if( _p_input_item )
        vlc_gc_decref( _p_input_item );

    vlc_gc_incref( p_input_item );
    _p_input_item = p_input_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: input_item_t* Container::getInputItem() const
{
    return _p_input_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/avi.c:                                const char *psz_data )
{
    if ( psz_data == NULL ) return 1;
    const char *psz = psz_data;
    AVI_BOX_ENTER( psz_meta );
    while (*psz) bo_AddByte( p_bo, *psz++ );
    bo_AddByte( p_bo, 0 );
    AVI_BOX_EXIT( 0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/ogg.c:                                 ogg_stream_state *p_os, mtime_t i_pts )
{
    return OggStreamGetPage( p_mux, p_os, i_pts, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/ogg.c:                                   ogg_stream_state *p_os, mtime_t i_pts )
{
    return OggStreamGetPage( p_mux, p_os, i_pts, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mp4.c: static int DelStream(sout_mux_t *p_mux, sout_input_t *p_input)
{
    VLC_UNUSED(p_input);
    msg_Dbg(p_mux, "removing input");
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/dummy.c: static int AddStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_input);
    msg_Dbg( p_mux, "adding input" );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/dummy.c: static int DelStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_input);
    msg_Dbg( p_mux, "removing input" );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpeg/ts.c: static int intcompare( const void *pa, const void *pb )
{
    return *(int*)pa - *(int*)pb;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpeg/ts.c: static uint32_t GetDescriptorLength24b( int i_length )
{
    uint32_t i_l1, i_l2, i_l3;

    i_l1 = i_length&0x7f;
    i_l2 = ( i_length >> 7 )&0x7f;
    i_l3 = ( i_length >> 14 )&0x7f;

    return( 0x808000 | ( i_l3 << 16 ) | ( i_l2 << 8 ) | i_l1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpeg/csa.c: csa_t *csa_New( void )
{
    return calloc( 1, sizeof( csa_t ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpjpeg.c: static int DelStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_input);
    msg_Dbg( p_mux, "removing input" );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/vlcpulse.c: static bool context_wait (pa_context *ctx, pa_threaded_mainloop *mainloop)
{
    pa_context_state_t state;

    while ((state = pa_context_get_state (ctx)) != PA_CONTEXT_READY)
    {
        if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
            return -1;
        pa_threaded_mainloop_wait (mainloop);
    }
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/directsound.c: static int DeviceSelect (audio_output_t *aout, const char *id)
{
    var_SetString(aout, "directx-audio-device", (id != NULL) ? id : "");
    aout_DeviceReport (aout, id);
    aout_RestartRequest (aout, AOUT_RESTART_OUTPUT);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/wasapi.c: static BOOL CALLBACK InitFreq(INIT_ONCE *once, void *param, void **context)
{
    (void) once; (void) context;
    return QueryPerformanceFrequency(param);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/waveout.c: static int DeviceSelect (audio_output_t *aout, const char *id)
{
    var_SetString(aout, "waveout-audio-device", (id != NULL) ? id : "");
    aout_DeviceReport (aout, id);
    aout_RestartRequest (aout, AOUT_RESTART_OUTPUT);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved)
{
    (void) dll;
    (void) reserved;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
        {
            HANDLE h = GetModuleHandle(TEXT("kernel32.dll"));
            if (unlikely(h == NULL))
                return FALSE;
            LOOKUP(InitializeConditionVariable);
            LOOKUP(SleepConditionVariableCS);
            LOOKUP(WakeConditionVariable);
            break;
        }
    }
    return TRUE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static int TryEnterMTA(vlc_object_t *obj)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (unlikely(FAILED(hr)))
    {
        msg_Err (obj, "cannot initialize COM (error 0x%lx)", hr);
        return -1;
    }
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static int vlc_FromHR(audio_output_t *aout, HRESULT hr)
{
    /* Restart on unplug */
    if (unlikely(hr == AUDCLNT_E_DEVICE_INVALIDATED))
        aout_RestartRequest(aout, AOUT_RESTART_OUTPUT);
    return SUCCEEDED(hr) ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static inline aout_sys_t *vlc_AudioSessionEvents_sys(IAudioSessionEvents *this)
{
    return (void *)(((char *)this) - offsetof(aout_sys_t, session_events));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c:                                       void **ppv)
{
    if (IsEqualIID(riid, &IID_IUnknown)
     || IsEqualIID(riid, &IID_IAudioSessionEvents))
    {
        *ppv = this;
        IUnknown_AddRef(this);
        return S_OK;
    }
    else
    {
       *ppv = NULL;
        return E_NOINTERFACE;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static inline aout_sys_t *vlc_AudioVolumeDuckNotification_sys(IAudioVolumeDuckNotification *this)
{
    return (void *)(((char *)this) - offsetof(aout_sys_t, duck));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c:     IAudioVolumeDuckNotification *this, REFIID riid, void **ppv)
{
    if (IsEqualIID(riid, &IID_IUnknown)
     || IsEqualIID(riid, &IID_IAudioVolumeDuckNotification))
    {
        *ppv = this;
        IUnknown_AddRef(this);
        return S_OK;
    }
    else
    {
       *ppv = NULL;
        return E_NOINTERFACE;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static inline aout_sys_t *vlc_AudioEndpointVolumeCallback_sys(IAudioEndpointVolumeCallback *this)
{
    return (void *)(((char *)this) - offsetof(aout_sys_t, endpoint_callback));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c:                                                REFIID riid, void **ppv)
{
    if (IsEqualIID(riid, &IID_IUnknown)
     || IsEqualIID(riid, &IID_IAudioEndpointVolumeCallback))
    {
        *ppv = this;
        IUnknown_AddRef(this);
        return S_OK;
    }
    else
    {
       *ppv = NULL;
        return E_NOINTERFACE;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static bool DeviceIsRender(IMMDevice *dev)
{
    void *pv;

    if (FAILED(IMMDevice_QueryInterface(dev, &IID_IMMEndpoint, &pv)))
        return false;

    IMMEndpoint *ep = pv;
    EDataFlow flow;

    if (FAILED(IMMEndpoint_GetDataFlow(ep, &flow)))
        flow = eCapture;

    IMMEndpoint_Release(ep);
    return flow == eRender;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static inline aout_sys_t *vlc_MMNotificationClient_sys(IMMNotificationClient *this)
{
    return (void *)(((char *)this) - offsetof(aout_sys_t, device_events));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c:                                         REFIID riid, void **ppv)
{
    if (IsEqualIID(riid, &IID_IUnknown)
     || IsEqualIID(riid, &IID_IMMNotificationClient))
    {
        *ppv = this;
        IUnknown_AddRef(this);
        return S_OK;
    }
    else
    {
       *ppv = NULL;
        return E_NOINTERFACE;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static wchar_t *var_InheritWide(vlc_object_t *obj, const char *name)
{
    char *v8 = var_InheritString(obj, name);
    if (v8 == NULL)
        return NULL;

    wchar_t *v16 = ToWide(v8);
    free(v8);
    return v16;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c:                               void **restrict pv)
{
    IMMDevice *dev = opaque;
    return IMMDevice_Activate(dev, iid, CLSCTX_ALL, actparms, pv);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/mmdevice.c: static int aout_stream_Start(void *func, va_list ap)
{
    aout_stream_start_t start = func;
    aout_stream_t *s = va_arg(ap, aout_stream_t *);
    audio_sample_format_t *fmt = va_arg(ap, audio_sample_format_t *);
    HRESULT *hr = va_arg(ap, HRESULT *);

    *hr = start(s, fmt, &GUID_VLC_AUD_OUT);
    if (*hr == AUDCLNT_E_DEVICE_INVALIDATED)
        return VLC_ETIMEOUT;
    return SUCCEEDED(*hr) ? VLC_SUCCESS : VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/pulse.c: static int stream_wait(pa_stream *stream, pa_threaded_mainloop *mainloop)
{
    pa_stream_state_t state;

    while ((state = pa_stream_get_state(stream)) != PA_STREAM_READY) {
        if (state == PA_STREAM_FAILED || state == PA_STREAM_TERMINATED)
            return -1;
        pa_threaded_mainloop_wait(mainloop);
    }
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/kai.c:                                    ULONG i_buf_size )
{
    audio_output_t *p_aout = (audio_output_t *)p_cb_data;
    int i_len;

    i_len = ReadBuffer( p_aout, p_buffer, i_buf_size );
    if(( ULONG )i_len < i_buf_size )
        memset(( uint8_t * )p_buffer + i_len, 0, i_buf_size - i_len );

    return i_buf_size;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/auhal.c: static int AudioDeviceHasOutput(AudioDeviceID i_dev_id)
{
    UInt32 dataSize = 0;
    OSStatus status;

    AudioObjectPropertyAddress streamsAddress = { kAudioDevicePropertyStreams, kAudioDevicePropertyScopeOutput, kAudioObjectPropertyElementMaster };
    status = AudioObjectGetPropertyDataSize(i_dev_id, &streamsAddress, 0, NULL, &dataSize);

    if (dataSize == 0 || status != noErr)
        return FALSE;

    return TRUE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/audio_output/winstore.c: static int aout_stream_Start(void *func, va_list ap)
{
    aout_stream_start_t start = func;
    aout_stream_t *s = va_arg(ap, aout_stream_t *);
    audio_sample_format_t *fmt = va_arg(ap, audio_sample_format_t *);
    HRESULT *hr = va_arg(ap, HRESULT *);

    *hr = start(s, fmt, &GUID_VLC_AUD_OUT);
    return SUCCEEDED(*hr) ? VLC_SUCCESS : VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/instance.c: static int strnullcmp(const char *a, const char *b)
{
    if (b == NULL)
        return a != NULL;
    if (a == NULL)
        return -1;
    return strcmp(a, b);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/chroma.c: static picture_t *VideoRender(filter_t *filter, picture_t *src)
{
    return Render(filter, src, false);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/sharpen.c: static float vlc_to_vdp_sigma(float sigma)
{
    sigma /= 2.f;
    if (sigma > +1.f)
        sigma = +1.f;
    if (sigma < -1.f)
        sigma = -1.f;
    return sigma;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c: static float vlc_to_vdp_brightness(float brightness)
{
    brightness -= 1.f;
    if (brightness > +1.f)
        brightness = +1.f;
    if (brightness < -1.f)
        brightness = -1.f;
    return brightness;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c:                               vlc_value_t prev, vlc_value_t cur, void *data)
{
    vlc_atomic_store_float(data, vlc_to_vdp_brightness(cur.f_float));
    (void) obj; (void) varname; (void) prev;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c: static float vlc_to_vdp_contrast(float contrast)
{
    if (contrast > 10.f)
        contrast = 10.f;
    if (contrast < 0.f)
        contrast = 0.f;
    return contrast;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c:                             vlc_value_t prev, vlc_value_t cur, void *data)
{
    vlc_atomic_store_float(data, vlc_to_vdp_contrast(cur.f_float));
    (void) obj; (void) varname; (void) prev;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c:                               vlc_value_t prev, vlc_value_t cur, void *data)
{
    vlc_atomic_store_float(data, vlc_to_vdp_saturation(cur.f_float));
    (void) obj; (void) varname; (void) prev;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c: static float vlc_to_vdp_hue(int hue)
{
    hue %= 360;
    if (hue > 180)
        hue -= 360;
    return (float)hue * (float)(M_PI / 180.);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/adjust.c:                               vlc_value_t prev, vlc_value_t cur, void *data)
{

    vlc_atomic_store_float(data, vlc_to_vdp_hue(cur.i_int));
    (void) obj; (void) varname; (void) prev;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/vlc_vdpau.c:                                                  VdpStatus status)
{
    (void) vdp;
    return (status != VDP_STATUS_OK) ? "Unknown error" : "No error";
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/vlc_vdpau.c: static VdpStatus vdp_fallback(/* UNDEFINED - LEAVE EMPTY */)
{
    return VDP_STATUS_NO_IMPLEMENTATION;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/vlc_vdpau.c:     VdpDevice device, uint32_t drawable, VdpPresentationQueueTarget *target)
{
    void *ptr;
    VdpStatus err = vdp_get_proc_address(vdp, device,
                       VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_CREATE_X11, &ptr);
    if (err != VDP_STATUS_OK)
        return err;

    VdpPresentationQueueTargetCreateX11 *f = ptr;
    return f(device, drawable, target);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/live555.cpp: 
static inline const char *strempty( const char *s ) { return s?s:""; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/live555.cpp: static inline Boolean toBool( bool b ) { return b?True:False; } // silly, no?

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/bd/bd.c: static int SortMpls( const void *a, const void *b )
{
    const bd_mpls_t * const *pp_mpls_a = a;
    const bd_mpls_t * const *pp_mpls_b = b;

    const int64_t i_length_a = GetMplsUniqueDuration( *pp_mpls_a );
    const int64_t i_length_b = GetMplsUniqueDuration( *pp_mpls_b );

    if( i_length_a == i_length_b )
        return 0;
    return i_length_a < i_length_b ? 1 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/bd/bd.c: static block_t *LoadBlock( demux_t *p_demux, const char *psz_name )
{
    stream_t *s = stream_UrlNew( p_demux, psz_name );
    if( !s )
        return NULL;

    const int64_t i_size = stream_Size( s );
    block_t *p_block = NULL;

    if( i_size > 0 && i_size < INT_MAX )
        p_block = stream_Block( s, i_size );

    stream_Delete( s );

    return p_block;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/bd/bd.c: static int ScanSort( const char **ppsz_a, const char **ppsz_b )
{
    return strcmp( *ppsz_a, *ppsz_b );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( !b_use_video && !b_use_audio )
    {
        dialog_Fatal( p_this, _("Capture failed"),
                        _("No video or audio device selected.") );
        return VLC_EGENERIC ;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:         ( b_use_video && !b_use_audio && b_err_video ) )
    {
        msg_Err( p_this, "FATAL: could not open ANY device" ) ;
        dialog_Fatal( p_this,  _("Capture failed"),
                        _("VLC cannot open ANY capture device. "
                          "Check the error log for details.") );
        return VLC_EGENERIC ;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( CommonOpen( p_this, p_sys, true ) != VLC_SUCCESS )
    {
        CommonClose( p_this, p_sys );
        return VLC_EGENERIC;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( CommonOpen( p_this, p_sys, false ) != VLC_SUCCESS )
    {
        CommonClose( p_this, p_sys );
        return VLC_EGENERIC;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     switch( i_fourcc )
    {
    case VLC_CODEC_I420:
    case VLC_CODEC_FL32:
        return 9;
    case VLC_CODEC_YV12:
    case VLC_FOURCC('a','r','a','w'):
        return 8;
    case VLC_CODEC_RGB24:
        return 7;
    case VLC_CODEC_YUYV:
    case VLC_CODEC_RGB32:
    case VLC_CODEC_RGBA:
        return 6;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     else
    {
        msg_Err( p_this, "can't use device: %s, unsupported device type",
                 devicename.c_str() );
        dialog_Fatal( p_this, _("Capture failed"),
                        _("The device you selected cannot be used, because its "
                          "type is not supported.") );
        return VLC_EGENERIC;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( p_class_enum == NULL )
    {
        msg_Err( p_this, "no %s capture device was detected", ( b_audio ? "audio" : "video" ) );
        return NULL;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     switch( i_query )
    {
    case ACCESS_CAN_SEEK:
    case ACCESS_CAN_FASTSEEK:
    case ACCESS_CAN_PAUSE:
    case ACCESS_CAN_CONTROL_PACE:
        pb_bool = (bool*)va_arg( args, bool* );
        *pb_bool = false;
        break;

    case ACCESS_GET_PTS_DELAY:
        pi_64 = (int64_t*)va_arg( args, int64_t * );
        *pi_64 =
            INT64_C(1000) * var_InheritInteger( p_access, "live-caching" );
        break;

    default:
        return VLC_EGENERIC;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( !p_item )
    {
        free( psz_device );
        CoUninitialize();
        return VLC_SUCCESS;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     else
    {
        /* If no device name was specified, pick the 1st one */
        list<string> list_devices;

        /* Enumerate devices */
        FindCaptureDevice( p_this, NULL, &list_devices, b_audio );
        if( list_devices.empty() )
        {
            CoUninitialize();
            return VLC_EGENERIC;
        }
        devicename = *list_devices.begin();
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( FAILED(hr) )
    {
        msg_Dbg( p_this, "couldn't find tuner interface" );
        return;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: HRESULT CapturePin::CustomGetSamples( deque<VLCMediaSample> &external_queue )
{
#if 0 //def DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::CustomGetSamples: %d samples in the queue", samples_queue.size());
#endif

    if( !samples_queue.empty() )
    {
        external_queue.swap(samples_queue);
        return S_OK;
    }
    return S_FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: HRESULT CapturePin::CustomGetSample( VLCMediaSample *vlc_sample )
{
#if 0 //def DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::CustomGetSample" );
#endif

    if( !samples_queue.empty() )
    {
        *vlc_sample = samples_queue.back();
        samples_queue.pop_back();
        return S_OK;
    }
    return S_FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: AM_MEDIA_TYPE &CapturePin::CustomGetMediaType()
{
    return cx_media_type;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CapturePin::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CapturePin::AddRef (ref: %i)", i_ref );
#endif

    return i_ref++;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CapturePin::Release()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CapturePin::Release (ref: %i)", i_ref );
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::QueryDirection( PIN_DIRECTION * pPinDir )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::QueryDirection" );
#endif

    *pPinDir = PINDIR_INPUT;
    return NOERROR;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::QueryId( LPWSTR * Id )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::QueryId" );
#endif

    *Id = (LPWSTR)L"VLC Capture Pin";

    return S_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::EnumMediaTypes( IEnumMediaTypes **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CapturePin::EnumMediaTypes" );
#endif

    *ppEnum = new CaptureEnumMediaTypes( p_input, this, NULL );

    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::QueryInternalConnections( IPin**, ULONG * )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CapturePin::QueryInternalConnections" );
#endif
    return E_NOTIMPL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::EndOfStream( void )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::EndOfStream" );
#endif
    return S_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::BeginFlush( void )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::BeginFlush" );
#endif
    return S_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::NewSegment( REFERENCE_TIME, REFERENCE_TIME, double )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::NewSegment" );
#endif
    return S_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::GetAllocator( IMemAllocator ** )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::GetAllocator" );
#endif

    return VFW_E_NO_ALLOCATOR;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::NotifyAllocator( IMemAllocator *, BOOL )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::NotifyAllocator" );
#endif

    return S_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::GetAllocatorRequirements( ALLOCATOR_PROPERTIES * )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::GetAllocatorRequirements" );
#endif

    return E_NOTIMPL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CapturePin::ReceiveCanBlock( void )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CapturePin::ReceiveCanBlock" );
#endif

    return S_FALSE; /* Thou shalt not block */
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureFilter::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureFilter::AddRef (ref: %i)", i_ref );
#endif

    return i_ref++;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureFilter::Release()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureFilter::Release (ref: %i)", i_ref );
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::GetClassID(CLSID *)
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::GetClassID" );
#endif
    return E_NOTIMPL;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::GetState(DWORD, FILTER_STATE *State)
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::GetState %i", state );
#endif

    *State = state;
    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::SetSyncSource(IReferenceClock *)
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::SetSyncSource" );
#endif

    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::GetSyncSource(IReferenceClock **pClock)
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::GetSyncSource" );
#endif

    *pClock = NULL;
    return NOERROR;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::Pause()
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::Pause" );
#endif

    state = State_Paused;
    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::Run(REFERENCE_TIME)
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::Run" );
#endif

    state = State_Running;
    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::EnumPins( IEnumPins ** ppEnum )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::EnumPins" );
#endif

    /* Create a new ref counted enumerator */
    *ppEnum = new CaptureEnumPins( p_input, this, NULL );
    return *ppEnum == NULL ? E_OUTOFMEMORY : NOERROR;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::FindPin( LPCWSTR, IPin ** )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::FindPin" );
#endif
    return E_NOTIMPL;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp:                                              LPCWSTR )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::JoinFilterGraph" );
#endif

    p_graph = pGraph;

    return NOERROR;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureFilter::QueryVendorInfo( LPWSTR* )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::QueryVendorInfo" );
#endif
    return E_NOTIMPL;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: CapturePin *CaptureFilter::CustomGetPin()
{
    return p_pin;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumPins::QueryInterface( REFIID riid, void **ppv )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::QueryInterface" );
#endif

    if( riid == IID_IUnknown ||
        riid == IID_IEnumPins )
    {
        AddRef();
        *ppv = (IEnumPins *)this;
        return NOERROR;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureEnumPins::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::AddRef (ref: %i)", i_ref );
#endif

    return i_ref++;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureEnumPins::Release()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::Release (ref: %i)", i_ref );
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumPins::Skip( ULONG cPins )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::Skip" );
#endif

    i_position += cPins;

    if( i_position > 1 )
    {
        return S_FALSE;
    }

    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumPins::Reset()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::Reset" );
#endif

    i_position = 0;
    return S_OK;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumPins::Clone( IEnumPins **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumPins::Clone" );
#endif

    *ppEnum = new CaptureEnumPins( p_input, p_filter, this );
    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumMediaTypes::QueryInterface( REFIID riid, void **ppv )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumMediaTypes::QueryInterface" );
#endif

    if( riid == IID_IUnknown ||
        riid == IID_IEnumMediaTypes )
    {
        AddRef();
        *ppv = (IEnumMediaTypes *)this;
        return NOERROR;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureEnumMediaTypes::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumMediaTypes::AddRef (ref: %i)", i_ref );
#endif

    return i_ref++;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP_(ULONG) CaptureEnumMediaTypes::Release()
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumMediaTypes::Release (ref: %i)", i_ref );
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp: STDMETHODIMP CaptureEnumMediaTypes::Clone( IEnumMediaTypes **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    msg_Dbg( p_input, "CaptureEnumMediaTypes::Clone" );
#endif

    *ppEnum = new CaptureEnumMediaTypes( p_input, p_pin, this );
    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
};

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/screen/xcb.c: static bool CheckSHM (xcb_connection_t *conn)
{
#ifdef HAVE_SYS_SHM_H
    xcb_shm_query_version_cookie_t ck = xcb_shm_query_version (conn);
    xcb_shm_query_version_reply_t *r;

    r = xcb_shm_query_version_reply (conn, ck, NULL);
    free (r);
    return r != NULL;
#else
    (void) conn;
    return false;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/scan.c: static uint32_t decode_BCD( uint32_t input )
{
    uint32_t output = 0;
    for( short index=28; index >= 0 ; index -= 4 )
    {
        output *= 10;
        output += ((input >> index) & 0x0f);
    };
    return output;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/scan.c: static int scan_service_type( int service_type )
{
    switch( service_type )
    {
    case 0x01: return SERVICE_DIGITAL_TELEVISION; break;
    case 0x02: return SERVICE_DIGITAL_RADIO; break;
    case 0x16: return SERVICE_DIGITAL_TELEVISION_AC_SD; break;
    case 0x19: return SERVICE_DIGITAL_TELEVISION_AC_HD; break;
    default:   return SERVICE_UNKNOWN; break;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: static fe_spectral_inversion_t DecodeInversion( access_t *p_access )
{
    int i_val;
    fe_spectral_inversion_t fe_inversion = 0;

    i_val = var_GetInteger( p_access, "dvb-inversion" );
    msg_Dbg( p_access, "using inversion=%d", i_val );

    switch( i_val )
    {
        case 0: fe_inversion = INVERSION_OFF; break;
        case 1: fe_inversion = INVERSION_ON; break;
        case 2: fe_inversion = INVERSION_AUTO; break;
        default:
            msg_Dbg( p_access, "dvb has inversion not set, using auto");
            fe_inversion = INVERSION_AUTO;
            break;
    }
    return fe_inversion;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: static fe_sec_voltage_t DecodeVoltage( access_t *p_access )
{
    switch( var_GetInteger( p_access, "dvb-voltage" ) )
    {
        case 0:  return SEC_VOLTAGE_OFF;
        case 13: return SEC_VOLTAGE_13;
        case 18: return SEC_VOLTAGE_18;
        default: return SEC_VOLTAGE_OFF;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: static fe_sec_tone_mode_t DecodeTone( access_t *p_access )
{
    switch( var_GetInteger( p_access, "dvb-tone" ) )
    {
        case 0:  return SEC_TONE_OFF;
        case 1:  return SEC_TONE_ON;
        default: return SEC_TONE_OFF;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: static fe_bandwidth_t DecodeBandwidth( access_t *p_access )
{
    fe_bandwidth_t      fe_bandwidth = 0;
    int i_bandwidth = var_GetInteger( p_access, "dvb-bandwidth" );

    msg_Dbg( p_access, "using bandwidth=%d", i_bandwidth );

    switch( i_bandwidth )
    {
        case 0: fe_bandwidth = BANDWIDTH_AUTO; break;
        case 6: fe_bandwidth = BANDWIDTH_6_MHZ; break;
        case 7: fe_bandwidth = BANDWIDTH_7_MHZ; break;
        case 8: fe_bandwidth = BANDWIDTH_8_MHZ; break;
        default:
            msg_Dbg( p_access, "terrestrial dvb has bandwidth not set, using auto" );
            fe_bandwidth = BANDWIDTH_AUTO;
            break;
    }
    return fe_bandwidth;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: static fe_transmit_mode_t DecodeTransmission( access_t *p_access )
{
    fe_transmit_mode_t  fe_transmission = 0;
    int i_transmission = var_GetInteger( p_access, "dvb-transmission" );

    msg_Dbg( p_access, "using transmission=%d", i_transmission );

    switch( i_transmission )
    {
        case 0: fe_transmission = TRANSMISSION_MODE_AUTO; break;
        case 2: fe_transmission = TRANSMISSION_MODE_2K; break;
        case 8: fe_transmission = TRANSMISSION_MODE_8K; break;
        default:
            msg_Dbg( p_access, "terrestrial dvb has transmission mode not set, using auto");
            fe_transmission = TRANSMISSION_MODE_AUTO;
            break;
    }
    return fe_transmission;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvb/linux_dvb.c: int DMXUnsetFilter( access_t * p_access, int i_fd )
{
    if( ioctl( i_fd, DMX_STOP ) < 0 )
    {
        msg_Err( p_access, "stopping demux failed: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_access, "DMXUnsetFilter: closing demux %d", i_fd );
    close( i_fd );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/en50221.c: static uint8_t *GetLength( uint8_t *p_data, int *pi_length )
{
    *pi_length = *p_data++;

    if ( (*pi_length & SIZE_INDICATOR) != 0 )
    {
        int l = *pi_length & ~SIZE_INDICATOR;
        int i;

        *pi_length = 0;
        for ( i = 0; i < l; i++ )
            *pi_length = (*pi_length << 8) | *p_data++;
    }

    return p_data;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/en50221.c: static int APDUGetTag( const uint8_t *p_apdu, int i_size )
{
    if ( i_size >= 3 )
    {
        int i, t = 0;
        for ( i = 0; i < 3; i++ )
            t = (t << 8) | *p_apdu++;
        return t;
    }

    return AOT_NONE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static uint64_t var_InheritFrequency (vlc_object_t *obj)
{
    uint64_t freq = var_InheritInteger (obj, "dvb-frequency");
    if (freq != 0 && freq < 30000000)
    {
        msg_Err (obj, "%"PRIu64" Hz carrier frequency is too low.", freq);
        freq *= 1000;
        msg_Info (obj, "Assuming %"PRIu64" Hz frequency instead.", freq);
    }
    return freq;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int modcmp (const void *a, const void *b)
{
    return strcasecmp (a, *(const char *const *)b);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int atsc_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");

    return dvb_set_atsc (dev, freq, mod);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int cqam_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");

    return dvb_set_cqam (dev, freq, mod);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int dvbc_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    unsigned srate = var_InheritInteger (obj, "dvb-srate");

    return dvb_set_dvbc (dev, freq, mod, srate, fec);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int dvbs_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    uint32_t srate = var_InheritInteger (obj, "dvb-srate");

    int ret = dvb_set_dvbs (dev, freq, srate, fec);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int dvbs2_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    uint32_t srate = var_InheritInteger (obj, "dvb-srate");
    int pilot = var_InheritInteger (obj, "dvb-pilot");
    int rolloff = var_InheritInteger (obj, "dvb-rolloff");
    uint8_t sid = var_InheritInteger (obj, "dvb-stream");

    int ret = dvb_set_dvbs2 (dev, freq, mod, srate, fec, pilot, rolloff, sid);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int dvbt_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec_hp = var_InheritCodeRate (obj, "dvb-code-rate-hp");
    uint32_t fec_lp = var_InheritCodeRate (obj, "dvb-code-rate-lp");
    uint32_t guard = var_InheritGuardInterval (obj);
    uint32_t bw = var_InheritInteger (obj, "dvb-bandwidth");
    int tx = var_InheritInteger (obj, "dvb-transmission");
    int h = var_InheritInteger (obj, "dvb-hierarchy");

    return dvb_set_dvbt (dev, freq, mod, fec_hp, fec_lp, bw, tx, guard, h);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int dvbt2_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    uint32_t guard = var_InheritGuardInterval (obj);
    uint32_t bw = var_InheritInteger (obj, "dvb-bandwidth");
    uint32_t plp = var_InheritInteger (obj, "dvb-plp-id");
    int tx = var_InheritInteger (obj, "dvb-transmission");

    return dvb_set_dvbt2 (dev, freq, mod, fec, bw, tx, guard, plp);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int isdbc_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    unsigned srate = var_InheritInteger (obj, "dvb-srate");

    return dvb_set_isdbc (dev, freq, mod, srate, fec);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/access.c: static int isdbs_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    uint16_t ts_id = var_InheritInteger (obj, "dvb-ts-id");

    int ret = dvb_set_isdbs (dev, freq, ts_id);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static ModulationType dvb_parse_modulation (const char *mod)
{
    if (!strcmp (mod, "16QAM"))   return BDA_MOD_16QAM;
    if (!strcmp (mod, "32QAM"))   return BDA_MOD_32QAM;
    if (!strcmp (mod, "64QAM"))   return BDA_MOD_64QAM;
    if (!strcmp (mod, "128QAM"))  return BDA_MOD_128QAM;
    if (!strcmp (mod, "256QAM"))  return BDA_MOD_256QAM;
    return BDA_MOD_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static BinaryConvolutionCodeRate dvb_parse_fec (uint32_t fec)
{
    switch (fec)
    {
        case VLC_FEC(1,2): return BDA_BCC_RATE_1_2;
        case VLC_FEC(2,3): return BDA_BCC_RATE_2_3;
        case VLC_FEC(3,4): return BDA_BCC_RATE_3_4;
        case VLC_FEC(5,6): return BDA_BCC_RATE_5_6;
        case VLC_FEC(7,8): return BDA_BCC_RATE_7_8;
    }
    return BDA_BCC_RATE_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static GuardInterval dvb_parse_guard (uint32_t guard)
{
    switch (guard)
    {
        case VLC_GUARD(1, 4): return BDA_GUARD_1_4;
        case VLC_GUARD(1, 8): return BDA_GUARD_1_8;
        case VLC_GUARD(1,16): return BDA_GUARD_1_16;
        case VLC_GUARD(1,32): return BDA_GUARD_1_32;
    }
    return BDA_GUARD_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static TransmissionMode dvb_parse_transmission (int transmit)
{
    switch (transmit)
    {
        case 2: return BDA_XMIT_MODE_2K;
        case 8: return BDA_XMIT_MODE_8K;
    }
    return BDA_XMIT_MODE_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static HierarchyAlpha dvb_parse_hierarchy (int hierarchy)
{
    switch (hierarchy)
    {
        case 1: return BDA_HALPHA_1;
        case 2: return BDA_HALPHA_2;
        case 4: return BDA_HALPHA_4;
    }
    return BDA_HALPHA_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static Polarisation dvb_parse_polarization (char pol)
{
    switch (pol)
    {
        case 'H': return BDA_POLARISATION_LINEAR_H;
        case 'V': return BDA_POLARISATION_LINEAR_V;
        case 'L': return BDA_POLARISATION_CIRCULAR_L;
        case 'R': return BDA_POLARISATION_CIRCULAR_R;
    }
    return BDA_POLARISATION_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: static SpectralInversion dvb_parse_inversion (int inversion)
{
    switch (inversion)
    {
        case  0: return BDA_SPECTRAL_INVERSION_NORMAL;
        case  1: return BDA_SPECTRAL_INVERSION_INVERTED;
        case -1: return BDA_SPECTRAL_INVERSION_AUTOMATIC;
    }
    /* should never happen */
    return BDA_SPECTRAL_INVERSION_NOT_SET;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: int dvb_add_pid (dvb_device_t *, uint16_t)
{
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp:                    uint8_t /*sid*/)
{
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp:                    uint32_t /*guard*/, uint8_t /*plp*/)
{
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp:                    uint32_t /*srate*/, uint32_t /*fec*/)
{
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: int dvb_set_isdbs (dvb_device_t *, uint64_t /*freq*/, uint16_t /*ts_id*/)
{
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: unsigned BDAGraph::GetSystem( REFCLSID clsid )
{
    unsigned sys = 0;

    if( clsid == CLSID_DVBTNetworkProvider )
        sys = DVB_T;
    if( clsid == CLSID_DVBCNetworkProvider )
        sys = DVB_C;
    if( clsid == CLSID_DVBSNetworkProvider )
        sys = DVB_S;
    if( clsid == CLSID_ATSCNetworkProvider )
        sys = ATSC;
    if( clsid == CLSID_DigitalCableNetworkType )
        sys = CQAM;

    return sys;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp: ssize_t BDAGraph::Pop(void *buf, size_t len)
{
    return output.Pop(buf, len);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/bdagraph.cpp:                                  long /*buffer_len*/ )
{
    return E_FAIL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: static int dvb_set_props (dvb_device_t *d, size_t n, ...)
{
    va_list ap;
    int ret;

    va_start (ap, n);
    ret = dvb_vset_props (d, n, ap);
    va_end (ap);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: static int dvb_set_prop (dvb_device_t *d, uint32_t prop, uint32_t val)
{
    return dvb_set_props (d, 1, prop, val);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: int dvb_set_inversion (dvb_device_t *d, int v)
{
    switch (v)
    {
        case 0:  v = INVERSION_OFF;  break;
        case 1:  v = INVERSION_ON;   break;
        default: v = INVERSION_AUTO; break;
    }
    return dvb_set_prop (d, DTV_INVERSION, v);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: int dvb_tune (dvb_device_t *d)
{
    return dvb_set_prop (d, DTV_TUNE, 0 /* dummy */);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c:                   uint32_t srate, uint32_t fec)
{
    unsigned mod = dvb_parse_modulation (modstr, QAM_AUTO);
    fec = dvb_parse_fec (fec);

    if (dvb_find_frontend (d, DVB_C))
        return -1;
    return dvb_set_props (d, 6, DTV_CLEAR, 0,
#if DVBv5(5)
                          DTV_DELIVERY_SYSTEM, SYS_DVBC_ANNEX_A,
#else
                          DTV_DELIVERY_SYSTEM, SYS_DVBC_ANNEX_AC,
#endif
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod,
                          DTV_SYMBOL_RATE, srate, DTV_INNER_FEC, fec);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c:                   uint32_t srate, uint32_t fec)
{
    uint32_t freq = freq_Hz / 1000;
    fec = dvb_parse_fec (fec);

    if (dvb_find_frontend (d, DVB_S))
        return -1;
    return dvb_set_props (d, 5, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_DVBS,
                          DTV_FREQUENCY, freq, DTV_SYMBOL_RATE, srate,
                          DTV_INNER_FEC, fec);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: static uint32_t dvb_parse_bandwidth (uint32_t i)
{
    switch (i)
    {
      //case  0: return 0;
        case  2: return 1712000;
        default: return i * 1000000;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c:                   int transmit_mode, uint32_t guard, int hierarchy)
{
    uint32_t mod = dvb_parse_modulation (modstr, QAM_AUTO);
    fec_hp = dvb_parse_fec (fec_hp);
    fec_lp = dvb_parse_fec (fec_lp);
    bandwidth = dvb_parse_bandwidth (bandwidth);
    transmit_mode = dvb_parse_transmit_mode (transmit_mode);
    guard = dvb_parse_guard (guard);
    hierarchy = dvb_parse_hierarchy (hierarchy);

    if (dvb_find_frontend (d, DVB_T))
        return -1;
    return dvb_set_props (d, 10, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_DVBT,
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod,
                          DTV_CODE_RATE_HP, fec_hp, DTV_CODE_RATE_LP, fec_lp,
                          DTV_BANDWIDTH_HZ, bandwidth,
                          DTV_TRANSMISSION_MODE, transmit_mode,
                          DTV_GUARD_INTERVAL, guard,
                          DTV_HIERARCHY, hierarchy);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c:                    uint32_t srate, uint32_t fec)
{
    unsigned mod = dvb_parse_modulation (modstr, QAM_AUTO);
    fec = dvb_parse_fec (fec);

    if (dvb_find_frontend (d, ISDB_C))
        return -1;
    return dvb_set_props (d, 6, DTV_CLEAR, 0,
#if DVBv5(5)
                          DTV_DELIVERY_SYSTEM, SYS_DVBC_ANNEX_C,
#else
# warning ISDB-C might need Linux DVB version 5.5 or later.
                          DTV_DELIVERY_SYSTEM, SYS_DVBC_ANNEX_AC,
#endif
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod,
                          DTV_SYMBOL_RATE, srate, DTV_INNER_FEC, fec);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: int dvb_set_isdbs (dvb_device_t *d, uint64_t freq_Hz, uint16_t ts_id)
{
    uint32_t freq = freq_Hz / 1000;

    if (dvb_find_frontend (d, ISDB_S))
        return -1;
    return dvb_set_props (d, 4, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_ISDBS,
                          DTV_FREQUENCY, freq,
#if DVBv5(8)
                          DTV_STREAM_ID,
#else
                          DTV_ISDBS_TS_ID,
#endif
                          (uint32_t)ts_id);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: int dvb_set_atsc (dvb_device_t *d, uint32_t freq, const char *modstr)
{
    unsigned mod = dvb_parse_modulation (modstr, VSB_8);

    if (dvb_find_frontend (d, ATSC))
        return -1;
    return dvb_set_props (d, 4, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_ATSC,
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dtv/linux.c: int dvb_set_cqam (dvb_device_t *d, uint32_t freq, const char *modstr)
{
    unsigned mod = dvb_parse_modulation (modstr, QAM_AUTO);

    if (dvb_find_frontend (d, CQAM))
        return -1;
    return dvb_set_props (d, 4, DTV_CLEAR, 0,
                          DTV_DELIVERY_SYSTEM, SYS_DVBC_ANNEX_B,
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/avio.c: static int UrlInterruptCallback(void *access)
{
    return !vlc_object_alive((vlc_object_t*)access);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/avio.c: static int SetupAvioCb(vlc_object_t *access)
{
    static vlc_mutex_t avio_lock = VLC_STATIC_MUTEX;
    vlc_mutex_lock(&avio_lock);
    assert(!access != !current_access);
    if (access && current_access) {
        vlc_mutex_unlock(&avio_lock);
        return VLC_EGENERIC;
    }
    url_set_interrupt_cb(access ? UrlInterruptCallbackSingle : NULL);

    current_access = access;

    vlc_mutex_unlock(&avio_lock);

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/v4l2/demux.c: static vlc_fourcc_t var_InheritFourCC (vlc_object_t *obj, const char *varname)
{
    char *str = var_InheritString (obj, varname);
    if (str == NULL)
        return 0;

    vlc_fourcc_t fourcc = vlc_fourcc_GetCodecFromString (VIDEO_ES, str);
    if (fourcc == 0)
        msg_Err (obj, "invalid codec %s", str);
    free (str);
    return fourcc;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/v4l2/demux.c: static void GetAR (int fd, unsigned *restrict num, unsigned *restrict den)
{
    struct v4l2_cropcap cropcap = { .type = V4L2_BUF_TYPE_VIDEO_CAPTURE };

    /* TODO: get CROPCAP only once (see ResetCrop()). */
    if (v4l2_ioctl (fd, VIDIOC_CROPCAP, &cropcap) < 0)
    {
        *num = *den = 1;
        return;
    }
    *num = cropcap.pixelaspect.numerator;
    *den = cropcap.pixelaspect.denominator;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/v4l2/lib.c: static int fd_open (int fd, int flags)
{
    (void) flags;
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/v4l2/lib.c: int v4l2_fd_open (int fd, int flags)
{
    static pthread_once_t once = PTHREAD_ONCE_INIT;

    pthread_once (&once, v4l2_lib_load);
    return v4l2_fd_open_ (fd, flags);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/v4l2/controls.c:                                   vlc_value_t old, vlc_value_t cur, void *data)
{
    ControlsReset (obj, data);
    (void) var; (void) old; (void) cur;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dv.c: static int AVCResetHandler( raw1394handle_t handle, unsigned int generation )
{
    raw1394_update_generation( handle, generation );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/directory.c: static int collate (const char **a, const char **b)
{
#ifdef HAVE_STRCOLL
    return strcoll (*a, *b);
#else
    return strcmp  (*a, *b);
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/directory.c: static int version (const char **a, const char **b)
{
    return strverscmp (*a, *b);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/vcd/cdrom.c:                        uint8_t **pp_buffer, int *pi_buffer )
{
    VLC_UNUSED( p_object );
    VLC_UNUSED( p_vcddev );
    VLC_UNUSED( pp_buffer );
    VLC_UNUSED( pi_buffer );
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtsp/access.c: static int Seek( access_t *p_access, uint64_t i_pos )
{
    VLC_UNUSED(p_access);
    VLC_UNUSED(i_pos);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtsp/real_sdpplin.c: 
static inline char *nl(char *data) {
  char *nlptr = (data) ? strchr(data,'\n') : NULL;
  return (nlptr) ? nlptr + 1 : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtsp/real_sdpplin.c: 
static inline int line_length(char * data) {
  char const * p = nl(data);
  if (p) {
    return p - data - 1;
  }
  return strlen(data);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtsp/real_asmrp.c: 
int asmrp_match (const char *rules, int bandwidth, int *matches, int matchsize) {

  asmrp_t *p;
  int      num_matches;

  p = asmrp_new ();

  asmrp_init (p, rules);

  asmrp_set_id (p, "Bandwidth", bandwidth);
  asmrp_set_id (p, "OldPNMPlayer", 0);

  num_matches = asmrp_eval (p, matches, matchsize);

  asmrp_dispose (p);

  return num_matches;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/mms/mmsh.c: static ssize_t ReadRedirect( access_t *p_access, uint8_t *p, size_t i_len )
{
    VLC_UNUSED(p_access); VLC_UNUSED(p); VLC_UNUSED(i_len);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/mms/buffer.c: uint16_t var_buffer_get16( var_buffer_t *p_buf )
{
    uint16_t i_b1, i_b2;

    i_b1 = var_buffer_get8( p_buf );
    i_b2 = var_buffer_get8( p_buf );

    return( i_b1 + ( i_b2 << 8 ) );

}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/mms/buffer.c: uint32_t var_buffer_get32( var_buffer_t *p_buf )
{
    uint32_t i_w1, i_w2;

    i_w1 = var_buffer_get16( p_buf );
    i_w2 = var_buffer_get16( p_buf );

    return( i_w1 + ( i_w2 << 16 ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/mms/buffer.c: uint64_t var_buffer_get64( var_buffer_t *p_buf )
{
    uint64_t i_dw1, i_dw2;

    i_dw1 = var_buffer_get32( p_buf );
    i_dw2 = var_buffer_get32( p_buf );

    return( i_dw1 + ( i_dw2 << 32 ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/ftp.c:                             int *restrict codep, char **restrict strp )
{
    return ftp_RecvAnswer( obj, sys, codep, strp, DummyLine, NULL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/ftp.c: static const char *IsASCII( const char *str )
{
    int8_t c;
    for( const char *p = str; (c = *p) != '\0'; p++ )
        if( c < 0 )
            return NULL;
    return str;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/ftp.c: static int _Seek( vlc_object_t *p_access, access_sys_t *p_sys, uint64_t i_pos )
{
    msg_Dbg( p_access, "seeking to %"PRIu64, i_pos );

    ftp_StopStream( (vlc_object_t *)p_access, p_sys );
    if( ftp_StartStream( (vlc_object_t *)p_access, p_sys, i_pos ) < 0 )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/ftp.c: static int OutSeek( sout_access_out_t *p_access, off_t i_pos )
{
    return _Seek( (vlc_object_t *)p_access, GET_OUT_SYS( p_access ), i_pos);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/vcdx/vcdplayer.h: /* vcdplayer_read return status */
typedef enum {
  READ_BLOCK,
  READ_STILL_FRAME,
  READ_ERROR,
  READ_END,
} vcdplayer_read_status_t;

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/vnc.c: static char *getPasswordHandler( rfbClient *p_client )
{
    demux_t *p_demux = (demux_t *) rfbClientGetClientData( p_client, DemuxThread );
    /* freed by libvnc */
    return var_InheritString( p_demux, CFG_PREFIX "password" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/file.c: static bool IsRemote (const char *path)
{
# if !defined(__OS2__) && !VLC_WINSTORE_APP
    wchar_t *wpath = ToWide (path);
    bool is_remote = (wpath != NULL && PathIsNetworkPathW (wpath));
    free (wpath);
    return is_remote;
# else
    return (! strncmp(path, "\\\\", 2));
# endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/file.c: static int NoSeek (access_t *p_access, uint64_t i_pos)
{
    /* assert(0); ?? */
    (void) p_access; (void) i_pos;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *pcmu_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_MULAW);
    fmt.audio.i_rate = 8000;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *gsm_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_GSM);
    fmt.audio.i_rate = 8000;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *pcma_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_ALAW);
    fmt.audio.i_rate = 8000;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *l16s_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_S16B);
    fmt.audio.i_rate = 44100;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHANS_STEREO;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *l16m_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_S16B);
    fmt.audio.i_rate = 44100;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *qcelp_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_QCELP);
    fmt.audio.i_rate = 8000;
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *mpa_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_MPGA);
    fmt.audio.i_original_channels =
    fmt.audio.i_physical_channels = AOUT_CHANS_STEREO;
    fmt.b_packetized = false;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/rtp.c: static void *mpv_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, VIDEO_ES, VLC_CODEC_MPGV);
    fmt.b_packetized = false;
    return codec_init (demux, &fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/input.c: static int rtp_timeout (mtime_t deadline)
{
    if (deadline == VLC_TS_INVALID)
        return -1; /* infinite */

    mtime_t t = mdate ();
    if (t >= deadline)
        return 0;

    t = (deadline - t) / (CLOCK_FREQ / INT64_C(1000));
    if (unlikely(t > INT_MAX))
        return INT_MAX;
    return t;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/xiph.c: static void *vorbis_init (demux_t *demux)
{
    (void)demux;
    return xiph_init (true);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/xiph.c: void *theora_init (demux_t *demux)
{
    (void)demux;
    return xiph_init (false);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/session.c: static void *no_init (demux_t *demux)
{
    (void)demux;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/srtp.c: static int hexdigit (char c)
{
    if ((c >= '0') && (c <= '9'))
        return c - '0';
    if ((c >= 'A') && (c <= 'F'))
        return c - 'A' + 0xA;
    if ((c >= 'a') && (c <= 'f'))
        return c - 'a' + 0xa;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/srtp.c:             uint32_t roc)
{
    gcry_md_reset (md);
    gcry_md_write (md, data, len);
    gcry_md_write (md, &(uint32_t){ htonl (roc) }, 4);
    return gcry_md_read (md, 0);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/srtp.c:             const uint32_t *salt, uint8_t *data, size_t len)
{
    return rtp_crypt (hd, ssrc, index >> 16, index & 0xffff, salt, data, len);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rtp/srtp.c: rtcp_digest (gcry_md_hd_t md, const void *data, size_t len)
{
    gcry_md_reset (md);
    gcry_md_write (md, data, len);
    return gcry_md_read (md, 0);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/idummy.c: static int DemuxNoOp( demux_t *demux )
{
    (void) demux;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/idummy.c: static int DemuxHold( demux_t *demux )
{
    (void) demux;
    msleep( 10000 ); /* FIXME!!! */
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/idummy.c: static int DemuxControl( demux_t *p_demux, int i_query, va_list args )
{
    (void)p_demux; (void)i_query; (void)args;
    switch( i_query )
    {
    case DEMUX_GET_PTS_DELAY:
    {
        int64_t *pi_pts_delay = va_arg( args, int64_t * );
        *pi_pts_delay = DEFAULT_PTS_DELAY;
        return VLC_SUCCESS;
    }
    default:
        return VLC_EGENERIC;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/vdr.c: static int64_t ParseFrameNumber( const char *psz_line, float fps )
{
    unsigned h, m, s, f, n;

    /* hour:min:sec.frame (frame is optional) */
    n = sscanf( psz_line, "%u:%u:%u.%u", &h, &m, &s, &f );
    if( n >= 3 )
    {
        if( n < 4 )
            f = 1;
        int64_t i_seconds = (int64_t)h * 3600 + (int64_t)m * 60 + s;
        return (int64_t)( i_seconds * (double)fps ) + __MAX(1, f) - 1;
    }

    /* only a frame number */
    int64_t i_frame = strtoll( psz_line, NULL, 10 );
    return __MAX(1, i_frame) - 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dcp/dcpparser.cpp: int XmlFile::ReadEndNode( demux_t *p_demux, xml_reader_t *p_xmlReader, string p_node, int p_type, string &s_value)
{
    string node;

    if ( xml_ReaderIsEmptyElement( p_xmlReader) )
            return 0;

    if (p_type != XML_READER_STARTELEM)
        return -1;

    int n = XmlFile::ReadNextNode( p_demux, p_xmlReader, node );
    if( n == XML_READER_TEXT )
    {
        s_value = node;
        n = XmlFile::ReadNextNode( p_demux, p_xmlReader, node );
        if( ( n == XML_READER_ENDELEM ) && node == p_node)
            return 0;
    }
    return n == XML_READER_ENDELEM ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/pulse.c: static int stream_wait(pa_stream *stream, pa_threaded_mainloop *mainloop)
{
    pa_stream_state_t state;

    while ((state = pa_stream_get_state(stream)) != PA_STREAM_READY) {
        if (state == PA_STREAM_FAILED || state == PA_STREAM_TERMINATED)
            return -1;
        pa_threaded_mainloop_wait(mainloop);
    }
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/linsys/linsys_sdi.c: static int Demux( demux_t *p_demux )
{
    return ( Capture( p_demux ) == VLC_SUCCESS );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/linsys/linsys_sdi.c:                                       const uint8_t *p_end )
{
    const uint8_t *p_tmp = FindReferenceCode( i_code, p_parser, p_end );
    if ( p_tmp == NULL )
    {
        *pi_count += p_end - p_parser;
        return NULL;
    }
    *pi_count += p_tmp - p_parser;
    return p_tmp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/linsys/linsys_hdsdi.c: static int Demux( demux_t *p_demux )
{
    return ( Capture( p_demux ) == VLC_SUCCESS );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rar/rar.c: static int IgnoreBlock(stream_t *s, int block)
{
    /* */
    rar_block_t bk;
    if (PeekBlock(s, &bk) || bk.type != block)
        return VLC_EGENERIC;
    return SkipBlock(s, &bk);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/rar/rar.c: int RarProbe(stream_t *s)
{
    const uint8_t *peek;
    if (stream_Peek(s, &peek, rar_marker_size) < rar_marker_size)
        return VLC_EGENERIC;
    if (memcmp(peek, rar_marker, rar_marker_size))
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/mtp.c: static int open_file( access_t *p_access, const char *path )
{
    int fd = vlc_open( path, O_RDONLY | O_NONBLOCK );
    if( fd == -1 )
    {
        msg_Err( p_access, "cannot open file %s: %s", path,
                 vlc_strerror_c(errno) );
        dialog_Fatal( p_access, _( "File reading failed" ),
                      _( "VLC could not open the file \"%s\": %s" ), path,
                      vlc_strerror(errno) );
        return -1;
    }
#ifdef F_RDAHEAD
    fcntl( fd, F_RDAHEAD, 1 );
#endif
#ifdef F_NOCACHE
    fcntl( fd, F_NOCACHE, 0 );
#endif
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/http.c: static char * cookie_get_content( const char * cookie )
{
    char * ret = strdup( cookie );
    if( !ret ) return NULL;
    char * str = ret;
    /* Look for a ';' */
    while( *str && *str != ';' ) str++;
    /* Replace it by a end-char */
    if( *str == ';' ) *str = 0;
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/http.c: static char * cookie_get_name( const char * cookie )
{
    char * ret = cookie_get_content( cookie ); /* NAME=VALUE */
    if( !ret ) return NULL;
    char * str = ret;
    while( *str && *str != '=' ) str++;
    *str = 0;
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     int *pi;
{
    unsigned char c;
    int err = (int)ZREAD(*pzlib_filefunc_def,filestream,&c,1);
    if (err==1)
    {
        *pi = (int)c;
        return UNZ_OK;
    }
    else
    {
        if (ZERROR(*pzlib_filefunc_def,filestream))
            return UNZ_ERRNO;
        else
            return UNZ_EOF;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     uLong *pX;
{
    uLong x ;
    int i = 0;
    int err;

    err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
    x = (uLong)i;

    if (err==UNZ_OK)
        err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
    x += ((uLong)i)<<8;

    if (err==UNZ_OK)
        *pX = x;
    else
        *pX = 0;
    return err;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     const char* fileName2;
{
    for (;;)
    {
        char c1=*(fileName1++);
        char c2=*(fileName2++);
        if ((c1>='a') && (c1<='z'))
            c1 -= 0x20;
        if ((c2>='a') && (c2<='z'))
            c2 -= 0x20;
        if (c1=='\0')
            return ((c2=='\0') ? 0 : -1);
        if (c2=='\0')
            return 1;
        if (c1<c2)
            return -1;
        if (c1>c2)
            return 1;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     int iCaseSensitivity;
{
    if (iCaseSensitivity==0)
        iCaseSensitivity=CASESENSITIVITYDEFAULTVALUE;

    if (iCaseSensitivity==1)
        return strcmp(fileName1,fileName2);

    return STRCMPCASENOSENTIVEFUNCTION(fileName1,fileName2);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     const char *path;
{
    return unzOpen2(path, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     uLong commentBufferSize;
{
    return unzlocal_GetCurrentFileInfoInternal(file,pfile_info,NULL,
                                                szFileName,fileNameBufferSize,
                                                extraField,extraFieldBufferSize,
                                                szComment,commentBufferSize);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     unzFile file;
{
    return unzOpenCurrentFile3(file, NULL, NULL, 0, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     const char* password;
{
    return unzOpenCurrentFile3(file, NULL, NULL, 0, password);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     int raw;
{
    return unzOpenCurrentFile3(file, method, level, raw, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/crypt.h: static int decrypt_byte(unsigned long* pkeys, const unsigned long* pcrc_32_tab)
{
    (void) pcrc_32_tab;
    unsigned temp;  /* POTENTIAL BUG:  temp*(temp^1) may overflow in an
                     * unpredictable manner on 16-bit systems; not a problem
                     * with any known compiler so far, though */

    temp = ((unsigned)(*(pkeys+2)) & 0xffff) | 2;
    return (int)(((temp * (temp ^ 1)) >> 8) & 0xff);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/crypt.h: static int update_keys(unsigned long* pkeys,const unsigned long* pcrc_32_tab,int c)
{
    (*(pkeys+0)) = CRC32((*(pkeys+0)), c);
    (*(pkeys+1)) += (*(pkeys+0)) & 0xff;
    (*(pkeys+1)) = (*(pkeys+1)) * 134775813L + 1;
    {
      register int keyshift = (int)((*(pkeys+1)) >> 24);
      (*(pkeys+2)) = CRC32((*(pkeys+2)), keyshift);
    }
    return c;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    int mode;
{
    (void) opaque;
    FILE* file = NULL;
    const char* mode_fopen = NULL;
    if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
        mode_fopen = "rb";
    else
    if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
        mode_fopen = "r+b";
    else
    if (mode & ZLIB_FILEFUNC_MODE_CREATE)
        mode_fopen = "wb";

    if ((filename!=NULL) && (mode_fopen != NULL))
        file = fopen(filename, mode_fopen);
    return file;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    uLong size;
{
    (void) opaque;
    uLong ret;
    ret = (uLong)fread(buf, 1, (size_t)size, (FILE *)stream);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    uLong size;
{
    (void) opaque;
    uLong ret;
    ret = (uLong)fwrite(buf, 1, (size_t)size, (FILE *)stream);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    voidpf stream;
{
    (void) opaque;
    long ret;
    ret = ftell((FILE *)stream);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    voidpf stream;
{
    (void) opaque;
    int ret;
    ret = fclose((FILE *)stream);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/ioapi.c:    voidpf stream;
{
    (void) opaque;
    int ret;
    ret = ferror((FILE *)stream);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipstream.c: bool isAllowedChar( char c )
{
    return ( c >= 'a' && c <= 'z' )
           || ( c >= 'A' && c <= 'Z' )
           || ( c >= '0' && c <= '9' )
           || ( c == ':' ) || ( c == '/' )
           || ( c == '\\' ) || ( c == '.' )
           || ( c == ' ' ) || ( c == '_' );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipstream.c: static void ZCALLBACK *ZipIO_Open( void *opaque, const char *file, int mode )
{
    (void) file;
    stream_t *s = (stream_t*) opaque;
    if( mode & ( ZLIB_FILEFUNC_MODE_CREATE | ZLIB_FILEFUNC_MODE_WRITE ) )
    {
        msg_Dbg( s, "ZipIO_Open: we cannot write into zip files" );
        return NULL;
    }
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipstream.c:                                     const void* buf, uLong size )
{
    (void)opaque; (void)stream; (void)buf; (void)size;
    int ERROR_zip_cannot_write_this_should_not_happen = 0;
    assert( ERROR_zip_cannot_write_this_should_not_happen );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipstream.c: static int ZCALLBACK ZipIO_Error( void* opaque, void* stream )
{
    (void)opaque;
    (void)stream;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipaccess.c:                                    void* buf, uLong size )
{
    (void)opaque;
    //access_t *p_access = (access_t*) opaque;
    //msg_Dbg(p_access, "read %d", size);
    return stream_Read( (stream_t*) stream, buf, size );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipaccess.c:                                     const void* buf, uLong size )
{
    (void)opaque; (void)stream; (void)buf; (void)size;
    int zip_access_cannot_write_this_should_not_happen = 0;
    assert(zip_access_cannot_write_this_should_not_happen);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipaccess.c: static long ZCALLBACK ZipIO_Tell( void* opaque, void* stream )
{
    (void)opaque;
    int64_t i64_tell = stream_Tell( (stream_t*) stream );
    //access_t *p_access = (access_t*) opaque;
    //msg_Dbg(p_access, "tell %" PRIu64, i64_tell);
    return (long)i64_tell;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipaccess.c: static int ZCALLBACK ZipIO_Close( void* opaque, void* stream )
{
    (void)opaque;
    stream_Delete( (stream_t*) stream );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/zipaccess.c: static int ZCALLBACK ZipIO_Error( void* opaque, void* stream )
{
    (void)opaque;
    (void)stream;
    //msg_Dbg( p_access, "error" );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvdnav.c: static int stream_cb_seek( void *s, uint64_t pos )
{
    return stream_Seek( (stream_t *)s, pos );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvdnav.c: static int stream_cb_read( void *s, void* buffer, int size )
{
    return stream_Read( (stream_t *)s, buffer, size );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dvdnav.c: static int ControlInternal( demux_t *p_demux, int i_query, ... )
{
    va_list args;
    int     i_result;

    va_start( args, i_query );
    i_result = Control( p_demux, i_query, args );
    va_end( args );

    return i_result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.h: static inline int PushCommand( extension_t *ext, int cmd, ... )
{
    va_list args;
    va_start( args, cmd );
    int i_ret = __PushCommand( ext, false, cmd, args );
    va_end( args );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.h: static inline int PushCommandUnique( extension_t *ext, int cmd, ... )
{
    va_list args;
    va_start( args, cmd );
    int i_ret = __PushCommand( ext, true, cmd, args );
    va_end( args );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/intf.c:     if( pw == NULL )
    {
        msg_Err( p_this, "password not configured" );
        msg_Info( p_this, "Please specify the password in the preferences." );
        return VLC_EGENERIC;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.c: static int file_compare( const char **a, const char **b )
{
    return strcmp( *a, *b );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.c: static int vlclua_add_modules_path_inner( lua_State *L, const char *psz_path )
{
    int count = 0;
    for( const char **ppsz_ext = ppsz_lua_exts; *ppsz_ext; ppsz_ext++ )
    {
        lua_pushfstring( L, "%s"DIR_SEP"modules"DIR_SEP"?%s;",
                         psz_path, *ppsz_ext );
        count ++;
    }

    return count;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.h: static inline bool luaL_checkboolean( lua_State *L, int narg )
{
    luaL_checktype( L, narg, LUA_TBOOLEAN ); /* can raise an error */
    return lua_toboolean( L, narg );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.h: static inline int luaL_optboolean( lua_State *L, int narg, int def )
{
    return luaL_opt( L, luaL_checkboolean, narg, def );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.h: static inline const char *luaL_nilorcheckstring( lua_State *L, int narg )
{
    if( lua_isnil( L, narg ) )
        return NULL;
    return luaL_checkstring( L, narg );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/vlc.h: static inline char *luaL_strdupornull( lua_State *L, int narg )
{
    if( lua_isstring( L, narg ) )
        return strdup( luaL_checkstring( L, narg ) );
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/meta.c: int ReadMeta( demux_meta_t *p_this )
{
    return vlclua_scripts_batch_execute( VLC_OBJECT(p_this), "meta"DIR_SEP"reader",
                                         (void*) &read_meta, NULL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/demux.c: static int Control( demux_t *p_demux, int i_query, va_list args )
{
    VLC_UNUSED(p_demux); VLC_UNUSED(i_query); VLC_UNUSED(args);
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/win.c: static HANDLE GetConsole( lua_State *L )
{
    /* Get the file descriptor of the console input */
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    if( hConsoleIn == INVALID_HANDLE_VALUE )
        luaL_error( L, "couldn't find user input handle" );
    return hConsoleIn;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/win.c: static int vlclua_console_init( lua_State *L )
{
    (void)L;
    //if ( !AllocConsole() )
    //    luaL_error( L, "failed to allocate windows console" );
    AllocConsole();

    freopen( "CONOUT$", "w", stdout );
    freopen( "CONOUT$", "w", stderr );
    freopen( "CONIN$", "r", stdin );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/win.c: static int vlclua_console_wait( lua_State *L )
{
    int i_timeout = luaL_optint( L, 1, 0 );
    DWORD status = WaitForSingleObject( GetConsole( L ), i_timeout );
    lua_pushboolean( L, status == WAIT_OBJECT_0 );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: void *vlclua_get_object( lua_State *L, void *id )
{
    lua_pushlightuserdata( L, id );
    lua_rawget( L, LUA_REGISTRYINDEX );
    const void *p = lua_topointer( L, -1 );
    lua_pop( L, 1 );
    return (void *)p;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: vlc_object_t * vlclua_get_this( lua_State *L )
{
    return vlclua_get_object( L, vlclua_set_this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: int vlclua_push_ret( lua_State *L, int i_error )
{
    lua_pushnumber( L, i_error );
    lua_pushstring( L, vlc_error( i_error ) );
    return 2;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_version( lua_State *L )
{
    lua_pushstring( L, VERSION_MESSAGE );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_copyright( lua_State *L )
{
    lua_pushliteral( L, COPYRIGHT_MESSAGE );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_license( lua_State *L )
{
    lua_pushstring( L, LICENSE_MSG );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_mdate( lua_State *L )
{
    lua_pushnumber( L, mdate() );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_mwait( lua_State *L )
{
    double f = luaL_checknumber( L, 1 );
    mwait( (int64_t)f );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/misc.c: static int vlclua_action_id( lua_State *L )
{
    vlc_action_t i_key = vlc_GetActionId( luaL_checkstring( L, 1 ) );
    if (i_key == 0)
        return 0;
    lua_pushnumber( L, i_key );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_decode_uri( lua_State *L )
{
    int i_top = lua_gettop( L );
    int i;
    for( i = 1; i <= i_top; i++ )
    {
        const char *psz_cstring = luaL_checkstring( L, 1 );
        char *psz_string = strdup( psz_cstring );
        lua_remove( L, 1 ); /* remove elements to prevent being limited by
                             * the stack's size (this function will work with
                             * up to (stack size - 1) arguments */
        decode_URI( psz_string );
        lua_pushstring( L, psz_string );
        free( psz_string );
    }
    return i_top;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_encode_uri_component( lua_State *L )
{
    int i_top = lua_gettop( L );
    int i;
    for( i = 1; i <= i_top; i++ )
    {
        const char *psz_cstring = luaL_checkstring( L, 1 );
        char *psz_string = encode_URI_component( psz_cstring );
        lua_remove( L,1 );
        lua_pushstring( L, psz_string );
        free( psz_string );
    }
    return i_top;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_make_uri( lua_State *L )
{
    const char *psz_input = luaL_checkstring( L, 1 );
    const char *psz_scheme = luaL_optstring( L, 2, NULL );
    if( strstr( psz_input, "://" ) == NULL )
    {
        char *psz_uri = vlc_path2uri( psz_input, psz_scheme );
        lua_pushstring( L, psz_uri );
        free( psz_uri );
    }
    else
        lua_pushstring( L, psz_input );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_make_path( lua_State *L )
{
    const char *psz_input = luaL_checkstring( L, 1 );
    char *psz_path = make_path( psz_input);
    lua_pushstring( L, psz_path );
    free( psz_path );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_resolve_xml_special_chars( lua_State *L )
{
    int i_top = lua_gettop( L );
    int i;
    for( i = 1; i <= i_top; i++ )
    {
        const char *psz_cstring = luaL_checkstring( L, 1 );
        char *psz_string = strdup( psz_cstring );
        lua_remove( L, 1 ); /* remove elements to prevent being limited by
                             * the stack's size (this function will work with
                             * up to (stack size - 1) arguments */
        resolve_xml_special_chars( psz_string );
        lua_pushstring( L, psz_string );
        free( psz_string );
    }
    return i_top;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_convert_xml_special_chars( lua_State *L )
{
    int i_top = lua_gettop( L );
    int i;
    for( i = 1; i <= i_top; i++ )
    {
        char *psz_string = convert_xml_special_chars( luaL_checkstring(L,1) );
        lua_remove( L, 1 );
        lua_pushstring( L, psz_string );
        free( psz_string );
    }
    return i_top;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/strings.c: static int vlclua_from_charset( lua_State *L )
{
    if( lua_gettop( L ) < 2 ) return vlclua_error( L );

    size_t i_in_bytes;
    const char *psz_input = luaL_checklstring( L, 2, &i_in_bytes );
    if( i_in_bytes == 0 ) return vlclua_error( L );

    const char *psz_charset = luaL_checkstring( L, 1 );
    char *psz_output = FromCharset( psz_charset, psz_input, i_in_bytes );
    lua_pushstring( L, psz_output ? psz_output : "" );
    free( psz_output );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_is_playing( lua_State *L )
{
    input_thread_t * p_input = vlclua_get_input_internal( L );
    lua_pushboolean( L, !!p_input );
    if( p_input )
        vlc_object_release( p_input );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_add_subtitle( lua_State *L )
{
    input_thread_t *p_input = vlclua_get_input_internal( L );
    if( !p_input )
        return luaL_error( L, "can't add subtitle: no current input" );
    if( !lua_isstring( L, 1 ) )
        return luaL_error( L, "vlc.input.add_subtitle() usage: (path)" );
    const char *psz_path = luaL_checkstring( L, 1 );
    input_AddSubtitle( p_input, psz_path, false );
    vlc_object_release( p_input );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static input_item_t* vlclua_input_item_get_internal( lua_State *L )
{
    input_item_t **pp_item = luaL_checkudata( L, 1, "input_item" );
    input_item_t *p_item = *pp_item;

    if( !p_item )
        luaL_error( L, "script went completely foobar" );

    return p_item;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_delete( lua_State *L )
{
    input_item_t **pp_item = luaL_checkudata( L, 1, "input_item" );
    input_item_t *p_item = *pp_item;

    if( !p_item )
        return luaL_error( L, "script went completely foobar" );

    *pp_item = NULL;
    vlc_gc_decref( p_item );

    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_get( lua_State *L, input_item_t *p_item )
{
    vlc_gc_incref( p_item );
    input_item_t **pp = lua_newuserdata( L, sizeof( input_item_t* ) );
    *pp = p_item;

    if( luaL_newmetatable( L, "input_item" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_input_item_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_input_item_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable(L, -2);

    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_get_current( lua_State *L )
{
    input_thread_t *p_input = vlclua_get_input_internal( L );
    input_item_t *p_item = p_input ? input_GetItem( p_input ) : NULL;
    if( !p_item )
    {
        lua_pushnil( L );
        if( p_input ) vlc_object_release( p_input );
        return 1;
    }

    vlclua_input_item_get( L, p_item );

    if( p_input ) vlc_object_release( p_input );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_metas( lua_State *L )
{
    vlclua_input_metas_internal( L, vlclua_input_item_get_internal( L ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_is_preparsed( lua_State *L )
{
    lua_pushboolean( L, input_item_IsPreparsed( vlclua_input_item_get_internal( L ) ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_uri( lua_State *L )
{
    lua_pushstring( L, input_item_GetURI( vlclua_input_item_get_internal( L ) ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_name( lua_State *L )
{
    lua_pushstring( L, input_item_GetName( vlclua_input_item_get_internal( L ) ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/input.c: static int vlclua_input_item_duration( lua_State *L )
{
    mtime_t duration = input_item_GetDuration( vlclua_input_item_get_internal( L ) );
    lua_pushnumber( L, ((double)duration)/1000000. );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/stream.c: static int vlclua_stream_new( lua_State *L )
{
    vlc_object_t * p_this = vlclua_get_this( L );
    const char * psz_url = luaL_checkstring( L, 1 );
    stream_t *p_stream = stream_UrlNew( p_this, psz_url );
    return vlclua_stream_new_inner( L, p_stream );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/stream.c: static int vlclua_memory_stream_new( lua_State *L )
{
    vlc_object_t * p_this = vlclua_get_this( L );
    /* FIXME: duplicating the whole buffer is suboptimal. Keeping a reference to the string so that it doesn't get garbage collected would be better */
    char * psz_content = strdup( luaL_checkstring( L, 1 ) );
    stream_t *p_stream = stream_MemoryNew( p_this, (uint8_t *)psz_content, strlen( psz_content ), false );
    return vlclua_stream_new_inner( L, p_stream );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/stream.c: static int vlclua_stream_read( lua_State *L )
{
    int i_read;
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    int n = luaL_checkint( L, 2 );
    uint8_t *p_read = malloc( n );
    if( !p_read ) return vlclua_error( L );

    i_read = stream_Read( *pp_stream, p_read, n );
    if( i_read > 0 )
        lua_pushlstring( L, (const char *)p_read, i_read );
    else
        lua_pushnil( L );
    free( p_read );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/stream.c: static int vlclua_stream_readline( lua_State *L )
{
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    char *psz_line = stream_ReadLine( *pp_stream );
    if( psz_line )
    {
        lua_pushstring( L, psz_line );
        free( psz_line );
    }
    else
        lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/stream.c: static int vlclua_stream_delete( lua_State *L )
{
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    stream_Delete( *pp_stream );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/messages.c: static int vlclua_msg_dbg( lua_State *L )
{
    int i_top = lua_gettop( L );
    vlc_object_t *p_this = vlclua_get_this( L );
    int i;
    for( i = 1; i <= i_top; i++ )
        msg_Dbg( p_this, "%s", luaL_checkstring( L, i ) );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/messages.c: static int vlclua_msg_warn( lua_State *L )
{
    int i_top = lua_gettop( L );
    vlc_object_t *p_this = vlclua_get_this( L );
    int i;
    for( i = 1; i <= i_top; i++ )
        msg_Warn( p_this, "%s", luaL_checkstring( L, i ) );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/messages.c: static int vlclua_msg_err( lua_State *L )
{
    int i_top = lua_gettop( L );
    vlc_object_t *p_this = vlclua_get_this( L );
    int i;
    for( i = 1; i <= i_top; i++ )
        msg_Err( p_this, "%s", luaL_checkstring( L, i ) );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/messages.c: static int vlclua_msg_info( lua_State *L )
{
    int i_top = lua_gettop( L );
    vlc_object_t *p_this = vlclua_get_this( L );
    int i;
    for( i = 1; i <= i_top; i++ )
        msg_Info( p_this, "%s", luaL_checkstring( L, i ) );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/gettext.c: static int vlclua_gettext( lua_State *L )
{
    lua_pushstring( L, _( luaL_checkstring( L, 1 ) ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/gettext.c: static int vlclua_gettext_noop( lua_State *L )
{
    lua_settop( L, 1 );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static vlclua_dtable_t *vlclua_get_dtable( lua_State *L )
{
    return vlclua_get_object( L, vlclua_get_dtable );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_fd_map_safe( lua_State *L, int fd )
{
    int luafd = vlclua_fd_map( L, fd );
    if( luafd == -1 )
        net_Close( fd );
    return luafd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_net_accept( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    int **ppi_fd = (int**)luaL_checkudata( L, 1, "net_listen" );
    int i_fd = net_Accept( p_this, *ppi_fd );

    lua_pushinteger( L, vlclua_fd_map_safe( L, i_fd ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_net_connect_tcp( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    const char *psz_host = luaL_checkstring( L, 1 );
    int i_port = luaL_checkint( L, 2 );
    int i_fd = net_Connect( p_this, psz_host, i_port, SOCK_STREAM, IPPROTO_TCP );
    lua_pushinteger( L, vlclua_fd_map_safe( L, i_fd ) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_net_close( lua_State *L )
{
    int i_fd = luaL_checkint( L, 1 );
    vlclua_fd_unmap_safe( L, i_fd );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_net_send( lua_State *L )
{
    int fd = vlclua_fd_get( L, luaL_checkint( L, 1 ) );
    size_t i_len;
    const char *psz_buffer = luaL_checklstring( L, 2, &i_len );

    i_len = luaL_optint( L, 3, i_len );
    lua_pushinteger( L, (fd != -1) ? send( fd, psz_buffer, i_len, 0 ) : -1 );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/net.c: static int vlclua_fd_write( lua_State *L )
{
    int fd = vlclua_fd_get( L, luaL_checkint( L, 1 ) );
    size_t i_len;
    const char *psz_buffer = luaL_checklstring( L, 2, &i_len );

    i_len = luaL_optint( L, 3, i_len );
    lua_pushinteger( L, (fd != -1) ? write( fd, psz_buffer, i_len ) : -1 );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/equalizer.c: static int vlclua_preamp_get( lua_State *L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    audio_output_t *p_aout = playlist_GetAout( p_playlist );
    if( p_aout == NULL )
        return 0;

    char *psz_af = var_GetNonEmptyString( p_aout, "audio-filter" );
    if( !psz_af || strstr ( psz_af, "equalizer" ) == NULL )
    {
        free( psz_af );
        vlc_object_release( p_aout );
        return 0;
    }
    free( psz_af );

    lua_pushnumber( L, var_GetFloat( p_aout, "equalizer-preamp") );
    vlc_object_release( p_aout );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/equalizer.c: static int vlclua_preamp_set( lua_State *L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    audio_output_t *p_aout = playlist_GetAout( p_playlist );
    if( p_aout == NULL )
        return 0;

    char *psz_af = var_GetNonEmptyString( p_aout, "audio-filter" );
    if( !psz_af || strstr ( psz_af, "equalizer" ) == NULL )
    {
        free( psz_af );
        vlc_object_release( p_aout );
        return 0;
    }
    free( psz_af );

    var_SetFloat( p_aout, "equalizer-preamp", luaL_checknumber( L, 1 ) );
    vlc_object_release( p_aout );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/equalizer.c: static int vlclua_equalizer_enable ( lua_State *L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    bool state = luaL_checkboolean ( L , 1 );
    playlist_EnableAudioFilter( p_playlist, "equalizer", state );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_datadir( lua_State *L )
{
    char *psz_data = config_GetDataDir();
    lua_pushstring( L, psz_data );
    free( psz_data );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_userdatadir( lua_State *L )
{
    char *dir = config_GetUserDir( VLC_DATA_DIR );
    lua_pushstring( L, dir );
    free( dir );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_homedir( lua_State *L )
{
    char *home = config_GetUserDir( VLC_HOME_DIR );
    lua_pushstring( L, home );
    free( home );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_configdir( lua_State *L )
{
    char *dir = config_GetUserDir( VLC_CONFIG_DIR );
    lua_pushstring( L, dir );
    free( dir );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_cachedir( lua_State *L )
{
    char *dir = config_GetUserDir( VLC_CACHE_DIR );
    lua_pushstring( L, dir );
    free( dir );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/configuration.c: static int vlclua_datadir_list( lua_State *L )
{
    const char *psz_dirname = luaL_checkstring( L, 1 );
    char **ppsz_dir_list = NULL;
    int i = 1;

    if( vlclua_dir_list( psz_dirname, &ppsz_dir_list )
        != VLC_SUCCESS )
        return 0;
    lua_newtable( L );
    for( char **ppsz_dir = ppsz_dir_list; *ppsz_dir; ppsz_dir++ )
    {
        lua_pushstring( L, *ppsz_dir );
        lua_rawseti( L, -2, i );
        i ++;
    }
    vlclua_dir_list_free( ppsz_dir_list );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/vlm.c: static int vlclua_vlm_delete( lua_State *L )
{
    vlm_t **pp_vlm = (vlm_t**)luaL_checkudata( L, 1, "vlm" );
    vlm_Delete( *pp_vlm );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/vlm.c: static int vlclua_vlm_execute_command( lua_State *L )
{
    vlm_t **pp_vlm = (vlm_t**)luaL_checkudata( L, 1, "vlm" );
    const char *psz_command = luaL_checkstring( L, 2 );
    vlm_message_t *message;
    int i_ret;
    i_ret = vlm_ExecuteCommand( *pp_vlm, psz_command, &message );
    lua_settop( L, 0 );
    push_message( L, message );
    vlm_MessageDelete( message );
    return 1 + vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/vlm.c: static int vlclua_vlm_new( lua_State *L )
{
    return luaL_error( L, "Cannot start VLM because it was disabled when compiling VLC." );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: playlist_t *vlclua_get_playlist_internal( lua_State *L )
{
    return vlclua_get_object( L, vlclua_set_playlist_internal );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_prev( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Prev( p_playlist );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_next( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Next( p_playlist );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_skip( lua_State * L )
{
    int i_skip = luaL_checkint( L, 1 );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Skip( p_playlist, i_skip );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_play( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Play( p_playlist );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_pause( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Pause( p_playlist );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_stop( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Stop( p_playlist );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_clear( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    playlist_Stop( p_playlist ); /* Isn't this already implied by Clear? */
    playlist_Clear( p_playlist, pl_Unlocked );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_repeat( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    int i_ret = vlclua_var_toggle_or_set( L, p_playlist, "repeat" );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_loop( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    int i_ret = vlclua_var_toggle_or_set( L, p_playlist, "loop" );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_random( lua_State * L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    int i_ret = vlclua_var_toggle_or_set( L, p_playlist, "random" );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_gotoitem( lua_State * L )
{
    int i_id = luaL_checkint( L, 1 );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    PL_LOCK;
    int i_ret = playlist_Control( p_playlist, PLAYLIST_VIEWPLAY,
                                  true, NULL,
                                  playlist_ItemGetById( p_playlist, i_id ) );
    PL_UNLOCK;
    return vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_add( lua_State *L )
{
    int i_count;
    vlc_object_t *p_this = vlclua_get_this( L );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    i_count = vlclua_playlist_add_internal( p_this, L, p_playlist,
                                            NULL, true );
    lua_pushinteger( L, i_count );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/playlist.c: static int vlclua_playlist_enqueue( lua_State *L )
{
    int i_count;
    vlc_object_t *p_this = vlclua_get_this( L );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    i_count = vlclua_playlist_add_internal( p_this, L, p_playlist,
                                            NULL, false );
    lua_pushinteger( L, i_count );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/osd.c: static int vlclua_spu_channel_register( lua_State *L )
{
    input_thread_t *p_input = vlclua_get_input_internal( L );
    if( !p_input )
        return luaL_error( L, "Unable to find input." );

    vout_thread_t *p_vout = input_GetVout( p_input );
    if( !p_vout )
    {
        vlc_object_release( p_input );
        return luaL_error( L, "Unable to find vout." );
    }

    int i_chan = vout_RegisterSubpictureChannel( p_vout );
    vlc_object_release( p_vout );
    vlc_object_release( p_input );
    lua_pushinteger( L, i_chan );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/osd.c: static int vlclua_spu_channel_clear( lua_State *L )
{
    int i_chan = luaL_checkint( L, 1 );
    input_thread_t *p_input = vlclua_get_input_internal( L );
    if( !p_input )
        return luaL_error( L, "Unable to find input." );
    vout_thread_t *p_vout = input_GetVout( p_input );
    if( !p_vout )
    {
        vlc_object_release( p_input );
        return luaL_error( L, "Unable to find vout." );
    }

    vout_FlushSubpictureChannel( p_vout, i_chan );
    vlc_object_release( p_vout );
    vlc_object_release( p_input );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_object_release( lua_State *L )
{
    vlc_object_t **p_obj = (vlc_object_t **)luaL_checkudata( L, 1, "vlc_object" );
    lua_pop( L, 1 );
    vlc_object_release( *p_obj );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_object_find( lua_State *L )
{
    lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_get_playlist( lua_State *L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    if( p_playlist )
    {
        vlc_object_hold( p_playlist );
        vlclua_push_vlc_object( L, p_playlist );
    }
    else lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_get_input( lua_State *L )
{
    input_thread_t *p_input = vlclua_get_input_internal( L );
    if( p_input )
    {
        /* NOTE: p_input is already held by vlclua_get_input_internal() */
        vlclua_push_vlc_object( L, p_input );
    }
    else lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: int vlclua_push_vlc_object( lua_State *L, vlc_object_t *p_obj )
{
    vlc_object_t **udata = (vlc_object_t **)
        lua_newuserdata( L, sizeof( vlc_object_t * ) );
    *udata = p_obj;

    if( luaL_newmetatable( L, "vlc_object" ) )
    {
        /* Hide the metatable */
        lua_pushliteral( L, "none of your business" );
        lua_setfield( L, -2, "__metatable" );
        /* Set the garbage collector if needed */
        lua_pushcfunction( L, vlclua_object_release );
        lua_setfield( L, -2, "__gc" );
    }
    lua_setmetatable( L, -2 );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_get_vout( lua_State *L )
{
    input_thread_t *p_input = vlclua_get_input_internal( L );
    if( p_input )
    {
        vout_thread_t *p_vout = input_GetVout( p_input );
        vlc_object_release( p_input );
        if(p_vout)
        {
            vlclua_push_vlc_object( L, (vlc_object_t *) p_vout );
            return 1;
        }
    }
    lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/objects.c: static int vlclua_get_aout( lua_State *L )
{
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    if( p_playlist != NULL )
    {
        audio_output_t *p_aout = playlist_GetAout( p_playlist );
        if( p_aout != NULL )
        {
            vlclua_push_vlc_object( L, (vlc_object_t *)p_aout );
            return 1;
        }
    }
    lua_pushnil( L );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/volume.c: static int vlclua_volume_set( lua_State *L )
{
    playlist_t *p_this = vlclua_get_playlist_internal( L );
    int i_volume = luaL_checkint( L, 1 );
    if( i_volume < 0 )
        i_volume = 0;
    int i_ret = playlist_VolumeSet( p_this, i_volume/(float)AOUT_VOLUME_DEFAULT );
    return vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/volume.c: static int vlclua_volume_get( lua_State *L )
{
    playlist_t *p_this = vlclua_get_playlist_internal( L );
    long i_volume = lroundf(playlist_VolumeGet( p_this ) * AOUT_VOLUME_DEFAULT);
    lua_pushnumber( L, i_volume );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/volume.c: static int vlclua_volume_up( lua_State *L )
{
    playlist_t *p_this = vlclua_get_playlist_internal( L );
    float volume;

    playlist_VolumeUp( p_this, luaL_optint( L, 1, 1 ), &volume );
    lua_pushnumber( L, lroundf(volume * AOUT_VOLUME_DEFAULT) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/volume.c: static int vlclua_volume_down( lua_State *L )
{
    playlist_t *p_this = vlclua_get_playlist_internal( L );
    float volume;

    playlist_VolumeDown( p_this, luaL_optint( L, 1, 1 ), &volume );
    lua_pushnumber( L, lroundf(volume * AOUT_VOLUME_DEFAULT) );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: static inline int vlclua_dialog_add_text_input( lua_State *L )
{
    return vlclua_dialog_add_text_inner( L, EXTENSION_WIDGET_TEXT_FIELD );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: static inline int vlclua_dialog_add_password( lua_State *L )
{
    return vlclua_dialog_add_text_inner( L, EXTENSION_WIDGET_PASSWORD );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: static inline int vlclua_dialog_add_html( lua_State *L )
{
    return vlclua_dialog_add_text_inner( L, EXTENSION_WIDGET_HTML );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: static int vlclua_dialog_update( lua_State *L )
{
    vlc_object_t *p_mgr = vlclua_get_this( L );

    extension_dialog_t **pp_dlg =
            (extension_dialog_t**) luaL_checkudata( L, 1, "dialog" );
    if( !pp_dlg || !*pp_dlg )
        return luaL_error( L, "Can't get pointer to dialog" );
    extension_dialog_t *p_dlg = *pp_dlg;

    // Updating dialog immediately
    dialog_ExtensionUpdate( p_mgr, p_dlg );

    // Reset update flag
    lua_SetDialogUpdate( L, 0 );

    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: static int lua_GetDialogUpdate( lua_State *L )
{
    /* Read entry in the Lua registry */
    lua_pushlightuserdata( L, (void*) &key_update );
    lua_gettable( L, LUA_REGISTRYINDEX );
    return luaL_checkinteger( L, -1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/dialog.c: int lua_DialogFlush( lua_State *L )
{
    lua_getglobal( L, "vlc" );
    lua_getfield( L, -1, "__dialog" );
    extension_dialog_t *p_dlg = ( extension_dialog_t* )lua_topointer( L, -1 );

    if( !p_dlg )
        return VLC_SUCCESS;

    int i_ret = VLC_SUCCESS;
    if( lua_GetDialogUpdate( L ) )
    {
        i_ret = dialog_ExtensionUpdate( vlclua_get_this( L ), p_dlg );
        lua_SetDialogUpdate( L, 0 );
    }

    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_var_inherit( lua_State *L )
{
    vlc_value_t val;
    vlc_object_t *p_obj;
    if( lua_type( L, 1 ) == LUA_TNIL )
        p_obj = vlclua_get_this( L );
    else
    {
        vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
        p_obj = *pp_obj;
    }
    const char *psz_var = luaL_checkstring( L, 2 );

    int i_type = config_GetType( p_obj, psz_var );
    if( var_Inherit( p_obj, psz_var, i_type, &val ) != VLC_SUCCESS )
        return 0;

    lua_pop( L, 2 );
    return vlclua_pushvalue( L, i_type, val, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_var_get( lua_State *L )
{
    vlc_value_t val;
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    int i_type = var_Type( *pp_obj, psz_var );
    if( var_Get( *pp_obj, psz_var, &val ) != VLC_SUCCESS )
        return 0;

    lua_pop( L, 2 );
    return vlclua_pushvalue( L, i_type, val, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_var_set( lua_State *L )
{
    vlc_value_t val;
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    int i_type = var_Type( *pp_obj, psz_var );
    vlclua_tovalue( L, i_type, &val );

    int i_ret = var_Set( *pp_obj, psz_var, val );

    lua_pop( L, 3 );
    return vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_var_get_list( lua_State *L )
{
    vlc_value_t val;
    vlc_value_t text;
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    int i_ret = var_Change( *pp_obj, psz_var, VLC_VAR_GETLIST, &val, &text );
    if( i_ret < 0 )
        return vlclua_push_ret( L, i_ret );

    vlclua_pushlist( L, val.p_list );
    vlclua_pushlist( L, text.p_list );

    var_FreeList( &val, &text );
    return 2;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static inline const void *luaL_checklightuserdata( lua_State *L, int narg )
{
    luaL_checktype( L, narg, LUA_TLIGHTUSERDATA ); /* can raise an error */
    return lua_topointer( L, narg );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_trigger_callback( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    return vlclua_push_ret( L, var_TriggerCallback( *pp_obj, psz_var ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_inc_integer( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );
    int64_t i_val = var_IncInteger( *pp_obj, psz_var );

    lua_pushinteger( L, i_val );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_dec_integer( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );
    int64_t i_val = var_DecInteger( *pp_obj, psz_var );

    lua_pushinteger( L, i_val );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_countchoices( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );
    int i_count = var_CountChoices( *pp_obj, psz_var );

    lua_pushinteger( L, i_count );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/variables.c: static int vlclua_togglebool( lua_State *L )
{
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );
    bool b_val = var_ToggleBool( *pp_obj, psz_var );

    lua_pushboolean( L, b_val );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/xml.c: static int vlclua_xml_delete( lua_State *L )
{
    xml_t *p_xml = *(xml_t**)luaL_checkudata( L, 1, "xml" );
    xml_Delete( p_xml );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/xml.c: static int vlclua_xml_reader_delete( lua_State *L )
{
    xml_reader_t *p_reader = *(xml_reader_t**)luaL_checkudata( L, 1, "xml_reader" );
    xml_ReaderDelete( p_reader );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/xml.c: static int vlclua_xml_reader_next_node( lua_State *L )
{
    xml_reader_t *p_reader = *(xml_reader_t**)luaL_checkudata( L, 1, "xml_reader" );
    const char *psz_name;
    int i_type = xml_ReaderNextNode( p_reader, &psz_name );
    if( i_type <= 0 )
    {
        lua_pushinteger( L, 0 );
        return 1;
    }

    lua_pushinteger( L, i_type );
    lua_pushstring( L, psz_name );
    return 2;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/xml.c: static int vlclua_xml_reader_next_attr( lua_State *L )
{
    xml_reader_t *p_reader = *(xml_reader_t**)luaL_checkudata( L, 1, "xml_reader" );
    const char *psz_value;
    const char *psz_name = xml_ReaderNextAttr( p_reader, &psz_value );
    if( !psz_name )
        return 0;

    lua_pushstring( L, psz_name );
    lua_pushstring( L, psz_value );
    return 2;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_item_set_ ## lowercase ( lua_State *L )\
{\
    services_discovery_t *p_sd = (services_discovery_t *)vlclua_get_this( L );\
    input_item_t **pp_node = (input_item_t **)luaL_checkudata( L, 1, "input_item_t" );\
    if( *pp_node )\
    {\
        if( lua_isstring( L, -1 ) )\
        {\
            input_item_Set ## normal ( *pp_node, lua_tostring( L, -1 ) );\
        } else\
            msg_Err( p_sd, "Error parsing set_ " # lowercase " arguments" );\
    }\
    return 1;\
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_add( lua_State *L )
{
    const char *psz_sd = luaL_checkstring( L, 1 );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    int i_ret = playlist_ServicesDiscoveryAdd( p_playlist, psz_sd );
    return vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_remove( lua_State *L )
{
    const char *psz_sd = luaL_checkstring( L, 1 );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    int i_ret = playlist_ServicesDiscoveryRemove( p_playlist, psz_sd );
    return vlclua_push_ret( L, i_ret );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_is_loaded( lua_State *L )
{
    const char *psz_sd = luaL_checkstring( L, 1 );
    playlist_t *p_playlist = vlclua_get_playlist_internal( L );
    lua_pushboolean( L, playlist_IsServicesDiscoveryLoaded( p_playlist, psz_sd ));
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_remove_item( lua_State *L )
{
    services_discovery_t *p_sd = (services_discovery_t *)vlclua_get_this( L );
    if( !lua_isnil( L, 1 ) )
    {
        input_item_t **pp_input = luaL_checkudata( L, 1, "input_item_t" );
        if( *pp_input )
            services_discovery_RemoveItem( p_sd, *pp_input );
        /* Make sure we won't try to remove it again */
        *pp_input = NULL;
    }
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_remove_node( lua_State *L )
{
    services_discovery_t *p_sd = (services_discovery_t *)vlclua_get_this( L );
    if( !lua_isnil( L, 1 ) )
    {
        input_item_t **pp_input = luaL_checkudata( L, 1, "node" );
        if( *pp_input )
            services_discovery_RemoveItem( p_sd, *pp_input );
        /* Make sure we won't try to remove it again */
        *pp_input = NULL;
    }
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/sd.c: static int vlclua_sd_remove_all_items_nodes( lua_State *L )
{
    services_discovery_t *p_sd = (services_discovery_t *)vlclua_get_this( L );
    services_discovery_RemoveAll( p_sd );
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/httpd.c: static int vlclua_httpd_host_delete( lua_State *L )
{
    httpd_host_t **pp_host = (httpd_host_t **)luaL_checkudata( L, 1, "httpd_host" );
    httpd_HostDelete( *pp_host );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/httpd.c: static int vlclua_httpd_redirect_delete( lua_State *L )
{
    httpd_redirect_t **pp_redirect = (httpd_redirect_t**)luaL_checkudata( L, 1, "httpd_redirect" );
    httpd_RedirectDelete( *pp_redirect );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/libs/httpd.c: static uint8_t *vlclua_todata( lua_State *L, int narg, int *pi_data )
{
    size_t i_data;
    const char *psz_data = lua_tolstring( L, narg, &i_data );
    uint8_t *p_data = (uint8_t*)malloc( i_data * sizeof(uint8_t) );
    *pi_data = (int)i_data;
    if( !p_data )
    {
        luaL_error( L, "Error while allocating buffer." );
        return NULL; /* To please gcc even though luaL_error longjmp-ed out of here */
    }
    memcpy( p_data, psz_data, i_data );
    return p_data;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c: static int ScanExtensions( extensions_manager_t *p_mgr )
{
    int i_ret =
        vlclua_scripts_batch_execute( VLC_OBJECT( p_mgr ),
                                      "extensions",
                                      &ScanLuaCallback,
                                      NULL );

    if( !i_ret )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c: static int vlclua_dummy_require( lua_State *L )
{
    (void) L;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c: int lua_ExtensionActivate( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    assert( p_mgr != NULL && p_ext != NULL );
    return lua_ExecuteFunction( p_mgr, p_ext, "activate", LUA_END );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c:                             const char *psz_function, ... )
{
    va_list args;
    va_start( args, psz_function );
    int i_ret = lua_ExecuteFunctionVa( p_mgr, p_ext, psz_function, args );
    va_end( args );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c: static inline int TriggerMenu( extension_t *p_ext, int i_id )
{
    return PushCommand( p_ext, CMD_TRIGGERMENU, i_id );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/lua/extension.c: extension_t *vlclua_extension_get( lua_State *L )
{
    lua_pushlightuserdata( L, vlclua_extension_set );
    lua_rawget( L, LUA_REGISTRYINDEX );
    extension_t *p_ext = (extension_t*) lua_topointer( L, -1 );
    lua_pop( L, 1 );
    return p_ext;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/goom.c: static inline int16_t FloatToInt16( float f )
{
    if( f >= 1.0 )
        return 32767;
    else if( f < -1.0 )
        return -32768;
    else
        return (int16_t)( f * 32768.0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/projectm.cpp:                          vlc_value_t oldv, vlc_value_t newv, void *p_data )
{
    VLC_UNUSED( p_vout ); VLC_UNUSED( oldv );
    vout_display_t *p_vd = (vout_display_t*)p_data;

    if( !strcmp(psz_name, "fullscreen") )
    {
        vout_SetDisplayFullscreen( p_vd, newv.b_bool );
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/vsxu.cpp:                          vlc_value_t oldv, vlc_value_t newv, void *p_data )
{
    VLC_UNUSED( p_vout ); VLC_UNUSED( oldv );
    vout_display_t *p_vd = (vout_display_t*)p_data;

    if( !strcmp(psz_name, "fullscreen") )
    {
        vout_SetDisplayFullscreen( p_vd, newv.b_bool );
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/visual/fft.c: static int reverseBits(unsigned int initial)
{
    unsigned int reversed = 0, loop;
    for(loop = 0; loop < FFT_BUFFER_SIZE_LOG; loop++) {
        reversed <<= 1;
        reversed += (initial & 1);
        initial >>= 1;
    }
    return reversed;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/visualization/visual/effects.c:                       const block_t * p_buffer , picture_t * p_picture)
{
    VLC_UNUSED(p_effect); VLC_UNUSED(p_aout); VLC_UNUSED(p_buffer);
    VLC_UNUSED(p_picture);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/smooth/utils.c: static int hex_digit( const char c )
{
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= '0' && c<= '9')
        return c - '0';
    else
        return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/smooth/utils.c: int es_cat_to_index( int i_cat )
{
    switch( i_cat )
    {
        case VIDEO_ES:
            return 0;
        case AUDIO_ES:
            return 1;
        case SPU_ES:
            return 2;
        default:
            return -1;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/smooth/utils.c: int index_to_es_cat( int index )
{
    switch( index )
    {
        case 0:
            return VIDEO_ES;
        case 1:
            return AUDIO_ES;
        case 2:
            return SPU_ES;
        default:
            return -1;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/mpd/MPDFactory.cpp: MPD* MPDFactory::create             (dash::xml::Node *root, stream_t *p_stream, Profile profile)
{
    switch(profile)
    {
        case dash::mpd::Full2011:
        case dash::mpd::Basic:
        case dash::mpd::BasicCM:    return MPDFactory::createBasicCMMPD(root, p_stream);
        case dash::mpd::IsoffMain:  return MPDFactory::createIsoffMainMPD(root, p_stream);

        default: return NULL;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/mpd/SegmentTemplate.cpp: bool            SegmentTemplate::isSingleShot() const
{
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/mpd/Segment.cpp: bool                    Segment::isSingleShot   () const
{
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/Helper.cpp: std::string Helper::combinePaths        (const std::string &path1, const std::string &path2)
{
    char path1Last  = path1.at(path1.size() - 1);
    char path2First = path2.at(0);

    if(path1Last == '/' && path2First == '/')
        return path1 + path2.substr(1, path2.size());

    if(path1Last != '/' && path2First != '/')
        return path1 + "/" + path2;

    return path1 + path2;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/Helper.cpp: std::string Helper::getDirectoryPath    (const std::string &path)
{
    int pos = path.find_last_of('/');

    return path.substr(0, pos);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/xml/DOMParser.cpp: bool    DOMParser::isDash                   (stream_t *stream)
{
    const char* psz_namespaceDIS = "urn:mpeg:mpegB:schema:DASH:MPD:DIS2011";
    const char* psz_namespaceIS  = "urn:mpeg:DASH:schema:MPD:2011";

    const uint8_t *peek;
    int peek_size = stream_Peek(stream, &peek, 1024);
    if (peek_size < (int)strlen(psz_namespaceDIS))
        return false;

    std::string header((const char*)peek, peek_size);
    return (header.find(psz_namespaceDIS) != std::string::npos) || (header.find(psz_namespaceIS) != std::string::npos);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/xml/Node.cpp: bool                                Node::hasText               () const
{
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/adaptationlogic/AdaptationLogicFactory.cpp:                                                   IMPDManager *mpdManager, stream_t *stream)
{
    switch(logic)
    {
        case IAdaptationLogic::AlwaysBest:      return new AlwaysBestAdaptationLogic    (mpdManager, stream);
        case IAdaptationLogic::RateBased:       return new RateBasedAdaptationLogic     (mpdManager, stream);
        case IAdaptationLogic::Default:
        case IAdaptationLogic::AlwaysLowest:
        default:
            return NULL;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/http/Chunk.cpp: int                 Chunk::getEndByte           () const
{
    return endByte;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/http/Chunk.cpp: int                 Chunk::getStartByte         () const
{
    return startByte;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/http/Chunk.cpp: const std::string&  Chunk::getUrl               () const
{
    return url;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static hls_stream_t *hls_Get(vlc_array_t *hls_stream, const int wanted)
{
    int count = vlc_array_count(hls_stream);
    if (count <= 0)
        return NULL;
    if ((wanted < 0) || (wanted >= count))
        return NULL;
    return (hls_stream_t *) vlc_array_item_at_index(hls_stream, wanted);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static inline hls_stream_t *hls_GetFirst(vlc_array_t *hls_stream)
{
    return hls_Get(hls_stream, 0);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static hls_stream_t *hls_GetLast(vlc_array_t *hls_stream)
{
    int count = vlc_array_count(hls_stream);
    if (count <= 0)
        return NULL;
    count--;
    return hls_Get(hls_stream, count);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static int parse_ProgramDateTime(stream_t *s, hls_stream_t *hls, char *p_read)
{
    VLC_UNUSED(hls);
    msg_Dbg(s, "tag not supported: #EXT-X-PROGRAM-DATE-TIME %s", p_read);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static int parse_Discontinuity(stream_t *s, hls_stream_t *hls, char *p_read)
{
    assert(hls);

    /* FIXME: Do we need to act on discontinuity ?? */
    msg_Dbg(s, "#EXT-X-DISCONTINUITY %s", p_read);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/httplive.c: static ssize_t read_M3U8_from_url(stream_t *s, const char* psz_url, uint8_t **buffer)
{
    assert(*buffer == NULL);

    /* Construct URL */
    stream_t *p_m3u8 = stream_UrlNew(s, psz_url);
    if (p_m3u8 == NULL)
        return VLC_EGENERIC;

    ssize_t size = read_M3U8_from_stream(p_m3u8, buffer);
    stream_Delete(p_m3u8);

    return size;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/a52.c: static int OpenDecoder( vlc_object_t *p_this )
{
    /* HACK: Don't use this codec if we don't have an a52 audio filter */
    if( !module_exists( "a52tofloat32" ) )
        return VLC_EGENERIC;
    return OpenCommon( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/a52.c: static int OpenPacketizer( vlc_object_t *p_this )
{
    return OpenCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/ddummy.c: static int OpenDecoder( vlc_object_t *p_this )
{
    return OpenDecoderCommon( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/ddummy.c: static int  OpenDecoderDump( vlc_object_t *p_this )
{
    return OpenDecoderCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.c: static subpicture_t *Decode( decoder_t *p_dec, block_t **pp_block )
{
    if( pp_block && *pp_block )
    {
        Push( p_dec, *pp_block );
        *pp_block = NULL;
    }

    for( ;; )
    {
        block_t *p_block = Pop( p_dec );
        if( !p_block )
            break;

        subpicture_t *p_spu = Convert( p_dec, p_block );
        if( p_spu )
            return p_spu;
    }
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.c: static bool Eia608ParseSingle( eia608_t *h, const uint8_t dx )
{
    assert( dx >= 0x20 );
    Eia608Write( h, dx );
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.c: static bool Eia608ParseDouble( eia608_t *h, uint8_t d2 )
{
    assert( d2 >= 0x30 && d2 <= 0x3f );
    Eia608Write( h, d2 + 0x50 ); /* We use charaters 0x80...0x8f */
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.c: static bool Eia608ParseExtended( eia608_t *h, uint8_t d1, uint8_t d2 )
{
    assert( d2 >= 0x20 && d2 <= 0x3f );
    assert( d1 == 0x12 || d1 == 0x13 );
    if( d1 == 0x12 )
        d2 += 0x70; /* We use charaters 0x90-0xaf */
    else
        d2 += 0x90; /* We use charaters 0xb0-0xcf */

    /* The extended characters replace the previous one with a more
     * advanced one */
    Eia608Cursor( h, -1 );
    Eia608Write( h, d2 );
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.c: static bool Eia608ParseCommand0x17( eia608_t *h, uint8_t d2 )
{
    switch( d2 )
    {
    case 0x21:  /* Tab offset 1 */
        Eia608Cursor( h, 1 );
        break;
    case 0x22:  /* Tab offset 2 */
        Eia608Cursor( h, 2 );
        break;
    case 0x23:  /* Tab offset 3 */
        Eia608Cursor( h, 3 );
        break;
    }
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/libass.c: static rectangle_t r_create( int x0, int y0, int x1, int y1 )
{
    rectangle_t r = { x0, y0, x1, y1 };
    return r;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/schroedinger.c: static void SchroBufferFree( SchroBuffer *buf, void *priv )
{
    block_t *p_block = priv;

    if( !p_block )
        return;

    block_Release( p_block );
    (void)buf;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/fdkaac.c: static const char *fdkaac_error(AACENC_ERROR erraac)
{
    switch (erraac) {
    case AACENC_OK: return "No error";
    case AACENC_INVALID_HANDLE: return "Invalid handle";
    case AACENC_MEMORY_ERROR: return "Memory allocation error";
    case AACENC_UNSUPPORTED_PARAMETER: return "Unsupported parameter";
    case AACENC_INVALID_CONFIG: return "Invalid config";
    case AACENC_INIT_ERROR: return "Initialization error";
    case AACENC_INIT_AAC_ERROR: return "AAC library initialization error";
    case AACENC_INIT_SBR_ERROR: return "SBR library initialization error";
    case AACENC_INIT_TP_ERROR: return "Transport library initialization error";
    case AACENC_INIT_META_ERROR: return "Metadata library initialization error";
    case AACENC_ENCODE_ERROR: return "Encoding error";
    case AACENC_ENCODE_EOF: return "End of file";
    default: return "Unknown error";
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/opus_header.c: static int comment_pad(char **comments, size_t *length)
{
    const unsigned padding = 512; /* default from opus-tools */

    if(SIZE_MAX - *length < padding + 255)
        return 1;

    char *p = *comments;
    /* Make sure there is at least "padding" worth of padding free, and
       round up to the maximum that fits in the current ogg segments. */
    size_t newlen = ((*length + padding) / 255 + 1) * 255 - 1;
    p = realloc(p, newlen);
    if (p == NULL)
        return 1;

    memset(p + *length, 0, newlen - *length);
    *comments = p;
    *length = newlen;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cc.h: static inline void cc_Exit( cc_data_t *c )
{
    VLC_UNUSED(c);
    return;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/dts.c: static int OpenDecoder( vlc_object_t *p_this )
{
    /* HACK: Don't use this codec if we don't have an dts audio filter */
    if( !module_exists( "dtstofloat32" ) )
        return VLC_EGENERIC;

    return OpenCommon( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/dts.c: static int OpenPacketizer( vlc_object_t *p_this )
{
    return OpenCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/substx3g.c: static int ConvertFlags( int i_atomflags )
{
    int i_vlcstyles_flags = 0;
    if ( i_atomflags & FONT_FACE_BOLD )
        i_vlcstyles_flags |= STYLE_BOLD;
    if ( i_atomflags & FONT_FACE_ITALIC )
        i_vlcstyles_flags |= STYLE_ITALIC;
    if ( i_atomflags & FONT_FACE_UNDERLINE )
        i_vlcstyles_flags |= STYLE_UNDERLINE;
    return i_vlcstyles_flags;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/substx3g.c: static size_t str8len( const char *psz_string )
{
    const char *psz_tmp = psz_string;
    size_t i=0;
    while ( *psz_tmp )
    {
        if ( (*psz_tmp & 0xC0) != 0x80 ) i++;
        psz_tmp++;
    }
    return i;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/substx3g.c: static char * str8indup( const char *psz_string, size_t i_skip, size_t n )
{
    while( i_skip && *psz_string )
    {
        if ( (*psz_string & 0xC0) != 0x80 ) i_skip--;
        psz_string++;
    }
    if ( ! *psz_string || i_skip ) return NULL;

    const char *psz_tmp = psz_string;
    while( n && *psz_tmp )
    {
        if ( (*psz_tmp & 0xC0) != 0x80 ) n--;
        psz_tmp++;
    }
    return strndup( psz_string, psz_tmp - psz_string );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/kate.c: static char *GetTigerString( decoder_t *p_dec, const char *psz_name )
{
    char *psz_value = var_CreateGetString( p_dec, psz_name );
    if( psz_value)
    {
        psz_value = strdup( psz_value );
    }
    var_Destroy( p_dec, psz_name );
    return psz_value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/kate.c: static int GetTigerInteger( decoder_t *p_dec, const char *psz_name )
{
    int i_value = var_CreateGetInteger( p_dec, psz_name );
    var_Destroy( p_dec, psz_name );
    return i_value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/kate.c: static double GetTigerFloat( decoder_t *p_dec, const char *psz_name )
{
    double f_value = var_CreateGetFloat( p_dec, psz_name );
    var_Destroy( p_dec, psz_name );
    return f_value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cdg.c: static uint32_t RenderRGB( int r, int g, int b )
{
    return ( r << CDG_COLOR_R_SHIFT ) | ( g << CDG_COLOR_G_SHIFT ) | ( b << CDG_COLOR_B_SHIFT );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/gstdecode.c:         gpointer p_data )
{
    VLC_UNUSED( p_src );
    decoder_t *p_dec = p_data;
    msg_Dbg( p_dec, "appsrc seeking to %"G_GUINT64_FORMAT, l_offset );
    return TRUE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/svcdsub.c: static int PacketizerOpen( vlc_object_t *p_this )
{
    if( DecoderOpen( p_this ) != VLC_SUCCESS ) return VLC_EGENERIC;

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/qsv.c: typedef struct async_task_t
{
    mfxBitstream     bs;                  // Intel's bitstream structure.
    mfxSyncPoint     syncp;               // Async Task Sync Point.
    block_t          *block;              // VLC's block structure to be returned by Encode.
} async_task_t;

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/qsv.c: static inline mtime_t qsv_timestamp_to_mtime(int64_t mfx_ts)
{
    return mfx_ts / INT64_C(9) * INT64_C(100);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/qsv.c: static inline uint64_t qsv_mtime_to_timestamp(mtime_t vlc_ts)
{
    return vlc_ts / UINT64_C(100) * UINT64_C(9);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.h: static inline int32_t fixmul32(int32_t x, int32_t y)
{
    int64_t temp;
    temp = x;
    temp *= y;

    temp >>= PRECISION;

    return (int32_t)temp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.h: static inline int32_t fixmul32b(int32_t x, int32_t y)
{
    int64_t temp;

    temp = x;
    temp *= y;

    temp >>= 31;        //16+31-16 = 31 bits

    return (int32_t)temp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: // avoid +32 for shift optimization (gcc should do that ...)
static inline  int32_t NEG_SSR32( int32_t a, int8_t s){
    asm ("sarl %1, %0\n\t"
         : "+r" (a)
         : "ic" ((uint8_t)(-s))
    );
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: static inline uint32_t NEG_USR32(uint32_t a, int8_t s){
    asm ("shrl %1, %0\n\t"
         : "+r" (a)
         : "ic" ((uint8_t)(-s))
    );
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: #    define unaligned(x)                                        \
static inline uint##x##_t unaligned##x(const void *v) {         \
    return *(const __unaligned uint##x##_t *) v;                \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: #    define unaligned(x)                                        \
static inline uint##x##_t unaligned##x(const void *v) {         \
    return *(const uint##x##_t *) v;                            \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:  */
static inline int get_xbits(GetBitContext *s, int n){
    register int sign;
    register int32_t cache;
    OPEN_READER(re, s)
    UPDATE_CACHE(re, s)
    cache = GET_CACHE(re,s);
    sign=(~cache)>>31;
    LAST_SKIP_BITS(re, s, n)
    CLOSE_READER(re, s)
    return (NEG_USR32(sign ^ cache, n) ^ sign) - sign;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: 
static inline int get_sbits(GetBitContext *s, int n){
    register int tmp;
    OPEN_READER(re, s)
    UPDATE_CACHE(re, s)
    tmp= SHOW_SBITS(re, s, n);
    LAST_SKIP_BITS(re, s, n)
    CLOSE_READER(re, s)
    return tmp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:  */
static inline unsigned int get_bits(GetBitContext *s, int n){
    register int tmp;
    OPEN_READER(re, s)
    UPDATE_CACHE(re, s)
    tmp= SHOW_UBITS(re, s, n);
    LAST_SKIP_BITS(re, s, n)
    CLOSE_READER(re, s)
    return tmp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:  */
static inline unsigned int show_bits(GetBitContext *s, int n){
    register int tmp;
    OPEN_READER(re, s)
    UPDATE_CACHE(re, s)
    tmp= SHOW_UBITS(re, s, n);
//    CLOSE_READER(re, s)
    return tmp;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: 
static inline unsigned int show_bits1(GetBitContext *s){
    return show_bits(s, 1);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:  */
static inline unsigned int get_bits_long(GetBitContext *s, int n){
    if(n<=17) return get_bits(s, n);
    else{
#ifdef ALT_BITSTREAM_READER_LE
        int ret= get_bits(s, 16);
        return ret | (get_bits(s, n-16) << 16);
#else
        int ret= get_bits(s, 16) << (n-16);
        return ret | get_bits(s, n-16);
#endif
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:  */
static inline unsigned int show_bits_long(GetBitContext *s, int n){
    if(n<=17) return show_bits(s, n);
    else{
        GetBitContext gb= *s;
        int ret= get_bits_long(s, n);
        *s= gb;
        return ret;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: static inline int check_marker(GetBitContext *s, const char *msg)
{
    int bit= get_bits1(s);
    if(!bit)
        av_log(NULL, AV_LOG_INFO, "Marker bit missing %s\n", msg);

    return bit;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h:                                   int bits, int max_depth)
{
    int code;

    OPEN_READER(re, s)
    UPDATE_CACHE(re, s)

    GET_VLC(code, re, s, table, bits, max_depth)

    CLOSE_READER(re, s)
    return code;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: 
static inline int decode012(GetBitContext *gb){
    int n;
    n = get_bits1(gb);
    if (n == 0)
        return 0;
    else
        return get_bits1(gb) + 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int32_t Fixed32From64(int64_t x)
{
  return x & 0xFFFFFFFF;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int64_t Fixed32To64(int32_t x)
{
  return (int64_t)x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int64_t fixmul64byfixed(int64_t x, int32_t y)
{
    return (x * y);
/*  return (int64_t) fixmul32(Fixed32From64(x),y); */
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int32_t fixdiv32(int32_t x, int32_t y)
{
    int64_t temp;

    if(x == 0)
        return 0;
    if(y == 0)
        return 0x7fffffff;
    temp = x;
    temp <<= PRECISION;
    return (int32_t)(temp / y);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int64_t fixdiv64(int64_t x, int64_t y)
{
    int64_t temp;

    if(x == 0)
        return 0;
    if(y == 0)
        return 0x07ffffffffffffffLL;
    temp = x;
    temp <<= PRECISION64;
    return (int64_t)(temp / y);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: static inline uint64_t ByteSwap64(uint64_t x)
{
    union { 
        uint64_t ll;
        struct {
           uint32_t l,h;
        } l;
    } r;
    r.l.l = bswap_32 (x);
    r.l.h = bswap_32 (x>>32);
    return r.ll;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: static inline unsigned short ByteSwap16(unsigned short x)
{
  __asm("xchgb %b0,%h0"	:
        "=q" (x)	:
        "0" (x));
    return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: static inline unsigned int ByteSwap32(unsigned int x)
{
#if __CPU__ > 386
 __asm("bswap	%0":
      "=r" (x)     :
#else
 __asm("xchgb	%b0,%h0\n"
      "	rorl	$16,%0\n"
      "	xchgb	%b0,%h0":
      "=q" (x)		:
#endif
      "0" (x));
  return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: 
static inline uint16_t ByteSwap16(uint16_t x) {
	__asm__("swap.b %0,%0":"=r"(x):"0"(x));
	return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: 
static inline uint32_t ByteSwap32(uint32_t x) {
	__asm__(
	"swap.b %0,%0\n"
	"swap.w %0,%0\n"
	"swap.b %0,%0\n"
	:"=r"(x):"0"(x));
	return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bswap.h: static inline uint64_t ByteSwap64(uint64_t x)
{
    union { 
        uint64_t ll;
        struct {
           uint32_t l,h;
        } l;
    } r;
    r.l.l = bswap_32 (x);
    r.l.h = bswap_32 (x>>32);
    return r.ll;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/edummy.c: static block_t *EncodeVideo( encoder_t *p_enc, picture_t *p_pict )
{
    VLC_UNUSED(p_enc); VLC_UNUSED(p_pict);
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/edummy.c: static block_t *EncodeAudio( encoder_t *p_enc, block_t *p_buf )
{
    VLC_UNUSED(p_enc); VLC_UNUSED(p_buf);
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/vout.c:     OMX_PTR app_data, OMX_BUFFERHEADERTYPE *omx_header)
{
    (void)omx_handle;
    (void)app_data;
    (void)omx_header;

    return OMX_ErrorNone;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/android_opaque.c: vlc_mutex_t* get_android_opaque_mutex()
{
    static vlc_mutex_t s_mutex = VLC_STATIC_MUTEX;
    return &s_mutex;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/utils.c:     OMX_PTR *event_data)
{
    OMX_ERRORTYPE status;
    OMX_EVENTTYPE event;
    mtime_t before =  mdate();

    while(1)
    {
        status = WaitForOmxEvent(queue, &event, data_1, data_2, event_data);
        if(status != OMX_ErrorNone) return status;

        if(event == specific_event) break;
        if(mdate() - before > CLOCK_FREQ) return OMX_ErrorTimeout;
    }

    return OMX_ErrorNone;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/utils.c: const char *GetOmxRole( vlc_fourcc_t i_fourcc, int i_cat, bool b_enc )
{
    if(b_enc)
        return i_cat == VIDEO_ES ?
            GetOmxVideoEncRole( i_fourcc ) : GetOmxAudioEncRole( i_fourcc );
    else
        return i_cat == VIDEO_ES ?
            GetOmxVideoRole( i_fourcc ) : GetOmxAudioRole( i_fourcc );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/qcom.c: static size_t tile_pos(size_t x, size_t y, size_t w, size_t h)
{
    size_t flim = x + (y & ~1) * w;

    if (y & 1) {
        flim += (x & ~3) + 2;
    } else if ((h & 1) == 0 || y != (h - 1)) {
        flim += (x + 2) & ~3;
    }

    return flim;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: #else
   static inline OMX_TICKS omx_ticks_from_s64(signed long long s) { OMX_TICKS t; t.nLowPart = (OMX_U32)s; t.nHighPart = (OMX_U32)(s>>32); return t; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: \code{nPortIndex} is \code{OMX_ALL}, it returns the sensor mode

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: \code{nNumModes} only \code{nNumModes} is returned. If

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: returns the sensor mode that would be selected for the values
currently in \code{OMX_IndexParamPortDefinition} for that port.

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: 
typedef struct OMX_FACEREGIONTYPE {
   OMX_S16 nLeft;              /**< X Coordinate of the top left corner of the rectangle */
   OMX_S16 nTop;               /**< Y Coordinate of the top left corner of the rectangle */
   OMX_U16 nWidth;             /**< Width of the rectangle */
   OMX_U16 nHeight;            /**< Height of the rectangle */
   OMX_FACEREGIONFLAGSTYPE nFlags;  /**< Flags for the region */
#ifndef OMX_SKIP64BIT
   OMX_U64 nFaceRecognitionId; /**< ID returned by face recognition for this face */
#else
   struct
   {
      OMX_U32 nLowPart;   /**< low bits of the signed 64 bit value */
      OMX_U32 nHighPart;  /**< high bits of the signed 64 bit value */
   } nFaceRecognitionId;
#endif
} OMX_FACEREGIONTYPE;

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: typedef struct OMX_PARAM_BRCMVIDEODRMPROTECTBUFFERTYPE
{
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;

   OMX_U32 size_wanted;     /**< Input. Zero size means internal video decoder buffer,
                                 mem_handle and phys_addr not returned in this case */
   OMX_U32 protect;         /**< Input. 1 = protect, 0 = unprotect */

   OMX_U32 mem_handle;      /**< Output. Handle for protected buffer */
   OMX_PTR phys_addr;       /**< Output. Physical memory address of protected buffer */
} OMX_PARAM_BRCMVIDEODRMPROTECTBUFFERTYPE;

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/omxil_utils.h: static inline int64_t FromOmxTicks(OMX_TICKS value)
{
    return (((int64_t)value.nHighPart) << 32) | value.nLowPart;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/omxil_utils.h: static inline OMX_TICKS ToOmxTicks(int64_t value)
{
    OMX_TICKS s;
    s.nLowPart = value;
    s.nHighPart = value >> 32;
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/telx.c: static uint8_t bytereverse( int n )
{
    n = (((n >> 1) & 0x55) | ((n << 1) & 0xaa));
    n = (((n >> 2) & 0x33) | ((n << 2) & 0xcc));
    n = (((n >> 4) & 0x0f) | ((n << 4) & 0xf0));
    return n;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/mpeg_audio.c: static int OpenDecoder( vlc_object_t *p_this )
{
    /* HACK: Don't use this codec if we don't have an mpga audio filter */
    if( !module_exists( "mpgatofixed32" ) )
        return VLC_EGENERIC;

    return Open( p_this );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cvdsub.c: static subpicture_t *Decode( decoder_t *p_dec, block_t **pp_block )
{
    block_t *p_block, *p_spu;

    if( pp_block == NULL || *pp_block == NULL ) return NULL;

    p_block = *pp_block;
    *pp_block = NULL;

    if( !(p_spu = Reassemble( p_dec, p_block )) ) return NULL;

    /* Parse and decode */
    return DecodePacket( p_dec, p_spu );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/subsusf.c: static subpicture_t *DecodeBlock( decoder_t *p_dec, block_t **pp_block )
{
    subpicture_t *p_spu;
    block_t *p_block;

    if( !pp_block || *pp_block == NULL )
        return NULL;

    p_block = *pp_block;

    p_spu = ParseText( p_dec, p_block );

    block_Release( p_block );
    *pp_block = NULL;

    return p_spu;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/lpcm.c: static int OpenDecoder( vlc_object_t *p_this )
{
    return OpenCommon( p_this, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/lpcm.c: static int OpenPacketizer( vlc_object_t *p_this )
{
    return OpenCommon( p_this, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/aes3.c: static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;

    return Open( p_dec, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/aes3.c: static int OpenPacketizer( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;

    return Open( p_dec, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/substext.h: static inline subpicture_t *decoder_NewSubpictureText(decoder_t *decoder)
{
    subpicture_updater_sys_t *sys = calloc(1, sizeof(*sys));
    subpicture_updater_t updater = {
        .pf_validate = SubpictureTextValidate,
        .pf_update   = SubpictureTextUpdate,
        .pf_destroy  = SubpictureTextDestroy,
        .p_sys       = sys,
    };
    subpicture_t *subpic = decoder_NewSubpicture(decoder, &updater);
    if (!subpic)
        free(sys);
    return subpic;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/scte27.c: static scte27_color_t bs_read_color(bs_t *bs)
{
    scte27_color_t color;

    /* XXX it's unclear if a value of 0 in Y/U/V means a transparent pixel */
    color.y     = bs_read(bs, 5) << 3;
    color.alpha = bs_read1(bs) ? 0xff : 0x80;
    color.v     = bs_read(bs, 5) << 3;
    color.u     = bs_read(bs, 5) << 3;

    return color;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/dxva2.c: static int DxResetVideoDecoder(vlc_va_t *va)
{
    msg_Err(va, "DxResetVideoDecoder unimplemented");
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/vda.c: static int Get( vlc_va_t *external, void **opaque, uint8_t **data )
{
    VLC_UNUSED( external );

    *data = (uint8_t *)1; // dummy
    (void) opaque;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/vda.c: static int Get( vlc_va_t *external, void **opaque, uint8_t **data )
{
    VLC_UNUSED( external );

    (void) data;
    (void) opaque;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/hwdummy.c: static int Lock(vlc_va_t *va, void **opaque, uint8_t **data)
{
    *data = (void *)(uintptr_t)DATA_MAGIC;
    *opaque = (void *)(uintptr_t)OPAQUE_MAGIC;
    (void) va;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/hwdummy.c:                         VdpBitstreamBuffer const *bitstream_buffers)
{
    (void) decoder; (void) target; (void) picture_info;
    (void) bitstream_buffer_count; (void) bitstream_buffers;
    assert(decoder == DECODER_MAGIC);
    assert(target == DATA_MAGIC);
    return VDP_STATUS_OK;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/avcodec/va.c: static int vlc_va_Start(void *func, va_list ap)
{
    vlc_va_t *va = va_arg(ap, vlc_va_t *);
    AVCodecContext *ctx = va_arg(ap, AVCodecContext *);
    const es_format_t *fmt = va_arg(ap, const es_format_t *);
    int (*open)(vlc_va_t *, AVCodecContext *, const es_format_t *) = func;

    return open(va, ctx, fmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/strings.c: char *vlc_b64_encode( const char *src )
{
    if( src )
        return vlc_b64_encode_binary( (const uint8_t*)src, strlen(src) );
    else
        return vlc_b64_encode_binary( (const uint8_t*)"", 0 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/strings.c: size_t vlc_b64_decode_binary( uint8_t **pp_dst, const char *psz_src )
{
    const int i_src = strlen( psz_src );
    uint8_t   *p_dst;

    *pp_dst = p_dst = malloc( i_src );
    if( !p_dst )
        return 0;
    return  vlc_b64_decode_binary_to_buffer( p_dst, i_src, psz_src );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/strings.c: static int write_meta(FILE *stream, input_item_t *item, vlc_meta_type_t type)
{
    if (item == NULL)
        return EOF;

    char *value = input_item_GetMeta(item, type);
    if (value == NULL)
        return EOF;

    int ret = fputs(value, stream);
    free(value);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/filesystem.c: static int dummy_select( const char *str )
{
    (void)str;
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/filesystem.c:                   int (*compar)( const char **, const char ** ) )
{
    DIR *dir = vlc_opendir (dirname);
    int val = -1;

    if (dir != NULL)
    {
        val = vlc_loaddir (dir, namelist, select, compar);
        closedir (dir);
    }
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/charset.c: double us_strtod( const char *str, char **end )
{
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t oldloc = uselocale (loc);
    double res = strtod (str, end);

    if (loc != (locale_t)0)
    {
        uselocale (oldloc);
        freelocale (loc);
    }
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/charset.c: float us_strtof( const char *str, char **end )
{
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t oldloc = uselocale (loc);
    float res = strtof (str, end);

    if (loc != (locale_t)0)
    {
        uselocale (oldloc);
        freelocale (loc);
    }
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/charset.c: double us_atof( const char *str )
{
    return us_strtod( str, NULL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/unicode.c: char *EnsureUTF8( char *str )
{
    char *ret = str;
    size_t n;
    uint32_t cp;

    while ((n = vlc_towc (str, &cp)) != 0)
        if (likely(n != (size_t)-1))
            str += n;
        else
        {
            *str++ = '?';
            ret = NULL;
        }
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/unicode.c: const char *IsUTF8( const char *str )
{
    size_t n;
    uint32_t cp;

    while ((n = vlc_towc (str, &cp)) != 0)
        if (likely(n != (size_t)-1))
            str += n;
        else
            return NULL;
    return str;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/url.c: char *decode_URI_duplicate (const char *str)
{
    char *buf = strdup (str);
    if (decode_URI (buf) == NULL)
    {
        free (buf);
        buf = NULL;
    }
    return buf;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/text/url.c: static inline bool isurisafe (int c)
{
    /* These are the _unreserved_ URI characters (RFC3986 §2.3) */
    return ((unsigned char)(c - 'a') < 26)
        || ((unsigned char)(c - 'A') < 26)
        || ((unsigned char)(c - '0') < 10)
        || (strchr ("-._~", c) != NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/services_discovery.c:                       const char *longname, int category)
{
    vlc_sd_probe_t names = { strdup(name), strdup(longname), category };

    if (unlikely (names.name == NULL || names.longname == NULL
               || vlc_probe_add (probe, &names, sizeof (names))))
    {
        free (names.name);
        free (names.longname);
        return VLC_ENOMEM;
    }
    return VLC_PROBE_CONTINUE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                             playlist_item_t *p_root, bool b_do_stop )
{
    PL_ASSERT_LOCKED;
    playlist_item_t *p_item = playlist_ItemFindFromInputAndRoot(
        p_playlist, p_input, p_root, false );
    if( !p_item ) return VLC_EGENERIC;
    return playlist_DeleteItem( p_playlist, p_item, b_do_stop );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                                       playlist_item_t *p_root, bool b_locked )
{
    int i_ret;
    PL_LOCK_IF( !b_locked );
    i_ret = DeleteFromInput( p_playlist, p_item, p_root, true );
    PL_UNLOCK_IF( !b_locked );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c: int playlist_DeleteFromItemId( playlist_t *p_playlist, int i_id )
{
    PL_ASSERT_LOCKED;
    playlist_item_t *p_item = playlist_ItemGetById( p_playlist, i_id );
    if( !p_item ) return VLC_EGENERIC;
    return playlist_DeleteItem( p_playlist, p_item, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                   bool b_playlist, bool b_locked )
{
    return playlist_AddExt( p_playlist, psz_uri, psz_name,
                            i_mode, i_pos, -1, 0, NULL, 0, b_playlist, b_locked );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                      bool b_playlist, bool b_locked )
{
    int i_ret;
    input_item_t *p_input;

    p_input = input_item_NewExt( psz_uri, psz_name,
                                 i_options, ppsz_options, i_option_flags,
                                 i_duration );
    if( p_input == NULL )
        return VLC_ENOMEM;
    i_ret = playlist_AddInput( p_playlist, p_input, i_mode, i_pos, b_playlist,
                               b_locked );
    vlc_gc_decref( p_input );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:     input_item_node_t *p_node, int i_pos, bool b_flat )
{
    playlist_item_t *p_first_leaf = NULL;
    return RecursiveAddIntoParent ( p_playlist, p_parent, p_node, i_pos, b_flat, &p_first_leaf );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                         bool b_stop )
{
    assert( b_stop );
    return playlist_NodeDelete( p_playlist, p_item, true, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/aout.c: float playlist_VolumeGet (playlist_t *pl)
{
    float volume = -1.f;

    audio_output_t *aout = playlist_GetAout (pl);
    if (aout != NULL)
    {
        volume = aout_VolumeGet (aout);
        vlc_object_release (aout);
    }
    return volume;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/aout.c: int playlist_VolumeSet (playlist_t *pl, float vol)
{
    int ret = -1;

    audio_output_t *aout = playlist_GetAout (pl);
    if (aout != NULL)
    {
        ret = aout_VolumeSet (aout, vol);
        vlc_object_release (aout);
    }
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/aout.c: int playlist_MuteGet (playlist_t *pl)
{
    int mute = -1;

    audio_output_t *aout = playlist_GetAout (pl);
    if (aout != NULL)
    {
        mute = aout_MuteGet (aout);
        vlc_object_release (aout);
    }
    return mute;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/aout.c: int playlist_MuteSet (playlist_t *pl, bool mute)
{
    int ret = -1;

    audio_output_t *aout = playlist_GetAout (pl);
    if (aout != NULL)
    {
        ret = aout_MuteSet (aout, mute);
        vlc_object_release (aout);
    }
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/tree.c:                          playlist_item_t *p_parent )
{
    return playlist_NodeInsert( p_playlist, p_item, p_parent, -1 );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_ALBUM, first, second )
{
    int i_ret = meta_sort( first, second, vlc_meta_Album, false );
    /* Items came from the same album: compare the track numbers */
    if( i_ret == 0 )
        i_ret = meta_sort( first, second, vlc_meta_TrackNumber, true );

    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_ARTIST, first, second )
{
    int i_ret = meta_sort( first, second, vlc_meta_Artist, false );
    /* Items came from the same artist: compare the albums */
    if( i_ret == 0 )
        i_ret = proto_SORT_ALBUM( first, second );

    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_DESCRIPTION, first, second )
{
    return meta_sort( first, second, vlc_meta_Description, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_GENRE, first, second )
{
    return meta_sort( first, second, vlc_meta_Genre, false );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_RATING, first, second )
{
    return meta_sort( first, second, vlc_meta_Rating, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_TITLE, first, second )
{
    return meta_strcasecmp_title( first, second );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: SORTFN( SORT_TRACK_NUMBER, first, second )
{
    return meta_sort( first, second, vlc_meta_TrackNumber, true );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: 	static int cmp_a_##s(const void *l,const void *r) \
	{ return proto_##s(*(const playlist_item_t *const *)l, \
                           *(const playlist_item_t *const *)r); } \

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/sort.c: 	static int cmp_d_##s(const void *l,const void *r) \
	{ return -1*proto_##s(*(const playlist_item_t * const *)l, \
                              *(const playlist_item_t * const *)r); }

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/loadsave.c: int playlist_Import( playlist_t *p_playlist, const char *psz_file )
{
    input_item_t *p_input;
    const char *const psz_option = "meta-file";
    char *psz_uri = vlc_path2uri( psz_file, NULL );

    if( psz_uri == NULL )
        return VLC_EGENERIC;

    p_input = input_item_NewExt( psz_uri, psz_file,
                                 1, &psz_option, VLC_INPUT_OPTION_TRUSTED, -1 );
    free( psz_uri );

    playlist_AddInput( p_playlist, p_input, PLAYLIST_APPEND, PLAYLIST_END,
                       true, false );
    return input_Read( p_playlist, p_input );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/control.c:                       bool b_locked, ... )
{
    va_list args;
    int i_result;
    PL_LOCK_IF( !b_locked );
    va_start( args, b_locked );
    i_result = PlaylistVAControl( p_playlist, i_query, args );
    va_end( args );
    PL_UNLOCK_IF( !b_locked );

    return i_result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/video_epg.c:                           mtime_t ts)
{
    VLC_UNUSED(subpic); VLC_UNUSED(ts);
    VLC_UNUSED(fmt_src); VLC_UNUSED(has_src_changed);
    VLC_UNUSED(fmt_dst);

    if (!has_dst_changed)
        return VLC_SUCCESS;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/interlacing.c: static bool DeinterlaceIsPresent(vout_thread_t *vout)
{
    char *filter = var_GetNonEmptyString(vout, "video-filter");

    bool is_found = FilterFind(filter, "deinterlace") != NULL;

    free(filter);

    return is_found;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/display.c: struct vlc_gl_t *vout_GetDisplayOpengl(vout_display_t *vd)
{
    struct vlc_gl_t *gl;
    if (vout_display_Control(vd, VOUT_DISPLAY_GET_OPENGL, &gl))
        return NULL;
    return gl;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/display.c:                                 mtime_t hide_timeout)
{
    return DisplayNew(vout, source, state, module, false, NULL,
                      double_click_timeout, hide_timeout, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/display.c: static int SplitterControl(vout_display_t *vd, int query, va_list args)
{
    (void)vd; (void)query; (void)args;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/video_text.c:                            mtime_t ts)
{
    VLC_UNUSED(subpic); VLC_UNUSED(ts);
    VLC_UNUSED(fmt_src); VLC_UNUSED(has_src_changed);
    VLC_UNUSED(fmt_dst);

    if( !has_dst_changed )
        return VLC_SUCCESS;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/video_widgets.c:                            mtime_t ts)
{
    VLC_UNUSED(subpic); VLC_UNUSED(ts);
    VLC_UNUSED(fmt_src); VLC_UNUSED(has_src_changed);
    VLC_UNUSED(fmt_dst);

    if (!has_dst_changed)
        return VLC_SUCCESS;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/window.c: static int vout_window_start(void *func, va_list ap)
{
    int (*activate)(vout_window_t *, const vout_window_cfg_t *) = func;
    vout_window_t *wnd = va_arg(ap, vout_window_t *);
    const vout_window_cfg_t *cfg = va_arg(ap, const vout_window_cfg_t *);

    return activate(wnd, cfg);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t oldval, vlc_value_t newval, void *data)
{
    vout_thread_t *vout = (vout_thread_t *)object;
    VLC_UNUSED(cmd); VLC_UNUSED(oldval); VLC_UNUSED(data); VLC_UNUSED(newval);

    vout_ControlChangeCropBorder(vout,
                                 var_GetInteger(object, "crop-left"),
                                 var_GetInteger(object, "crop-top"),
                                 var_GetInteger(object, "crop-right"),
                                 var_GetInteger(object, "crop-bottom"));
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                          vlc_value_t oldval, vlc_value_t newval, void *data )
{
    vout_thread_t *vout = (vout_thread_t *)object;
    VLC_UNUSED(cmd); VLC_UNUSED(oldval); VLC_UNUSED(data);
    unsigned num, den;

    if (sscanf(newval.psz_string, "%u:%u", &num, &den) == 2 &&
        (num > 0) == (den > 0))
        vout_ControlChangeSampleAspectRatio(vout, num, den);
    else if (*newval.psz_string == '\0')
        vout_ControlChangeSampleAspectRatio(vout, 0, 0);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_thread_t *p_vout = (vout_thread_t *)obj;

    (void) name; (void) prev; (void) data;
    vout_ControlChangeDisplayFilled( p_vout, cur.b_bool );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                           vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_thread_t *p_vout = (vout_thread_t *)obj;

    (void) name; (void) prev; (void) data;
    vout_ControlChangeZoom( p_vout, 1000 * cur.f_float, 1000 );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                          vlc_value_t prev, vlc_value_t cur, void *data )
{
    (void) name; (void) prev; (void) data;
    return var_SetFloat( obj, "scale", cur.f_float );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                           vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_ControlChangeWindowState( (vout_thread_t *)obj,
        cur.b_bool ? VOUT_WINDOW_STATE_ABOVE : VOUT_WINDOW_STATE_NORMAL );
    (void) name; (void) prev; (void) data;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_thread_t *vout = (vout_thread_t *)obj;

    if( cur.b_bool )
    {
        vout_ControlChangeWindowState( vout, VOUT_WINDOW_STATE_BELOW );
        vout_ControlChangeFullscreen( vout, true );
    }
    else
    {
        var_TriggerCallback( obj, "fullscreen" );
        var_TriggerCallback( obj, "video-on-top" );
    }
    (void) name; (void) prev; (void) data;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                        vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    (void)psz_cmd; (void)p_data;

    if( oldval.b_bool != newval.b_bool )
        vout_ControlChangeFullscreen( p_vout, newval.b_bool );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                        vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval);
    VLC_UNUSED(newval); VLC_UNUSED(p_data);

    VoutSaveSnapshot( p_vout );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                                 vlc_value_t oldval, vlc_value_t newval, void *p_data)
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    vout_ControlChangeFilters( p_vout, newval.psz_string );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t oldval, vlc_value_t newval, void *p_data)
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    vout_ControlChangeSubSources( p_vout, newval.psz_string );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t oldval, vlc_value_t newval, void *p_data)
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    vout_ControlChangeSubFilters( p_vout, newval.psz_string );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_intf.c:                               vlc_value_t oldval, vlc_value_t newval, void *p_data)
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    vout_ControlChangeSubMargin( p_vout, newval.i_int );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static spu_scale_t spu_scale_create(int w, int h)
{
    spu_scale_t s = { .w = w, .h = h };
    if (s.w <= 0)
        s.w = SCALE_UNIT;
    if (s.h <= 0)
        s.h = SCALE_UNIT;
    return s;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static spu_scale_t spu_scale_createq(int64_t wn, int64_t wd, int64_t hn, int64_t hd)
{
    return spu_scale_create(wn * SCALE_UNIT / wd,
                            hn * SCALE_UNIT / hd);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int spu_scale_w(int v, const spu_scale_t s)
{
    return v * s.w / SCALE_UNIT;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int spu_scale_h(int v, const spu_scale_t s)
{
    return v * s.h / SCALE_UNIT;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int spu_invscale_w(int v, const spu_scale_t s)
{
    return v * SCALE_UNIT / s.w;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int spu_invscale_h(int v, const spu_scale_t s)
{
    return v * SCALE_UNIT / s.h;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static spu_area_t spu_area_create(int x, int y, int w, int h, spu_scale_t s)
{
    spu_area_t a = { .x = x, .y = y, .width = w, .height = h, .scale = s };
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static spu_area_t spu_area_scaled(spu_area_t a)
{
    if (a.scale.w == SCALE_UNIT && a.scale.h == SCALE_UNIT)
        return a;

    a.x      = spu_scale_w(a.x,      a.scale);
    a.y      = spu_scale_h(a.y,      a.scale);
    a.width  = spu_scale_w(a.width,  a.scale);
    a.height = spu_scale_h(a.height, a.scale);

    a.scale = spu_scale_unit();
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static spu_area_t spu_area_unscaled(spu_area_t a, spu_scale_t s)
{
    if (a.scale.w == s.w && a.scale.h == s.h)
        return a;

    a = spu_area_scaled(a);

    a.x      = spu_invscale_w(a.x,      s);
    a.y      = spu_invscale_h(a.y,      s);
    a.width  = spu_invscale_w(a.width,  s);
    a.height = spu_invscale_h(a.height, s);

    a.scale = s;
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static bool spu_area_overlap(spu_area_t a, spu_area_t b)
{
    const int dx = 0;
    const int dy = 0;

    a = spu_area_scaled(a);
    b = spu_area_scaled(b);

    return __MAX(a.x - dx, b.x) < __MIN(a.x + a.width  + dx, b.x + b.width ) &&
           __MAX(a.y - dy, b.y) < __MIN(a.y + a.height + dy, b.y + b.height);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int IntegerCmp(int64_t i0, int64_t i1)
{
    return i0 < i1 ? -1 : i0 > i1 ? 1 : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c:                         vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(oldval); VLC_UNUSED(newval); VLC_UNUSED(var);

    UpdateSPU((spu_t *)data, object);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c:                               const char *psz_log, input_resource_t *p_resource )
{
    return Create( p_parent, p_item, psz_log, false, p_resource );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c:                                       input_item_t *p_item, const char *psz_log )
{
    input_thread_t *p_input = input_Create( p_parent, p_item, psz_log, NULL );

    if( input_Start( p_input ) )
    {
        vlc_object_release( p_input );
        return NULL;
    }
    return p_input;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c: int input_Read( vlc_object_t *p_parent, input_item_t *p_item )
{
    input_thread_t *p_input = Create( p_parent, p_item, NULL, false, NULL );
    if( !p_input )
        return VLC_EGENERIC;

    if( !Init( p_input ) )
    {
        MainLoop( p_input, false );
        End( p_input );
    }

    vlc_object_release( p_input );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c: int input_Preparse( vlc_object_t *p_parent, input_item_t *p_item )
{
    input_thread_t *p_input;

    /* Allocate descriptor */
    p_input = Create( p_parent, p_item, NULL, true, NULL );
    if( !p_input )
        return VLC_EGENERIC;

    if( !Init( p_input ) )
        End( p_input );

    vlc_object_release( p_input );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c: static input_source_t *InputSourceNew( input_thread_t *p_input )
{
    VLC_UNUSED(p_input);

    return calloc( 1,  sizeof( input_source_t ) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c:                          (i_flags & SUB_CANFAIL) ) )
    {
        free( sub );
        return;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/input.c:     else
    {
        psz_file = str_format( input, psz_path );
        path_sanitize( psz_file );
        return psz_file;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/event.c: void input_SendEventProgramScrambled( input_thread_t *p_input, int i_group, bool b_scrambled )
{
    if( var_GetInteger( p_input, "program" ) != i_group )
        return;

    var_SetBool( p_input, "program-scrambled", b_scrambled );
    Trigger( p_input, INPUT_EVENT_PROGRAM );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/event.c: static const char *GetEsVarName( int i_cat )
{
    switch( i_cat )
    {
    case VIDEO_ES:
        return "video-es";
    case AUDIO_ES:
        return "audio-es";
    default:
        assert( i_cat == SPU_ES );
        return "spu-es";
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/item.c:                              const char *psz_format, ... )
{
    va_list args;

    va_start( args, psz_format );
    const int i_ret = InputItemVaAddInfo( p_i, psz_cat, psz_name, psz_format, args );
    va_end( args );

    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/item.c:                                  mtime_t i_duration )
{
    return input_item_NewWithType( psz_uri, psz_name,
                                  i_options, ppsz_options, i_option_flags,
                                  i_duration, ITEM_TYPE_UNKNOWN );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/item.c: input_item_node_t *input_item_node_AppendItem( input_item_node_t *p_node, input_item_t *p_item )
{
    input_item_node_t *p_new_child = input_item_node_Create( p_item );
    if( !p_new_child ) return NULL;
    input_item_node_AppendNode( p_node, p_new_child );
    return p_new_child;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/resource.c: vout_thread_t *input_resource_HoldVout( input_resource_t *p_resource )
{
    return HoldVout( p_resource );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlm.c: static int vlm_ControlMediaInstanceStop( vlm_t *p_vlm, int64_t id, const char *psz_id )
{
    vlm_media_sys_t *p_media = vlm_ControlMediaGetById( p_vlm, id );
    vlm_media_instance_sys_t *p_instance;

    if( !p_media )
        return VLC_EGENERIC;

    p_instance = vlm_ControlMediaInstanceGetByName( p_media, psz_id );
    if( !p_instance )
        return VLC_EGENERIC;

    vlm_MediaInstanceDelete( p_vlm, id, p_instance, p_media );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlm.c: int vlm_ControlInternal( vlm_t *p_vlm, int i_query, ... )
{
    va_list args;
    int     i_result;

    va_start( args, i_query );
    i_result = vlm_vaControlInternal( p_vlm, i_query, args );
    va_end( args );

    return i_result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/demux.h: static inline int demux_Control( demux_t *p_demux, int i_query, ... )
{
    va_list args;
    int     i_result;

    va_start( args, i_query );
    i_result = demux_vaControl( p_demux, i_query, args );
    va_end( args );
    return i_result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/decoder.c:                                 input_resource_t *p_resource )
{
    return decoder_New( p_parent, NULL, fmt, NULL, p_resource, NULL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline mtime_t es_out_GetWakeup( es_out_t *p_out )
{
    mtime_t i_wu;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_WAKE_UP, &i_wu );

    assert( !i_ret );
    return i_wu;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline bool es_out_GetBuffering( es_out_t *p_out )
{
    bool b;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_BUFFERING, &b );

    assert( !i_ret );
    return b;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline bool es_out_GetEmpty( es_out_t *p_out )
{
    bool b;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_EMPTY, &b );

    assert( !i_ret );
    return b;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_SetRecordState( es_out_t *p_out, bool b_record )
{
    return es_out_Control( p_out, ES_OUT_SET_RECORD_STATE, b_record );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_SetPauseState( es_out_t *p_out, bool b_source_paused, bool b_paused, mtime_t i_date )
{
    return es_out_Control( p_out, ES_OUT_SET_PAUSE_STATE, b_source_paused, b_paused, i_date );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_SetRate( es_out_t *p_out, int i_source_rate, int i_rate )
{
    return es_out_Control( p_out, ES_OUT_SET_RATE, i_source_rate, i_rate );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_SetTime( es_out_t *p_out, mtime_t i_date )
{
    return es_out_Control( p_out, ES_OUT_SET_TIME, i_date );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_SetFrameNext( es_out_t *p_out )
{
    return es_out_Control( p_out, ES_OUT_SET_FRAME_NEXT );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h:                                        vlc_object_t **pp_decoder, vout_thread_t **pp_vout, audio_output_t **pp_aout )
{
    return es_out_Control( p_out, ES_OUT_GET_ES_OBJECTS_BY_ID, i_id, pp_decoder, pp_vout, pp_aout );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/es_out.h: static inline int es_out_GetGroupForced( es_out_t *p_out )
{
    int i_group;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_GROUP_FORCED, &i_group );
    assert( !i_ret );
    return i_group;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                           void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    if( newval.i_int == PLAYING_S || newval.i_int == PAUSE_S )
    {
        input_ControlPush( p_input, INPUT_CONTROL_SET_STATE, &newval );
        return VLC_SUCCESS;
    }

    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                          vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(oldval); VLC_UNUSED(p_data); VLC_UNUSED(psz_cmd);

    newval.i_int = INPUT_RATE_DEFAULT / newval.f_float;
    input_ControlPush( p_input, INPUT_CONTROL_SET_RATE, &newval );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                             void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    input_ControlPush( p_input, INPUT_CONTROL_SET_PROGRAM, &newval );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                                void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    vlc_value_t     val;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval);

    /* Issue a title change */
    val.i_int = (intptr_t)p_data;
    input_ControlPush( p_input, INPUT_CONTROL_SET_TITLE, &val );

    var_Change( p_input, "title", VLC_VAR_SETVALUE, &val, NULL );

    /* And a chapter change */
    input_ControlPush( p_input, INPUT_CONTROL_SET_SEEKPOINT, &newval );

    var_Change( p_input, "chapter", VLC_VAR_SETVALUE, &newval, NULL );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                              vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    if( !strcmp( psz_cmd, "audio-delay" ) )
    {
        input_ControlPush( p_input, INPUT_CONTROL_SET_AUDIO_DELAY, &newval );
    }
    else if( !strcmp( psz_cmd, "spu-delay" ) )
    {
        input_ControlPush( p_input, INPUT_CONTROL_SET_SPU_DELAY, &newval );
    }
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                              void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    input_ControlPush( p_input, INPUT_CONTROL_SET_BOOKMARK, &newval );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                            void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);

    input_ControlPush( p_input, INPUT_CONTROL_SET_RECORD_STATE, &newval );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/var.c:                               void *p_data )
{
    input_thread_t *p_input = (input_thread_t*)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval); VLC_UNUSED(p_data);
    VLC_UNUSED(newval);

    input_ControlPush( p_input, INPUT_CONTROL_SET_FRAME_NEXT, NULL );

    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlmshell.c: static int ExecuteSyntaxError( const char *psz_cmd, vlm_message_t **pp_status )
{
    *pp_status = vlm_MessageNew( psz_cmd, "Wrong command syntax" );
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlmshell.c: static bool ExecuteIsMedia( vlm_t *p_vlm, const char *psz_name )
{
    int64_t id;

    if( !psz_name || vlm_ControlInternal( p_vlm, VLM_GET_MEDIA_ID, psz_name, &id ) )
        return false;
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlmshell.c: static bool ExecuteIsSchedule( vlm_t *p_vlm, const char *psz_name )
{
    if( !psz_name || !vlm_ScheduleSearch( p_vlm, psz_name ) )
        return false;
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/vlmshell.c: static int ExecuteExport( vlm_t *p_vlm, vlm_message_t **pp_status )
{
    char *psz_export = Save( p_vlm );

    *pp_status = vlm_MessageNew( "export", "%s", psz_export );
    free( psz_export );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/clock.c: static inline clock_point_t clock_point_Create( mtime_t i_stream, mtime_t i_system )
{
    clock_point_t p = { .i_stream = i_stream, .i_system = i_system };
    return p;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/control.c: int input_Control( input_thread_t *p_input, int i_query, ...  )
{
    va_list args;
    int     i_result;

    va_start( args, i_query );
    i_result = input_vaControl( p_input, i_query, args );
    va_end( args );

    return i_result;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/subtitles.c: static void strcpy_strip_ext( char *d, const char *s )
{
    unsigned char c;

    const char *tmp = strrchr(s, '.');
    if( !tmp )
    {
        strcpy(d, s);
        return;
    }
    else
        strlcpy(d, s, tmp - s + 1 );
    while( (c = *d) != '\0' )
    {
        *d = tolower(c);
        d++;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/subtitles.c: static int whiteonly( const char *s )
{
    unsigned char c;

    while( (c = *s) != '\0' )
    {
        if( isalnum( c ) )
            return 0;
        s++;
    }
    return 1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/info.h:                                             const char *format, ...)
{
    va_list args;

    va_start(args, format);
    info_t *info = info_category_VaAddInfo(cat, name, format, args);
    va_end(args);

    return info;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/error.c: const char *vlc_strerror(int errnum)
{
    /* We cannot simply use strerror() here, since it is not thread-safe. */
    return vlc_strerror_l(errnum, "");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/error.c: const char *vlc_strerror_c(int errnum)
{
    return vlc_strerror_l(errnum, "C");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_open (const char *filename, int flags, ...)
{
    unsigned int mode = 0;
    va_list ap;

    va_start (ap, flags);
    if (flags & O_CREAT)
        mode = va_arg (ap, unsigned int);
    va_end (ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif

    int fd = open (filename, flags, mode);
    if (fd != -1)
        fcntl (fd, F_SETFD, FD_CLOEXEC);
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_mkdir (const char *dirname, mode_t mode)
{
    return mkdir (dirname, mode);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: DIR *vlc_opendir (const char *dirname)
{
    return opendir (dirname);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_stat (const char *filename, struct stat *buf)
{
    return stat (filename, buf);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_lstat (const char *filename, struct stat *buf)
{
    return lstat (filename, buf);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_unlink (const char *filename)
{
    return unlink (filename);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_rename (const char *oldpath, const char *newpath)
{
    return rename (oldpath, newpath);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/filesystem.c: int vlc_dup (int oldfd)
{
    int newfd;

#ifdef F_DUPFD_CLOEXEC
    newfd = fcntl (oldfd, F_DUPFD_CLOEXEC, 0);
    if (unlikely(newfd == -1 && errno == EINVAL))
#endif
    {
        newfd = dup (oldfd);
        if (likely(newfd != -1))
            fcntl (newfd, F_SETFD, FD_CLOEXEC);
    }
    return newfd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/plugin.c:                  module_handle_t *p_handle, bool lazy)
{
#if defined (RTLD_NOW)
    const int flags = lazy ? RTLD_LAZY : RTLD_NOW;
#elif defined (DL_LAZY)
    const int flags = DL_LAZY;
#else
    const int flags = 0;
#endif

    module_handle_t handle = dlopen (path, flags);
    if( handle == NULL )
    {
        msg_Warn( p_this, "cannot load module `%s' (%s)", path, dlerror() );
        return -1;
    }
    *p_handle = handle;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/plugin.c: void module_Unload( module_handle_t handle )
{
#ifdef HAVE_VALGRIND_VALGRIND_H
    if( RUNNING_ON_VALGRIND > 0 )
        return; /* do not dlclose() so that we get proper stack traces */
#endif
    dlclose( handle );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/plugin.c: void *module_Lookup( module_handle_t handle, const char *psz_function )
{
    return dlsym( handle, psz_function );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: static struct timespec mtime_to_ts (mtime_t date)
{
    lldiv_t d = lldiv (date, CLOCK_FREQ);
    struct timespec ts = { d.quot, d.rem * (1000000000 / CLOCK_FREQ) };

    return ts;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: void vlc_assert_locked (vlc_mutex_t *p_mutex)
{
    if (RUNNING_ON_VALGRIND > 0)
        return;
    assert (pthread_mutex_lock (p_mutex) == EDEADLK);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: int vlc_mutex_trylock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_trylock( p_mutex );

    if (val != EBUSY)
        VLC_THREAD_ASSERT ("locking mutex");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c:                         mtime_t deadline)
{
    struct timespec ts = mtime_to_ts (deadline);
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: void vlc_sem_destroy (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_destroy (sem) == 0))
        return;

    val = errno;

    VLC_THREAD_ASSERT ("destroying semaphore");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: int vlc_sem_post (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_post (sem) == 0))
        return 0;

    val = errno;

    if (unlikely(val != EOVERFLOW))
        VLC_THREAD_ASSERT ("unlocking semaphore");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: void vlc_sem_wait (vlc_sem_t *sem)
{
    int val;

    do
        if (likely(sem_wait (sem) == 0))
            return;
    while ((val = errno) == EINTR);

    VLC_THREAD_ASSERT ("locking semaphore");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: int vlc_threadvar_create (vlc_threadvar_t *key, void (*destr) (void *))
{
    return pthread_key_create (key, destr);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: int vlc_threadvar_set (vlc_threadvar_t key, void *value)
{
    return pthread_setspecific (key, value);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c: void *vlc_threadvar_get (vlc_threadvar_t key)
{
    return pthread_getspecific (key);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c:                int priority)
{
    pthread_attr_t attr;

    pthread_attr_init (&attr);
    return vlc_clone_attr (th, &attr, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c:                       int priority)
{
    vlc_thread_t dummy;
    pthread_attr_t attr;

    if (th == NULL)
        th = &dummy;

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    return vlc_clone_attr (th, &attr, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/version.c: const char * VLC_##func ( void )                                            \
{                                                                           \
    return VLC_##var ;                                                      \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/test/md5.c: int main( void )
{
    test_config_StringEscape();

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/test/url.c: static char *make_URI_def (const char *in)
{
    return vlc_path2uri (in, NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/netconf.c: char *vlc_getProxyUrl(const char *url)
{
    VLC_UNUSED(url);

    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_openat (int dir, const char *filename, int flags, ...)
{
    errno = ENOSYS;

    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_mkdir (const char *dirname, mode_t mode)
{
    char *locname = ToLocale (dirname);
    if (unlikely(locname == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int res = mkdir (locname, mode);
    LocaleFree (locname);
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: DIR *vlc_opendir (const char *dirname)
{
    const char *locname = ToLocale (dirname);
    if (unlikely(locname == NULL))
    {
        errno = ENOENT;
        return NULL;
    }

    DIR *dir = opendir (locname);

    LocaleFree (locname);

    return dir;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: static int vlc_statEx (const char *filename, struct stat *buf, bool deref)
{
    const char *local_name = ToLocale (filename);
    if (unlikely(local_name == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int res = deref ? stat (local_name, buf)
                    : lstat (local_name, buf);
    LocaleFree (local_name);
    return res;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_stat (const char *filename, struct stat *buf)
{
    return vlc_statEx (filename, buf, true);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_lstat (const char *filename, struct stat *buf)
{
    return vlc_statEx (filename, buf, false);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_unlink (const char *filename)
{
    const char *local_name = ToLocale (filename);
    if (unlikely(local_name == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int ret = unlink (local_name);
    LocaleFree (local_name);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_rename (const char *oldpath, const char *newpath)
{
    const char *lo = ToLocale (oldpath);
    if (lo == NULL)
        goto error;

    const char *ln = ToLocale (newpath);
    if (ln == NULL)
    {
        LocaleFree (lo);
error:
        errno = ENOENT;
        return -1;
    }

    int ret = rename (lo, ln);
    LocaleFree (lo);
    LocaleFree (ln);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_dup (int oldfd)
{
    int newfd;

    newfd = dup (oldfd);
    if (likely(newfd != -1))
        fcntl (newfd, F_SETFD, FD_CLOEXEC);

    return newfd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_socket (int pf, int type, int proto, bool nonblock)
{
    int fd;

    fd = socket (pf, type, proto);
    if (fd == -1)
        return -1;

    fcntl (fd, F_SETFD, FD_CLOEXEC);
    if (nonblock)
        fcntl (fd, F_SETFL, fcntl (fd, F_GETFL, 0) | O_NONBLOCK);
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/filesystem.c: int vlc_accept (int lfd, struct sockaddr *addr, socklen_t *alen, bool nonblock)
{
    do
    {
        int fd = accept (lfd, addr, alen);
        if (fd != -1)
        {
            fcntl (fd, F_SETFD, FD_CLOEXEC);
            if (nonblock)
                fcntl (fd, F_SETFL, fcntl (fd, F_GETFL, 0) | O_NONBLOCK);
            return fd;
        }
    }
    while (errno == EINTR);

    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/plugin.c:                  module_handle_t *p_handle, bool lazy )
{
    const int flags = lazy ? RTLD_LAZY : RTLD_NOW;
    char *path = ToLocale( psz_file );

    module_handle_t handle = dlopen( path, flags );
    if( handle == NULL )
    {
        msg_Warn( p_this, "cannot load module `%s' (%s)", path, dlerror() );
        LocaleFree( path );
        return -1;
    }
    LocaleFree( path );
    *p_handle = handle;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/plugin.c: void *module_Lookup( module_handle_t handle, const char *psz_function )
{
    return dlsym( handle, psz_function );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: static ULONG vlc_WaitForSingleObject (HEV hev, ULONG ulTimeout)
{
    return vlc_DosWaitEventSemEx( hev, ulTimeout );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: static ULONG vlc_Sleep (ULONG ulTimeout)
{
    ULONG rc = vlc_DosWaitEventSemEx( NULLHANDLE, ulTimeout );

    return ( rc != ERROR_TIMEOUT ) ? rc : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c:                 void *data, int priority)
{
    return vlc_clone_attr (p_handle, false, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c:                       void *data, int priority)
{
    vlc_thread_t th;
    if (p_handle == NULL)
        p_handle = &th;

    return vlc_clone_attr (p_handle, true, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: unsigned vlc_timer_getoverrun (vlc_timer_t timer)
{
    (void)timer;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/getaddrinfo.c: makeipv4info (int type, int proto, u_long ip, u_short port, const char *name)
{
    struct sockaddr_in addr;

    memset (&addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
# ifdef HAVE_SA_LEN
    addr.sin_len = sizeof (addr);
# endif
    addr.sin_port = port;
    addr.sin_addr.s_addr = ip;

    return makeaddrinfo (AF_INET, type, proto,
                         (struct sockaddr*)&addr, sizeof (addr), name);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/dirs.c: char *config_GetUserDir (vlc_userdir_t type)
{
    switch (type)
    {
        case VLC_HOME_DIR:
        case VLC_CONFIG_DIR:
        case VLC_DATA_DIR:
        case VLC_CACHE_DIR:
        case VLC_DESKTOP_DIR:
        case VLC_DOWNLOAD_DIR:
        case VLC_TEMPLATES_DIR:
        case VLC_PUBLICSHARE_DIR:
        case VLC_DOCUMENTS_DIR:
        case VLC_MUSIC_DIR:
        case VLC_PICTURES_DIR:
        case VLC_VIDEOS_DIR:
            break;
    }
    return config_GetHomeDir ();
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/core.c: static inline char *strdupnull (const char *src)
{
    return src ? strdup (src) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/keys.c: static int keystrcmp (const void *key, const void *elem)
{
    const char *sa = key, *sb = elem;
    return strcmp (sa, sb);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/keys.c: static char *nooptext (const char *txt)
{
    return (char *)txt;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/chain.c: static bool IsEscapeNeeded( char c )
{
    return c == '\'' || c == '"' || c == '\\';
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/chain.c: static bool IsSpace( char c  )
{
    return c == ' ' || c == '\t';
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/file.c: static inline char *strdupnull (const char *src)
{
    return src ? strdup (src) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/file.c: static int64_t strtoi (const char *str)
{
    char *end;
    long long l;

    errno = 0;
    l = strtoll (str, &end, 0);

    if (!errno)
    {
#if (LLONG_MAX > 0x7fffffffffffffffLL)
        if (l > 0x7fffffffffffffffLL
         || l < -0x8000000000000000LL)
            errno = ERANGE;
#endif
        if (*end)
            errno = EINVAL;
    }
    return l;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/file.c: static int config_PrepareDir (vlc_object_t *obj)
{
    char *psz_configdir = config_GetUserDir (VLC_CONFIG_DIR);
    if (psz_configdir == NULL)
        return -1;

    int ret = config_CreateDir (obj, psz_configdir);
    free (psz_configdir);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/file.c: int config_AutoSaveConfigFile( vlc_object_t *p_this )
{
    int ret = 0;

    assert( p_this );

    vlc_rwlock_rdlock (&config_lock);
    if (config_dirty)
    {
        /* Note: this will get the read lock recursively. Ok. */
        ret = config_SaveConfigFile (p_this);
        config_dirty = (ret != 0);
    }
    vlc_rwlock_unlock (&config_lock);

    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/help.c: static int vlc_swidth(const char *str)
{
    for (int total = 0;;)
    {
        uint32_t cp;
        size_t charlen = vlc_towc(str, &cp);

        if (charlen == 0)
            return total;
        if (charlen == (size_t)-1)
            return -1;
        str += charlen;

        int w = wcwidth(cp);
        if (w == -1)
            return -1;
        total += w;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/error.c: const char* vlc_strerror(int errnum)
{
    return vlc_strerror_c(errnum);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/netconf.c: char *vlc_getProxyUrl(const char *url)
{
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: static struct timespec mtime_to_ts (mtime_t date)
{
    lldiv_t d = lldiv (date, CLOCK_FREQ);
    struct timespec ts = { d.quot, d.rem * (1000000000 / CLOCK_FREQ) };

    return ts;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: int vlc_mutex_trylock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_trylock( p_mutex );

    if (val != EBUSY)
        VLC_THREAD_ASSERT ("locking mutex");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c:                int priority)
{
    (void) priority;
    return vlc_clone_attr (th, entry, data, false);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c:                       int priority)
{
    vlc_thread_t dummy;
    if (th == NULL)
        th = &dummy;

    (void) priority;
    return vlc_clone_attr (th, entry, data, true);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: int vlc_set_priority (vlc_thread_t th, int priority)
{
    (void) th; (void) priority;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: int vlc_threadvar_create (vlc_threadvar_t *key, void (*destr) (void *))
{
    return pthread_key_create (key, destr);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: int vlc_threadvar_set (vlc_threadvar_t key, void *value)
{
    return pthread_setspecific (key, value);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/android/thread.c: void *vlc_threadvar_get (vlc_threadvar_t key)
{
    return pthread_getspecific (key);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: httpd_host_t *vlc_http_HostNew (vlc_object_t *obj)
{
    msg_Err (obj, "HTTP server not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: httpd_host_t *vlc_https_HostNew (vlc_object_t *obj)
{
    msg_Err (obj, "HTTPS server not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: httpd_host_t *vlc_rtsp_HostNew (vlc_object_t *obj)
{
    msg_Err (obj, "RTSP server not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c:                                       const char *access, const char *name)
{
    VLC_UNUSED (access); VLC_UNUSED (name);
    msg_Err (obj, "Output support not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c:                                                 const char *dst)
{
    VLC_UNUSED (sdp); VLC_UNUSED (dst);
    msg_Err (obj, "SDP export not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: encoder_t *sout_EncoderCreate( vlc_object_t *p_this )
{
    msg_Err (p_this, "Encoding support not compiled-in!");
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c:                      const struct sockaddr *addr, size_t addrlen)
{
    VLC_UNUSED (obj); VLC_UNUSED (cfg); VLC_UNUSED (src); VLC_UNUSED (srclen);
    VLC_UNUSED (addr); VLC_UNUSED (addrlen);
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: vlm_message_t *vlm_MessageSimpleNew (const char *a)
{
    VLC_UNUSED (a);
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: vlm_message_t *vlm_MessageNew (const char *a, const char *fmt, ...)
{
    VLC_UNUSED (a);
    VLC_UNUSED (fmt);
    return vlm_MessageSimpleNew (a);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/missing.c: vlm_t *vlm_New (vlc_object_t *obj)
{
     msg_Err (obj, "VLM not compiled-in!");
     return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/error.c: const char *vlc_strerror(int errnum)
{
    return vlc_strerror_c(errnum);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: static struct timespec mtime_to_ts (mtime_t date)
{
    lldiv_t d = lldiv (date, CLOCK_FREQ);
    struct timespec ts = { d.quot, d.rem * (1000000000 / CLOCK_FREQ) };

    return ts;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: void vlc_assert_locked (vlc_mutex_t *p_mutex)
{
    if (RUNNING_ON_VALGRIND > 0)
        return;
    assert (pthread_mutex_lock (p_mutex) == EDEADLK);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: int vlc_mutex_trylock (vlc_mutex_t *p_mutex)
{
    int val = pthread_mutex_trylock( p_mutex );

    if (val != EBUSY)
        VLC_THREAD_ASSERT ("locking mutex");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: void vlc_sem_destroy (vlc_sem_t *sem)
{
    int val;

    if (likely(semaphore_destroy(mach_task_self(), *sem) == KERN_SUCCESS))
        return;

    val = EINVAL;

    VLC_THREAD_ASSERT ("destroying semaphore");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: int vlc_sem_post (vlc_sem_t *sem)
{
    int val;

    if (likely(semaphore_signal(*sem) == KERN_SUCCESS))
        return 0;

    val = EINVAL;

    if (unlikely(val != EOVERFLOW))
        VLC_THREAD_ASSERT ("unlocking semaphore");
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: void vlc_sem_wait (vlc_sem_t *sem)
{
    int val;

    if (likely(semaphore_wait(*sem) == KERN_SUCCESS))
        return;

    val = EINVAL;

    VLC_THREAD_ASSERT ("locking semaphore");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: int vlc_threadvar_create (vlc_threadvar_t *key, void (*destr) (void *))
{
    return pthread_key_create (key, destr);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: int vlc_threadvar_set (vlc_threadvar_t key, void *value)
{
    return pthread_setspecific (key, value);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: void *vlc_threadvar_get (vlc_threadvar_t key)
{
    return pthread_getspecific (key);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c:                int priority)
{
    pthread_attr_t attr;

    pthread_attr_init (&attr);
    return vlc_clone_attr (th, &attr, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c:                       int priority)
{
    vlc_thread_t dummy;
    pthread_attr_t attr;

    if (th == NULL)
        th = &dummy;

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    return vlc_clone_attr (th, &attr, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/darwin/thread.c: int vlc_set_priority (vlc_thread_t th, int priority)
{
    (void) th; (void) priority;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/textdomain.c: char *vlc_gettext (const char *msgid)
{
#ifdef ENABLE_NLS
    if (likely(*msgid))
        return dgettext (PACKAGE_NAME, msgid);
#endif
    return (char *)msgid;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/textdomain.c: char *vlc_ngettext (const char *msgid, const char *plural, unsigned long n)
{
#ifdef ENABLE_NLS
    if (likely(*msgid))
        return dngettext (PACKAGE_NAME, msgid, plural, n);
#endif
    return (char *)((n == 1) ? msgid : plural);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/entry.c: static char *strdup_null (const char *str)
{
    return (str != NULL) ? strdup (str) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/entry.c: module_t *vlc_plugin_describe (vlc_plugin_cb entry)
{
    module_t *module = NULL;

    if (entry (vlc_plugin_setter, &module) != 0)
    {
        if (module != NULL) /* partially initialized plug-in... */
            vlc_module_destroy (module);
        module = NULL;
    }
    return module;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/modules.c: bool module_provides (const module_t *m, const char *cap)
{
    return !strcmp (module_get_capability (m), cap);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/modules.c: static int generic_start(void *func, va_list ap)
{
    vlc_object_t *obj = va_arg(ap, vlc_object_t *);
    int (*activate)(vlc_object_t *) = func;

    return activate(obj);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/modules.c:                       bool strict)
{
    return vlc_module_load(obj, cap, name, strict, generic_start, obj);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/modules.c: bool module_exists (const char * psz_name)
{
    return module_find (psz_name) != NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/cache.c: static int CacheSaveString (FILE *file, const char *str)
{
    uint16_t size = (str != NULL) ? strlen (str) : 0;

    SAVE_IMMEDIATE (size);
    if (size != 0 && fwrite (str, 1, size, file) != size)
    {
error:
        return -1;
    }
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/block.c: block_t *block_mmap_Alloc (void *addr, size_t length)
{
    (void)addr; (void)length; return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/block.c: ssize_t pread (int fd, void *buf, size_t count, off_t offset)
{
    HANDLE handle = (HANDLE)(intptr_t)_get_osfhandle (fd);
    if (handle == INVALID_HANDLE_VALUE)
        return -1;

    OVERLAPPED olap; olap.Offset = offset; olap.OffsetHigh = (offset >> 32);
    DWORD written;
    /* This braindead API will override the file pointer even if we specify
     * an explicit read offset... So do not expect this to mix well with
     * regular read() calls. */
    if (ReadFile (handle, buf, count, &written, &olap))
        return written;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/block.c: block_t *block_FilePath (const char *path)
{
    int fd = vlc_open (path, O_RDONLY);
    if (fd == -1)
        return NULL;

    block_t *block = block_File (fd);
    close (fd);
    return block;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/filter_chain.c: static inline chained_filter_t *chained (filter_t *filter)
{
    return (chained_filter_t *)filter;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/filter_chain.c:                                      const es_format_t *p_fmt_out )
{
    filter_t *p_filter = filter_chain_AppendFilterInternal( p_chain, psz_name,
                                                            p_cfg, p_fmt_in,
                                                            p_fmt_out );
    if( UpdateBufferFunctions( p_chain ) < 0 )
        msg_Err( p_filter, "Woah! This doesn't look good." );
    return p_filter;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/filter_chain.c:                                    const char *psz_string )
{
    const int i_ret = filter_chain_AppendFromStringInternal( p_chain, psz_string );
    if( i_ret < 0 )
        return i_ret;

    /* FIXME That one seems bad if a error is returned */
    return UpdateBufferFunctions( p_chain );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/filter_chain.c: int filter_chain_DeleteFilter( filter_chain_t *p_chain, filter_t *p_filter )
{
    const int i_ret = filter_chain_DeleteFilterInternal( p_chain, p_filter );
    if( i_ret < 0 )
        return i_ret;

    /* FIXME That one seems bad if a error is returned */
    return UpdateBufferFunctions( p_chain );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/picture.c: static int LCM( int a, int b )
{
    return a * b / GCD( a, b );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/picture.c: picture_t *picture_NewFromFormat( const video_format_t *p_fmt )
{
    return picture_NewFromResource( p_fmt, NULL );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/picture.c: picture_t *picture_New( vlc_fourcc_t i_chroma, int i_width, int i_height, int i_sar_num, int i_sar_den )
{
    video_format_t fmt;

    memset( &fmt, 0, sizeof(fmt) );
    video_format_Setup( &fmt, i_chroma, i_width, i_height,
                        i_width, i_height, i_sar_num, i_sar_den );

    return picture_NewFromFormat( &fmt );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update_crypto.c: static int mpi_len(const uint8_t *mpi)
{
    return (scalar_number(mpi, 2) + 7) / 8;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update_crypto.c: static size_t read_mpi(uint8_t *dst, const uint8_t *buf, size_t buflen, size_t bits)
{
    if (buflen < 2)
        return 0;

    size_t n = mpi_len(buf);

    if (n * 8 > bits)
        return 0;

    n += 2;

    if (buflen < n)
        return 0;

    memcpy(dst, buf, n);
    return n;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update_crypto.c: static long crc_octets( uint8_t *octets, size_t len )
{
    long crc = CRC24_INIT;
    int i;
    while (len--)
    {
        crc ^= (*octets++) << 16;
        for (i = 0; i < 8; i++)
        {
            crc <<= 1;
            if (crc & 0x1000000)
                crc ^= CRC24_POLY;
        }
    }
    return crc & 0xFFFFFFL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/image.c: vlc_fourcc_t image_Ext2Fourcc( const char *psz_name )
{
    psz_name = strrchr( psz_name, '.' );
    if( !psz_name ) return 0;
    psz_name++;

    return image_Type2Fourcc( psz_name );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/text_style.c: text_style_t *text_style_Duplicate( const text_style_t *p_src )
{
    if( !p_src )
        return NULL;

    text_style_t *p_dst = calloc( 1, sizeof(*p_dst) );
    if( p_dst )
        text_style_Copy( p_dst, p_src );
    return p_dst;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update.c: update_t *update_New( vlc_object_t *p_this )
{
    (void)p_this;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update.c: bool update_NeedUpgrade( update_t *p_update )
{
    (void)p_update;
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/update.c: update_release_t *update_GetRelease( update_t *p_update )
{
    (void)p_update;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/es_format.c: static int BinaryLog( uint32_t i )
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/es_format.c: static video_transform_t transform_FromBasicOps( unsigned angle, bool hflip )
{
    switch ( angle )
    {
        case 90:
            return hflip ? TRANSFORM_TRANSPOSE : TRANSFORM_R90;
        case 180:
            return hflip ? TRANSFORM_VFLIP : TRANSFORM_R180;
        case 270:
            return hflip ? TRANSFORM_ANTI_TRANSPOSE : TRANSFORM_R270;
        default:
            return hflip ? TRANSFORM_HFLIP : TRANSFORM_IDENTITY;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/es_format.c:                                              video_orientation_t dst )
{
    unsigned angle1, angle2;
    bool hflip1, hflip2;

    transform_GetBasicOps(  (video_transform_t)src, &angle1, &hflip1 );
    transform_GetBasicOps( transform_Inverse( (video_transform_t)dst ),
                           &angle2, &hflip2 );

    int angle = (angle1 + angle2) % 360;
    bool hflip = hflip1 ^ hflip2;

    return transform_FromBasicOps(angle, hflip);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/objects.c: void *vlc_object_create( vlc_object_t *p_this, size_t i_size )
{
    return vlc_custom_create( p_this, i_size, "generic" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/epg.c: vlc_epg_t *vlc_epg_New( const char *psz_name )
{
    vlc_epg_t *p_epg = malloc( sizeof(*p_epg) );
    if( p_epg )
        vlc_epg_Init( p_epg, psz_name );
    return p_epg;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/addons.c: int addons_manager_LoadCatalog( addons_manager_t *p_manager )
{
    LoadLocalStorage( p_manager );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/addons.c: int addons_manager_Install( addons_manager_t *p_manager, const addon_uuid_t uuid )
{
    addon_entry_t *p_install_entry = getHeldEntryByUUID( p_manager, uuid );
    if ( ! p_install_entry ) return VLC_EGENERIC;
    int i_ret = InstallEntry( p_manager, p_install_entry );
    addon_entry_Release( p_install_entry );
    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/addons.c: int addons_manager_Remove( addons_manager_t *p_manager, const addon_uuid_t uuid )
{
    return addons_manager_Install( p_manager, uuid );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/fourcc.c: vlc_fourcc_t vlc_fourcc_GetCodec( int i_cat, vlc_fourcc_t i_fourcc )
{
    entry_t e = Find( i_cat, i_fourcc );

    if( CreateFourcc( e.p_class ) == 0 )
        return i_fourcc;
    return CreateFourcc( e.p_class );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/fourcc.c: const char *vlc_fourcc_GetDescription( int i_cat, vlc_fourcc_t i_fourcc )
{
    entry_t e = Find( i_cat, i_fourcc );

    return e.psz_description;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/fourcc.c: const vlc_fourcc_t *vlc_fourcc_GetYUVFallback( vlc_fourcc_t i_fourcc )
{
    return GetFallback( i_fourcc, pp_YUV_fallback, p_list_YUV );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/fourcc.c: const vlc_fourcc_t *vlc_fourcc_GetRGBFallback( vlc_fourcc_t i_fourcc )
{
    return GetFallback( i_fourcc, pp_RGB_fallback, p_RGB32_fallback );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpBool( vlc_value_t v, vlc_value_t w )
{
    return v.b_bool ? w.b_bool ? 0 : 1 : w.b_bool ? -1 : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpInt( vlc_value_t v, vlc_value_t w )
{
    return v.i_int == w.i_int ? 0 : v.i_int > w.i_int ? 1 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpTime( vlc_value_t v, vlc_value_t w )
{
    return v.i_time == w.i_time ? 0 : v.i_time > w.i_time ? 1 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpString( vlc_value_t v, vlc_value_t w )
{
    if( !v.psz_string )
        return !w.psz_string ? 0 : -1;
    else
        return !w.psz_string ? 1 : strcmp( v.psz_string, w.psz_string );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpFloat( vlc_value_t v, vlc_value_t w ) { return v.f_float == w.f_float ? 0 : v.f_float > w.f_float ? 1 : -1; }

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: static int CmpAddress( vlc_value_t v, vlc_value_t w ) { return v.p_address == w.p_address ? 0 : v.p_address > w.p_address ? 1 : -1; }

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: int var_Set( vlc_object_t *p_this, const char *psz_name, vlc_value_t val )
{
    return var_SetChecked( p_this, psz_name, 0, val );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/misc/variables.c: int var_Get( vlc_object_t *p_this, const char *psz_name, vlc_value_t *p_val )
{
    return var_GetChecked( p_this, psz_name, 0, p_val );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/rootbind.c:                    const struct sockaddr *addr, size_t alen)
{
    (void)family;
    (void)socktype;
    (void)protocol;
    (void)addr;
    (void)alen;
    errno = EACCES;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/tls.c: static int tls_server_load(void *func, va_list ap)
{
    int (*activate) (vlc_tls_creds_t *, const char *, const char *) = func;
    vlc_tls_creds_t *crd = va_arg (ap, vlc_tls_creds_t *);
    const char *cert = va_arg (ap, const char *);
    const char *key = va_arg (ap, const char *);

    return activate (crd, cert, key);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/tls.c: static int tls_client_load(void *func, va_list ap)
{
    int (*activate) (vlc_tls_creds_t *) = func;
    vlc_tls_creds_t *crd = va_arg (ap, vlc_tls_creds_t *);

    return activate (crd);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/tcp.c: int net_AcceptSingle (vlc_object_t *obj, int lfd)
{
    int fd = vlc_accept (lfd, NULL, NULL, true);
    if (fd == -1)
    {
        if (net_errno != EAGAIN && net_errno != EWOULDBLOCK)
            msg_Err (obj, "accept failed (from socket %d): %s", lfd,
                     vlc_strerror_c(net_errno));
        return -1;
    }

    msg_Dbg (obj, "accepted socket %d (from socket %d)", fd, lfd);
    setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/io.c:                     const char *psz_fmt, ... )
{
    int i_ret;
    va_list args;
    va_start( args, psz_fmt );
    i_ret = net_vaPrintf( p_this, fd, p_vs, psz_fmt, args );
    va_end( args );

    return i_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/udp.c: static unsigned var_GetIfIndex (vlc_object_t *obj)
{
    char *ifname = var_InheritString (obj, "miface");
    if (ifname == NULL)
        return 0;

    unsigned ifindex = if_nametoindex (ifname);
    if (ifindex == 0)
        msg_Err (obj, "invalid multicast interface: %s", ifname);
    free (ifname);
    return ifindex;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/httpd.c: httpd_host_t *vlc_http_HostNew(vlc_object_t *p_this)
{
    return httpd_HostCreate(p_this, "http-host", "http-port", NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/network/httpd.c: httpd_host_t *vlc_rtsp_HostNew(vlc_object_t *p_this)
{
    return httpd_HostCreate(p_this, "rtsp-host", "rtsp-port", NULL);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/output.c:                      vlc_value_t value, void *data)
{
    vlc_object_t *dst = data;

    (void) src; (void) prev;
    return var_Set (dst, name, value);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/output.c:                            vlc_value_t prev, vlc_value_t cur, void *data)
{
    if (strcmp(prev.psz_string, cur.psz_string))
        aout_InputRequestRestart ((audio_output_t *)obj);
    (void) var; (void) data;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/output.c: float aout_VolumeGet (audio_output_t *aout)
{
    return var_GetFloat (aout, "volume");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/output.c: int aout_MuteGet (audio_output_t *aout)
{
    return var_InheritBool (aout, "mute");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/output.c: char *aout_DeviceGet (audio_output_t *aout)
{
    return var_GetNonEmptyString (aout, "device");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/filters.c:                                 const audio_sample_format_t *outfmt)
{
    return CreateFilter (obj, "audio converter", NULL, NULL, infmt, outfmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/audio_output/filters.c:                                 const audio_sample_format_t *outfmt)
{
    return CreateFilter (obj, "audio resampler", "$audio-resampler", NULL,
                         infmt, outfmt);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/libvlc.h: static inline libvlc_priv_t *libvlc_priv (libvlc_int_t *libvlc)
{
    return (libvlc_priv_t *)libvlc;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/error.c: const char *vlc_strerror(int errnum)
{
    return /*vlc_gettext*/(vlc_strerror_c(errnum));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: static wchar_t *widen_path (const char *path)
{
    wchar_t *wpath;

    errno = 0;
    wpath = ToWide (path);
    if (wpath == NULL)
    {
        if (errno == 0)
            errno = ENOENT;
        return NULL;
    }
    return wpath;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_openat (int dir, const char *filename, int flags, ...)
{
    (void) dir; (void) filename; (void) flags;
    errno = ENOSYS;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_mkdir( const char *dirname, mode_t mode )
{
    wchar_t *wpath = widen_path (dirname);
    if (wpath == NULL)
        return -1;

    int ret = _wmkdir (wpath);
    free (wpath);
    (void) mode;
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_stat (const char *filename, struct stat *buf)
{
    wchar_t *wpath = widen_path (filename);
    if (wpath == NULL)
        return -1;

    static_assert (sizeof (*buf) == sizeof (struct _stati64),
                   "Mismatched struct stat definition.");

    int ret = _wstati64 (wpath, buf);
    free (wpath);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_lstat (const char *filename, struct stat *buf)
{
    return vlc_stat (filename, buf);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_unlink (const char *filename)
{
    wchar_t *wpath = widen_path (filename);
    if (wpath == NULL)
        return -1;

    int ret = _wunlink (wpath);
    free (wpath);
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_dup (int oldfd)
{
    int fd = dup (oldfd);
    if (fd != -1)
        setmode (fd, O_BINARY);
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_socket (int pf, int type, int proto, bool nonblock)
{
    int fd = socket (pf, type, proto);
    if (fd == -1)
        return -1;

    if (nonblock)
        ioctlsocket (fd, FIONBIO, &(unsigned long){ 1 });
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/filesystem.c: int vlc_accept (int lfd, struct sockaddr *addr, socklen_t *alen, bool nonblock)
{
    int fd = accept (lfd, addr, alen);
    if (fd != -1 && nonblock)
        ioctlsocket (fd, FIONBIO, &(unsigned long){ 1 });
    return fd;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/plugin.c: void *module_Lookup( module_handle_t handle, const char *psz_function )
{
    return (void *)GetProcAddress( handle, (char *)psz_function );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: static DWORD vlc_WaitForSingleObject (HANDLE handle, DWORD delay)
{
    return vlc_WaitForMultipleObjects (1, &handle, delay);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: static DWORD vlc_Sleep (DWORD delay)
{
    DWORD ret = vlc_WaitForMultipleObjects (0, NULL, delay);
    return (ret != WAIT_TIMEOUT) ? ret : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: int vlc_sem_post (vlc_sem_t *sem)
{
    ReleaseSemaphore (*sem, 1, NULL);
    return 0; /* FIXME */
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c:                 void *data, int priority)
{
    return vlc_clone_attr (p_handle, false, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c:                       void *data, int priority)
{
    vlc_thread_t th;
    if (p_handle == NULL)
        p_handle = &th;

    return vlc_clone_attr (p_handle, true, entry, data, priority);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: unsigned vlc_timer_getoverrun (vlc_timer_t timer)
{
    (void)timer;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/specific.c: static int system_InitWSA(int hi, int lo)
{
    WSADATA data;

    if (WSAStartup(MAKEWORD(hi, lo), &data) == 0)
    {
        if (LOBYTE(data.wVersion) == 2 && HIBYTE(data.wVersion) == 2)
            return 0;
        /* Winsock DLL is not usable */
        WSACleanup( );
    }
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/interface/interface.c:                             vlc_value_t old, vlc_value_t cur, void *data )
{
    playlist_t *playlist = data;

    int ret = intf_Create( playlist, cur.psz_string );
    if( ret )
        msg_Err( obj, "interface \"%s\" initialization failed",
                 cur.psz_string );

    (void) var; (void) old;
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/extras/libc.c:                   char **outbuf, size_t *outbytesleft )
{
#ifndef __linux__
    if ( cd == (vlc_iconv_t)(-2) )
        return ISO6937toUTF8( (const unsigned char **)inbuf, inbytesleft,
                              (unsigned char **)outbuf, outbytesleft );
#endif
#if defined(HAVE_ICONV)
    return iconv( cd, (ICONV_CONST char **)inbuf, inbytesleft,
                  outbuf, outbytesleft );
#else
    abort ();
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/extras/libc.c: int vlc_iconv_close( vlc_iconv_t cd )
{
#ifndef __linux__
    if ( cd == (vlc_iconv_t)(-2) )
        return 0;
#endif
#if defined(HAVE_ICONV)
    return iconv_close( cd );
#else
    abort ();
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/stream_output/sdp.c: static bool IsSDPString (const char *str)
{
    if (strchr (str, '\r') != NULL)
        return false;
    if (strchr (str, '\n') != NULL)
        return false;
    if (!IsUTF8 (str))
        return false;
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/stream_output/sdp.c: char *sdp_AddAttribute (char **sdp, const char *name, const char *fmt, ...)
{
    char *ret;
    va_list ap;

    va_start (ap, fmt);
    ret = vsdp_AddAttribute (sdp, name, fmt, ap);
    va_end (ap);

    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/stream_output/stream_output.c: encoder_t *sout_EncoderCreate( vlc_object_t *p_this )
{
    return vlc_custom_create( p_this, sizeof( encoder_t ), "encoder" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/wx_player.cpp: 
void MainWindow::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, wxT("Choose File"));

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    else {
        libvlc_media_t *media;
        wxFileName filename = wxFileName::FileName(openFileDialog.GetPath());
        filename.MakeRelativeTo();
        media = libvlc_media_new_path(vlc_inst, filename.GetFullPath().mb_str());
        libvlc_media_player_set_media(media_player, media);
        play();
        libvlc_media_release(media);
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/wx_player.cpp: 
bool MyApp::OnInit() {
    mainWindow = new MainWindow(wxT("wxWidgets libVLC demo"));
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/QtPlayer/player.cpp: 
int Mwindow::changeVolume(int vol) { /* Called on volume slider change */

    if (vlcPlayer)
        return libvlc_audio_set_volume (vlcPlayer,vol);

    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/libvlc_DVD_ripper.c: 
gchar* get_filepath(GtkWidget* widget, GtkFileChooserAction action) {
    GtkWidget *dialog;
    gchar *path;
    dialog = gtk_file_chooser_dialog_new("Choose location", GTK_WINDOW(gtk_widget_get_toplevel(widget)), action, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    else {
        path = NULL;
    }
    gtk_widget_destroy(dialog);
    return path;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/libvlc_DVD_ripper.c: 
gboolean update_progressbar(char *handle) {
    float pos = libvlc_vlm_get_media_instance_position(vlcinst, handle, 0);
    char *pos_string;
    if(pos < 1.0 && 0.0 <= pos) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), pos);
        pos_string = get_pos_string(pos);
        if(pos_string != NULL) {
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar), pos_string);
            free(pos_string);
        }
        return TRUE;
    }
    if(stopped = 1) {
        free(handle);
        return FALSE;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/libvlc_DVD_ripper.c: 
gboolean on_end(void) {
    GtkWidget *dialog;
    stop();
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Rip done");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/libvlc_DVD_ripper.c: 
gboolean on_error(void) {
    GtkWidget *dialog;
    stop();
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error");gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return FALSE;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/ChangeLog-2010:     ====>
    {
        if( !a )
        {
            y();
            return;
        }
    
        x();
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.h: 
FORCEINLINE LRESULT MySndDlgItemMsg(HWND hDlg,int id,UINT Msg,WPARAM wp=0,LPARAM lp=0) {return SendMessage(GetDlgItem(hDlg,id),Msg,wp,lp);}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.h: #ifndef UAC_NOCUSTOMIMPLEMENTATIONS
FORCEINLINE HANDLE WINAPI GetCurrentProcess(){return ((HANDLE)(-1));}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.h: FORCEINLINE HANDLE WINAPI GetCurrentThread(){return ((HANDLE)(-2));}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.h: #define lstrcpy MyTStrCpy
FORCEINLINE LPTSTR MyTStrCpy(LPTSTR s1,LPCTSTR s2) {return PCJOIN(lstr,PCJOIN(cpyn,TFUNCSUFFIX))(s1,s2,0x7FFFFFFF);}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: enum _IPCSRVWNDMSG 
{
	IPC_GETEXITCODE=WM_USER,	//Get exit-code of the process spawned by the last call to ExecWait/ShellExecWait
	IPC_ELEVATEAGAIN,
	IPC_GETSRVPID,				//Get PID of outer process
	IPC_GETSRVHWND,				//Get $HWNDParent of outer process
	IPC_EXECCODESEGMENT,		//wp:pos | lp:hwnd | returns ErrorCode+1
	IPC_GETOUTERPROCESSTOKEN,	
#ifdef UAC_HACK_FGWND1
	IPC_HACKFINDRUNAS,
#endif
};

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: enum _COPYDATAID 
{
	CDI_SHEXEC=666,	//returns WindowsErrorCode+1
	CDI_SYNCVAR,
	CDI_STACKPUSH,
};

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: void* __cdecl memset(void*mem,int c,size_t len) 
{
	char *p=(char*)mem;
	while (len-- > 0){*p++=c;}
	return mem;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 
FORCEINLINE NSISCH* GetIPCWndClass() { return _T("NSISUACIPC"); }

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: FORCEINLINE bool StrCmpI(LPCTSTR s1,LPCTSTR s2) {return 0==lstrcmpi(s1,s2);}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: LPTSTR StrNextChar(LPCTSTR Str) { return CharNext(Str); }

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: bool StrContainsWhiteSpace(LPCTSTR s) { if (s) {while(*s && *s>_T(' '))s=StrNextChar(s);if (*s)return true;}return false; }

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: DWORD GetSysVer(bool Major=true) 
{
	OSVERSIONINFO ovi = { sizeof(ovi) };
	if ( !GetVersionEx(&ovi) ) return 0;
	return Major ? ovi.dwMajorVersion : ovi.dwMinorVersion;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: UINT_PTR StrToUInt(LPTSTR s,bool ForceHEX=false,BOOL*pFoundBadChar=0) 
{
	UINT_PTR v=0;
	BYTE base=ForceHEX?16:10;	
	if (pFoundBadChar)*pFoundBadChar=false;
	if ( !ForceHEX && *s=='0' && ((*(s=StrNextChar(s)))&~0x20)=='X' && (s=StrNextChar(s)) )base=16;
	for (TCHAR c=*s; c; c=*(s=StrNextChar(s)) ) 
	{
		if (c >= _T('0') && c <= _T('9')) c-='0';
		else if (base==16 && (c & ~0x20) >= 'A' && (c & ~0x20) <= 'F') c=(c & 7) +9;
		else 
		{
			if (pFoundBadChar /*&& c!=' '*/)*pFoundBadChar=true;
			break;
		}
		v*=base;v+=c;
	}
	return v;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: LPTSTR FindExePathEnd(LPTSTR p) 
{
	if ( *p=='"' && *(++p) ) 
	{
		while( *p && *p!='"' )p=StrNextChar(p);
		if (*p)
			p=StrNextChar(p);
		else 
			return 0;
	}
	else 
		if ( *p!='/' )while( *p && *p!=' ' )p=StrNextChar(p);
	return p;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: void* MSRunAsDlgMod_Init() 
{
	if(GetOSVerMaj()!=5 || GetOSVerMin()<1)return NULL;//only XP/2003
	return g_MSRunAsHook=SetWindowsHookEx(WH_CALLWNDPROCRET,MSRunAsDlgMod_ShellProc,0,GetCurrentThreadId());
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: FORCEINLINE DWORD MaintainDllSelfRef() //Call this from every exported function to prevent NSIS from unloading our plugin
{ 
	if(!g.CheckedIPCParam && !g.DllRef) 
	{
		HWND hSrv;
		g.CheckedIPCParam=true;
		g.UseIPC=GetIPCSrvWndFromParams(hSrv);
		if(g.UseIPC) 
		{
			g.DllRef++;
			g.hSrvIPC=hSrv;
		}
	}
	return (g.DllRef)?DllSelfAddRef():NO_ERROR;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: DWORD SendIPCMsg(UINT Msg,WPARAM wp,LPARAM lp,DWORD_PTR&MsgRet,DWORD tout=IPCTOUT_DEF,const HWND hIPCSrv=g.hSrvIPC) 
{
	if (tout==INFINITE) //BUGFIX: SendMessageTimeout(...,INFINITE,...) seems to be broken, SendMessageTimeout(...,SMTO_NORMAL,0,..) seems to work but why take the chance
	{
		MsgRet=SendMessage(hIPCSrv,Msg,wp,lp);
		return NO_ERROR;
	}
	if ( SendMessageTimeout(hIPCSrv,Msg,wp,lp,SMTO_NORMAL,tout,&MsgRet) )return NO_ERROR;
	return (tout=GetLastError()) ? tout : ERROR_TIMEOUT; 
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: DWORD DelayLoadGetProcAddr(void**ppProc,HMODULE hLib,LPCSTR Export) 
{
	ASSERT(ppProc && hLib && Export);
	if (!*ppProc) 
	{
		*ppProc=(void*)GetProcAddress(hLib,Export);
		if (!*ppProc)return GetLastError();
	}
	return NO_ERROR;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (!GetVersionEx(&ovi)) 
	{
		ASSERT(!"_SupportsUAC>GetVersionEx");
		return false;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (ovi.dwMajorVersion>=6 && _GetElevationType(&tet)==NO_ERROR) 
	{
		const bool ret=tet!=TokenElevationTypeDefault && tet!=NULL;
		TRACEF("_SupportsUAC tet=%d, returning %d\n",tet,ret);
		return ret;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (_dbg!=IDCANCEL){SetLastError(0);return _dbg==IDYES;}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (VER_PLATFORM_WIN32_NT != ovi.dwPlatformId) //Not NT
	{
		SetLastError(NO_ERROR);
		return true;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (ec=DelayLoadDlls()) 
	{
		TRACEF("DelayLoadDlls failed in _IsAdmin() with err x%X\n",ec);
		SetLastError(ec);
		return false;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (g.threadIPC) 
	{
		while(!g.hSrvIPC && !g.LastWaitExitCode)Sleep(20);
		return g.hSrvIPC ? NO_ERROR : g.LastWaitExitCode;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	for (;;) 
	{
		NSIS::MemFree(pszExePathBuf);
		if (!(pszExePathBuf=(LPTSTR)NSIS::MemAlloc((++len)*sizeof(TCHAR))))goto dieOOM;
		if ( GetModuleFileName(0,pszExePathBuf,len) < len )break; //FUCKO: what if GetModuleFileName returns 0?
		len+=MAX_PATH;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (p && *p++=='/'&&*p++=='U'&&*p++=='A'&&*p++=='C'&&*p++==':') 
	{
		hwndOut=(HWND)StrToUInt(p,true);
		return !!IsWindow(hwndOut);
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/runas.cpp: 
FORCEINLINE bool MySetDlgItemText(HWND hDlg,int id,LPCTSTR s) {return MySndDlgItemMsg(hDlg,id,WM_SETTEXT,0,(LPARAM)s)!=0;}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/runas.cpp: 
bool ErrorIsLogonError(DWORD err) {
	switch (err) {
	case ERROR_LOGON_FAILURE:
	case ERROR_ACCOUNT_RESTRICTION:
	case ERROR_INVALID_LOGON_HOURS:
	case ERROR_INVALID_WORKSTATION:
	case ERROR_PASSWORD_EXPIRED:
	case ERROR_ACCOUNT_DISABLED:
	case ERROR_NONE_MAPPED:
	case ERROR_NO_SUCH_USER:
	case ERROR_INVALID_ACCOUNT_NAME:
		return true;
	}
	return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/rootwrap.c: static inline int is_allowed_port (uint16_t port)
{
    port = ntohs (port);
    return (port == 80) || (port == 443) || (port == 554);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/rootwrap.c: static inline int send_err (int fd, int err)
{
    return send (fd, &err, sizeof (err), 0) == sizeof (err) ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/vlc.c: static bool signal_ignored (int signum)
{
    struct sigaction sa;

    if (sigaction (signum, NULL, &sa))
        return false;
    return ((sa.sa_flags & SA_SIGINFO)
            ? (void *)sa.sa_sigaction : (void *)sa.sa_handler) == SIG_IGN;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/winvlc.c: static char *FromWide (const wchar_t *wide)
{
    size_t len;
    len = WideCharToMultiByte (CP_UTF8, 0, wide, -1, NULL, 0, NULL, NULL);

    char *out = (char *)malloc (len);
    if (out)
        WideCharToMultiByte (CP_UTF8, 0, wide, -1, out, len, NULL, NULL);
    return out;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/winvlc.c: static BOOL SetDefaultDllDirectories_(DWORD flags)
{
    HMODULE h = GetModuleHandle(TEXT("kernel32.dll"));
    if (h == NULL)
        return FALSE;

    BOOL WINAPI (*SetDefaultDllDirectoriesReal)(DWORD);

    SetDefaultDllDirectoriesReal = GetProcAddress(h,
                                                  "SetDefaultDllDirectories");
    if (SetDefaultDllDirectoriesReal == NULL)
        return FALSE;

    return SetDefaultDllDirectoriesReal(flags);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/override.c: int putenv (char *str)
{
    if (override)
    {
        LOG("Blocked", "\"%s\"", str);
        return 0;
    }
    return CALL(putenv, str);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/override.c: int setenv (const char *name, const char *value, int overwrite)
{
    if (override)
    {
        LOG("Blocked", "\"%s\", \"%s\", %d", name, value, overwrite);
        return 0;
    }
    return CALL(setenv, name, value, overwrite);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/override.c: int unsetenv (const char *name)
{
    if (override)
    {
        LOG("Blocked", "\"%s\"", name);
        return 0;
    }
    return CALL(unsetenv, name);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/bin/darwinvlc.c: static bool signal_ignored (int signum)
{
    struct sigaction sa;

    if (sigaction (signum, NULL, &sa))
        return false;
    return ((sa.sa_flags & SA_SIGINFO)
            ? (void *)sa.sa_sigaction : (void *)sa.sa_handler) == SIG_IGN;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_aout.h:                             vlc_value_t oldval, vlc_value_t newval, void *data)
{
    audio_output_t *aout = (audio_output_t *)obj;
    (void)varname; (void)oldval; (void)newval; (void)data;

    aout_RestartRequest (aout, AOUT_RESTART_OUTPUT);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline char *FromWide (const wchar_t *wide)
{
    size_t len = WideCharToMultiByte (CP_UTF8, 0, wide, -1, NULL, 0, NULL, NULL);
    if (len == 0)
        return NULL;

    char *out = (char *)malloc (len);

    if (likely(out))
        WideCharToMultiByte (CP_UTF8, 0, wide, -1, out, len, NULL, NULL);
    return out;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline wchar_t *ToWide (const char *utf8)
{
    int len = MultiByteToWideChar (CP_UTF8, 0, utf8, -1, NULL, 0);
    if (len == 0)
        return NULL;

    wchar_t *out = (wchar_t *)malloc (len * sizeof (wchar_t));

    if (likely(out))
        MultiByteToWideChar (CP_UTF8, 0, utf8, -1, out, len);
    return out;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline char *ToCodePage (unsigned cp, const char *utf8)
{
    wchar_t *wide = ToWide (utf8);
    if (wide == NULL)
        return NULL;

    size_t len = WideCharToMultiByte (cp, 0, wide, -1, NULL, 0, NULL, NULL);
    if (len == 0) {
        free(wide);
        return NULL;
    }

    char *out = (char *)malloc (len);
    if (likely(out != NULL))
        WideCharToMultiByte (cp, 0, wide, -1, out, len, NULL, NULL);
    free (wide);
    return out;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline char *FromCodePage (unsigned cp, const char *mb)
{
    int len = MultiByteToWideChar (cp, 0, mb, -1, NULL, 0);
    if (len == 0)
        return NULL;

    wchar_t *wide = (wchar_t *)malloc (len * sizeof (wchar_t));
    if (unlikely(wide == NULL))
        return NULL;
    MultiByteToWideChar (cp, 0, mb, -1, wide, len);

    char *utf8 = FromWide (wide);
    free (wide);
    return utf8;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline char *FromANSI (const char *ansi)
{
    return FromCodePage (GetACP (), ansi);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: static inline char *ToANSI (const char *utf8)
{
    return ToCodePage (GetACP (), utf8);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: VLC_USED static inline char *FromLocale (const char *locale)
{
    return locale ? FromCharset ((char *)"", locale, strlen(locale)) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: VLC_USED static inline char *ToLocale (const char *utf8)
{
    size_t outsize;
    return utf8 ? (char *)ToCharset ("", utf8, &outsize) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: VLC_USED static inline char *FromLocaleDup (const char *locale)
{
    return FromCharset ("", locale, strlen(locale));
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_charset.h: VLC_USED static inline char *ToLocaleDup (const char *utf8)
{
    size_t outsize;
    return (char *)ToCharset ("", utf8, &outsize);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_plugin.h: int CDECL_SYMBOL __VLC_SYMBOL(vlc_entry) (vlc_set_cb vlc_set, void *opaque) \
{ \
    module_t *module; \
    module_config_t *config = NULL; \
    if (vlc_plugin_set (VLC_MODULE_CREATE, &module)) \
        goto error; \
    if (vlc_module_set (VLC_MODULE_NAME, (MODULE_STRING))) \
        goto error;

#define vlc_module_end() \
    (void) config; \
    return 0; \
error: \
    return -1; \
} \

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline int64_t GCD ( int64_t a, int64_t b )
{
    while( b )
    {
        int64_t c = a % b;
        a = b;
        b = c;
    }
    return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint8_t clip_uint8_vlc( int32_t a )
{
    if( a&(~255) ) return (-a)>>31;
    else           return a;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline unsigned clz (unsigned x)
{
#if VLC_GCC_VERSION(3,4)
    return __builtin_clz (x);
#else
    unsigned i = sizeof (x) * 8;

    while (x)
    {
        x >>= 1;
        i--;
    }
    return i;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline unsigned ctz (unsigned x)
{
#if VLC_GCC_VERSION(3,4)
    return __builtin_ctz (x);
#else
    unsigned i = sizeof (x) * 8;

    while (x)
    {
        x <<= 1;
        i--;
    }
    return i;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline unsigned popcount (unsigned x)
{
#if VLC_GCC_VERSION(3,4)
    return __builtin_popcount (x);
#else
    unsigned count = 0;
    while (x)
    {
        count += x & 1;
        x = x >> 1;
    }
    return count;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline unsigned parity (unsigned x)
{
#if VLC_GCC_VERSION(3,4)
    return __builtin_parity (x);
#else
    for (unsigned i = 4 * sizeof (x); i > 0; i /= 2)
        x ^= x >> i;
    return x & 1;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint16_t bswap16 (uint16_t x)
{
    return (x << 8) | (x >> 8);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint32_t bswap32 (uint32_t x)
{
#if VLC_GCC_VERSION(4,3) || defined(__clang__)
    return __builtin_bswap32 (x);
#else
    return ((x & 0x000000FF) << 24)
         | ((x & 0x0000FF00) <<  8)
         | ((x & 0x00FF0000) >>  8)
         | ((x & 0xFF000000) >> 24);
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint16_t U16_AT (const void *p)
{
    uint16_t x;

    memcpy (&x, p, sizeof (x));
    return ntoh16 (x);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint32_t U32_AT (const void *p)
{
    uint32_t x;

    memcpy (&x, p, sizeof (x));
    return ntoh32 (x);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint64_t U64_AT (const void *p)
{
    uint64_t x;

    memcpy (&x, p, sizeof (x));
    return ntoh64 (x);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint16_t GetWLE (const void *p)
{
    uint16_t x;

    memcpy (&x, p, sizeof (x));
#ifdef WORDS_BIGENDIAN
    x = bswap16 (x);
#endif
    return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint32_t GetDWLE (const void *p)
{
    uint32_t x;

    memcpy (&x, p, sizeof (x));
#ifdef WORDS_BIGENDIAN
    x = bswap32 (x);
#endif
    return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline uint64_t GetQWLE (const void *p)
{
    uint64_t x;

    memcpy (&x, p, sizeof (x));
#ifdef WORDS_BIGENDIAN
    x = bswap64 (x);
#endif
    return x;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline void *vlc_memalign(size_t align, size_t size)
{
    void *base;
    if (unlikely(posix_memalign(&base, align, size)))
        base = NULL;
    return base;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline const char *vlc_pgettext_aux( const char *ctx, const char *id )
{
    const char *tr = vlc_gettext( ctx );
    return (tr == ctx) ? id : tr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline void *xmalloc (size_t len)
{
    void *ptr = malloc (len);
    if (unlikely (ptr == NULL))
        abort ();
    return ptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline void *xrealloc (void *ptr, size_t len)
{
    void *nptr = realloc (ptr, len);
    if (unlikely (nptr == NULL))
        abort ();
    return nptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline void *xcalloc (size_t n, size_t size)
{
    void *ptr = calloc (n, size);
    if (unlikely (ptr == NULL))
        abort ();
    return ptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_common.h: static inline char *xstrdup (const char *str)
{
    char *ptr = strdup (str);
    if (unlikely(ptr == NULL))
        abort ();
    return ptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_vout_window.h: static inline int vout_window_SetState(vout_window_t *window, unsigned state)
{
    return vout_window_Control(window, VOUT_WINDOW_SET_STATE, state);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_vout_window.h:                                       unsigned width, unsigned height)
{
    return vout_window_Control(window, VOUT_WINDOW_SET_SIZE, width, height);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_vout_window.h: static inline int vout_window_SetFullScreen(vout_window_t *window, bool full)
{
    return vout_window_Control(window, VOUT_WINDOW_SET_FULLSCREEN, full);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_gcrypt.h: static int gcry_vlc_mutex_init( void **p_sys )
{
    vlc_mutex_t *p_lock = (vlc_mutex_t *)malloc( sizeof( vlc_mutex_t ) );
    if( p_lock == NULL)
        return ENOMEM;

    vlc_mutex_init( p_lock );
    *p_sys = p_lock;
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_gcrypt.h: static int gcry_vlc_mutex_destroy( void **p_sys )
{
    vlc_mutex_t *p_lock = (vlc_mutex_t *)*p_sys;
    vlc_mutex_destroy( p_lock );
    free( p_lock );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_gcrypt.h: static int gcry_vlc_mutex_lock( void **p_sys )
{
    vlc_mutex_lock( (vlc_mutex_t *)*p_sys );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_gcrypt.h: static int gcry_vlc_mutex_unlock( void **lock )
{
    vlc_mutex_unlock( (vlc_mutex_t *)*lock );
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                         bool b_default )
{
    bool b = b_default;
    int i_ret = extension_Control( p_mgr, i_flag, p_ext, &b );
    if( i_ret != VLC_SUCCESS )
        return b_default;
    else
        return b;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                      uint16_t **ppi )
{
    return extension_Control( p_mgr, EXTENSION_GET_MENU, p_ext, pppsz, ppi );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                          uint16_t i )
{
    return extension_Control( p_mgr, EXTENSION_TRIGGER_MENU, p_ext, i );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                         struct input_thread_t *p_input )
{
    return extension_Control( p_mgr, EXTENSION_SET_INPUT, p_ext, p_input );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                             int state )
{
    return extension_Control( p_mgr, EXTENSION_PLAYING_CHANGED, p_ext, state );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                          extension_t *p_ext )
{
    return extension_Control( p_mgr, EXTENSION_META_CHANGED, p_ext );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_filter.h:                                         picture_t *p_pic )              \
    {                                                                   \
        picture_t *p_outpic = filter_NewPicture( p_filter );            \
        if( p_outpic )                                                  \
        {                                                               \
            name( p_filter, p_pic, p_outpic );                          \
            picture_CopyProperties( p_outpic, p_pic );                  \
        }                                                               \
        picture_Release( p_pic );                                       \
        return p_outpic;                                                \
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_mouse.h: static inline bool vlc_mouse_IsLeftPressed( const vlc_mouse_t *p_mouse )
{
    return vlc_mouse_IsPressed( p_mouse, MOUSE_BUTTON_LEFT );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_mouse.h: static inline bool vlc_mouse_IsCenterPressed( const vlc_mouse_t *p_mouse )
{
    return vlc_mouse_IsPressed( p_mouse, MOUSE_BUTTON_CENTER );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_mouse.h: static inline bool vlc_mouse_IsRightPressed( const vlc_mouse_t *p_mouse )
{
    return vlc_mouse_IsPressed( p_mouse, MOUSE_BUTTON_RIGHT );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_mouse.h: static inline bool vlc_mouse_IsWheelUpPressed( const vlc_mouse_t *p_mouse )
{
    return vlc_mouse_IsPressed( p_mouse, MOUSE_BUTTON_WHEEL_UP );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_mouse.h: static inline bool vlc_mouse_IsWheelDownPressed( const vlc_mouse_t *p_mouse )
{
    return vlc_mouse_IsPressed( p_mouse, MOUSE_BUTTON_WHEEL_DOWN );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_input_item.h: static inline char *input_item_GetNowPlayingFb( input_item_t *p_item )
{
    char *psz_meta = input_item_GetMeta( p_item, vlc_meta_NowPlaying );
    if( !psz_meta || strlen( psz_meta ) == 0 )
    {
        free( psz_meta );
        return input_item_GetMeta( p_item, vlc_meta_ESNowPlaying );
    }
    return psz_meta;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_input_item.h: char *input_item_Get ## name (input_item_t *p_input) \
{ \
    return input_item_GetMeta (p_input, vlc_meta_ ## name); \
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_arrays.h: static inline void *realloc_down( void *ptr, size_t size )
{
    void *ret = realloc( ptr, size );
    return ret ? ret : ptr;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_epg.h: typedef struct
{
    int64_t i_start;    /* Interpreted as a value return by time() */
    int     i_duration;    /* Duration of the event in second */

    char    *psz_name;
    char    *psz_short_description;
    char    *psz_description;

    uint8_t i_rating;   /* Parental control, set to 0 when undefined */
} vlc_epg_event_t;

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_atomic.h: static inline float vlc_atomic_load_float(vlc_atomic_float *atom)
{
    union { float f; uint32_t i; } u;
    u.i = atomic_load(atom);
    return u.f;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_fixups.h: static inline char *getenv (const char *name)
{
    (void)name;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_fixups.h: static inline locale_t uselocale(locale_t loc)
{
    (void)loc;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_fixups.h: static inline locale_t newlocale(int mask, const char * locale, locale_t base)
{
    (void)mask; (void)locale; (void)base;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_modules.h: VLC_USED static inline bool module_is_main( const module_t * p_module )
{
    return !strcmp( module_get_object( p_module ), "core" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_bits.h: static inline uint32_t bs_show( bs_t *s, int i_count )
{
    bs_t     s_tmp = *s;
    return bs_read( &s_tmp, i_count );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_threads.h: mtime_t impossible_delay( mtime_t delay )
{
    (void) delay;
    return VLC_HARD_MIN_SLEEP;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_threads.h: mtime_t harmful_delay( mtime_t delay )
{
    return delay;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_threads.h: mtime_t impossible_deadline( mtime_t deadline )
{
    return deadline;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_es.h: static inline video_transform_t transform_Inverse( video_transform_t transform )
{
    switch ( transform ) {
        case TRANSFORM_R90:
            return TRANSFORM_R270;
        case TRANSFORM_R270:
            return TRANSFORM_R90;
        default:
            return transform;
    }
}

small function in /export/scratch/vaibhav/vlc-2.2.6/configure: "
  as_required="as_fn_return () { (exit \$1); }

small function in /export/scratch/vaibhav/vlc-2.2.6/configure: as_fn_success () { as_fn_return 0; }

small function in /export/scratch/vaibhav/vlc-2.2.6/configure: as_fn_failure () { as_fn_return 1; }

small function in /export/scratch/vaibhav/vlc-2.2.6/configure: as_fn_ret_success () { return 0; }

small function in /export/scratch/vaibhav/vlc-2.2.6/configure: as_fn_ret_failure () { return 1; }

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list_player.c: int libvlc_media_list_player_next(libvlc_media_list_player_t * p_mlp)
{
    lock(p_mlp);
    int failure = set_relative_playlist_position_and_play(p_mlp, 1);
    unlock(p_mlp);
    return failure;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list_player.c: int libvlc_media_list_player_previous(libvlc_media_list_player_t * p_mlp)
{
    lock(p_mlp);
    int failure = set_relative_playlist_position_and_play(p_mlp, -1);
    unlock(p_mlp);
    return failure;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/core.c: libvlc_module_description_t *libvlc_audio_filter_list_get( libvlc_instance_t *p_instance )
{
    return module_description_list_get( p_instance, "audio filter" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/core.c: libvlc_module_description_t *libvlc_video_filter_list_get( libvlc_instance_t *p_instance )
{
    return module_description_list_get( p_instance, "video filter2" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/event.c:                          void *p_user_data )
{
    return event_attach(p_event_manager, event_type, pf_callback, p_user_data,
                        false /* synchronous */);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_is_playing( libvlc_media_player_t *p_mi )
{
    libvlc_state_t state = libvlc_media_player_get_state( p_mi );
    return (libvlc_Playing == state) || (libvlc_Buffering == state);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: void * libvlc_media_player_get_nsobject( libvlc_media_player_t *p_mi )
{
    assert (p_mi != NULL);
#ifdef __APPLE__
    return var_GetAddress (p_mi, "drawable-nsobject");
#else
    return NULL;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: uint32_t libvlc_media_player_get_agl( libvlc_media_player_t *p_mi )
{
    assert (p_mi != NULL);
#ifdef __APPLE__
    return var_GetInteger (p_mi, "drawable-agl");
#else
    return 0;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: uint32_t libvlc_media_player_get_xwindow( libvlc_media_player_t *p_mi )
{
    return var_GetInteger (p_mi, "drawable-xid");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: void *libvlc_media_player_get_hwnd( libvlc_media_player_t *p_mi )
{
    assert (p_mi != NULL);
#if defined (_WIN32) || defined (__OS2__)
    return (void *)(uintptr_t)var_GetInteger (p_mi, "drawable-hwnd");
#else
    return NULL;
#endif
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c:                              libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    libvlc_time_t i_time;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    i_time = from_mtime(var_GetTime( p_input_thread, "length" ));
    vlc_object_release( p_input_thread );

    return i_time;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: libvlc_time_t libvlc_media_player_get_time( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    libvlc_time_t i_time;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    i_time = from_mtime(var_GetTime( p_input_thread , "time" ));
    vlc_object_release( p_input_thread );
    return i_time;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c:                                    libvlc_time_t i_time )
{
    input_thread_t *p_input_thread;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return;

    var_SetTime( p_input_thread, "time", to_mtime(i_time) );
    vlc_object_release( p_input_thread );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c:                                        float position )
{
    input_thread_t *p_input_thread;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return;

    var_SetFloat( p_input_thread, "position", position );
    vlc_object_release( p_input_thread );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: float libvlc_media_player_get_position( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    float f_position;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1.0;

    f_position = var_GetFloat( p_input_thread, "position" );
    vlc_object_release( p_input_thread );

    return f_position;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c:                                       int chapter )
{
    input_thread_t *p_input_thread;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return;

    var_SetInteger( p_input_thread, "chapter", chapter );
    vlc_object_release( p_input_thread );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_get_chapter( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    int i_chapter;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    i_chapter = var_GetInteger( p_input_thread, "chapter" );
    vlc_object_release( p_input_thread );

    return i_chapter;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_get_chapter_count( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    vlc_value_t val;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    int i_ret = var_Change( p_input_thread, "chapter", VLC_VAR_CHOICESCOUNT, &val, NULL );
    vlc_object_release( p_input_thread );

    return i_ret == VLC_SUCCESS ? val.i_int : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_get_title( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    int i_title;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    i_title = var_GetInteger( p_input_thread, "title" );
    vlc_object_release( p_input_thread );

    return i_title;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_get_title_count( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    vlc_value_t val;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return -1;

    int i_ret = var_Change( p_input_thread, "title", VLC_VAR_CHOICESCOUNT, &val, NULL );
    vlc_object_release( p_input_thread );

    return i_ret == VLC_SUCCESS ? val.i_int : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: void libvlc_media_player_next_chapter( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return;

    int i_type = var_Type( p_input_thread, "next-chapter" );
    var_TriggerCallback( p_input_thread, (i_type & VLC_VAR_TYPE) != 0 ?
                            "next-chapter":"next-title" );

    vlc_object_release( p_input_thread );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: void libvlc_media_player_previous_chapter( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return;

    int i_type = var_Type( p_input_thread, "next-chapter" );
    var_TriggerCallback( p_input_thread, (i_type & VLC_VAR_TYPE) != 0 ?
                            "prev-chapter":"prev-title" );

    vlc_object_release( p_input_thread );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: float libvlc_media_player_get_fps( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread ( p_mi );
    double f_fps = 0.0;

    if( p_input_thread )
    {
        if( input_Control( p_input_thread, INPUT_GET_VIDEO_FPS, &f_fps ) )
            f_fps = 0.0;
        vlc_object_release( p_input_thread );
    }
    return f_fps;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_set_rate( libvlc_media_player_t *p_mi, float rate )
{
    var_SetFloat (p_mi, "rate", rate);

    input_thread_t *p_input_thread = libvlc_get_input_thread ( p_mi );
    if( !p_input_thread )
        return 0;
    var_SetFloat( p_input_thread, "rate", rate );
    vlc_object_release( p_input_thread );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: float libvlc_media_player_get_rate( libvlc_media_player_t *p_mi )
{
    return var_GetFloat (p_mi, "rate");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_is_seekable( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    bool b_seekable;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if ( !p_input_thread )
        return false;
    b_seekable = var_GetBool( p_input_thread, "can-seek" );
    vlc_object_release( p_input_thread );

    return b_seekable;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_can_pause( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    bool b_can_pause;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if ( !p_input_thread )
        return false;
    b_can_pause = var_GetBool( p_input_thread, "can-pause" );
    vlc_object_release( p_input_thread );

    return b_can_pause;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_player.c: int libvlc_media_player_program_scrambled( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread;
    bool b_program_scrambled;

    p_input_thread = libvlc_get_input_thread ( p_mi );
    if ( !p_input_thread )
        return false;
    b_program_scrambled = var_GetBool( p_input_thread, "program-scrambled" );
    vlc_object_release( p_input_thread );

    return b_program_scrambled;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/vlm.c:                                vlm_t **restrict pp_vlm, const char *name )
{
    vlm_media_t *p_media;
    vlm_t *p_vlm;
    int64_t id;

    VLM_RET(p_vlm, NULL);
    if( vlm_Control( p_vlm, VLM_GET_MEDIA_ID, name, &id ) ||
        vlm_Control( p_vlm, VLM_GET_MEDIA, id, &p_media ) )
        return NULL;
    *pp_vlm = p_vlm;
    return p_media;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/vlm.c:                                          const char *psz_name, int i_instance )
{
    vlm_media_instance_t *p_mi;

    p_mi = libvlc_vlm_get_media_instance( p_instance, psz_name, i_instance );
    if( p_mi )
        vlm_media_instance_Delete( p_mi );
    return p_mi ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/vlm.c:                                            int i_instance )
{
    vlm_media_instance_t *p_mi;

    p_mi = libvlc_vlm_get_media_instance( p_instance, psz_name,
                                          i_instance );
    if( p_mi )
        vlm_media_instance_Delete( p_mi );
    return p_mi ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/vlm.c:                                             int i_instance )
{
    vlm_media_instance_t *p_mi;

    p_mi = libvlc_vlm_get_media_instance( p_instance, psz_name, i_instance );
    if( p_mi )
        vlm_media_instance_Delete( p_mi );
    return p_mi ? 0 : -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list.c:                                  libvlc_media_t * p_md )
{
    if( !mlist_is_writable(p_mlist) )
        return -1;
    _libvlc_media_list_add_media( p_mlist, p_md );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list.c:                                     int index )
{
    if( !mlist_is_writable(p_mlist) )
        return -1;
    _libvlc_media_list_insert_media( p_mlist, p_md, index );
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list.c:                                      int index )
{
    if( !mlist_is_writable(p_mlist) )
        return -1;
    return _libvlc_media_list_remove_index( p_mlist, index );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/event_async.c: static inline bool is_queue_initialized(libvlc_event_manager_t * p_em)
{
    return queue(p_em) != NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c:                                       const char *psz_audio_output )
{
    (void) p_instance; (void) psz_audio_output;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c:                                            int i_device )
{
    (void) p_instance; (void) psz_audio_output; (void) i_device;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c:                                      int i_device )
{
    (void) p_instance; (void) psz_audio_output; (void) i_device;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_output_get_device_type( libvlc_media_player_t *mp )
{
    (void) mp;
    return libvlc_AudioOutputDevice_Error;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_get_mute( libvlc_media_player_t *mp )
{
    int mute = -1;

    audio_output_t *aout = GetAOut( mp );
    if( aout != NULL )
    {
        mute = aout_MuteGet( aout );
        vlc_object_release( aout );
    }
    return mute;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_get_volume( libvlc_media_player_t *mp )
{
    int volume = -1;

    audio_output_t *aout = GetAOut( mp );
    if( aout != NULL )
    {
        float vol = aout_VolumeGet( aout );
        vlc_object_release( aout );
        volume = lroundf( vol * 100.f );
    }
    return volume;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_get_track_count( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread( p_mi );
    int i_track_count;

    if( !p_input_thread )
        return -1;

    i_track_count = var_CountChoices( p_input_thread, "audio-es" );

    vlc_object_release( p_input_thread );
    return i_track_count;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c:         libvlc_audio_get_track_description( libvlc_media_player_t *p_mi )
{
    return libvlc_get_track_description( p_mi, "audio-es" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_get_track( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread( p_mi );
    if( !p_input_thread )
        return -1;

    int id = var_GetInteger( p_input_thread, "audio-es" );
    vlc_object_release( p_input_thread );
    return id;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_get_channel( libvlc_media_player_t *mp )
{
    audio_output_t *p_aout = GetAOut( mp );
    if( !p_aout )
        return 0;

    int val = var_GetInteger( p_aout, "stereo-mode" );
    vlc_object_release( p_aout );
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int64_t libvlc_audio_get_delay( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread ( p_mi );
    int64_t val = 0;
    if( p_input_thread != NULL )
    {
      val = var_GetTime( p_input_thread, "audio-delay" );
      vlc_object_release( p_input_thread );
    }
    return val;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: int libvlc_audio_set_delay( libvlc_media_player_t *p_mi, int64_t i_delay )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread ( p_mi );
    int ret = 0;
    if( p_input_thread != NULL )
    {
      var_SetTime( p_input_thread, "audio-delay", i_delay );
      vlc_object_release( p_input_thread );
    }
    else
    {
      ret = -1;
    }
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: unsigned libvlc_audio_equalizer_get_preset_count( void )
{
    return NB_PRESETS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: unsigned libvlc_audio_equalizer_get_band_count( void )
{
    return EQZ_BANDS_MAX;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: static vout_thread_t **GetVouts( libvlc_media_player_t *p_mi, size_t *n )
{
    input_thread_t *p_input = libvlc_get_input_thread( p_mi );
    if( !p_input )
    {
        *n = 0;
        return NULL;
    }

    vout_thread_t **pp_vouts;
    if (input_Control( p_input, INPUT_GET_VOUTS, &pp_vouts, n))
    {
        *n = 0;
        pp_vouts = NULL;
    }
    vlc_object_release (p_input);
    return pp_vouts;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_get_fullscreen( libvlc_media_player_t *p_mi )
{
    return var_GetBool (p_mi, "fullscreen");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_height( libvlc_media_player_t *p_mi )
{
    unsigned width, height;

    if (libvlc_video_get_size (p_mi, 0, &width, &height))
        return 0;
    return height;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_width( libvlc_media_player_t *p_mi )
{
    unsigned width, height;

    if (libvlc_video_get_size (p_mi, 0, &width, &height))
        return 0;
    return width;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                              int *restrict px, int *restrict py )
{
    vout_thread_t *p_vout = GetVout (mp, num);
    if (p_vout == NULL)
        return -1;

    var_GetCoords (p_vout, "mouse-moved", px, py);
    vlc_object_release (p_vout);
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: float libvlc_video_get_scale( libvlc_media_player_t *mp )
{
    float f_scale = var_GetFloat (mp, "scale");
    if (var_GetBool (mp, "autoscale"))
        f_scale = 0.;
    return f_scale;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: char *libvlc_video_get_aspect_ratio( libvlc_media_player_t *p_mi )
{
    return var_GetNonEmptyString (p_mi, "aspect-ratio");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_spu_count( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread( p_mi );
    int i_spu_count;

    if( !p_input_thread )
        return 0;

    i_spu_count = var_CountChoices( p_input_thread, "spu-es" );
    vlc_object_release( p_input_thread );
    return i_spu_count;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:         libvlc_video_get_spu_description( libvlc_media_player_t *p_mi )
{
    return libvlc_get_track_description( p_mi, "spu-es" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                     const char *psz_subtitle )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread ( p_mi );
    bool b_ret = false;

    if( p_input_thread )
    {
        if( !input_AddSubtitle( p_input_thread, psz_subtitle, true ) )
            b_ret = true;
        vlc_object_release( p_input_thread );
    }
    return b_ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:         libvlc_video_get_title_description( libvlc_media_player_t *p_mi )
{
    return libvlc_get_track_description( p_mi, "title" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: char *libvlc_video_get_crop_geometry (libvlc_media_player_t *p_mi)
{
    return var_GetNonEmptyString (p_mi, "crop");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_teletext( libvlc_media_player_t *p_mi )
{
    return var_GetInteger (p_mi, "vbi-page");
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_track_count( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread( p_mi );
    int i_track_count;

    if( !p_input_thread )
        return -1;

    i_track_count = var_CountChoices( p_input_thread, "video-es" );

    vlc_object_release( p_input_thread );
    return i_track_count;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:         libvlc_video_get_track_description( libvlc_media_player_t *p_mi )
{
    return libvlc_get_track_description( p_mi, "video-es" );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c: int libvlc_video_get_track( libvlc_media_player_t *p_mi )
{
    input_thread_t *p_input_thread = libvlc_get_input_thread( p_mi );

    if( !p_input_thread )
        return -1;

    int id = var_GetInteger( p_input_thread, "video-es" );
    vlc_object_release( p_input_thread );
    return id;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                   unsigned option )
{
    return get_int( p_mi, "marq", marq_option_bynumber(option) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                         unsigned option )
{
    return get_string( p_mi, "marq", marq_option_bynumber(option) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                unsigned option )
{
    return get_int( p_mi, "logo", logo_option_bynumber(option) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                  unsigned option )
{
    return get_int( p_mi, "adjust", adjust_option_bynumber(option) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/video.c:                                      unsigned option )
{
    return get_float( p_mi, "adjust", adjust_option_bynumber(option) );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c: unsigned libvlc_get_log_verbosity( const libvlc_instance_t *p_instance )
{
    (void) p_instance;
    return -1;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c: libvlc_log_t *libvlc_log_open( libvlc_instance_t *p_instance )
{
    (void) p_instance;
    return malloc(1);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c: unsigned libvlc_log_count( const libvlc_log_t *p_log )
{
    (void) p_log;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c: libvlc_log_iterator_t *libvlc_log_get_iterator( const libvlc_log_t *p_log )
{
    return (p_log != NULL) ? malloc(1) : NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c: int libvlc_log_iterator_has_next( const libvlc_log_iterator_t *p_iter )
{
    (void) p_iter;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/log.c:                                                 libvlc_log_message_t *buffer )
{
    (void) p_iter; (void) buffer;
    return NULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/libvlc_internal.h: static inline libvlc_time_t from_mtime(mtime_t time)
{
    return (time + 500ULL)/ 1000ULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/libvlc_internal.h: static inline mtime_t to_mtime(libvlc_time_t time)
{
    return time * 1000ULL;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list_path.h: static inline libvlc_media_list_path_t libvlc_media_list_path_copy( const libvlc_media_list_path_t path )
{
    libvlc_media_list_path_t ret;
    int depth = libvlc_media_list_path_depth( path );
    ret = xmalloc( sizeof(int)*(depth+1) );
    memcpy( ret, path, sizeof(int)*(depth+1) );
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list_path.h: static inline libvlc_media_list_path_t libvlc_media_list_path_of_item( libvlc_media_list_t * p_mlist, libvlc_media_t * p_md )
{
    libvlc_media_list_path_t path = libvlc_media_list_path_empty();
    libvlc_media_list_path_t ret;
    ret = get_path_rec( path, p_mlist, p_md );
    free( path );
    return ret;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/media_list_path.h: libvlc_media_list_sublist_at_path( libvlc_media_list_t * p_mlist, const libvlc_media_list_path_t path )
{
    libvlc_media_list_t * ret;
    libvlc_media_t * p_md = libvlc_media_list_item_at_path( p_mlist, path );
    if( !p_md )
        return NULL;
 
    ret = libvlc_media_subitems( p_md );
    libvlc_media_release( p_md );
 
    return ret;
}

Total functions = 1647