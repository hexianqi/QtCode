/***************************************************************************************************
**      2019-04-16  IGradeCollection 分级数据集合接口。
***************************************************************************************************/

#ifndef IGRADECOLLECTION_H
#define IGRADECOLLECTION_H

#include "IDataCollection.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IGrade;

class IGradeCollection : public HCollection<IGrade>, public IDataCollection
{
public:
    using HCollection::HCollection;

public:
    // 获取某类型所有分级
    virtual QVariant levels(QString type) = 0;
    // 计算分级
    virtual int calcLevel(QVariantMap value, QString &text) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IGRADECOLLECTION_H
