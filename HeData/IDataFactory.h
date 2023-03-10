/***************************************************************************************************
**      2018-06-19  IDataFactory 数据工厂接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IPrint;
class ITextExport;
class IDataStream;
class ITextStream;
class IXlsxStream;
class IMultStream;
class ITestData;
class ITestSpec;
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
class IQuality;
class IQualityCollection;
class IQualityItem;
class ILocation;
class ILocationCollection;
class IAdjust;
class IAdjust2;
class IAdjustCollection;
class IAdjust2Collection;
class IAdjustItem;
class IAdjustItemCollection;

class ILinearStrategy;

class IDataFactory : public IInitializeable
{
public:
    // 创建打印
    virtual IPrint *createPrint(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建文本导出
    virtual ITextExport *createTextExport(QString type, QVariantMap param = QVariantMap()) = 0;

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
    // 创建测试数据 - 光谱
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) = 0;

public:
    // 创建配置管理
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱校准数据
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建电校准数据
    virtual IElecCalibrateCollection *createElecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IElecCalibrate *createElecCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IElecCalibrateItemCollection *createElecCalibrateItemCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IElecCalibrateItem *createElecCalibrateItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光校准数据
    virtual ILuminousCalibrateCollection *createLuminousCalibrateCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual ILuminousCalibrate *createLuminousCalibrate(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual ILuminousCalibrateItem *createLuminousCalibrateItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建色容差数据
    virtual IChromatismCollection *createChromatismCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IChromatism *createChromatism(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IChromatismItem *createChromatismItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建分级数据
    virtual IGradeCollection *createGradeCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IGrade *createGrade(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IGradeItem *createGradeItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建品质数据
    virtual IQualityCollection *createQualityCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IQuality *createQuality(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IQualityItem *createQualityItem(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建布局数据
    virtual ILocationCollection *createLocationCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual ILocation *createLocation(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建校正数据
    virtual IAdjustCollection *createAdjustCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IAdjust2Collection *createAdjust2Collection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IAdjust *createAdjust(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IAdjust2 *createAdjust2(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IAdjustItemCollection *createAdjustItemCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual IAdjustItem *createAdjustItem(QString type, QVariantMap param = QVariantMap()) = 0;

public:
    // 创建线性策略
    virtual ILinearStrategy *createLinearStrategy(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE
