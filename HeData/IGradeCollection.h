/***************************************************************************************************
**      2019-04-16  IGradeCollection 分级数据集合接口。
***************************************************************************************************/

#ifndef IGRADECOLLECTION_H
#define IGRADECOLLECTION_H

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class IFileStream;
class IGrade;

class IGradeCollection : public HCollection<IGrade>
{
public:
    using HCollection::HCollection;

public:
    // 获取数据工厂
    virtual IDataFactory *dataFactory() = 0;
    // 获取文件流
    virtual IFileStream *fileStream() = 0;
    // 使用的索引
    virtual QString useIndex() = 0;
    // 设置使用索引
    virtual void setUseIndex(QString value) = 0;
    // 计算级别
    virtual int calcLevel(QVariantMap value, QString &text) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADECOLLECTION_H
