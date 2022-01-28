#pragma once

#include "HConfigManage.h"

HE_BEGIN_NAMESPACE

class IDataFactory;
class IDataStream;

class HConfigManagePrivate
{
public:
    HConfigManagePrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    quint32 contain = 0;
    IDataFactory *factory = nullptr;
    IDataStream *stream = nullptr;
    ISpecCalibrateCollection *specCalibrate = nullptr;
    IElecCalibrateCollection *elecCalibrate = nullptr;
    ILuminousCalibrateCollection *luminousCalibrate = nullptr;
    IChromatismCollection *chromatism = nullptr;
    IGradeCollection *grade = nullptr;
    IQualityCollection *quality = nullptr;
    ILocationCollection *location = nullptr;
    IAdjustCollection *adjust = nullptr;
    IAdjust2Collection *adjust2 = nullptr;
};

HE_END_NAMESPACE
