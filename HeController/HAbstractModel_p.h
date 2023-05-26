#pragma once

#include "HAbstractModel.h"

HE_BEGIN_NAMESPACE

class IConfigManage;
class IThreadCollection;
class HDelayThread;

class HE_CONTROLLER_EXPORT HAbstractModelPrivate
{
public:
    HAbstractModelPrivate();

public:
    bool initialized = false;
    bool running = false;
    QString configFileName;
    IConfigManage *configManage = nullptr;
    IThreadCollection *threads = nullptr;
    HDelayThread *delayThread = nullptr;
};

HE_END_NAMESPACE
