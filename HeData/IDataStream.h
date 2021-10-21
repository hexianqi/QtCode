/***************************************************************************************************
**      2020-09-29  IDataStream 数据流接口。
**                      class                       MagicNumber     Filter
**                  IConfigManage                   0x00010001      *.cfg
**                  ISpecCalibrateCollection        0x00020001      *.hcs
**                  IElecCalibrateCollection        0x00020002      *.hce
**                  ILuminousCalibrateCollection    0x00020003      *.hcl
**                  IChromatismCollection           0x00020101      *.hcc
**                  IGradeCollection                0x00030001      *.hcg
**                  IQualityCollection              0x00030101      *.hcq
**                  IAdjustCollection               0x00040001      *.hca
**                  IMemento                        0x01010001      *.tmp
***************************************************************************************************/

#pragma once

#include "IStream.h"
#include <functional>

HE_DATA_BEGIN_NAMESPACE

class IDataStream : public virtual IStream
{
public:
    // 设置Magic数
    virtual void setMagicNumber(quint32 value) = 0;
    // 设置文件版本
    virtual void setFileVersion(quint32 value) = 0;
    // 设置读取内容函数
    virtual void setReadContent(std::function<void(QDataStream &)> func) = 0;
    // 设置写入内容函数
    virtual void setWriteContent(std::function<void(QDataStream &)> func) = 0;
    // 读取内容
    virtual bool readContent(QDataStream &) = 0;
    // 写入内容
    virtual bool writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE
