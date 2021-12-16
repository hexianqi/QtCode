/***************************************************************************************************
**      2020-07-28  HFFSourceControl
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

struct AVInputFormat;
struct AVRational;

HE_BEGIN_NAMESPACE

struct HFFAudioParams;
struct HFFFrame;
class HFFPlayerService;
class HFFSourceControlPrivate;

class HFFSourceControl : public QObject
{
    Q_OBJECT

public:
    enum SyncMode
    {
        SYNC_AUDIO_MASTER,
        SYNC_VIDEO_MASTER,
        SYNC_EXTERNAL_CLOCK     // synchronize to an external clock
    };

    enum ShowMode
    {
        SHOW_MODE_NONE = -1,
        SHOW_MODE_VIDEO = 0,
        SHOW_MODE_WAVES,
        SHOW_MODE_RDFT,
        SHOW_MODE_NB
    };

public:
    explicit HFFSourceControl(HFFPlayerService *service);
    ~HFFSourceControl() override;

signals:
    void default_window_size_changed(int width, int height);

public:
    bool abort_request();
    QString title();
    int master_sync_type();
    double master_clock();
    double clock_diff(int type);

public:
    void set_pix_fmts(QList<int> value);
    void set_default_window_size(int width, int height, AVRational sar);
    void set_screen_size(int width, int height);
    void set_abort();
    void set_force_refresh();
    void update_video_pts(double pts, int64_t pos, int serial);
    void update_audio_pts(double pts, int serial, double time);

public:
    bool open(const QString &filename, AVInputFormat *iformat);
    void close();
    void start();
    void wake();

public:
    void seek_to_start();
    void seek(int64_t pos, int64_t rel, bool by_bytes);
    void seek_to(int x);
    void seek_section(int incr);
    void seek_chapter(int incr);
    void step_to_next_frame();
    void switch_channel(int type);
    void toggle_pause();
    double toggle_refresh();

public:
    int audio_open(int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params);
    void audio_update(uint8_t *stream, int len, int min_buf_size);
    void audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len);
    void audio_upload(QRect rect, int channels, int16_t *sample, int start, int size);
    void audio_upload(QRect rect, int channels, int freq, float **data, int start);
    void video_open();
    void subtitle_upload(HFFFrame *frame);

protected:
    bool is_skip();
    bool is_buffer_full();

protected:
    bool open_format_context(AVInputFormat *iformat);
    bool open_stream();
    void run();
    void wait_timeout(ulong time = 10);
    void check_external_clock_speed();
    void audio_display();
    void video_display();

protected:
    void handle_open_stream_finished();
    void handle_close_stream_finished();
    void handle_paused();
    void handle_seek_request();
    bool handle_queue_attachments_request();
    bool handle_loop_request();
    bool handle_read_frame();

protected:
    QScopedPointer<HFFSourceControlPrivate> d_ptr;

    friend class HFFSourceControlThread;
};

HE_END_NAMESPACE

