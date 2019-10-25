#ifndef HABSTRACTMODEL_P_H
#define HABSTRACTMODEL_P_H

#include "HAbstractModel.h"
#include "HeData/HDataGlobal.h"
#include "HeCommunicate/HCommunicateGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThreadCollection;
class HDelayThread;

class HE_CONTROLLER_EXPORT HAbstractModelPrivate
{
public:
    HAbstractModelPrivate(IModel *);

public:
    bool initialized;
    QString configFileName;
    IModel *q_ptr;
    IConfigManage *configManage = nullptr;
    IThreadCollection *threads = nullptr;
    HDelayThread *delayThread = nullptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_P_H
