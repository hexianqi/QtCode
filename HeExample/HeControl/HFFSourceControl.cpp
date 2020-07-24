#include "HFFSourceControl_p.h"
#include "HFFConfig.h"
#include "HFFCmdUtil.h"
#include "HFFTypes.h"
#include "HFFPlayerService.h"
#include "HFFStreamsControl.h"
#include "HFFDataControl.h"
#include <QtCore/QRect>
#include <QtCore/QThread>

extern "C" {
////#include "libavcodec/avfft.h"
#include "libavutil/bprint.h"
////#include "libavutil/display.h"
}

using namespace std;

HE_CONTROL_BEGIN_NAMESPACE

QRect calc_display_rect(QRect src, QSize tgt, AVRational pic_sar)
{
    int64_t width, height, x, y;
    auto aspect_ratio = av_cmp_q(pic_sar, av_make_q(0, 1)) <= 0 ? av_make_q(1, 1) : pic_sar;
    aspect_ratio = av_mul_q(aspect_ratio, av_make_q(tgt.width(), tgt.height()));

    height = src.height();
    width = av_rescale(height, aspect_ratio.num, aspect_ratio.den) & ~1;
    if (width > src.width())
    {
        width = src.width();
        height = av_rescale(width, aspect_ratio.den, aspect_ratio.num) & ~1;
    }
    x = (src.width() - width) / 2;
    y = (src.height() - height) / 2;
    return QRect(src.x() + x, src.y()  + y, FFMAX(width,  1), FFMAX(height, 1));
}

int demuxing_interrupt(void *opaque)
{
    return static_cast<HFFSourceControl *>(opaque)->abort_request() ? 1 : 0;
}

class HFFSourceControlThread : public QThread
{
public:
    HFFSourceControlThread(HFFSourceControl *source);

protected:
    void run() override;

private:
    HFFSourceControl *_source;
};

HFFSourceControlThread::HFFSourceControlThread(HFFSourceControl *source) :
    QThread(source)
{
    _source = source;
}

void HFFSourceControlThread::run()
{
    _source->run();
}

HFFSourceControlPrivate::HFFSourceControlPrivate()
{
    start_time = AV_NOPTS_VALUE;
    duration = AV_NOPTS_VALUE;
}

HFFSourceControl::HFFSourceControl(HFFPlayerService *service) :
    QObject(service),
    d_ptr(new HFFSourceControlPrivate)
{
    d_ptr->service = service;
    init_opts();
    av_init_packet(&flush_pkt);
    flush_pkt.data = (uint8_t *)&flush_pkt;

    d_ptr->thread = new HFFSourceControlThread(this);
    d_ptr->video_ctl = new HFFVideoStreamsControl(this);
    d_ptr->audio_ctl = new HFFAudioStreamsControl(this);
    d_ptr->subtitle_ctl = new HFFSubtitleStreamsControl(this);
    d_ptr->video_clk = new HFFClock(this);
    d_ptr->audio_clk = new HFFClock(this);
    d_ptr->ext_clk = new HFFClock(this);

    connect(d_ptr->video_ctl, &HFFStreamsControl::open_finished, this, &HFFSourceControl::handle_open_stream_finished);
    connect(d_ptr->audio_ctl, &HFFStreamsControl::open_finished, this, &HFFSourceControl::handle_open_stream_finished);
    connect(d_ptr->subtitle_ctl, &HFFStreamsControl::open_finished, this, &HFFSourceControl::handle_open_stream_finished);
    connect(d_ptr->audio_ctl, &HFFStreamsControl::close_finished, this, &HFFSourceControl::handle_close_stream_finished);
}

HFFSourceControl::~HFFSourceControl()
{
    close();
    uninit_opts();
    av_log(nullptr, AV_LOG_QUIET, "%s", "");
}

bool HFFSourceControl::abort_request()
{
    return d_ptr->abort_request;
}

QString HFFSourceControl::title()
{
    AVDictionaryEntry *t;
    if (d_ptr->fmt_ctx && (t = av_dict_get(d_ptr->fmt_ctx->metadata, "title", nullptr, 0)))
        return t->value;
    return "";
}

int HFFSourceControl::master_sync_type()
{
    if (d_ptr->sync_mode == SYNC_VIDEO_MASTER)
        return d_ptr->video_ctl->is_open() ? SYNC_VIDEO_MASTER : SYNC_AUDIO_MASTER;
    if (d_ptr->sync_mode == SYNC_AUDIO_MASTER)
        return d_ptr->audio_ctl->is_open() ? SYNC_AUDIO_MASTER : SYNC_EXTERNAL_CLOCK;
    return SYNC_EXTERNAL_CLOCK;
}

