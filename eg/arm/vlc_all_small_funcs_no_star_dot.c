small function in /export/scratch/vaibhav/vlc-2.2.6/compat/lldiv.c: lldiv_t lldiv (long long num, long long denom)
{
    lldiv_t d = { num / denom, num % demon, };
    return d;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/compat/flockfile.c: int putchar_unlocked (int c)
{
    return putc_unlocked (c, stdout);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: 
static bool dirac_isEOS( uint8_t u_parse_code ) { return 0x10 == u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static bool dirac_isSeqHdr( uint8_t u_parse_code ) { return 0 == u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static bool dirac_isPicture( uint8_t u_parse_code ) { return 0x08 & u_parse_code; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/packetizer/dirac.c: static int dirac_numRefs( uint8_t u_parse_code ) { return 0x3 & u_parse_code; }

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/msw/directx.c:                                       LPDIRECTDRAWSURFACE2 surface)
{
    if (DirectXLockSurface(front_surface, surface, NULL))
        return VLC_EGENERIC;

    DirectXUnlockSurface(front_surface, surface);
    return VLC_SUCCESS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_output/decklink.cpp: static inline int clip(int a)
{
    if      (a < 4) return 4;
    else if (a > 1019) return 1019;
    else               return a;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_splitter/panoramix.c: static inline int clip_accuracy( int a )
{
    return (a > ACCURACY) ? ACCURACY : (a < 0) ? 0 : a;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/caf.c: static inline bool AACCookieChkLen( int64_t i_length, uint64_t i_size, uint64_t i_offset )
{
    return ( i_offset + i_length <= i_size );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/demux/mkv/stream_io_callback.cpp: uint64 vlc_stream_io_callback::getFilePointer( void )
{
    if ( s == NULL )
        return 0;
    return stream_Tell( s );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_out/langfromtelx.c: static uint8_t bytereverse( int n )
{
    n = (((n >> 1) & 0x55) | ((n << 1) & 0xaa));
    n = (((n >> 2) & 0x33) | ((n << 2) & 0xcc));
    n = (((n >> 4) & 0x0f) | ((n << 4) & 0xf0));
    return n;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp: QStringList RecentsMRL::recentList()
{
    return recents;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/recents.cpp:                     bool b_playlist)
{
    return openMRLwithOptions( p_intf, mrl, NULL, b_start, b_playlist );
}

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/input_manager.cpp: int InputManager::playingStatus()
{
    return i_old_playing_status;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QModelIndex PLModel::indexByPLID( const int i_plid, const int c ) const
{
    return index( findByPLId( rootItem, i_plid ), c );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: QModelIndex PLModel::indexByInputItemID( const int i_inputitem_id, const int c ) const
{
    return index( findByInputId( rootItem, i_inputitem_id ), c );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist_model.cpp: void PLModel::processItemRemoval( int i_pl_itemid )
{
    if( i_pl_itemid <= 0 ) return;
    removeItem( findByPLId( rootItem, i_pl_itemid ) );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/vlc_model.cpp: int VLCModel::columnCount( const QModelIndex & ) const
{
    return columnFromMeta( COLUMN_END );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/playlist/playlist.cpp: QSize SplitterHandle::sizeHint() const
{
    return (orientation() == Qt::Horizontal) ? QSize( 1, height() ) : QSize( width(), 1 );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: QRectF EPGItem::boundingRect() const
{
    return m_boundingRect;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: const QDateTime& EPGItem::start() const
{
    return m_start;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: int EPGItem::duration() const
{
    return m_duration;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/components/epg/EPGItem.cpp: bool EPGItem::playsAt( const QDateTime & ref ) const
{
    return (m_start <= ref) && !endsBefore( ref );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/pictureflow.hpp: inline PFreal fcos(int iangle)
{
    return fsin(iangle + (IANGLE_MAX >> 2));
}

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/qt4/util/animators.cpp: const QPersistentModelIndex & DelegateAnimationHelper::getIndex() const
{
    return index;
}

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/controls/ctrl_slider.cpp: static inline float scroll( bool up, float pct, float step )
{
    return pct + ( up ? step : -step );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_graphics.cpp: bool X11Graphics::hit( int x, int y ) const
{
    return XPointInRegion( m_mask, x, y );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_window.cpp: bool X11Window::invalidateRect( int x, int y, int w, int h ) const
{
    XClearArea( XDISPLAY, m_wnd, x, y, w, h, True );
    return true;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_display.cpp: template<class type> type X11Display::putPixel(type r, type g, type b) const
{
    return ( (r >> m_redRightShift)   << m_redLeftShift   ) |
           ( (g >> m_greenRightShift) << m_greenLeftShift ) |
           ( (b >> m_blueRightShift)  << m_blueLeftShift  );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/x11/x11_display.cpp:     const
{
    unsigned long value = putPixel<unsigned long>(r,g,b);

    return m_pixelSize==1 ? 255 - value : value;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/src/generic_layout.cpp: const list<LayeredControl> &GenericLayout::getControlList() const
{
    return m_controlList;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/bezier.cpp:         __inline long int lrintf( float x )
        {
            int i;
            _asm fld x __asm fistp i
            return i;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/utils/var_tree.cpp: VarTree::IteratorVisible VarTree::getItem( int index )
{
   Iterator it =
        m_flat ? getLeaf( index + 1 )
               : getVisibleItem( index + 1 );

   return IteratorVisible( it, this );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: int Win32Factory::getScreenWidth() const
{
    return GetSystemMetrics(SM_CXSCREEN);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_factory.cpp: int Win32Factory::getScreenHeight() const
{
    return GetSystemMetrics(SM_CYSCREEN);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/gui/skins2/win32/win32_graphics.cpp: bool Win32Graphics::hit( int x, int y ) const
{
    return PtInRegion( m_mask, x, y ) != 0;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: DBUS_METHOD( ShuffleSet )
{
    REPLY_INIT;
    dbus_bool_t b_shuffle;

    if( VLC_SUCCESS != DemarshalSetPropertyValue( p_from, &b_shuffle ) )
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    var_SetBool( PL, "random", ( b_shuffle == TRUE ) );

    REPLY_SEND;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/control/dbus/dbus_player.c: #define PROPERTY_MAPPING_END else { return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; }

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/vhs.c: 
static inline int64_t MOD(int64_t a, int64_t b) {
    return ( ( a % b ) + b ) % b; }

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/atmo/AtmoZoneDefinition.cpp: int CAtmoZoneDefinition::getZoneNumber()
{
    return m_zonenumber;
}

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/yuvp.c: static inline uint8_t vlc_uint8( int v )
{
    if( v > 255 )
        return 255;
    else if( v < 0 )
        return 0;
    return v;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/oldmovie.c: 
static inline int64_t MOD(int64_t a, int64_t b) {
    return ( ( a % b ) + b ) % b; }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/video_filter/filter_picture.h: static inline uint8_t vlc_uint8( int v )
{
    if( v > 255 )
        return 255;
    else if( v < 0 )
        return 0;
    return v;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/sap.c: static inline int min_int( int a, int b )
{
    return a > b ? b : a;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/services_discovery/upnp.cpp: mtime_t Item::getDuration() const
{
    return _duration;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/mux/mpeg/ts.c: static uint32_t GetDescriptorLength24b( int i_length )
{
    uint32_t i_l1, i_l2, i_l3;

    i_l1 = i_length&0x7f;
    i_l2 = ( i_length >> 7 )&0x7f;
    i_l3 = ( i_length >> 14 )&0x7f;

    return( 0x808000 | ( i_l3 << 16 ) | ( i_l2 << 8 ) | i_l1 );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/hw/vdpau/vlc_vdpau.c:                                                  VdpStatus status)
{
    (void) vdp;
    return (status != VDP_STATUS_OK) ? "Unknown error" : "No error";
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/live555.cpp: static inline Boolean toBool( bool b ) { return b?True:False; } // silly, no?

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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( !p_item )
    {
        free( psz_device );
        CoUninitialize();
        return VLC_SUCCESS;
    }

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/dshow.cpp:     if( FAILED(hr) )
    {
        msg_Dbg( p_this, "couldn't find tuner interface" );
        return;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dshow/filter.cpp:                                              LPCWSTR )
{
#ifdef DEBUG_DSHOW
    msg_Dbg( p_input, "CaptureFilter::JoinFilterGraph" );
#endif

    p_graph = pGraph;

    return NOERROR;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/dv.c: static int AVCResetHandler( raw1394handle_t handle, unsigned int generation )
{
    raw1394_update_generation( handle, generation );
    return 0;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     int iCaseSensitivity;
{
    if (iCaseSensitivity==0)
        iCaseSensitivity=CASESENSITIVITYDEFAULTVALUE;

    if (iCaseSensitivity==1)
        return strcmp(fileName1,fileName2);

    return STRCMPCASENOSENTIVEFUNCTION(fileName1,fileName2);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/access/zip/unzip/unzip.c:     int raw;
{
    return unzOpenCurrentFile3(file, method, level, raw, NULL);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/mpd/SegmentTemplate.cpp: bool            SegmentTemplate::isSingleShot() const
{
    return false;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/mpd/Segment.cpp: bool                    Segment::isSingleShot   () const
{
    return true;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/stream_filter/dash/xml/Node.cpp: bool                                Node::hasText               () const
{
    return false;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/libass.c: static rectangle_t r_create( int x0, int y0, int x1, int y1 )
{
    rectangle_t r = { x0, y0, x1, y1 };
    return r;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/cdg.c: static uint32_t RenderRGB( int r, int g, int b )
{
    return ( r << CDG_COLOR_R_SHIFT ) | ( g << CDG_COLOR_G_SHIFT ) | ( b << CDG_COLOR_B_SHIFT );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/bitstream.h: static inline uint32_t NEG_USR32(uint32_t a, int8_t s){
    asm ("shrl %1, %0\n\t"
         : "+r" (a)
         : "ic" ((uint8_t)(-s))
    );
    return a;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int32_t Fixed32From64(int64_t x)
{
  return x & 0xFFFFFFFF;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/wmafixed/wmafixed.c: int64_t Fixed32To64(int32_t x)
{
  return (int64_t)x;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/omxil/OMX_Broadcom.h: \code{nPortIndex} is \code{OMX_ALL}, it returns the sensor mode

small function in /export/scratch/vaibhav/vlc-2.2.6/modules/codec/telx.c: static uint8_t bytereverse( int n )
{
    n = (((n >> 1) & 0x55) | ((n << 1) & 0xaa));
    n = (((n >> 2) & 0x33) | ((n << 2) & 0xcc));
    n = (((n >> 4) & 0x0f) | ((n << 4) & 0xf0));
    return n;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                   bool b_playlist, bool b_locked )
{
    return playlist_AddExt( p_playlist, psz_uri, psz_name,
                            i_mode, i_pos, -1, 0, NULL, 0, b_playlist, b_locked );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/playlist/item.c:                         bool b_stop )
{
    assert( b_stop );
    return playlist_NodeDelete( p_playlist, p_item, true, false );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/video_epg.c:                           mtime_t ts)
{
    VLC_UNUSED(subpic); VLC_UNUSED(ts);
    VLC_UNUSED(fmt_src); VLC_UNUSED(has_src_changed);
    VLC_UNUSED(fmt_dst);

    if (!has_dst_changed)
        return VLC_SUCCESS;
    return VLC_EGENERIC;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/display.c:                                 mtime_t hide_timeout)
{
    return DisplayNew(vout, source, state, module, false, NULL,
                      double_click_timeout, hide_timeout, NULL);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/video_output/vout_subpictures.c: static int IntegerCmp(int64_t i0, int64_t i1)
{
    return i0 < i1 ? -1 : i0 > i1 ? 1 : 0;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/input/item.c:                                  mtime_t i_duration )
{
    return input_item_NewWithType( psz_uri, psz_name,
                                  i_options, ppsz_options, i_option_flags,
                                  i_duration, ITEM_TYPE_UNKNOWN );
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/posix/thread.c:                         mtime_t deadline)
{
    struct timespec ts = mtime_to_ts (deadline);
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/test/md5.c: int main( void )
{
    test_config_StringEscape();

    return 0;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: static ULONG vlc_WaitForSingleObject (HEV hev, ULONG ulTimeout)
{
    return vlc_DosWaitEventSemEx( hev, ulTimeout );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: static ULONG vlc_Sleep (ULONG ulTimeout)
{
    ULONG rc = vlc_DosWaitEventSemEx( NULLHANDLE, ulTimeout );

    return ( rc != ERROR_TIMEOUT ) ? rc : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/os2/thread.c: unsigned vlc_timer_getoverrun (vlc_timer_t timer)
{
    (void)timer;
    return 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/chain.c: static bool IsEscapeNeeded( char c )
{
    return c == '\'' || c == '"' || c == '\\';
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/config/chain.c: static bool IsSpace( char c  )
{
    return c == ' ' || c == '\t';
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/modules/modules.c:                       bool strict)
{
    return vlc_module_load(obj, cap, name, strict, generic_start, obj);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: static DWORD vlc_WaitForSingleObject (HANDLE handle, DWORD delay)
{
    return vlc_WaitForMultipleObjects (1, &handle, delay);
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: static DWORD vlc_Sleep (DWORD delay)
{
    DWORD ret = vlc_WaitForMultipleObjects (0, NULL, delay);
    return (ret != WAIT_TIMEOUT) ? ret : 0;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/src/win32/thread.c: unsigned vlc_timer_getoverrun (vlc_timer_t timer)
{
    (void)timer;
    return 0;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/doc/libvlc/wx_player.cpp: 
bool MyApp::OnInit() {
    mainWindow = new MainWindow(wxT("wxWidgets libVLC demo"));
    return true;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: FORCEINLINE bool StrCmpI(LPCTSTR s1,LPCTSTR s2) {return 0==lstrcmpi(s1,s2);}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: LPTSTR StrNextChar(LPCTSTR Str) { return CharNext(Str); }

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (!GetVersionEx(&ovi)) 
	{
		ASSERT(!"_SupportsUAC>GetVersionEx");
		return false;
	}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (_dbg!=IDCANCEL){SetLastError(0);return _dbg==IDYES;}

small function in /export/scratch/vaibhav/vlc-2.2.6/extras/package/win32/NSIS/UAC/uac.cpp: 	if (ec=DelayLoadDlls()) 
	{
		TRACEF("DelayLoadDlls failed in _IsAdmin() with err x%X\n",ec);
		SetLastError(ec);
		return false;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_vout_window.h:                                       unsigned width, unsigned height)
{
    return vout_window_Control(window, VOUT_WINDOW_SET_SIZE, width, height);
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

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                          uint16_t i )
{
    return extension_Control( p_mgr, EXTENSION_TRIGGER_MENU, p_ext, i );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_extensions.h:                                             int state )
{
    return extension_Control( p_mgr, EXTENSION_PLAYING_CHANGED, p_ext, state );
}

small function in /export/scratch/vaibhav/vlc-2.2.6/include/vlc_fixups.h: static inline locale_t uselocale(locale_t loc)
{
    (void)loc;
    return NULL;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: unsigned libvlc_audio_equalizer_get_preset_count( void )
{
    return NB_PRESETS;
}

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/audio.c: unsigned libvlc_audio_equalizer_get_band_count( void )
{
    return EQZ_BANDS_MAX;
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

small function in /export/scratch/vaibhav/vlc-2.2.6/lib/libvlc_internal.h: static inline libvlc_time_t from_mtime(mtime_t time)
{
    return (time + 500ULL)/ 1000ULL;
}

Total functions = 338