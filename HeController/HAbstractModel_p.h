#ifndef HABSTRACTMODEL_P_H
#define HABSTRACTMODEL_P_H

#include "HAbstractModel.h"

HE_COMMUNICATE_BEGIN_NAMESPACE
class HDeviceCollection;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThread;

class HAbstractModelPrivate
{
public:
    HAbstractModelPrivate();

public:
    HDeviceCollection *devices;
    QMap<QString, IThread *> threads;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_P_H