// get the current master clock value
double HFFSourceControl::master_clock()
{
    auto type = master_sync_type();
    if (type == SYNC_VIDEO_MASTER)
        return d_ptr->video_clk->get_clock();
    if (type == SYNC_AUDIO_MASTER)
        return d_ptr->audio_clk->get_clock();
    return d_ptr->ext_clk->get_clock();
}

double HFFSourceControl::clock_diff(int type)
{
    if (type == master_sync_type())
        return 0;
    double c;
    if (type == SYNC_VIDEO_MASTER)
        c = d_ptr->video_clk->get_clock();
    else if (type == SYNC_AUDIO_MASTER)
        c =  d_ptr->audio_clk->get_clock();
    else
        c = d_ptr->ext_clk->get_clock();
    return c - master_clock();
}

void HFFSourceControl::set_pix_fmts(QList<int> value)
{
    d_ptr->video_ctl->set_pix_fmts(value);
}

void HFFSourceControl::set_default_window_size(int width, int height, AVRational sar)
{
    int max_width  = d_ptr->screen_size.isEmpty() ? INT_MAX : d_ptr->screen_size.width();
    int max_height = d_ptr->screen_size.isEmpty() ? INT_MAX : d_ptr->screen_size.height();
    if (max_width == INT_MAX && max_height == INT_MAX)
        max_height = height;
    auto rect = calc_display_rect(QRect(0, 0, max_width, max_height), QSize(width, height), sar);
    if (d_ptr->default_window_size == rect.size())
        return;
    d_ptr->default_window_size = rect.size();
    emit default_window_size_changed(rect.width(), rect.height());
}

void HFFSourceControl::set_screen_size(int width, int height)
{
    d_ptr->screen_size = QSize(width, height);
    d_ptr->window.setWidth(width);
    d_ptr->window.setHeight(height);
}

void HFFSourceControl::set_abort()
{
    d_ptr->abort_request = true;
    // TODO:
    //    SDL_Event event;

    //    event.type = FF_QUIT_EVENT;
    //    event.user.data1 = is;
    //    SDL_PushEvent(&event);

}

void HFFSourceControl::set_force_refresh()
{
    d_ptr->force_refresh = true;
}

// update current video pts
void HFFSourceControl::update_video_pts(double pts, int64_t /*pos*/, int serial)
{
    d_ptr->video_clk->set_clock(pts, serial);
    d_ptr->ext_clk->sync_clock(d_ptr->video_clk);
}

void HFFSourceControl::update_audio_pts(double pts, int serial, double time)
{
    d_ptr->audio_clk->set_clock(pts, serial, time);
    d_ptr->ext_clk->sync_clock(d_ptr->audio_clk);
}

bool HFFSourceControl::open(const QString &filename, AVInputFormat *iformat)
{
    try
    {
        auto str = filename.toStdString();
        d_ptr->filename = av_strdup(str.c_str());
        if (!d_ptr->filename)
        {
            av_log(nullptr, AV_LOG_FATAL, "Input file is empty.");
            return false;
        }
        d_ptr->abort_request = false;
        d_ptr->queue_attachments_request = false;
        d_ptr->force_refresh = false;
        d_ptr->paused = false;
        d_ptr->last_paused = false;
        d_ptr->seek_request = false;
        d_ptr->step = false;
        d_ptr->window = QRect();
        d_ptr->video_ctl->init(VIDEO_QUEUE_SIZE, true);
        d_ptr->audio_ctl->init(AUDIO_QUEUE_SIZE, true);
        d_ptr->subtitle_ctl->init(SUBTITLE_QUEUE_SIZE, false);
        d_ptr->video_clk->init(d_ptr->video_ctl->packets_serial());
        d_ptr->audio_clk->init(d_ptr->audio_ctl->packets_serial());
        d_ptr->ext_clk->init();

        if (!open_format_context(iformat))
            throw "";
        seek_to_start();
        if (!open_stream())
            throw "";
        return true;
    }
    catch (...)
    {
        av_log(nullptr, AV_LOG_FATAL, "Failed to open source control!\n");
        close();
        return false;
    }
}

void HFFSourceControl::close()
{
    d_ptr->abort_request = true;
    if (d_ptr->thread->isRunning())
        d_ptr->thread->wait();
    d_ptr->video_ctl->close();
    d_ptr->audio_ctl->close();
    d_ptr->subtitle_ctl->close();
    if (d_ptr->fmt_ctx)
        avformat_close_input(&d_ptr->fmt_ctx);
    av_free(d_ptr->filename);
}

