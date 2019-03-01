#ifndef HABSTRACTMODEL_P_H
#define HABSTRACTMODEL_P_H

#include "HAbstractModel.h"

HE_COMMUNICATE_BEGIN_NAMESPACE
class IDeviceCollection;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThreadCollection;

class HE_CONTROLLER_EXPORT HAbstractModelPrivate
{
public:
    HAbstractModelPrivate();

public:
    IDeviceCollection *devices;
    IThreadCollection *threads;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_P_H
