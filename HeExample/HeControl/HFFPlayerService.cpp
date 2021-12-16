#include "HFFPlayerService_p.h"
#include "HFFmpeg.h"
#include "HFFPlayerServiceThread.h"
//#include "HFFPlayerControl.h"
#include "HFFSourceControl.h"
#include "HSDLControl.h"
#include <QtCore/QRect>

HE_BEGIN_NAMESPACE

HFFPlayerService::HFFPlayerService(QObject *parent) :
    QObject(parent),
    d_ptr(new HFFPlayerServicePrivate)
{
    init();
}

HFFPlayerService::~HFFPlayerService()
{
    d_ptr->thread->shutdown();
    av_log(nullptr, AV_LOG_QUIET, "%s", "");
    avformat_network_deinit();
}

bool HFFPlayerService::load(const QString &value)
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->thread->clearTask();
    if (value.isEmpty())
    {
        av_log(nullptr, AV_LOG_FATAL, "An input file must be specified.\n");
        return false;
    }
    d_ptr->media = value;
    d_ptr->thread->addTask(HFFPlayerServiceThread::SetSource);
//    d_ptr->playerControl->updateStatus(HFFPlayerControl::Stopped);
    return true;
}

void HFFPlayerService::play()
{
    d_ptr->thread->addTask(HFFPlayerServiceThread::Play);
}

void HFFPlayerService::pause()
{
    d_ptr->thread->addTask(HFFPlayerServiceThread::Pause);
}

void HFFPlayerService::stop()
{
    d_ptr->thread->addTask(HFFPlayerServiceThread::Stop);
}

void HFFPlayerService::init()
{
    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    avdevice_register_all();
    avformat_network_init();
//    d_ptr->player_control = new HFFPlayerControl(this, this);

    d_ptr->sdl = new HSDLControl(this);
    d_ptr->sdl->init();
    d_ptr->source = new HFFSourceControl(this);
    d_ptr->source->set_pix_fmts(d_ptr->sdl->av_pix_fmts());
    d_ptr->thread = new HFFPlayerServiceThread(this);
    d_ptr->thread->start();

    connect(d_ptr->sdl, &HSDLControl::pause_request,            d_ptr->source, &HFFSourceControl::toggle_pause);
    connect(d_ptr->sdl, &HSDLControl::step_request,             d_ptr->source, &HFFSourceControl::step_to_next_frame);
    connect(d_ptr->sdl, &HSDLControl::seek_to_request,          d_ptr->source, &HFFSourceControl::seek_to);
    connect(d_ptr->sdl, &HSDLControl::seek_section_request,     d_ptr->source, &HFFSourceControl::seek_section);
    connect(d_ptr->sdl, &HSDLControl::seek_chapter_request,     d_ptr->source, &HFFSourceControl::seek_chapter);
    connect(d_ptr->sdl, &HSDLControl::switch_channel_request,   d_ptr->source, &HFFSourceControl::switch_channel);
    connect(d_ptr->sdl, &HSDLControl::force_refresh_request,    d_ptr->source, &HFFSourceControl::set_force_refresh);
    connect(d_ptr->sdl, &HSDLControl::screen_size_changed,      d_ptr->source, &HFFSourceControl::set_screen_size);
}

void HFFPlayerService::doSetSource()
{
    d_ptr->source->open(d_ptr->media, d_ptr->iformat);
}

void HFFPlayerService::doPlay()
{
    d_ptr->source->start();
    d_ptr->sdl->start();
}

void HFFPlayerService::doPause()
{

}

void HFFPlayerService::doStop()
{

}

int HFFPlayerService::audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params)
{
    return d_ptr->sdl->audio_open(opaque, wanted_channel_layout, wanted_nb_channels, wanted_sample_rate, hw_params);
}

void HFFPlayerService::audio_pause(int pause)
{
    d_ptr->sdl->audio_pause(pause);
}

void HFFPlayerService::audio_close()
{
    d_ptr->sdl->audio_close();
}

void HFFPlayerService::audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len)
{
    d_ptr->sdl->audio_fill_stream(stream, buf, index, len);
}

void HFFPlayerService::audio_upload(QRect rect, int channels, int16_t *sample, int start, int size)
{
    d_ptr->sdl->audio_upload(rect, channels, sample, start, size);
}

void HFFPlayerService::audio_upload(QRect rect, int channels, int freq, float **data, int start)
{
    d_ptr->sdl->audio_upload(rect, channels, freq, data, start);
}

void HFFPlayerService::video_open(int width, int height)
{
    d_ptr->sdl->video_open(width, height);
}

void HFFPlayerService::video_upload(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame)
{
    d_ptr->sdl->video_upload(rect, video_frame, subtitle_frame);
}

void HFFPlayerService::subtitle_upload(HFFFrame *frame)
{
    d_ptr->sdl->subtitle_upload(frame);
}

double HFFPlayerService::refresh()
{
    return d_ptr->source->toggle_refresh();
}

HE_END_NAMESPACE
