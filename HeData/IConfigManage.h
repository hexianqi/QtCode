/***************************************************************************************************
**      2018-06-19  IConfigManage 配置管理接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IStream;
class ISpecCalibrate;
class ISpecCalibrateCollection;
class IElecCalibrateCollection;
class ILuminousCalibrateCollection;
class IChromatismCollection;
class IGradeCollection;
class IQualityCollection;
class ILocationCollection;
class IAdjustCollection;
class IAdjust2Collection;
class ITestData;

class IConfigManage : public IInitializeable
{
public:
    enum ContainType
    {
        ContainNone          = 0x00000000,
        ContainSpec          = 0x00000001,
        ContainElec          = 0x00000002,
        ContainLuminous      = 0x00000004,
        ContainChromatism    = 0x00000100,
        ContainGrade         = 0x00010000,
        ContainQuality       = 0x00020000,
        ContainLocation      = 0x00100000,
        ContainAdjust        = 0x01000000,
        ContainAdjust2       = 0x02000000,
        ContainAll           = 0xFFFFFFFF
    };
    Q_DECLARE_FLAGS(ContainTypes, ContainType)

public:
    // 获取流
    virtual IStream *stream() = 0;
    // 包含内容
    virtual void setContain(quint32 value) = 0;
    virtual quint32 contain() = 0;
    // 光谱校准数据
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) = 0;
    virtual ISpecCalibrate *specCalibrate(QString name) = 0;
    // 电校准数据
    virtual void setElecCalibrateCollection(IElecCalibrateCollection *) = 0;
    virtual IElecCalibrateCollection *elecCalibrateCollection() = 0;
    // 光校准数据
    virtual void setLuminousCalibrateCollection(ILuminousCalibrateCollection *) = 0;
    virtual ILuminousCalibrateCollection *luminousCalibrateCollection() = 0;
    // 色容差数据
    virtual void setChromatismCollection(IChromatismCollection *) = 0;
    virtual IChromatismCollection *chromatismCollection() = 0;
    // 分级数据
    virtual void setGradeCollection(IGradeCollection *) = 0;
    virtual IGradeCollection *gradeCollection() = 0;
    // 品质数据
    virtual void addQualityCollection(QString key, IQualityCollection *) = 0;
    virtual IQualityCollection *qualityCollection(QString key) = 0;
    // 布局数据
    virtual void setLocationCollection(ILocationCollection *) = 0;
    virtual ILocationCollection *locationCollection() = 0;
    // 调整数据
    virtual void setAdjustCollection(IAdjustCollection *) = 0;
    virtual void setAdjust2Collection(IAdjust2Collection *) = 0;
    virtual IAdjustCollection *adjustCollection() = 0;
    virtual IAdjust2Collection *adjust2Collection() = 0;

public:
    // 导入部分数据
    virtual bool importPart(quint32 value) = 0;
    // 导出部分数据
    virtual bool exportPart(quint32 value) = 0;

public:
    // 测试数据后续处理
    virtual QStringList supplement(QStringList) = 0;
    virtual void processAll(ITestData *, QStringList optional, QString keyQuality) = 0;
    virtual bool processChromatism(ITestData *) = 0;
    virtual bool processAdjust(ITestData *, QStringList optional) = 0;
    virtual bool processGrade(ITestData *, QStringList optional) = 0;
    virtual bool processQuality(ITestData *, QStringList optional, QString key) = 0;
};

HE_END_NAMESPACE
