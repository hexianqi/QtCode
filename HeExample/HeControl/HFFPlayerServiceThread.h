/***************************************************************************************************
**      2020-07-28  HFFPlayerServiceThread
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QThread>

HE_BEGIN_NAMESPACE

class HFFPlayerService;
class HFFPlayerServiceThreadPrivate;

class HFFPlayerServiceThread : public QThread
{
    Q_OBJECT

public:
    enum Task
    {
        Shutdown            = 0x00001,
        SetSource           = 0x00002,
        //        SetAudioOutput     = 0x00008,
        //        SetVideoOutput     = 0x00010,
        //        SetOutputs         = SetAudioOutput | SetVideoOutput,
        //        SetAudioProbe      = 0x00020,
        //        SetVideoProbe      = 0x00040,
        //        SetProbes          = SetAudioProbe | SetVideoProbe,
        //        Render             = 0x00080,
        //        FinalizeLoad       = 0x00100,
        //        SetRate            = 0x00200,
        //        Seek               = 0x00400,
                Play               = 0x00800,
                Pause              = 0x01000,
                Stop               = 0x02000,
        //        ReleaseGraph       = 0x04000,
        //        ReleaseAudioOutput = 0x08000,
        //        ReleaseVideoOutput = 0x10000,
        //        ReleaseAudioProbe  = 0x20000,
        //        ReleaseVideoProbe  = 0x40000,
        //        ReleaseFilters     = ReleaseGraph | ReleaseAudioOutput
        //                         | ReleaseVideoOutput | ReleaseAudioProbe
        //                         | ReleaseVideoProbe
    };

public:
    explicit HFFPlayerServiceThread(HFFPlayerService *service);
    ~HFFPlayerServiceThread() override;

public:
    void shutdown();
    void addTask(Task value);
    void clearTask();

protected:
    void enqueueTask(Task value);
    Task dequeueTask();

protected:
    void run() override;

protected:
    QScopedPointer<HFFPlayerServiceThreadPrivate> d_ptr;
};

HE_END_NAMESPACE

