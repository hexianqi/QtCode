#ifndef HCONFIGMANAGE_P_H
#define HCONFIGMANAGE_P_H

#include "HConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

class HConfigManagePrivate
{
public:
    HConfigManagePrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    quint32 contain;
    IDataFactory *factory = nullptr;
    IFileStream *fileStream = nullptr;
    ISpecCalibrateCollection *specCalibrates = nullptr;
    IGradeCollection *grades = nullptr;
    IAdjustCollection *adjusts = nullptr;
    IQualityCollection *qualitys = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_P_H
