/***************************************************************************************************
**      2018-06-19  IConfigManage 配置管理接口。
***************************************************************************************************/

#ifndef ICONFIGMANAGE_H
#define ICONFIGMANAGE_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream;
class ISpecCalibrate;
class ISpecCalibrateCollection;

enum ConfigContainType
{
    CCT_No              = 0x00000000,
    CCT_Spec            = 0x00000001,
    CCT_All             = 0xFFFFFFFF
};

Q_DECLARE_FLAGS(ConfigContainTypes, ConfigContainType)

class IConfigManage : public IInitializeable
{
public:
    virtual void setContain(quint32 value) = 0;
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) = 0;

public:
    virtual quint32 contain() = 0;
    virtual ISpecCalibrate *specCalibrate(QString name) = 0;
    virtual IFileStream *fileStream() = 0;

public:
    virtual bool importPart(quint32 value) = 0;
    virtual bool exportPart(quint32 value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICONFIGMANAGE_H