void HFFSourceControl::start()
{
    d_ptr->video_ctl->start();
    d_ptr->audio_ctl->start();
    d_ptr->subtitle_ctl->start();
    d_ptr->thread->start();
}

void HFFSourceControl::wake()
{
    d_ptr->cond.wakeOne();
}

void HFFSourceControl::seek_to_start()
{
    // if seeking requested, we execute it
    if (d_ptr->start_time == AV_NOPTS_VALUE)
        return;

    auto time = d_ptr->start_time;
    // add the stream start time
    if (d_ptr->fmt_ctx->start_time != AV_NOPTS_VALUE)
        time += d_ptr->fmt_ctx->start_time;
    if (avformat_seek_file(d_ptr->fmt_ctx, -1, INT64_MIN, time, INT64_MAX, 0) < 0)
        av_log(nullptr, AV_LOG_WARNING, "Could not seek to position %0.3f\n", 1.0 * time / AV_TIME_BASE);
}

void HFFSourceControl::seek(int64_t pos, int64_t rel, bool by_bytes)
{
    if (d_ptr->seek_request)
        return;

    d_ptr->seek_pos = pos;
    d_ptr->seek_rel = rel;
    d_ptr->seek_flags &= ~AVSEEK_FLAG_BYTE;
    if (by_bytes)
        d_ptr->seek_flags |= AVSEEK_FLAG_BYTE;
    d_ptr->seek_request = true;
    wake();
}

void HFFSourceControl::seek_to(int x)
{
    if (d_ptr->seek_by_bytes || d_ptr->fmt_ctx->duration <= 0)
    {
        seek(x * avio_size(d_ptr->fmt_ctx->pb) / d_ptr->window.width(), 0, true);
        return;
    }

    int64_t ts;
    int ns, hh, mm, ss;
    int tns, thh, tmm, tss;
    double frac;
    tns  = d_ptr->fmt_ctx->duration / 1000000LL;
    thh  = tns / 3600;
    tmm  = (tns % 3600) / 60;
    tss  = (tns % 60);
    frac = x / d_ptr->window.width();
    ns   = frac * tns;
    hh   = ns / 3600;
    mm   = (ns % 3600) / 60;
    ss   = (ns % 60);
    av_log(nullptr, AV_LOG_INFO, "Seek to %2.0f%% (%2d:%02d:%02d) of total duration (%2d:%02d:%02d)\n", frac*100, hh, mm, ss, thh, tmm, tss);
    ts = frac * d_ptr->fmt_ctx->duration;
    if (d_ptr->fmt_ctx->start_time != AV_NOPTS_VALUE)
        ts += d_ptr->fmt_ctx->start_time;
    seek(ts, 0, false);
}

void HFFSourceControl::seek_section(int incr)
{
    double pos;
    if (d_ptr->seek_by_bytes)
    {
        pos = -1;
        if (pos < 0 && d_ptr->video_ctl->is_open())
            pos = d_ptr->video_ctl->frame_last_pos();
        if (pos < 0 && d_ptr->audio_ctl->is_open())
            pos = d_ptr->audio_ctl->frame_last_pos();
        if (pos < 0)
            pos = avio_tell(d_ptr->fmt_ctx->pb);
        if (d_ptr->fmt_ctx->bit_rate)
            incr *= d_ptr->fmt_ctx->bit_rate / 8.0;
        else
            incr *= 180000.0;
        pos += incr;
        seek(pos, incr, true);
    }
    else
    {
        pos = master_clock();
        if (isnan(pos))
            pos = 1.0 * d_ptr->seek_pos / AV_TIME_BASE;
        pos += incr;
        if (d_ptr->fmt_ctx->start_time != AV_NOPTS_VALUE && pos < 1.0 * d_ptr->fmt_ctx->start_time / AV_TIME_BASE)
            pos = 1.0 * d_ptr->fmt_ctx->start_time / AV_TIME_BASE;
        seek((int64_t)(pos * AV_TIME_BASE), (int64_t)(incr * AV_TIME_BASE), false);
    }
}

