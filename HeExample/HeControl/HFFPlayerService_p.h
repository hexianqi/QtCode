#pragma once

#include "HFFPlayerService.h"
#include <QtCore/QMutexLocker>

struct AVInputFormat;

HE_CONTROL_BEGIN_NAMESPACE

class HFFPlayerControl;
class HFFSourceControl;
class HSDLControl;
class HFFPlayerServiceThread;

class HFFPlayerServicePrivate
{
public:
    QString media;
    AVInputFormat *iformat = nullptr;

public:
    QMutex mutex;
    HFFPlayerControl *player = nullptr;
    HFFSourceControl *source = nullptr;
    HSDLControl *sdl = nullptr;
    HFFPlayerServiceThread *thread;
};

HE_CONTROL_END_NAMESPACE

