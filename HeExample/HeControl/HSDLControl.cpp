#include "HSDLControl_p.h"
#include "HFFPlayerService.h"
#include "HFFSourceControl.h"
#include "HFFmpeg.h"
#include "HFFTypes.h"
#include <QtCore/QRect>
#include <QtCore/QThread>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

#define USE_ONEPASS_SUBTITLE_RENDER 1

#define SDL_STOP_EVENT    (SDL_USEREVENT + 2)

// Minimum SDL audio buffer size, in samples.
#define SDL_AUDIO_MIN_BUFFER_SIZE 512
// Calculate actual buffer size keeping in mind not cause too frequent audio callbacks
#define SDL_AUDIO_MAX_CALLBACKS_PER_SEC 30

// Step size for volume control in dB
#define SDL_VOLUME_STEP (0.75)

// polls for possible required screen refresh at least this often, should be less than 1/fps
#define SDL_REFRESH_RATE 0.01

#define CURSOR_HIDE_DELAY 1000

unsigned sws_flags = SWS_BICUBIC;

// prepare a new audio buffer
void audio_callback(void *opaque, uint8_t *stream, int len)
{
    auto source = static_cast<HFFSourceControl *>(opaque);
    source->audio_update(stream, len, SDL_AUDIO_MIN_BUFFER_SIZE);
}

SDL_Rect convert(QRect value)
{
    return { value.x(), value.y(), value.width(), value.height() };
}

class HSDLControlThread : public QThread
{
public:
    HSDLControlThread(HSDLControl *control);

protected:
    void run() override;

private:
    HSDLControl *_control;
};

HSDLControlThread::HSDLControlThread(HSDLControl *control) :
    QThread(control)
{
    _control = control;
}

void HSDLControlThread::run()
{
    _control->run();
}

HSDLControlPrivate::HSDLControlPrivate()
{
    texture_formats.insert(SDL_PIXELFORMAT_RGB332,   AV_PIX_FMT_RGB8);
    texture_formats.insert(SDL_PIXELFORMAT_RGB444,   AV_PIX_FMT_RGB444);
    texture_formats.insert(SDL_PIXELFORMAT_RGB555,   AV_PIX_FMT_RGB555);
    texture_formats.insert(SDL_PIXELFORMAT_BGR555,   AV_PIX_FMT_BGR555);
    texture_formats.insert(SDL_PIXELFORMAT_RGB565,   AV_PIX_FMT_RGB565);
    texture_formats.insert(SDL_PIXELFORMAT_BGR565,   AV_PIX_FMT_BGR565);
    texture_formats.insert(SDL_PIXELFORMAT_RGB24,    AV_PIX_FMT_RGB24);
    texture_formats.insert(SDL_PIXELFORMAT_BGR24,    AV_PIX_FMT_BGR24);
    texture_formats.insert(SDL_PIXELFORMAT_RGB888,   AV_PIX_FMT_0RGB32);
    texture_formats.insert(SDL_PIXELFORMAT_BGR888,   AV_PIX_FMT_0BGR32);
    texture_formats.insert(SDL_PIXELFORMAT_RGBX8888, AV_PIX_FMT_NE(RGB0, 0BGR));
    texture_formats.insert(SDL_PIXELFORMAT_BGRX8888, AV_PIX_FMT_NE(BGR0, 0RGB));
    texture_formats.insert(SDL_PIXELFORMAT_ARGB8888, AV_PIX_FMT_RGB32);
    texture_formats.insert(SDL_PIXELFORMAT_RGBA8888, AV_PIX_FMT_RGB32_1);
    texture_formats.insert(SDL_PIXELFORMAT_ABGR8888, AV_PIX_FMT_BGR32);
    texture_formats.insert(SDL_PIXELFORMAT_BGRA8888, AV_PIX_FMT_BGR32_1);
    texture_formats.insert(SDL_PIXELFORMAT_IYUV,     AV_PIX_FMT_YUV420P);
    texture_formats.insert(SDL_PIXELFORMAT_YUY2,     AV_PIX_FMT_YUYV422);
    texture_formats.insert(SDL_PIXELFORMAT_UYVY,     AV_PIX_FMT_UYVY422);
    texture_formats.insert(SDL_PIXELFORMAT_UNKNOWN,  AV_PIX_FMT_NONE);
}

