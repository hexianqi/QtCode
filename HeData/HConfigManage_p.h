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
    IDataFactory *factory;
    IFileStream *fileStream;
    ISpecCalibrateCollection *specCalibrates;
    IGradeCollection *grades;
    quint32 contain;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_P_H
