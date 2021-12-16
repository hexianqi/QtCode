/***************************************************************************************************
**      2020-06-12  HFFmpegThread
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QThread>

HE_BEGIN_NAMESPACE

class HFFmpegThreadPrivate;

class HFFmpegThread : public QThread
{
    Q_OBJECT

public:
    explicit HFFmpegThread(QObject *parent = nullptr);
    ~HFFmpegThread() override;

signals:
    // 收到图片信号
    void receiveImage(const QImage &image);

public slots:
    // 设置视频流地址
    void setUrl(const QString &value);
    // 初始化视频对象
    bool init();
    // 释放视频对象
    void free();
    // 播放视频对象
    void play();
    // 暂停播放
    void pause();
    // 继续播放
    void next();
    // 停止采集线程
    void stop();

protected:
    HFFmpegThread(HFFmpegThreadPrivate &p, QObject *parent = nullptr);

protected:
    void run() override;

protected:
    QScopedPointer<HFFmpegThreadPrivate> d_ptr;
};

HE_END_NAMESPACE