bool HSDLControlPrivate::init()
{
    int flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (audio_disable)
    {
        flags &= ~SDL_INIT_AUDIO;
    }
    else
    {
        // Try to work around an occasional ALSA buffer underflow issue when the
        // period size is NPOT due to ALSA resampling by forcing the buffer size.
        if (!SDL_getenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE"))
            SDL_setenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE", "1", 1);
    }
    if (video_disable)
        flags &= ~SDL_INIT_VIDEO;
    if (SDL_Init(flags))
    {
        qFatal("Could not initialize SDL - %s", SDL_GetError());
        return false;
    }

    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

    if (!video_disable)
    {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
        if (always_on_top)
            flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;
        else
            flags |= SDL_WINDOW_RESIZABLE;
        window = SDL_CreateWindow(title.toStdString().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, default_width, default_height, flags);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        if (window)
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (!renderer)
            {
                qWarning("Failed to initialize a hardware accelerated renderer: %s", SDL_GetError());
                renderer = SDL_CreateRenderer(window, -1, 0);
            }
            if (renderer)
            {
                renderer_info = new SDL_RendererInfo();
                if (!SDL_GetRendererInfo(renderer, renderer_info))
                    qInfo("Initialized %s renderer.\n", renderer_info->name);
            }
        }
        if (!window || !renderer || renderer_info->num_texture_formats < 1)
        {
            qFatal("Failed to create window or renderer: %s", SDL_GetError());
            destroy();
            return false;
        }
    }
    return true;
}