void HFFSourceControl::seek_chapter(int incr)
{
    int64_t pos = master_clock() * AV_TIME_BASE;
    uint i;

    if (d_ptr->fmt_ctx->nb_chapters <= 1)
        return;

    // find the current chapter
    for (i = 0; i < d_ptr->fmt_ctx->nb_chapters; i++)
    {
        AVChapter *ch = d_ptr->fmt_ctx->chapters[i];
        if (av_compare_ts(pos, AV_TIME_BASE_Q, ch->start, ch->time_base) < 0)
        {
            i--;
            break;
        }
    }

    i += incr;
    i = FFMAX(i, 0);
    if (i >= d_ptr->fmt_ctx->nb_chapters)
        return;

    av_log(nullptr, AV_LOG_VERBOSE, "Seeking to chapter %d.\n", i);
    seek(av_rescale_q(d_ptr->fmt_ctx->chapters[i]->start, d_ptr->fmt_ctx->chapters[i]->time_base, AV_TIME_BASE_Q), 0, false);
}

void HFFSourceControl::step_to_next_frame()
{
    // if the stream is paused unpause it, then step
    if (d_ptr->paused)
        toggle_pause();
    d_ptr->step = true;
}

void HFFSourceControl::switch_channel(int type)
{
    auto p = d_ptr->video_ctl->find_program();
    if (type == AVMEDIA_TYPE_VIDEO)
        d_ptr->video_ctl->switch_channel();
    if (type == AVMEDIA_TYPE_AUDIO)
        d_ptr->audio_ctl->switch_channel(p);
    if (type == AVMEDIA_TYPE_SUBTITLE)
        d_ptr->subtitle_ctl->switch_channel(p);
}

void HFFSourceControl::toggle_pause()
{
    if (d_ptr->paused)
    {
        d_ptr->video_ctl->add_frame_timer(av_gettime_relative() / 1000000.0 - d_ptr->video_clk->last_updated());
        if (d_ptr->read_pause_return != AVERROR(ENOSYS))
            d_ptr->video_clk->set_paused(false);
        d_ptr->video_clk->sync_clock();
    }
    d_ptr->ext_clk->sync_clock();
    d_ptr->paused = !d_ptr->paused;
    d_ptr->video_clk->set_paused(d_ptr->paused);
    d_ptr->audio_clk->set_paused(d_ptr->paused);
    d_ptr->ext_clk->set_paused(d_ptr->paused);
}

double HFFSourceControl::toggle_refresh()
{
    int ret;
    double remaining_time = 0.0;

    if (d_ptr->show_mode == SHOW_MODE_NONE || (d_ptr->paused && !d_ptr->force_refresh))
        return 0.0;

    if (!d_ptr->paused && master_sync_type() == SYNC_EXTERNAL_CLOCK && d_ptr->realtime)
        check_external_clock_speed();

    video_open();

    if (d_ptr->show_mode != SHOW_MODE_VIDEO && d_ptr->audio_ctl->is_open())
    {
        auto time = av_gettime_relative() / 1000000.0;
        if (d_ptr->force_refresh || d_ptr->last_vis_time + d_ptr->rdft_speed < time)
        {
            audio_display();
            d_ptr->last_vis_time = time;
        }
        remaining_time = d_ptr->last_vis_time + d_ptr->rdft_speed - time;
    }

    if (d_ptr->video_ctl->is_open())
    {
        while (d_ptr->video_ctl->frame_remaining() > 0)
        {
            ret = d_ptr->video_ctl->frame_handle(d_ptr->paused, d_ptr->step, &remaining_time);
            if (ret < 0)
                break;
            if (ret == 0)
            {
                d_ptr->video_ctl->frame_next();
                continue;
            }

            if (d_ptr->subtitle_ctl->is_open())
            {
                while (d_ptr->subtitle_ctl->frame_remaining() > 0)
                {
                    if (d_ptr->subtitle_ctl->frame_handle(d_ptr->video_clk->pts()) < 0)
                        break;
                    d_ptr->subtitle_ctl->frame_next();
                }
            }

            d_ptr->video_ctl->frame_next();
            d_ptr->force_refresh = true;
            if (d_ptr->step && !d_ptr->paused)
                toggle_pause();
            break;
        }
        if (d_ptr->force_refresh && d_ptr->show_mode == SHOW_MODE_VIDEO && d_ptr->video_ctl->frame_remaining())
            video_display();
    }
    d_ptr->force_refresh = false;

    if (d_ptr->show_status)
    {
        AVBPrint buf;
        static int64_t last_time;
        int64_t cur_time;
        int aqsize, vqsize, sqsize;
        double av_diff;

        cur_time = av_gettime_relative();
        if (!last_time || (cur_time - last_time) >= 30000)
        {
            aqsize = 0;
            vqsize = 0;
            sqsize = 0;
            if (d_ptr->audio_ctl->is_open())
                aqsize = d_ptr->audio_ctl->packets_size();
            if (d_ptr->video_ctl->is_open())
                vqsize = d_ptr->video_ctl->packets_size();
            if (d_ptr->subtitle_ctl->is_open())
                sqsize = d_ptr->subtitle_ctl->packets_size();
            av_diff = 0;
            if (d_ptr->audio_ctl->is_open() && d_ptr->video_ctl->is_open())
                av_diff = d_ptr->audio_clk->get_clock() - d_ptr->video_clk->get_clock();
            else if (d_ptr->video_ctl->is_open())
                av_diff = master_clock() - d_ptr->video_clk->get_clock();
            else if (d_ptr->audio_ctl->is_open())
                av_diff = master_clock() - d_ptr->audio_clk->get_clock();

            av_bprint_init(&buf, 0, AV_BPRINT_SIZE_AUTOMATIC);
            av_bprintf(&buf,
                       "%7.2f %s:%7.3f aq=%5dKB vq=%5dKB sq=%5dB \r",
                       master_clock(),
                       (d_ptr->audio_ctl->is_open() && d_ptr->video_ctl->is_open()) ? "A-V" : (d_ptr->video_ctl->is_open() ? "M-V" : (d_ptr->audio_ctl->is_open() ? "M-A" : "   ")),
                       av_diff,
                       aqsize / 1024,
                       vqsize / 1024,
                       sqsize);
            av_log(nullptr, AV_LOG_INFO, "%s", buf.str);

            fflush(stderr);
            av_bprint_finalize(&buf, nullptr);
            last_time = cur_time;
        }
    }
    return remaining_time;
}

