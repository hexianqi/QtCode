#pragma once

#include "HUsbPortLpc214.h"
#include "HAbstractPort_p.h"

#ifndef Q_CC_MSVC
    class QLibrary;
#endif

HE_BEGIN_NAMESPACE

class HUsbPortLpc214Private : public HAbstractPortPrivate
{
public:
    void loadDll();
    void unloadDLL();

public:
    bool isLoaded;
#ifndef Q_CC_MSVC
public:
    using Fun = int(*)(int, uchar *, int, int);
    Fun readData;
    Fun writeData;
    QScopedPointer<QLibrary> lib;
#endif
};

HE_END_NAMESPACE
