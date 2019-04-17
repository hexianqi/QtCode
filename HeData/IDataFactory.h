/***************************************************************************************************
**      2018-06-19  IDataFactory 数据工厂接口。
***************************************************************************************************/

#ifndef IDATAFACTORY_H
#define IDATAFACTORY_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IFileStream;
class IExcelStream;
class IConfigManage;
class ISpecCalibrate;
class ISpecCalibrateCollection;
class IGradeCollection;

class IDataFactory : public IInitializeable
{
public:
    // 创建文件流
    virtual IFileStream *createFileStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建Excel文件流
    virtual IExcelStream *createExcelStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建配置管理
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准时间
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据集
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建分级数据集
    virtual IGradeCollection *createGradeCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATAFACTORY_H