int HFFSourceControl::audio_open(int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params)
{
    return d_ptr->service->audio_open(d_ptr->audio_ctl, wanted_channel_layout, wanted_nb_channels, wanted_sample_rate, hw_params);
}

void HFFSourceControl::audio_update(uint8_t *stream, int len, int min_buf_size)
{
    d_ptr->audio_ctl->frame_handle(d_ptr->paused, d_ptr->show_mode != SHOW_MODE_VIDEO, stream, len, min_buf_size);
}

void HFFSourceControl::audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len)
{
    d_ptr->service->audio_fill_stream(stream, buf, index, len);
}

void HFFSourceControl::audio_upload(QRect rect, int channels, int16_t *sample, int start, int size)
{
    d_ptr->service->audio_upload(rect, channels, sample, start, size);
}

void HFFSourceControl::audio_upload(QRect rect, int channels, int freq, float **data, int start)
{
    d_ptr->service->audio_upload(rect, channels, freq, data, start);
}

void HFFSourceControl::video_open()
{
    if (!d_ptr->window.isEmpty())
        return;
    d_ptr->window.setSize(d_ptr->screen_size.isEmpty() ? d_ptr->default_window_size : d_ptr->screen_size);
    d_ptr->service->video_open(d_ptr->window.width(), d_ptr->window.height());
}

void HFFSourceControl::subtitle_upload(HFFFrame *frame)
{
    d_ptr->service->subtitle_upload(frame);
}

bool HFFSourceControl::is_skip()
{
    return d_ptr->paused && (!strcmp(d_ptr->fmt_ctx->iformat->name, "rtsp") || (d_ptr->fmt_ctx->pb && !strncmp(d_ptr->filename, "mmsh:", 5)));
}

bool HFFSourceControl::is_buffer_full()
{
    if (d_ptr->infinite_buffer == 1)
        return false;
    if (d_ptr->video_ctl->packets_size() + d_ptr->audio_ctl->packets_size() + d_ptr->subtitle_ctl->packets_size() > MAX_PACKET_QUEUE_SIZE)
        return true;
    if (d_ptr->video_ctl->has_enough_packets() && d_ptr->audio_ctl->has_enough_packets() && d_ptr->subtitle_ctl->has_enough_packets())
        return true;
    return false;
}

