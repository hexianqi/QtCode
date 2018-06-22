/***************************************************************************************************
**      2018-06-19  IDataFactory 数据工厂接口。
***************************************************************************************************/

#ifndef IDATAFACTORY_H
#define IDATAFACTORY_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IConfigManage;
class ISpecCalibrate;
class ISpecCalibrateCollection;

class IDataFactory : public IInitializeable
{
public:
    // 创建配置管理
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准集合
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATAFACTORY_H
