#pragma once

#include "HFFSourceControl.h"
#include <QtCore/QRect>
#include <QtCore/QMutexLocker>
#include <QtCore/QWaitCondition>

struct AVFormatContext;

HE_BEGIN_NAMESPACE

class HFFVideoStreamsControl;
class HFFAudioStreamsControl;
class HFFSubtitleStreamsControl;
class HFFClock;

class HFFSourceControlPrivate
{
public:
    HFFSourceControlPrivate();

public:
    bool show_status = true;
    bool genpts = false;                        // generate pts
    bool find_stream_info = true;               // read and decode the streams to fill missing information with heuristics
    int seek_by_bytes = -1;                     // seek by bytes [0=off 1=on -1=auto]
    int infinite_buffer = -1;                   // don't limit the input buffer size (useful with realtime streams) [0=off 1=on -1=auto]
    int64_t start_time;                         // start time
    int64_t duration;
    const char *wanted_stream_spec[5] = {0};    // desired stream
    bool audio_disable = false;                 // disable audio
    bool video_disable = false;                 // disable video
    bool subtitle_disable = false;              // disable subtitling
    double rdft_speed = 0.02;                   // rdft speed(ms)
    int loop_times = 1;                         // number of times the playback shall be looped
    bool auto_exit = false;                     // exit at the end

public:
    HFFSourceControl::ShowMode show_mode = HFFSourceControl::SHOW_MODE_NONE;
    HFFSourceControl::SyncMode sync_mode = HFFSourceControl::SYNC_AUDIO_MASTER;
    bool abort_request = false;
    bool queue_attachments_request = false;
    bool force_refresh = false;
    bool paused = false;
    bool last_paused = false;
    int read_pause_return = 0;
    bool seek_request = false;
    int seek_flags;
    int64_t seek_pos;
    int64_t seek_rel;
    bool step = false;
    bool eof = false;

    QSize default_window_size = QSize(600, 480);
    QSize screen_size;
    QRect window;
    double last_vis_time;

public:
    char *filename;
    AVFormatContext *fmt_ctx = nullptr;
    bool realtime = false;

public:
    HFFPlayerService *service = nullptr;
    HFFVideoStreamsControl *video_ctl = nullptr;
    HFFAudioStreamsControl *audio_ctl = nullptr;
    HFFSubtitleStreamsControl *subtitle_ctl = nullptr;
    HFFClock *video_clk = nullptr;
    HFFClock *audio_clk = nullptr;
    HFFClock *ext_clk = nullptr;
    QThread *thread = nullptr;
    QMutex mutex;
    QWaitCondition cond;
};

HE_END_NAMESPACE

