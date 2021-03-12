#pragma once

#include "HElecCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HElecCalibratePrivate
{
public:
    HElecCalibratePrivate();

public:
    IDataFactory *factory = nullptr;
    QMap<QString, IElecCalibrateItemCollection *> datas;
};

HE_DATA_END_NAMESPACE
