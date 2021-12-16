/***************************************************************************************************
**      2020-07-28  HFFPlayerService
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

struct HFFAudioParams;
struct HFFFrame;
class HFFPlayerServicePrivate;

class HFFPlayerService : public QObject
{
    Q_OBJECT

public:
    explicit HFFPlayerService(QObject *parent = nullptr);
    ~HFFPlayerService() override;

public:
    bool load(const QString &value);
    void play();
    void pause();
    void stop();

protected:
    QScopedPointer<HFFPlayerServicePrivate> d_ptr;

protected:
    void init();

protected:
    void doSetSource();
    void doPlay();
    void doPause();
    void doStop();

protected:
    int audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HFFAudioParams *hw_params);
    void audio_pause(int pause);
    void audio_close();
    void audio_fill_stream(uint8_t *stream, uint8_t *buf, int index, int len);
    void audio_upload(QRect rect, int channels, int16_t *sample, int start, int size);
    void audio_upload(QRect rect, int channels, int freq, float **data, int start);
    void video_open(int width, int height);
    void video_upload(QRect rect, HFFFrame *video_frame, HFFFrame *subtitle_frame = nullptr);
    void subtitle_upload(HFFFrame *frame);

protected:
    double refresh();

    friend class HFFPlayerServiceThread;
    friend class HFFSourceControl;
    friend class HSDLControl;
};

HE_END_NAMESPACE

