#ifndef HABSTRACTMODEL_P_H
#define HABSTRACTMODEL_P_H

#include "HAbstractModel.h"
#include "HeData/HDataGlobal.h"
#include "HeCommunicate/HCommunicateGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE
class IDeviceCollection;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThreadCollection;
class HDelayThread;

class HE_CONTROLLER_EXPORT HAbstractModelPrivate
{
public:
    HAbstractModelPrivate(HAbstractModel *);

public:
    bool initialized;
    QString configFileName;
    HAbstractModel *q_ptr;
    IConfigManage *configManage = nullptr;
    IDeviceCollection *devices = nullptr;
    IThreadCollection *threads = nullptr;
    HDelayThread *delayThread;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_P_H
