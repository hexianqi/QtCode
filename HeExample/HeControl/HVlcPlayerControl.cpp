#include "HVlcPlayerControl_p.h"
#include "HeCore/HCallback.h"
#include <QtWidgets/QWidget>
#include <QtCore/QDebug>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

// 此函数无法使用control里面的变量
//static void handleEvents(const libvlc_event_t *event, void *data)
//{
//    auto control = static_cast<HVlcPlayerControl *>(data);
//    switch (event->type)
//    {
//    case libvlc_MediaParsedChanged:
//        if (event->u.media_parsed_changed.new_status == libvlc_media_parsed_status_done)
//            control->updateMeta();
//        break;
//    case libvlc_MediaPlayerOpening:
//    case libvlc_MediaPlayerBuffering:
//        break;
//    case libvlc_MediaPlayerPlaying:
//        emit control->stateChanged(HVlcPlayerControl::Playing);
//        break;
//    case libvlc_MediaPlayerPaused:
//        emit control->stateChanged(HVlcPlayerControl::Paused);
//        break;
//    case libvlc_MediaPlayerStopped:
//        emit control->stateChanged(HVlcPlayerControl::Stopped);
//        break;
//    case libvlc_MediaPlayerEncounteredError:
//        emit control->stateChanged(HVlcPlayerControl::Error);
//        break;
//    case libvlc_MediaPlayerLengthChanged:
//        emit control->durationChanged(event->u.media_player_length_changed.new_length);
//        break;
//    case libvlc_MediaPlayerTimeChanged:
//        emit control->timeChanged(event->u.media_player_time_changed.new_time);
//        break;
//    case libvlc_MediaPlayerPositionChanged:
//        emit control->positionChanged(event->u.media_player_position_changed.new_position);
//        break;
//    default:
//        break;
//    }
//}

HVlcPlayerControlPrivate::HVlcPlayerControlPrivate()
{
    mediaEvents << libvlc_MediaParsedChanged;
    playerEvents << libvlc_MediaPlayerOpening
                 << libvlc_MediaPlayerBuffering
                 << libvlc_MediaPlayerPlaying
                 << libvlc_MediaPlayerPaused
                 << libvlc_MediaPlayerStopped
                 << libvlc_MediaPlayerEncounteredError
                 << libvlc_MediaPlayerMuted
                 << libvlc_MediaPlayerUnmuted
                 << libvlc_MediaPlayerAudioVolume
                 << libvlc_MediaPlayerLengthChanged
                 << libvlc_MediaPlayerTimeChanged
                 << libvlc_MediaPlayerPositionChanged;
}


HVlcPlayerControl::HVlcPlayerControl(QObject *parent) :
    QObject(parent),
    d_ptr(new HVlcPlayerControlPrivate)
{
}

