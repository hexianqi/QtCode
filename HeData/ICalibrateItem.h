/***************************************************************************************************
**      2019-03-27  ICalibrateItem  校准子项接口。
***************************************************************************************************/


#ifndef ICALIBRATEITEM_H
#define ICALIBRATEITEM_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ICalibrateItem : public IInitializeable
{
public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 设置数据
    virtual void setData(QString name, QVariant value) = 0;
    // 获取数据
    virtual QVariant data(QString name) = 0;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ICALIBRATEITEM_H