void HSDLControlPrivate::destroy()
{
    if (video_texture)
        SDL_DestroyTexture(video_texture);
    if (audio_texture)
        SDL_DestroyTexture(audio_texture);
    if (subtitle_texture)
        SDL_DestroyTexture(subtitle_texture);
    if (renderer_info)
        delete renderer_info;
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

int HSDLControlPrivate::pix_fmt(int format)
{
    if (texture_formats.values().contains(format))
        return texture_formats.key(format);
    return SDL_PIXELFORMAT_UNKNOWN;
}

SDL_BlendMode HSDLControlPrivate::blend_mode(int format)
{
    if (format == AV_PIX_FMT_RGB32 || format == AV_PIX_FMT_RGB32_1 || format == AV_PIX_FMT_BGR32 || format == AV_PIX_FMT_BGR32_1)
        return SDL_BLENDMODE_BLEND;
    return SDL_BLENDMODE_NONE;
}

HSDLControl::HSDLControl(HFFPlayerService *service) :
    QObject(service),
    d_ptr(new HSDLControlPrivate)
{
    d_ptr->service = service;
    d_ptr->thread = new HSDLControlThread(this);
    connect(this, &HSDLControl::display_request, this, &HSDLControl::video_display);
}

HSDLControl::~HSDLControl()
{
    destroy();
}

QList<int> HSDLControl::av_pix_fmts()
{
    if (d_ptr->renderer_info == nullptr)
        return { AV_PIX_FMT_NONE };
    QList<int> list;
    for (uint i = 0; i < d_ptr->renderer_info->num_texture_formats; i++)
    {
        auto key = d_ptr->renderer_info->texture_formats[i];
        if (d_ptr->texture_formats.contains(key))
            list << d_ptr->texture_formats.value(key);
    }
    list << AV_PIX_FMT_NONE;
    return list;
}

bool HSDLControl::init(QVariantMap param)
{
    if (param.contains("audio_disable"))
        d_ptr->audio_disable = param.value("audio_disable").toBool();
    if (param.contains("display_disable"))
        d_ptr->video_disable = param.value("video_disable").toBool();
    if (param.contains("always_on_top"))
        d_ptr->always_on_top = param.value("always_on_top").toBool();
    if (param.contains("borderless"))
        d_ptr->borderless = param.value("borderless").toBool();
    return d_ptr->init();
}

void HSDLControl::destroy()
{
    stop();
    d_ptr->destroy();
}

void HSDLControl::start()
{
    d_ptr->last_mouse_move_time.restart();
    d_ptr->last_mouse_click_time.restart();
    d_ptr->thread->start();
}

void HSDLControl::toggle_full_screen()
{
    d_ptr->full_screen = !d_ptr->full_screen;
    SDL_SetWindowFullscreen(d_ptr->window, d_ptr->full_screen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    emit force_refresh_request();
}

void HSDLControl::toggle_mute()
{
    d_ptr->muted = !d_ptr->muted;
}

void HSDLControl::update_volume(int sign, double step)
{
    double level = d_ptr->audio_volume ? 20 * log(1.0 * d_ptr->audio_volume / SDL_MIX_MAXVOLUME) / log(10) : -1000.0;
    int volume = lrint(SDL_MIX_MAXVOLUME * pow(10.0, (level + sign * step) / 20.0));
    d_ptr->audio_volume = qBound(0, d_ptr->audio_volume == volume ? d_ptr->audio_volume + sign : volume, SDL_MIX_MAXVOLUME);
}

int HSDLControl::audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params)
{
    SDL_AudioSpec wanted_spec, spec;
    QVector<int> next_nb_channels = {0, 0, 1, 6, 2, 6, 4, 6};
    QVector<int> next_sample_rates = {0, 44100, 48000, 96000, 192000};
    int next_sample_rate_idx = next_sample_rates.size() - 1;
    auto env = SDL_getenv("SDL_AUDIO_CHANNELS");
    if (env)
    {
        wanted_nb_channels = atoi(env);
        wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
    }
    if (!wanted_channel_layout || wanted_nb_channels != av_get_channel_layout_nb_channels(wanted_channel_layout))
    {
        wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
        wanted_channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
    }
    wanted_nb_channels = av_get_channel_layout_nb_channels(wanted_channel_layout);

    if (wanted_sample_rate <= 0 || wanted_nb_channels <= 0)
    {
        qFatal("Invalid sample rate or channel count!");
        return -1;
    }

    while (next_sample_rate_idx && next_sample_rates[next_sample_rate_idx] >= wanted_sample_rate)
        next_sample_rate_idx--;

    wanted_spec.channels = wanted_nb_channels;
    wanted_spec.freq = wanted_sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.silence = 0;
    wanted_spec.samples = qMax(SDL_AUDIO_MIN_BUFFER_SIZE, 2 << int(qLn(wanted_spec.freq / SDL_AUDIO_MAX_CALLBACKS_PER_SEC) / qLn(2)));
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = opaque;

    while (!(d_ptr->audio_dev = SDL_OpenAudioDevice(nullptr, 0, &wanted_spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE)))
    {
        qInfo("SDL_OpenAudio (%d channels, %d Hz): %s.", wanted_spec.channels, wanted_spec.freq, SDL_GetError());
        wanted_spec.channels = next_nb_channels.at(wanted_spec.channels > 7 ? 7 : wanted_spec.channels);
        if (!wanted_spec.channels)
        {
            wanted_spec.freq = next_sample_rates[next_sample_rate_idx--];
            wanted_spec.channels = wanted_nb_channels;
            if (!wanted_spec.freq)
            {
                qCritical("No more combinations to try, audio open failed.");
                return -1;
            }
        }
    }

    if (spec.format != AUDIO_S16SYS)
    {
        qCritical("SDL advised audio format %d is not supported!", spec.format);
        return -1;
    }

    hw_params->format = AV_SAMPLE_FMT_S16;
    hw_params->freq = spec.freq;
    hw_params->channels = spec.channels;
    hw_params->channel_layout = av_get_default_channel_layout(spec.channels);
    hw_params->frame_size = av_samples_get_buffer_size(nullptr, hw_params->channels, 1, hw_params->format, 1);
    hw_params->bytes_per_sec = av_samples_get_buffer_size(nullptr, hw_params->channels, hw_params->freq, hw_params->format, 1);
    if (!hw_params->channel_layout)
    {
        qCritical("SDL advised channel count %d is not supported!", hw_params->channels);
        return -1;
    }
    if (hw_params->bytes_per_sec <= 0 || hw_params->frame_size <= 0)
    {
        qCritical("av_samples_get_buffer_size failed.");
        return -1;
    }
    return spec.size;
}

void HSDLControl::audio_close()
{
    SDL_CloseAudioDevice(d_ptr->audio_dev);
}

void HSDLControl::audio_pause(int pause)
{
    SDL_PauseAudioDevice(d_ptr->audio_dev, pause);
}

void HSDLControl::audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len)
{
    if (!d_ptr->muted && buf && d_ptr->audio_volume == SDL_MIX_MAXVOLUME)
        memcpy(stream, buf + index, len);
    else
    {
        memset(stream, 0, len);
        if (!d_ptr->muted && buf)
            SDL_MixAudioFormat(stream, buf + index, AUDIO_S16SYS, len, d_ptr->audio_volume);
    }
}

