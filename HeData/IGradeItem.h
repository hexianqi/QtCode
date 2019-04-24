/***************************************************************************************************
**      2019-04-17  IGradeItem  分级数据子项接口。
***************************************************************************************************/

#ifndef IGRADEITEM_H
#define IGRADEITEM_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IGradeItem : public IInitializeable
{
public:
    // 设置数据
    virtual void setData(QString name, QVariant value) = 0;
    // 获取数据
    virtual QVariant data(QString name) = 0;
    // 设置等级
    virtual void setLevels(QVariant value) = 0;
    // 等级
    virtual QVariant levels() = 0;
    // 等级
    virtual QStringList level(int i) = 0;
    // 索引
    virtual QSet<int> indexOf(QVariant value) = 0;
    // 总数
    virtual int count() = 0;
    // 表头
    virtual QStringList headers() = 0;
    // 数据类型
    virtual QStringList types() = 0;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADEITEM_H
