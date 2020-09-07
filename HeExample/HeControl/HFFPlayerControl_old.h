/***************************************************************************************************
**      2020-07-20  HFFPlayerControl
***************************************************************************************************/

#pragma once

#include "IMediaPlayerControl.h"
#include <QtCore/QThread>

HE_CONTROL_BEGIN_NAMESPACE

class HFFPlayerControlPrivate;

class HFFPlayerControl : public QThread
{
    Q_OBJECT

public:
    explicit HFFPlayerControl(QObject *parent = nullptr);
    ~HFFPlayerControl() override;

public:
    void setUrl(const QString &value);
    void play();

protected:
    void run() override;

protected:
    QScopedPointer<HFFPlayerControlPrivate> d_ptr;

private:
    bool initSDL();
    bool initVideoState();
    void free();
};

HE_CONTROL_END_NAMESPACE

