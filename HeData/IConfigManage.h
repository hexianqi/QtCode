#ifndef ICONFIGMANAGE_H
#define ICONFIGMANAGE_H

#include "IFileStream.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate;
class ISpecCalibrateCollection;

enum ConfigContainType
{
    CCT_No              = 0x00000000,
    CCT_Spec            = 0x00000001,
    CCT_All             = 0xFFFFFFFF
};

Q_DECLARE_FLAGS(ConfigContainTypes, ConfigContainType)

class IConfigManage : virtual public IFileStream, public IInitializeable
{
public:
    virtual void setContain(ConfigContainType value) = 0;
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) = 0;
    virtual ISpecCalibrate *getSpecCalibrate(QString name) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICONFIGMANAGE_H
