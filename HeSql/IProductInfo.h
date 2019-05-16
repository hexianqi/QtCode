/***************************************************************************************************
**      2019-05-14  IProductInfo 产品信息接口。
***************************************************************************************************/

#ifndef IPRODUCTINFO_H
#define IPRODUCTINFO_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtCore/QVariant>

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class IProductInfo : public IInitializeable
{
public:
    // 设置关联表
    virtual void setRelationTableName(QString value) = 0;
    // 设置数据
    virtual void setData(QString type, QVariant value) = 0;
    virtual void setData(QVariantMap value) = 0;
    // 获取数据
    virtual QVariant data(QString type) = 0;
    // 是否包含
    virtual bool contains(QString type) = 0;
    // 是否自增
    virtual bool increase() = 0;
    // 是否编辑
    virtual bool editable() = 0;
    // 保存一次
    virtual void saveOnce() = 0;
};

HE_SQL_END_NAMESPACE

#endif // IPRODUCTINFO_H