void HSDLControl::audio_upload(QRect rect, int channels, int16_t *sample, int start, int size)
{
    SDL_SetRenderDrawColor(d_ptr->renderer, 255, 255, 255, 255);

    int i, ch, h1, h2, y, y1, ys;
    h1 = rect.height() / channels;  // total height for one channel
    h2 = h1 * 9 / 20;               // graph height / 2
    for (ch = 0; ch < channels; ch++)
    {
        i = start + ch;
        y1 = rect.y() + ch * h1 + h1 / 2; // position of center line
        for (int x = 0; x < rect.width(); x++)
        {
            ys = y1;
            y = (sample[i] * h2) >> 15;
            if (y < 0)
            {
                y = -y;
                ys = y1 - y;
            }
            fill_rectangle(rect.x() + x, ys, 1, y);
            i += channels;
            if (i >= size)
                i -= size;
        }
    }
    SDL_SetRenderDrawColor(d_ptr->renderer, 0, 0, 255, 255);
    for (ch = 1; ch < channels; ch++)
    {
        y = rect.y() + ch * h1;
        fill_rectangle(rect.x(), y, rect.width(), 1);
    }
}

void HSDLControl::audio_upload(QRect rect, int channels, int freq, float **data, int start)
{
    if (!texture_realloc(&d_ptr->audio_texture, SDL_PIXELFORMAT_ARGB8888, rect.width(), rect.height(), SDL_BLENDMODE_NONE, 1))
        return;

    uint32_t *pixels;
    int a, b, y ,pitch;
    double w;
    SDL_Rect rect2;
    rect2.x = start;
    rect2.y = 0;
    rect2.w = 1;
    rect2.h = rect.height();

    if (!SDL_LockTexture(d_ptr->audio_texture, &rect2, (void **)&pixels, &pitch))
    {
        pitch >>= 2;
        pixels += pitch * rect.height();
        for (y = 0; y < rect.height(); y++)
        {
            w = 1 / sqrt(freq);
            a = sqrt(w * sqrt(data[0][2 * y + 0] * data[0][2 * y + 0] + data[0][2 * y + 1] * data[0][2 * y + 1]));
            b = channels == 2  ? sqrt(w * hypot(data[1][2 * y + 0], data[1][2 * y + 1])): a;
            a = qMin(a, 255);
            b = qMin(b, 255);
            pixels -= pitch;
            *pixels = (a << 16) + (b << 8) + ((a + b) >> 1);
        }
        SDL_UnlockTexture(d_ptr->audio_texture);
    }
    SDL_RenderCopy(d_ptr->renderer, d_ptr->audio_texture, nullptr, nullptr);
}