HVlcPlayerControl::HVlcPlayerControl(HVlcPlayerControlPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HVlcPlayerControl::~HVlcPlayerControl()
{
    close();
    if (d_ptr->instance != nullptr)
    {
        libvlc_release(d_ptr->instance);
        d_ptr->instance = nullptr;
    }
}

void HVlcPlayerControl::setVideoWindow(QWidget *p)
{
    if (p == d_ptr->widget)
        return;
    d_ptr->widget = p;

    if (d_ptr->player == nullptr)
        return;
    attachWindow();
}

void HVlcPlayerControl::setUrl(const QString &value)
{
    if (d_ptr->url == value)
        return;
    d_ptr->url = value;
    close();
    open();
}

void HVlcPlayerControl::setVolume(int value)
{
    if (d_ptr->player == nullptr)
        return;
    libvlc_audio_set_volume(d_ptr->player, value);
}

void HVlcPlayerControl::setMute(bool b)
{
    if (d_ptr->player == nullptr)
        return;
    libvlc_audio_set_mute(d_ptr->player, b);
}

void HVlcPlayerControl::setChapter(int value)
{
    if (d_ptr->player == nullptr)
        return;
    libvlc_media_player_set_chapter(d_ptr->player, value);
}

void HVlcPlayerControl::snapshot(const QString &fileName)
{
    if (d_ptr->player == nullptr)
        return;
    libvlc_video_take_snapshot(d_ptr->player, 0, fileName.toUtf8().constData(), 0, 0);
}

void HVlcPlayerControl::fullScreen()
{
    if (d_ptr->widget == nullptr)
        return;

    d_ptr->fullScreen = !d_ptr->fullScreen;
    if (d_ptr->fullScreen)
    {
        d_ptr->widget->setWindowFlags(d_ptr->widget->windowFlags() | Qt::Window);
        d_ptr->widget->showFullScreen();
    }
    else
    {
        d_ptr->widget->setWindowFlags(d_ptr->widget->windowFlags() & ~Qt::WindowFlags(Qt::Window));
        d_ptr->widget->showNormal();
    }
}

void HVlcPlayerControl::seek(double pos)
{
    if (d_ptr->player == nullptr)
        return;

    auto ms = pos * libvlc_media_get_duration(d_ptr->media);
    libvlc_media_player_set_time(d_ptr->player, libvlc_time_t(ms));
}

void HVlcPlayerControl::play()
{
    if (d_ptr->player == nullptr)
        return;

    if (d_ptr->state == Paused)
        libvlc_media_player_set_pause(d_ptr->player, false);
    else
        libvlc_media_player_play(d_ptr->player);
}

void HVlcPlayerControl::pause()
{
    if (d_ptr->player == nullptr)
        return;

    if (libvlc_media_player_can_pause(d_ptr->player))
        libvlc_media_player_set_pause(d_ptr->player, true);
}

void HVlcPlayerControl::stop()
{
    if (d_ptr->player == nullptr)
        return;
    libvlc_media_player_stop(d_ptr->player);
}

void HVlcPlayerControl::close()
{
    if (!d_ptr->opened)
        return;

    if (d_ptr->player != nullptr)
    {
        libvlc_media_player_stop(d_ptr->player);
        libvlc_media_player_release(d_ptr->player);
        d_ptr->player = nullptr;
    }
    if (d_ptr->media != nullptr)
    {
        libvlc_media_release(d_ptr->media);
        d_ptr->media = nullptr;
    }
    d_ptr->opened = false;
}

void HVlcPlayerControl::setOption(const QString &value)
{
    if (d_ptr->media == nullptr)
        return;
    auto data = value.toUtf8();
    auto option = data.constData();
    libvlc_media_add_option(d_ptr->media, option);
}

bool HVlcPlayerControl::open()
{
    if (d_ptr->opened)
        return true;

    if (d_ptr->url.isEmpty())
        return false;

    if (!initInstance())
        return false;

    d_ptr->media = libvlc_media_new_location(d_ptr->instance, d_ptr->url.toUtf8().constData());
    if (d_ptr->media == nullptr)
        return false;
    d_ptr->player = libvlc_media_player_new_from_media(d_ptr->media);
    if (d_ptr->player == nullptr)
        return false;

    d_ptr->mediaManager = libvlc_media_event_manager(d_ptr->media);
    d_ptr->playerManager = libvlc_media_player_event_manager(d_ptr->player);
    attachWindow();
    attachEvents();

    // 设置硬件加速 none auto any d3d11va dxva2
    setOption(QString(":avcodec-hw=%1").arg("none"));
    // 设置通信协议 tcp udp
    setOption(QString(":rtsp-%1").arg("tcp"));
    // 设置缓存时间 默认500毫秒
    setOption(QString(":network-caching=%1").arg(500));

    auto flags = d_ptr->url.startsWith("file://", Qt::CaseInsensitive) ? libvlc_media_parse_local : libvlc_media_parse_network;
    libvlc_media_parse_with_options(d_ptr->media, flags, 1000);

    d_ptr->opened = true;
    return true;
}

bool HVlcPlayerControl::initInstance()
{
    if (d_ptr->instance == nullptr)
    {
        const char *args[9] =
            {
                "-I",
                "dummy",
                "--no-osd",
                "--no-stats",
                "--ignore-config",
                "--no-video-on-top",
                "--no-video-title-show",
                "--no-snapshot-preview",
                ""
            };
        d_ptr->instance = libvlc_new(sizeof(args) / sizeof(args[0]), args);
    }
    return d_ptr->instance != nullptr;
}

void HVlcPlayerControl::attachWindow()
{
    WId wid = 0;
    if (d_ptr->widget != nullptr)
        wid = d_ptr->widget->winId();
#if defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(d_ptr->player, (void *)wid);
#elif defined(Q_OS_LINUX)
    libvlc_media_player_set_xwindow(d_ptr->player, wid);
#elif defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(d_ptr->player, (void *)wid);
#endif

    libvlc_video_set_mouse_input(d_ptr->player, wid == 0);
    libvlc_video_set_key_input(d_ptr->player, wid == 0);
}

void HVlcPlayerControl::attachEvents()
{
    if (d_ptr->callback == nullptr)
    {
        HCallback<void(const libvlc_event_t *, void *)>::func = std::bind(&HVlcPlayerControl::handleEvents, this, std::placeholders::_1, std::placeholders::_2);
        d_ptr->callback = (HCallback<void(const libvlc_event_t *, void *)>::callback);
    }
    for(auto e : d_ptr->mediaEvents)
        libvlc_event_attach(d_ptr->mediaManager, e, d_ptr->callback, this);
    for(auto e : d_ptr->playerEvents)
        libvlc_event_attach(d_ptr->playerManager, e, d_ptr->callback, this);
}

void HVlcPlayerControl::detachEvents()
{
    for(auto e : d_ptr->mediaEvents)
        libvlc_event_detach(d_ptr->mediaManager, e, d_ptr->callback, this);
    for(auto e : d_ptr->playerEvents)
        libvlc_event_detach(d_ptr->playerManager, e, d_ptr->callback, this);
}

void HVlcPlayerControl::handleEvents(const libvlc_event_t *event, void */*data*/)
{
    switch (event->type)
    {
    case libvlc_MediaParsedChanged:
        if (event->u.media_parsed_changed.new_status == libvlc_media_parsed_status_done)
            updateMediaInfo();
        break;
    case libvlc_MediaPlayerOpening:
    case libvlc_MediaPlayerBuffering:
        break;
    case libvlc_MediaPlayerPlaying:
        emit stateChanged(HVlcPlayerControl::Playing);
        break;
    case libvlc_MediaPlayerPaused:
        emit stateChanged(HVlcPlayerControl::Paused);
        break;
    case libvlc_MediaPlayerStopped:
        emit stateChanged(HVlcPlayerControl::Stopped);
        break;
    case libvlc_MediaPlayerEncounteredError:
        emit stateChanged(HVlcPlayerControl::Error);
        break;
    case libvlc_MediaPlayerMuted:
        emit mutedChanged(true);
        break;
    case libvlc_MediaPlayerUnmuted:
        emit mutedChanged(false);
        break;
    case libvlc_MediaPlayerAudioVolume:
        emit volumeChanged(event->u.media_player_audio_volume.volume);
        break;
    case libvlc_MediaPlayerLengthChanged:
        emit durationChanged(event->u.media_player_length_changed.new_length);
        break;
    case libvlc_MediaPlayerTimeChanged:
        emit timeChanged(event->u.media_player_time_changed.new_time);
        break;
    case libvlc_MediaPlayerPositionChanged:
        emit positionChanged(event->u.media_player_position_changed.new_position);
        break;
    default:
        break;
    }
}

void HVlcPlayerControl::updateMediaInfo()
{
    updateMetaInfo();
    updateTracksInfo();
}

void HVlcPlayerControl::updateMetaInfo()
{
    if (d_ptr->media == nullptr)
        return;
    qDebug() << "---------- Meta info ----------";
    qDebug() << "title: " << libvlc_media_get_meta(d_ptr->media, libvlc_meta_Title);
    qDebug() << "artist: " << libvlc_media_get_meta(d_ptr->media, libvlc_meta_Artist);
    qDebug() << "album: " << libvlc_media_get_meta(d_ptr->media, libvlc_meta_Album);

    //    // 设置媒体信息
    //    libvlc_media_set_meta(d_ptr->media, libvlc_meta_Title, "Title");
    //    libvlc_media_set_meta(d_ptr->media, libvlc_meta_Artist, "Artist");
    //    libvlc_media_set_meta(d_ptr->media, libvlc_meta_Album, "Album");
    //    libvlc_media_save_meta(d_ptr->media);
}

void HVlcPlayerControl::updateTracksInfo()
{
    if (d_ptr->player == nullptr)
        return;

    libvlc_media_track_t **tracks;
    auto count = libvlc_media_tracks_get(d_ptr->media, &tracks);
    if (count <= 0)
        return;

    qDebug() << "---------- Tracks info ----------";
    for (unsigned i = 0; i < count; i++)
    {
        auto track = tracks[i];
        auto codec = libvlc_media_get_codec_description(track->i_type, track->i_codec);
        auto fourcc_codec = libvlc_media_get_codec_description(track->i_type, track->i_original_fourcc);
        qDebug() << "type: " << track->i_type;
        if (codec != nullptr)
            qDebug() << "track codec: " << codec;
        if (fourcc_codec != nullptr)
            qDebug() << "fourcc codec: " << fourcc_codec;
        if (track->psz_language != nullptr)
            qDebug() << "psz_language: " << track->psz_language;
        if (track->psz_description != nullptr)
            qDebug() << "psz_description: " << track->psz_description;
        if (track->i_type == libvlc_track_audio)
        {
            qDebug() << "channels: " << track->audio->i_channels;
            qDebug() << "rate: " << track->audio->i_rate;
        }
        else if (track->i_type == libvlc_track_video)
        {
            qDebug() << "width: " << track->video->i_width;
            qDebug() << "height: " << track->video->i_height;
            // 帧率
            if (track->video->i_sar_num > 0)
                qDebug() << "frame_rate: " << 1.0 * track->video->i_frame_rate_num / track->video->i_frame_rate_den;
            // 像素宽高比
            if (track->video->i_sar_num > 0)
               qDebug() << "sar: " << 1.0 * track->video->i_sar_num / track->video->i_sar_den;
        }
        else if (track->i_type == libvlc_track_text)
            qDebug() << "encoding: " << track->subtitle->psz_encoding;
        qDebug() << "--------------------";
    }
    if (count > 0)
        libvlc_media_tracks_release(tracks, count);

//    // 当前音频声道
    //    qDebug() << "channels: " << libvlc_audio_get_channel(d_ptr->player);
}

HE_CONTROL_END_NAMESPACE
