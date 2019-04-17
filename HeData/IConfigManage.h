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

enum ConfigContainType
{
    CCT_No              = 0x00000000,
    CCT_Spec            = 0x00000001,
    CCT_Grade           = 0x00010000,
    CCT_All             = 0xFFFFFFFF
};
Q_DECLARE_FLAGS(ConfigContainTypes, ConfigContainType)

class IConfigManage : public IInitializeable
{
public:
    // 设置包含内容
    virtual void setContain(quint32 value) = 0;
    // 设置光谱校准数据集
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) = 0;
    // 设置分级数据集
    virtual void setGradeCollection(IGradeCollection *) = 0;

public:
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
    // 获取包含内容
    virtual quint32 contain() = 0;
    // 获取光谱校准数据
    virtual ISpecCalibrate *specCalibrate(QString name) = 0;
    // 获取分级数据集
    virtual IGradeCollection *gradeCollection() = 0;

public:
    // 导入部分数据
    virtual bool importPart(quint32 value) = 0;
    // 导出部分数据
    virtual bool exportPart(quint32 value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICONFIGMANAGE_H
