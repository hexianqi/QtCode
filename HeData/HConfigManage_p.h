#ifndef HCONFIGMANAGE_P_H
#define HCONFIGMANAGE_P_H

#include "HConfigManage.h"
#include "HAbstractFileStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class ISpecCalibrateCollection;

class HConfigManagePrivate : public HAbstractFileStreamPrivate
{
public:
    HConfigManagePrivate(IDataFactory *);

public:
    quint32 contain = 0;
    ISpecCalibrateCollection *specCalibrates = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_P_H