bool HFFSourceControl::open_format_context(AVInputFormat *iformat)
{
    bool scan_all_pmts = false;
    AVDictionaryEntry *t;

    d_ptr->fmt_ctx = avformat_alloc_context();
    if (!d_ptr->fmt_ctx)
    {
        av_log(nullptr, AV_LOG_FATAL, "Could not allocate context.\n");
        return false;
    }
    d_ptr->fmt_ctx->interrupt_callback.callback = demuxing_interrupt;
    d_ptr->fmt_ctx->interrupt_callback.opaque = this;

    if (!av_dict_get(format_opts, "scan_all_pmts", nullptr, AV_DICT_MATCH_CASE))
    {
        av_dict_set(&format_opts, "scan_all_pmts", "1", AV_DICT_DONT_OVERWRITE);
        scan_all_pmts = true;
    }
    if (avformat_open_input(&d_ptr->fmt_ctx, d_ptr->filename, iformat, &format_opts) < 0)
    {
        av_log(nullptr, AV_LOG_FATAL, "Could not open input stream.\n");
        return false;
    }
    if (scan_all_pmts)
        av_dict_set(&format_opts, "scan_all_pmts", nullptr, AV_DICT_MATCH_CASE);
    if ((t = av_dict_get(format_opts, "", nullptr, AV_DICT_IGNORE_SUFFIX)))
    {
        av_log(nullptr, AV_LOG_ERROR, "Option %s not found.\n", t->key);
        return false;
    }

    if (d_ptr->genpts)
        d_ptr->fmt_ctx->flags |= AVFMT_FLAG_GENPTS;

    av_format_inject_global_side_data(d_ptr->fmt_ctx);

    if (d_ptr->find_stream_info)
    {
        auto opts = setup_find_stream_info_opts(d_ptr->fmt_ctx, codec_opts);
        auto orig = d_ptr->fmt_ctx->nb_streams;
        auto ret = avformat_find_stream_info(d_ptr->fmt_ctx, opts);
        for (uint i = 0; i < orig; i++)
            av_dict_free(&opts[i]);
        av_freep(&opts);
        if (ret < 0)
        {
            av_log(nullptr, AV_LOG_WARNING, "%s: could not find codec parameters.\n", d_ptr->filename);
            return false;
        }
    }

    if (d_ptr->fmt_ctx->pb)
        d_ptr->fmt_ctx->pb->eof_reached = 0; // FIXME hack, ffplay maybe should not use avio_feof() to test for the end
    d_ptr->realtime = is_realtime(d_ptr->fmt_ctx);
    if (d_ptr->seek_by_bytes < 0)
        d_ptr->seek_by_bytes = !!(d_ptr->fmt_ctx->iformat->flags & AVFMT_TS_DISCONT) && strcmp("ogg", d_ptr->fmt_ctx->iformat->name);
    if (d_ptr->infinite_buffer < 0 && d_ptr->realtime)
        d_ptr->infinite_buffer = 1;

    if (d_ptr->show_status)
        av_dump_format(d_ptr->fmt_ctx, 0, d_ptr->filename, 0);

    return true;
}