void HSDLControl::video_open(int width, int height)
{
    SDL_SetWindowSize(d_ptr->window, width, height);
    SDL_SetWindowPosition(d_ptr->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    if (d_ptr->full_screen)
        SDL_SetWindowFullscreen(d_ptr->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_ShowWindow(d_ptr->window);
}

void HSDLControl::video_upload(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame)
{
    emit display_request(rect, video_frame, subtitle_frame); // 需要在同一线程下面，不然设置窗口大小以后无法显示
}

void HSDLControl::subtitle_upload(HFFFrame *frame)
{
    if (frame->uploaded)
    {
        for (uint i = 0; i < frame->sub.num_rects; i++)
        {
            auto sub_rect = frame->sub.rects[i];
            uint8_t *pixels;
            int pitch;
            if (!SDL_LockTexture(d_ptr->subtitle_texture, (SDL_Rect *)sub_rect, (void **)&pixels, &pitch))
            {
                for (int j = 0; j < sub_rect->h; j++, pixels += pitch)
                    memset(pixels, 0, sub_rect->w << 2);
                SDL_UnlockTexture(d_ptr->subtitle_texture);
            }
        }
    }
    else
    {
        uint8_t* pixels[4];
        int pitch[4];

        if (!texture_realloc(&d_ptr->subtitle_texture, SDL_PIXELFORMAT_ARGB8888, frame->width, frame->height, SDL_BLENDMODE_BLEND, true))
            return;
        for (uint i = 0; i < frame->sub.num_rects; i++)
        {
            auto sub_rect = frame->sub.rects[i];
            sub_rect->x = qBound(0, sub_rect->x, frame->width );
            sub_rect->y = qBound(0, sub_rect->y, frame->height);
            sub_rect->w = qBound(0, sub_rect->w, frame->width  - sub_rect->x);
            sub_rect->h = qBound(0, sub_rect->h, frame->height - sub_rect->y);

            d_ptr->sub_convert_ctx = sws_getCachedContext(d_ptr->sub_convert_ctx,
                                                          sub_rect->w, sub_rect->h, AV_PIX_FMT_PAL8,
                                                          sub_rect->w, sub_rect->h, AV_PIX_FMT_BGRA,
                                                          0, nullptr, nullptr, nullptr);
            if (d_ptr->sub_convert_ctx == nullptr)
            {
                qFatal("Cannot initialize the conversion context.");
                return;
            }
            if (!SDL_LockTexture(d_ptr->subtitle_texture, (SDL_Rect *)sub_rect, (void **)pixels, pitch))
            {
                sws_scale(d_ptr->sub_convert_ctx, (const uint8_t * const *)sub_rect->data, sub_rect->linesize, 0, sub_rect->h, pixels, pitch);
                SDL_UnlockTexture(d_ptr->subtitle_texture);
            }
        }
        frame->uploaded = true;
    }
}

// 是否停止退出事件
bool HSDLControl::is_exit_event(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
        return d_ptr->exit_on_keydown || event->key.keysym.sym == SDLK_ESCAPE || event->key.keysym.sym == SDLK_q;
    if (event->type == SDL_MOUSEBUTTONDOWN)
        return d_ptr->exit_on_mousedown;
    if (event->type == SDL_QUIT || event->type == SDL_STOP_EVENT)
        return true;
    return false;
}

void HSDLControl::set_yuv_conversion_mode(AVFrame *frame)
{
    SDL_YUV_CONVERSION_MODE mode = SDL_YUV_CONVERSION_AUTOMATIC;
    if (frame && (frame->format == AV_PIX_FMT_YUV420P || frame->format == AV_PIX_FMT_YUYV422 || frame->format == AV_PIX_FMT_UYVY422))
    {
        if (frame->color_range == AVCOL_RANGE_JPEG)
            mode = SDL_YUV_CONVERSION_JPEG;
        else if (frame->colorspace == AVCOL_SPC_BT709)
            mode = SDL_YUV_CONVERSION_BT709;
        else if (frame->colorspace == AVCOL_SPC_BT470BG || frame->colorspace == AVCOL_SPC_SMPTE170M || frame->colorspace == AVCOL_SPC_SMPTE240M)
            mode = SDL_YUV_CONVERSION_BT601;
    }
    SDL_SetYUVConversionMode(mode);
}

bool HSDLControl::texture_realloc(SDL_Texture **texture, uint format, int width, int height, SDL_BlendMode mode, bool init)
{
    uint fmt;
    int access, w, h;
    if (!*texture || SDL_QueryTexture(*texture, &fmt, &access, &w, &h) < 0 || width != w || height != h || format != fmt)
    {
        if (*texture)
            SDL_DestroyTexture(*texture);
        *texture = SDL_CreateTexture(d_ptr->renderer, format, SDL_TEXTUREACCESS_STREAMING, width, height);
        if (!*texture)
            return false;
        if (SDL_SetTextureBlendMode(*texture, mode) < 0)
            return false;
        if (init)
        {
            void *pixels;
            int pitch;
            if (SDL_LockTexture(*texture, nullptr, &pixels, &pitch) < 0)
                return false;
            memset(pixels, 0, pitch * height);
            SDL_UnlockTexture(*texture);
        }
        qInfo("Created %dx%d texture with %s.\n", width, height, SDL_GetPixelFormatName(format));
    }
    return true;
}

bool HSDLControl::video_upload(SDL_Texture **texture, AVFrame *frame)
{
    auto pix_fmt = d_ptr->pix_fmt(frame->format);
    auto blend_mode = d_ptr->blend_mode(frame->format);
    if (!texture_realloc(texture, pix_fmt == SDL_PIXELFORMAT_UNKNOWN ? SDL_PIXELFORMAT_ARGB8888 : pix_fmt, frame->width, frame->height, blend_mode, false))
        return false;

    if (pix_fmt == SDL_PIXELFORMAT_UNKNOWN)
    {
        // This should only happen if we are not using avfilter...
        d_ptr->img_convert_ctx = sws_getCachedContext(d_ptr->img_convert_ctx,
                                                      frame->width, frame->height, (AVPixelFormat)frame->format,
                                                      frame->width, frame->height, AV_PIX_FMT_BGRA,
                                                      sws_flags, nullptr, nullptr, nullptr);
        if (d_ptr->img_convert_ctx == nullptr)
        {
            qFatal("Cannot initialize the conversion context.");
            return false;
        }

        uint8_t *pixels[4];
        int pitch[4];
        if (!SDL_LockTexture(*texture, nullptr, (void **)pixels, pitch))
        {
            sws_scale(d_ptr->img_convert_ctx, (const uint8_t * const *)frame->data, frame->linesize, 0, frame->height, pixels, pitch);
            SDL_UnlockTexture(*texture);
        }
        return true;
    }
    if (pix_fmt == SDL_PIXELFORMAT_IYUV)
    {
        if (frame->linesize[0] > 0 && frame->linesize[1] > 0 && frame->linesize[2] > 0)
        {
            return SDL_UpdateYUVTexture(*texture, nullptr,
                                        frame->data[0], frame->linesize[0],
                                        frame->data[1], frame->linesize[1],
                                        frame->data[2], frame->linesize[2]) >= 0;
        }
        if (frame->linesize[0] < 0 && frame->linesize[1] < 0 && frame->linesize[2] < 0)
        {
            return SDL_UpdateYUVTexture(*texture, nullptr,
                                        frame->data[0] + frame->linesize[0] * (frame->height                    - 1), -frame->linesize[0],
                                        frame->data[1] + frame->linesize[1] * (AV_CEIL_RSHIFT(frame->height, 1) - 1), -frame->linesize[1],
                                        frame->data[2] + frame->linesize[2] * (AV_CEIL_RSHIFT(frame->height, 1) - 1), -frame->linesize[2]) >= 0;
        }
        qFatal("Mixed negative and positive linesizes are not supported.");
        return false;
    }
    if (frame->linesize[0] < 0)
        return SDL_UpdateTexture(*texture, nullptr, frame->data[0] + frame->linesize[0] * (frame->height - 1), -frame->linesize[0]) >= 0;
    return SDL_UpdateTexture(*texture, nullptr, frame->data[0], frame->linesize[0]) >= 0;
}

void HSDLControl::video_display(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame)
{
    auto rect2 = convert(rect);
    SDL_SetRenderDrawColor(d_ptr->renderer, 0, 0, 0, 255);
    SDL_RenderClear(d_ptr->renderer);
    if (!video_frame->uploaded)
    {
        if (!video_upload(&d_ptr->video_texture, video_frame->frame))
            return;
        video_frame->uploaded = true;
        video_frame->flip_v = video_frame->frame->linesize[0] < 0;
    }
    set_yuv_conversion_mode(video_frame->frame);
    SDL_RenderCopyEx(d_ptr->renderer, d_ptr->video_texture, nullptr, &rect2, 0, nullptr, video_frame->flip_v ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    set_yuv_conversion_mode(nullptr);
    if (subtitle_frame)
    {
#if USE_ONEPASS_SUBTITLE_RENDER
        SDL_RenderCopy(d_ptr->renderer, d_ptr->subtitle_texture, nullptr, &rect2);
#else
        auto xratio = 1.0 * rect.width() / subtitle_frame->width;
        auto yratio = 1.0 * rect.height() / subtitle_frame->height;
        for (uint i = 0; i < subtitle_frame->sub.num_rects; i++)
        {
            auto sub_rect = (SDL_Rect*)subtitle_frame->sub.rects[i];
            SDL_Rect target;
            target.x = rect.x() + sub_rect->x * xratio;
            target.y = rect.y() + sub_rect->y * yratio;
            target.w = sub_rect->w * xratio;
            target.h = sub_rect->h * yratio;
            SDL_RenderCopy(d_ptr->renderer, d_ptr->subtitle_texture, sub_rect, &target);
        }
#endif
    }
    SDL_RenderPresent(d_ptr->renderer);
}

void HSDLControl::fill_rectangle(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    if (w && h)
        SDL_RenderFillRect(d_ptr->renderer, &rect);
}

void HSDLControl::refresh_loop_wait_event(SDL_Event *event)
{
    double remaining_time = 0.0;
    SDL_PumpEvents();
    while (!SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT))
    {
        if (!d_ptr->cursor_hidden && d_ptr->last_mouse_move_time.elapsed() > CURSOR_HIDE_DELAY)
        {
            SDL_ShowCursor(0);
            d_ptr->cursor_hidden = true;
        }
        if (remaining_time > 0.0)
            SDL_Delay(remaining_time * 1000.0);
        remaining_time = qMin(SDL_REFRESH_RATE, d_ptr->service->refresh());
        SDL_PumpEvents();
    }
}

void HSDLControl::stop()
{
    if (!d_ptr->thread->isRunning())
        return;

    SDL_Event event;
    event.type = SDL_STOP_EVENT;
    event.user.data1 = this;
    SDL_PushEvent(&event);
    d_ptr->thread->wait();
}

void HSDLControl::run()
{
    SDL_Event event;
    double x;
    for (;;)
    {
        refresh_loop_wait_event(&event);
        if (is_exit_event(&event))
        {
            emit exit_request();
            break;
        }
        switch (event.type)
        {
        case SDL_KEYDOWN:
//            // If we don't yet have a window, skip all key events, because read_thread might still be initializing...
//            if (!cur_stream->width)
//                continue;
            switch (event.key.keysym.sym)
            {
            case SDLK_f:
                toggle_full_screen();
                break;
            case SDLK_p:
            case SDLK_SPACE:
                emit pause_request();
                break;
            case SDLK_m:
                toggle_mute();
                break;
            case SDLK_KP_MULTIPLY:
            case SDLK_0:
                update_volume(1, SDL_VOLUME_STEP);
                break;
            case SDLK_KP_DIVIDE:
            case SDLK_9:
                update_volume(-1, SDL_VOLUME_STEP);
                break;
            case SDLK_s: // S: Step to next frame
                emit step_request();
                break;
            case SDLK_a:
                emit switch_channel_request(AVMEDIA_TYPE_AUDIO);
                break;
            case SDLK_v:
                emit switch_channel_request(AVMEDIA_TYPE_VIDEO);
                break;
            case SDLK_t:
                emit switch_channel_request(AVMEDIA_TYPE_SUBTITLE);
                break;
            case SDLK_PAGEUP:
                emit seek_chapter_request(1);
                break;
            case SDLK_PAGEDOWN:
                emit seek_chapter_request(-1);
                break;
            case SDLK_LEFT:
                emit seek_section_request(-10);
                break;
            case SDLK_RIGHT:
                emit seek_section_request(10);
                break;
            case SDLK_UP:
                emit seek_section_request(60);
                break;
            case SDLK_DOWN:
                emit seek_section_request(60);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (d_ptr->last_mouse_click_time.elapsed() <= 500)
                {
                    toggle_full_screen();
                    break;
                }
                else
                    d_ptr->last_mouse_click_time.restart();
            }
        case SDL_MOUSEMOTION:
            if (d_ptr->cursor_hidden)
            {
                SDL_ShowCursor(1);
                d_ptr->cursor_hidden = true;
            }
            d_ptr->last_mouse_move_time.restart();
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button != SDL_BUTTON_RIGHT)
                    break;
                x = event.button.x;
            }
            else
            {
                if (!(event.motion.state & SDL_BUTTON_RMASK))
                    break;
                x = event.motion.x;
            }
            emit seek_to_request(x);
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                emit screen_size_changed(event.window.data1, event.window.data2);
                if (d_ptr->video_texture)
                {
                    SDL_DestroyTexture(d_ptr->video_texture);
                    d_ptr->video_texture = nullptr;
                }
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                emit force_refresh_request();
            }
            break;
        default:
            break;
        }
    }
}

HE_CONTROL_END_NAMESPACE
