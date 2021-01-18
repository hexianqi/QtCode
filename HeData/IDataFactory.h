/***************************************************************************************************
**      2018-06-19  IDataFactory 数据工厂接口。
***************************************************************************************************/

#ifndef IDATAFACTORY_H
#define IDATAFACTORY_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IDataStream;
class ITextStream;
class IXlsxStream;
class IMultStream;
class ITestData;
class ITestSpec;
class ITestElec;
class ITestLuminous;
class IConfigManage;
class ISpecCalibrate;
class ISpecCalibrateCollection;
class IElecCalibrate;
class IElecCalibrateCollection;
class IElecCalibrateItem;
class IElecCalibrateItemCollection;
class ILuminousCalibrate;
class ILuminousCalibrateCollection;
class ILuminousCalibrateItem;
class IChromatism;
class IChromatismCollection;
class IChromatismItem;
class IGrade;
class IGradeCollection;
class IGradeItem;
class IAdjust;
class IAdjustCollection;
class IAdjustItem;
class IQuality;
class IQualityCollection;
class IQualityItem;
class HSpecFitting;

class IDataFactory : public IInitializeable
{
public:
    // 创建数据流
    virtual IDataStream *createDataStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建文本流
    virtual ITextStream *createTextStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建Xlsx流
    virtual IXlsxStream *createXlsxStream(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建组合流
    virtual IMultStream *createMultStream(QString type, QVariantMap param = QVariantMap()) = 0;

public:
    // 创建测试数据
    virtual ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱测试数据
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电测试数据
    virtual ITestElec *createTestElec(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光测试数据
    virtual ITestLuminous *createTestLuminous(QString type, QVariantMap param = QVariantMap()) = 0;

public:
    // 创建配置管理
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据集
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电校准数据集
    virtual IElecCalibrateCollection *createElecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电校准数据
    virtual IElecCalibrate *createElecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电校准数据子项集
    virtual IElecCalibrateItemCollection *createElecCalibrateItemCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电校准数据子项
    virtual IElecCalibrateItem *createElecCalibrateItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光校准数据集
    virtual ILuminousCalibrateCollection *createLuminousCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光校准数据
    virtual ILuminousCalibrate *createLuminousCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光校准数据子项
    virtual ILuminousCalibrateItem *createLuminousCalibrateItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建色容差数据集
    virtual IChromatismCollection *createChromatismCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建色容差数据
    virtual IChromatism *createChromatism(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建色容差数据子项
    virtual IChromatismItem *createChromatismItem(QString type, QVariantMap param = QVariantMap()) = 0;
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
    // 创建光谱拟合
    virtual HSpecFitting *createSpecFitting(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATAFACTORY_H
