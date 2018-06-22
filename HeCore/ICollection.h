/***************************************************************************************************
**      2018-06-19  ICollection 集合模板接口。
***************************************************************************************************/

#ifndef ICOLLECTION_H
#define ICOLLECTION_H

#include "IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

template <class T>
class ICollection : public IInitializeable
{
public:
    virtual void clear() = 0;
    virtual bool contains(QString name) = 0;
    virtual void insert(QString name, T *value) = 0;
    virtual T *first() = 0;
    virtual T *value(QString name) = 0;
    virtual QList<T *> values() = 0;
};

HE_CORE_END_NAMESPACE

#endif // ICOLLECTION_H
