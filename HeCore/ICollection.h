/***************************************************************************************************
**      2018-06-19  ICollection 集合模板接口。
***************************************************************************************************/

#ifndef ICOLLECTION_H
#define ICOLLECTION_H

#include "IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

template <typename T>
class ICollection : public IInitializeable
{
public:
    // 清空
    virtual void clear() = 0;
    // 是否包含
    virtual bool contains(QString key) = 0;
    // 插入
    virtual void insert(QString key, T *value) = 0;
    // 第一个值
    virtual T *first() = 0;
    // key值
    virtual T *value(QString key) = 0;
    // name项
    virtual T *item(QString key) = 0;
    // 所有键
    virtual QStringList keys() = 0;
    // 所有值
    virtual QList<T *> values() = 0;
};

HE_CORE_END_NAMESPACE

#endif // ICOLLECTION_H