bool HFFSourceControl::open_stream()
{
    int st_index[AVMEDIA_TYPE_NB];

    memset(st_index, -1, sizeof(st_index));
    for (uint i = 0; i < d_ptr->fmt_ctx->nb_streams; i++)
    {
        auto st = d_ptr->fmt_ctx->streams[i];
        auto type = st->codecpar->codec_type;
        st->discard = AVDISCARD_ALL;
        if (type >= 0 && d_ptr->wanted_stream_spec[type] && st_index[type] == -1)
            if (avformat_match_stream_specifier(d_ptr->fmt_ctx, st, d_ptr->wanted_stream_spec[type]) > 0)
                st_index[type] = i;
    }
    for (int i = 0; i < AVMEDIA_TYPE_NB; i++)
    {
        if (d_ptr->wanted_stream_spec[i] && st_index[i] == -1)
        {
            av_log(nullptr, AV_LOG_ERROR, "Stream specifier %s does not match any %s stream.\n", d_ptr->wanted_stream_spec[i], av_get_media_type_string((AVMediaType)i));
            st_index[i] = INT_MAX;
        }
    }

    if (!d_ptr->video_disable)
        st_index[AVMEDIA_TYPE_VIDEO] = av_find_best_stream(d_ptr->fmt_ctx, AVMEDIA_TYPE_VIDEO, st_index[AVMEDIA_TYPE_VIDEO], -1, nullptr, 0);
    if (!d_ptr->audio_disable)
        st_index[AVMEDIA_TYPE_AUDIO] = av_find_best_stream(d_ptr->fmt_ctx, AVMEDIA_TYPE_AUDIO, st_index[AVMEDIA_TYPE_AUDIO], st_index[AVMEDIA_TYPE_VIDEO], nullptr, 0);
    if (!d_ptr->video_disable && !d_ptr->subtitle_disable)
        st_index[AVMEDIA_TYPE_SUBTITLE] = av_find_best_stream(d_ptr->fmt_ctx, AVMEDIA_TYPE_SUBTITLE, st_index[AVMEDIA_TYPE_SUBTITLE], (st_index[AVMEDIA_TYPE_AUDIO] >= 0 ? st_index[AVMEDIA_TYPE_AUDIO] : st_index[AVMEDIA_TYPE_VIDEO]), nullptr, 0);

    if (st_index[AVMEDIA_TYPE_VIDEO] >= 0)
    {
        auto st = d_ptr->fmt_ctx->streams[st_index[AVMEDIA_TYPE_VIDEO]];
        auto codecpar = st->codecpar;
        auto sar = av_guess_sample_aspect_ratio(d_ptr->fmt_ctx, st, nullptr);
        if (codecpar->width)
            set_default_window_size(codecpar->width, codecpar->height, sar);
    }

    // open the streams
    if (st_index[AVMEDIA_TYPE_VIDEO] >= 0)
        d_ptr->video_ctl->open(st_index[AVMEDIA_TYPE_VIDEO], d_ptr->fmt_ctx);
//    if (st_index[AVMEDIA_TYPE_AUDIO] >= 0)
//        d_ptr->audio_ctl->open(st_index[AVMEDIA_TYPE_AUDIO], d_ptr->fmt_ctx);
//    if (st_index[AVMEDIA_TYPE_SUBTITLE] >= 0)
//        d_ptr->subtitle_ctl->open(st_index[AVMEDIA_TYPE_SUBTITLE], d_ptr->fmt_ctx);

    if (d_ptr->show_mode == SHOW_MODE_NONE)
        d_ptr->show_mode = d_ptr->video_ctl->is_open() ? SHOW_MODE_VIDEO : SHOW_MODE_RDFT;

    if (!d_ptr->video_ctl->is_open() && !d_ptr->audio_ctl->is_open())
    {
        av_log(nullptr, AV_LOG_FATAL, "Failed to open file '%s' or configure filtergraph.\n", d_ptr->filename);
        return false;
    }
    return true;
}

void HFFSourceControl::run()
{
    for (;;)
    {
        if (d_ptr->abort_request)
            break;

        handle_paused();
        if (is_skip())
        {
            av_usleep(10000);
            continue;
        }
        handle_seek_request();
        if (!handle_queue_attachments_request())
            break;
        if (is_buffer_full())
        {
            wait_timeout(10);
            continue;
        }
        if (!handle_loop_request())
            break;
        if (!handle_read_frame())
            break;
    }
}

void HFFSourceControl::wait_timeout(ulong time)
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->cond.wait(&d_ptr->mutex, time);
}

void HFFSourceControl::check_external_clock_speed()
{
    auto factor1 = d_ptr->video_ctl->speed_factor();
    auto factor2 = d_ptr->audio_ctl->speed_factor();
    auto speed = d_ptr->ext_clk->speed();
    if (factor1 < 0 || factor2 < 0)
        d_ptr->ext_clk->set_clock_speed(FFMAX(EXTERNAL_CLOCK_SPEED_MIN, speed - EXTERNAL_CLOCK_SPEED_STEP));
    else if (factor1 > 0 && factor2 > 0)
        d_ptr->ext_clk->set_clock_speed(FFMAX(EXTERNAL_CLOCK_SPEED_MIN, speed + EXTERNAL_CLOCK_SPEED_STEP));
    else if (speed != 1.0)
        d_ptr->ext_clk->set_clock_speed(speed + EXTERNAL_CLOCK_SPEED_STEP * (1.0 - speed) / fabs(1.0 - speed));
}

void HFFSourceControl::audio_display()
{
    d_ptr->audio_ctl->display(d_ptr->paused, d_ptr->show_mode == SHOW_MODE_WAVES, d_ptr->window);
}

void HFFSourceControl::video_display()
{
    auto vp = d_ptr->video_ctl->frame_peek_last();
    auto sp = d_ptr->subtitle_ctl->display(vp->pts, vp->width, vp->height);
    auto rect = calc_display_rect(d_ptr->window, QSize(vp->width, vp->height), vp->sar);
    d_ptr->service->video_upload(rect, vp, sp);
}

void HFFSourceControl::handle_open_stream_finished()
{
    d_ptr->eof = false;
    if (sender() == d_ptr->video_ctl)
        d_ptr->queue_attachments_request = true;
    if (sender() == d_ptr->audio_ctl)
        d_ptr->service->audio_pause(0);
}

