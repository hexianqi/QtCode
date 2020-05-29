#ifndef HCONFIGMANAGE_P_H
#define HCONFIGMANAGE_P_H

#include "HConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

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
    IFileStream *fileStream = nullptr;
    ISpecCalibrateCollection *specCalibrates = nullptr;
    IElecCalibrateCollection *elecCalibrates = nullptr;
    ILuminousCalibrateCollection *luminousCalibrates = nullptr;
    IChromatismCollection *chromatisms = nullptr;
    IGradeCollection *grades = nullptr;
    IAdjustCollection *adjusts = nullptr;
    IQualityCollection *qualitys = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_P_H
