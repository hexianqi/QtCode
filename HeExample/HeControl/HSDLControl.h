/***************************************************************************************************
**      2020-07-21  HSDLControl
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "SDL2/SDL_blendmode.h"
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QRect>

union SDL_Event;
struct SDL_Texture;
struct AVFrame;

HE_BEGIN_NAMESPACE

struct HFFAudioParams;
struct HFFFrame;
class HFFPlayerService;
class HSDLControlPrivate;

class HSDLControl : public QObject
{
    Q_OBJECT

public:
    explicit HSDLControl(HFFPlayerService *service);
    ~HSDLControl() override;

signals:
    void exit_request();
    void pause_request();
    void step_request();
    void seek_to_request(int x);
    void seek_section_request(int incr);
    void seek_chapter_request(int incr);
    void switch_channel_request(int type);
    void force_refresh_request();
    void screen_size_changed(int width, int height);
    void display_request(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame);

public:
    QList<int> av_pix_fmts();

public:
    bool init(QVariantMap param = QVariantMap());
    void destroy();
    void start();
    void test();

public:
    void toggle_full_screen();
    void toggle_mute();
    void update_volume(int sign, double step);

public:
    int audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params);
    void audio_close();
    void audio_pause(int pause);
    void audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len);
    void audio_upload(QRect rect, int channels, int16_t *sample, int start, int size);
    void audio_upload(QRect rect, int channels, int freq, float **data, int start);
    void video_open(int width, int height);
    void video_upload(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame);
    void subtitle_upload(HFFFrame *frame);

protected:
    bool is_exit_event(SDL_Event *event);

protected:
    void set_yuv_conversion_mode(AVFrame *frame);
    bool texture_realloc(SDL_Texture **texture, uint format, int width, int height, SDL_BlendMode mode, bool init);
    bool video_upload(SDL_Texture **texture, AVFrame *frame);
    void video_display(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame = nullptr);
    void fill_rectangle(int x, int y, int w, int h);
    void refresh_loop_wait_event(SDL_Event *event);

protected:
    void stop();
    void run();

protected:
    QScopedPointer<HSDLControlPrivate> d_ptr;

    friend class HSDLControlThread;
};

HE_END_NAMESPACE

