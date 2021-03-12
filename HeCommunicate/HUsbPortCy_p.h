#pragma once

#include "HUsbPortCy.h"
#include "HAbstractPort_p.h"

#ifndef Q_CC_MSVC
    class QLibrary;
#endif

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortCyPrivate : public HAbstractPortPrivate
{
public:
    void loadDll();
    void unloadDLL();

public:
    bool isLoaded;
#ifndef Q_CC_MSVC
public:
    using FunOpen = bool(*)(int);
    using FunClose = bool(*)();
    using FunSetTimeout = bool(*)(int);
    using FunReadData = int(*)(uchar *, int);
    using FunWriteData = int(*)(uchar *, int);

    FunOpen open;
    FunClose close;
    FunSetTimeout setTimeout;
    FunReadData readData;
    FunWriteData writeData;
    QScopedPointer<QLibrary> lib;
#endif
};

HE_COMMUNICATE_END_NAMESPACE
