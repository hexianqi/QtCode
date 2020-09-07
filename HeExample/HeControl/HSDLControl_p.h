#pragma once

#include "HSDLControl.h"
#include "SDL2/SDL.h"
#include <QtCore/QTime>

struct SwsContext;

HE_CONTROL_BEGIN_NAMESPACE

class HSDLControlPrivate
{
public:
    HSDLControlPrivate();

public:
    bool init();
    void destroy();
    void test();

public:
    int pix_fmt(int format);
    SDL_BlendMode blend_mode(int format);

public:
    bool exit_on_keydown = false;
    bool exit_on_mousedown = false;

public:
    QString title;
    bool audio_disable = false;
    bool video_disable = false;
    bool always_on_top = false;
    bool borderless = false;
    int default_width = 640;
    int default_height = 480;
    bool cursor_hidden = false;
    bool full_screen = false;
    bool muted = false;
    int audio_volume = 100;

public:
    QTime last_mouse_move_time;
    QTime last_mouse_click_time;
    HFFPlayerService *service = nullptr;
    QThread *thread = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_RendererInfo *renderer_info = nullptr;
    SDL_AudioDeviceID audio_dev;
    SDL_Texture *video_texture = nullptr;
    SDL_Texture *audio_texture = nullptr;
    SDL_Texture *subtitle_texture = nullptr;
    SwsContext *img_convert_ctx;
    SwsContext *sub_convert_ctx;
    QHash<int, int> texture_formats;
};

HE_CONTROL_END_NAMESPACE
