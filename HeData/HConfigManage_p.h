#pragma once

#include "HConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

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
    ISpecCalibrateCollection *specCalibrates = nullptr;
    IElecCalibrateCollection *elecCalibrates = nullptr;
    ILuminousCalibrateCollection *luminousCalibrates = nullptr;
    IChromatismCollection *chromatisms = nullptr;
    IGradeCollection *grades = nullptr;
    IAdjustCollection *adjusts = nullptr;
    IAdjust2Collection *adjusts2 = nullptr;
    IQualityCollection *qualitys = nullptr;
};

HE_DATA_END_NAMESPACE
