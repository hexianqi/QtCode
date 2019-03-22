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
    virtual bool contains(QString name) = 0;
    // 插入
    virtual void insert(QString name, T *value) = 0;
    // 第一个值
    virtual T *first() = 0;
    // name值
    virtual T *value(QString name) = 0;
    // 所有值
    virtual QList<T *> values() = 0;
};

HE_CORE_END_NAMESPACE

#endif // ICOLLECTION_H
