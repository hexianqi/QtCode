/***************************************************************************************************
**      2019-04-12  ISqlFactory 数据库工厂接口。
***************************************************************************************************/

#ifndef ISQLFACTORY_H
#define ISQLFACTORY_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

//class IFileStream;
//class IExcelStream;
//class IConfigManage;
//class ISpecCalibrate;
//class ISpecCalibrateCollection;

class ISqlFactory : public IInitializeable
{
public:
//    // 创建文件流
//    virtual IFileStream *createFileStream(QString type, QVariantMap param = QVariantMap()) = 0;
//    // 创建Excel文件流
//    virtual IExcelStream *createExcelStream(QString type, QVariantMap param = QVariantMap()) = 0;
//    // 创建配置管理
//    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
//    // 创建光谱校准
//    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
//    // 创建光谱校准集合
//    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLFACTORY_H