void HFFSourceControl::handle_close_stream_finished()
{
    if (sender() == d_ptr->audio_ctl)
        d_ptr->service->audio_close();
}

void HFFSourceControl::handle_paused()
{
    if (d_ptr->paused == d_ptr->last_paused)
        return;
    d_ptr->last_paused = d_ptr->paused;
    if (d_ptr->paused)
        d_ptr->read_pause_return = av_read_pause(d_ptr->fmt_ctx);
    else
        av_read_play(d_ptr->fmt_ctx);
}

void HFFSourceControl::handle_seek_request()
{
    if (!d_ptr->seek_request)
        return;

    // FIXME the +-2 is due to rounding being not done in the correct direction in generation of the seek_pos/seek_rel variables
    auto val = d_ptr->seek_pos;
    auto min = d_ptr->seek_rel > 0 ? val - d_ptr->seek_rel + 2: INT64_MIN;
    auto max = d_ptr->seek_rel < 0 ? val - d_ptr->seek_rel - 2: INT64_MAX;

    if (avformat_seek_file(d_ptr->fmt_ctx, -1, min, val, max, d_ptr->seek_flags) < 0)
    {
        av_log(nullptr, AV_LOG_ERROR, "%s: error while seeking\n", d_ptr->fmt_ctx->url);
    }
    else
    {
        d_ptr->video_ctl->packet_put_flush();
        d_ptr->audio_ctl->packet_put_flush();
        d_ptr->subtitle_ctl->packet_put_flush();
        d_ptr->ext_clk->set_clock((d_ptr->seek_flags & AVSEEK_FLAG_BYTE) ? NAN : 1.0 * val / AV_TIME_BASE, 0);
    }
    d_ptr->seek_request = false;
    d_ptr->queue_attachments_request = true;
    d_ptr->eof = false;
    if (d_ptr->paused)
        step_to_next_frame();
}

bool HFFSourceControl::handle_queue_attachments_request()
{
    if (!d_ptr->queue_attachments_request)
        return true;
    if (!d_ptr->video_ctl->packet_put_attached())
        return false;
    d_ptr->queue_attachments_request = false;
    return true;
}

bool HFFSourceControl::handle_loop_request()
{
    if (d_ptr->paused)
        return true;

    if (d_ptr->audio_ctl->is_finish() && d_ptr->video_ctl->is_finish())
    {
        if (d_ptr->loop_times > 1)
        {
            d_ptr->loop_times--;
            seek(d_ptr->start_time != AV_NOPTS_VALUE ? d_ptr->start_time : 0, 0, false);
        }
        else if (d_ptr->auto_exit)
            return false;
    }
    return true;
}

bool HFFSourceControl::handle_read_frame()
{
    AVPacket pkt1, *pkt = &pkt1;
    auto ret = av_read_frame(d_ptr->fmt_ctx, pkt);
    if (ret < 0)
    {
        if ((ret == AVERROR_EOF || avio_feof(d_ptr->fmt_ctx->pb)) && !d_ptr->eof)
        {
            d_ptr->video_ctl->packet_put_null();
            d_ptr->audio_ctl->packet_put_null();
            d_ptr->subtitle_ctl->packet_put_null();
            d_ptr->eof = true;
        }
        if (d_ptr->fmt_ctx->pb && d_ptr->fmt_ctx->pb->error)
            return false;
        wait_timeout(10);
        return true;
    }

    d_ptr->eof = false;
    // check if packet is in play range specified by user, then queue, otherwise discard
    auto stream = d_ptr->fmt_ctx->streams[pkt->stream_index];
    auto stream_start_time = stream->start_time;
    if (stream_start_time == AV_NOPTS_VALUE)
        stream_start_time = 0;
    auto pkt_ts = pkt->pts == AV_NOPTS_VALUE ? pkt->dts : pkt->pts;
    auto pkt_in_play_range = d_ptr->duration == AV_NOPTS_VALUE || (pkt_ts - stream_start_time) * av_q2d(stream->time_base) - (d_ptr->start_time != AV_NOPTS_VALUE ? d_ptr->start_time : 0) / 1000000.0 <= d_ptr->duration / 1000000.0;
    if (pkt_in_play_range)
    {
        if (d_ptr->audio_ctl->packet_put(pkt) ||
            d_ptr->video_ctl->packet_put(pkt) ||
            d_ptr->subtitle_ctl->packet_put(pkt))
            return true;
    }
    av_packet_unref(pkt);
    return true;
}

HE_CONTROL_END_NAMESPACE
