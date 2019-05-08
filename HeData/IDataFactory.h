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
class ITestData;
class ITestSpec;
class IConfigManage;
class ISpecCalibrate;
class ISpecCalibrateCollection;
class IGrade;
class IGradeCollection;
class IGradeItem;
class IAdjust;
class IAdjustCollection;
class IAdjustItem;
class IQuality;
class IQualityCollection;
class IQualityItem;

class IDataFactory : public IInitializeable
{
public:
    // 创建文件流
    virtual IFileStream *createFileStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建Excel文件流
    virtual IExcelStream *createExcelStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建测试数据
    virtual ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱测试数据
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建配置管理
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据集
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建分级数据集
    virtual IGradeCollection *createGradeCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建分级数据
    virtual IGrade *createGrade(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建分级数据子项
    virtual IGradeItem *createGradeItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建校正数据集
    virtual IAdjustCollection *createAdjustCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建校正数据
    virtual IAdjust *createAdjust(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建校正数据子项
    virtual IAdjustItem *createAdjustItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建品质数据集
    virtual IQualityCollection *createQualityCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建品质数据
    virtual IQuality *createQuality(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建品质数据子项
    virtual IQualityItem *createQualityItem(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATAFACTORY_H
