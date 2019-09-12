#ifndef HPROTOCOLDEMO_P_H
#define HPROTOCOLDEMO_P_H

#include "HProtocolDemo.h"

class QMutex;
class QLibrary;

class HProtocolDemoPrivate
{
public:
    HProtocolDemoPrivate();

public:
    void loadDll();
    void unloadDLL();

public:
    using FunOpen = bool(*)();
    using FunClose = bool(*)();
//    using FunSetTimeout = bool(*)(int);
//    using FunReadData = int(*)(uchar *, int);
//    using FunWriteData = int(*)(uchar *, int);
    FunOpen open;
    FunClose close;
//    FunSetTimeout setTimeout;
//    FunReadData readData;
//    FunWriteData writeData;
    QScopedPointer<QLibrary> lib;

public:
    bool isLoaded = false;
    QMutex *mutex = nullptr;
};

#endif // HPROTOCOLDEMO_P_H
