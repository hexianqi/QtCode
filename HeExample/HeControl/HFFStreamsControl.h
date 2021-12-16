/***************************************************************************************************
**      2020-07-28  HFFStreamsControl
***************************************************************************************************/

#pragma once

#include "HFFConfig.h"
#include <QtCore/QObject>

struct AVFormatContext;
struct AVPacket;
struct AVFrame;
struct AVProgram;

HE_BEGIN_NAMESPACE

struct HFFFrame;
class HFFSourceControl;
class HFFStreamsControlPrivate;

class HFFStreamsControl : public QObject
{
    Q_OBJECT

public:
    explicit HFFStreamsControl(HFFSourceControl *source);
    ~HFFStreamsControl() override;

signals:
    void open_finished();
    void close_finished();

public:
    bool is_open();
    bool is_finish();
    int *packets_serial();
    int packets_size();
    int frame_remaining();
    int frame_rindex_shown();
    int speed_factor();
    bool has_enough_packets();

public:
    void init(int max_size, bool keep_last);
    bool open(int index, AVFormatContext *ctx);
    void close();
    void start();
    void abort();
    virtual void switch_channel(AVProgram *p = nullptr) = 0;

public:
    virtual bool packet_put(AVPacket *pkt);
    void packet_put_flush();
    void packet_put_null();
    bool packet_put_attached();

public:
    int64_t frame_last_pos();
    HFFFrame *frame_peek_last();
    void frame_next();

protected:
    HFFStreamsControl(HFFStreamsControlPrivate &p, HFFSourceControl *source);

protected:
    bool open_codec_context(int index);
    virtual bool open_else() = 0;
    virtual void close_else() = 0;
    virtual void run() = 0;

protected:
    QScopedPointer<HFFStreamsControlPrivate> d_ptr;

private:
    void init();

    friend class HFFStreamsControlThread;
};

class HFFVideoStreamsControlPrivate;

class HFFVideoStreamsControl : public HFFStreamsControl
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFFVideoStreamsControl)

public:
    explicit HFFVideoStreamsControl(HFFSourceControl *source);
    ~HFFVideoStreamsControl() override;

public:
    AVProgram *find_program();
    void switch_channel(AVProgram *p = nullptr) override;
    bool packet_put(AVPacket *pkt) override;
    void set_pix_fmts(QList<int> value);
    void add_frame_timer(double value);
    int frame_handle(bool paused, int step, double *remaining_time);

protected:
    bool open_else() override;
    void close_else() override;
    void run() override;

protected:
    bool is_frame_drop();
    int decode(AVFrame *frame);
    int frame_add(AVFrame *frame, double pts, double duration, int serial);
    double compute_frame_duration(HFFFrame *current, HFFFrame *next);
    double compute_target_delay(double delay);

#if CONFIG_AVFILTER
protected:
    bool configure_filters(const QString &filters, AVFrame *frame);
#endif
};

class HFFAudioStreamsControlPrivate;

class HFFAudioStreamsControl : public HFFStreamsControl
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFFAudioStreamsControl)

public:
    explicit HFFAudioStreamsControl(HFFSourceControl *source);
    ~HFFAudioStreamsControl() override;

public:
    void frame_handle(bool paused, bool display, uint8_t *stream, int len, int min_buf_size);
    void display(bool paused, bool show_wave, QRect rect);
    void switch_channel(AVProgram *p = nullptr) override;

protected:
    bool open_else() override;
    void close_else() override;
    void run() override;

protected:
    int decode();
    int synchronize(int nb_samples);
    void update_sample_display(short *samples, int samples_size);
    int frame_add(AVFrame *frame, double pts, double duration, int serial);
    int compute_i_start(bool paused, bool show_wave, int data_used);

#if CONFIG_AVFILTER
    bool configure_filters(const QString &filters, bool force_output_format);
#endif
};

class HFFSubtitleStreamsControlPrivate;

class HFFSubtitleStreamsControl : public HFFStreamsControl
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFFSubtitleStreamsControl)

public:
    explicit HFFSubtitleStreamsControl(HFFSourceControl *source);
    ~HFFSubtitleStreamsControl() override;

public:
    int frame_handle(double pts);
    HFFFrame *display(double pts, int width, int height);
    void switch_channel(AVProgram *p = nullptr) override;

protected:
    bool open_else() override;
    void close_else() override;
    void run() override;
};

HE_END_NAMESPACE

