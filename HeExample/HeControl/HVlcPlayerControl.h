/***************************************************************************************************
**      2020-08-24  HVlcPlayerControl
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

struct libvlc_event_t;

HE_CONTROL_BEGIN_NAMESPACE

class HVlcPlayerControlPrivate;

class HVlcPlayerControl : public QObject
{
    Q_OBJECT

public:
    enum State
    {
        Idle,
        Opening,
        Buffering,
        Playing,
        Paused,
        Stopped,
        Ended,
        Error
    };

public:
    explicit HVlcPlayerControl(QObject *parent = nullptr);
    ~HVlcPlayerControl() override;

signals:
    void stateChanged(int);
    void mutedChanged(bool);
    void volumeChanged(double);
    void positionChanged(double);
    void timeChanged(qlonglong);
    void durationChanged(qlonglong);

public slots:
    void setVideoWindow(QWidget *);
    void setUrl(const QString &value);
    void setVolume(int value);
    void setMute(bool b);
    void setChapter(int value);
    void snapshot(const QString &fileName);
    void fullScreen();
    void seek(double pos);
    void play();
    void pause();
    void stop();
    void close();

public:
    void setOption(const QString &value);

protected:
    HVlcPlayerControl(HVlcPlayerControlPrivate &p, QObject *parent = nullptr);

protected:
    bool open();
    bool initInstance();
    void attachWindow();
    void attachEvents();
    void handleEvents(const libvlc_event_t *, void *);
    void updateMediaInfo();
    void updateMetaInfo();
    void updateTracksInfo();

protected:
    QScopedPointer<HVlcPlayerControlPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

