/***************************************************************************************************
**      2019-03-27  IDataItem  数据子项接口。
***************************************************************************************************/


#ifndef IDATAITEM_H
#define IDATAITEM_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IDataItem : public IInitializeable
{
public:
    // 设置数据
    virtual void setData(QString name, QVariant value) = 0;
    // 设置数据
    virtual void setData(QVariantMap value) = 0;
    // 获取数据
    virtual QVariant data(QString name) = 0;
    // 获取数据
    virtual QVariantMap data() = 0;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IDATAITEM_H
