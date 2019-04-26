/***************************************************************************************************
**      2019-04-26  IAdjustCollection 调整数据集合接口。
***************************************************************************************************/

#ifndef IADJUSTCOLLECTION_H
#define IADJUSTCOLLECTION_H

#include "IDataCollection.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IAdjust;

class IAdjustCollection : public HCollection<IAdjust>, public IDataCollection
{
public:
    using HCollection::HCollection;

public:
    // 纠正
    virtual QVariantMap correct(QVariantMap value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IADJUSTCOLLECTION_H
