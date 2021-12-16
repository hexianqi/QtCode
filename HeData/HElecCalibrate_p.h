#pragma once

#include "HElecCalibrate.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HElecCalibratePrivate
{
public:
    HElecCalibratePrivate();

public:
    IDataFactory *factory = nullptr;
    QMap<QString, IElecCalibrateItemCollection *> datas;
};

HE_END_NAMESPACE
