#ifndef HELECCALIBRATE_P_H
#define HELECCALIBRATE_P_H

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

#endif // HELECCALIBRATE_P_H
