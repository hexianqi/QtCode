/***************************************************************************************************
**      2020-07-28  HFFPlayerControl
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

//class HFFPlayerService;
//class HFFPlayerControlPrivate;

//class HFFPlayerControl : public QObject
//{
//    Q_OBJECT

//public:
//    enum PlayerStatus
//    {
//        Stopped,
//        Playing,
//        Paused
//    };

//    enum MediaStatus
//    {
//        Unknown,
//        No,
//        Loading,
//        Loaded,
//        Stalled,
//        Buffering,
//        Buffered,
//        End,
//        Invalid
//    };

//public:
//    explicit HFFPlayerControl(HFFPlayerService *service, QObject *parent = nullptr);
//    ~HFFPlayerControl() override;

//signals:
//    void mediaChanged(const QString &);
//    void statusChanged(PlayerStatus);

//public:
//    bool setMedia(const QString &value);
//    void play();
//    void pause();
//    void stop();

//public:
//    void updateStatus(PlayerStatus value);
//    void updateStatus(MediaStatus value);

//protected:
//    void playOrPause(PlayerStatus value);

//protected:
//    QScopedPointer<HFFPlayerControlPrivate> d_ptr;
//};

HE_CONTROL_END_NAMESPACE

