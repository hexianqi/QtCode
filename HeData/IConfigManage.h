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
class IGradeCollection;
class IAdjustCollection;
class IQualityCollection;

class IConfigManage : public IInitializeable
{
public:
    enum ContainType
    {
        ContainNone          = 0x00000000,
        ContainSpec          = 0x00000001,
        ContainGrade         = 0x00010000,
        ContainQuality       = 0x00020000,
        ContainAdjust        = 0x01000000,
        ContainAll           = 0xFFFFFFFF
    };
    Q_DECLARE_FLAGS(ContainTypes, ContainType)

public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
    // 设置包含内容
    virtual void setContain(quint32 value) = 0;
    // 获取包含内容
    virtual quint32 contain() = 0;
    // 设置光谱校准数据集
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) = 0;
    // 获取光谱校准数据
    virtual ISpecCalibrate *specCalibrate(QString name) = 0;
    // 设置分级数据集
    virtual void setGradeCollection(IGradeCollection *) = 0;
    // 获取分级数据集
    virtual IGradeCollection *gradeCollection() = 0;
    // 设置分级数据集
    virtual void setAdjustCollection(IAdjustCollection *) = 0;
    // 获取分级数据集
    virtual IAdjustCollection *adjustCollection() = 0;
    // 设置品质数据集
    virtual void setQualityCollection(IQualityCollection *) = 0;
    // 获取品质数据集
    virtual IQualityCollection *qualityCollection() = 0;

public:
    // 导入部分数据
    virtual bool importPart(quint32 value) = 0;
    // 导出部分数据
    virtual bool exportPart(quint32 value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICONFIGMANAGE_H
