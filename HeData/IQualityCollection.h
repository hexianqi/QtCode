/***************************************************************************************************
**      2019-05-05  IQualityCollection 品质数据集合接口。
***************************************************************************************************/

#ifndef IQUALITYCOLLECTION_H
#define IQUALITYCOLLECTION_H

#include "IDataCollection.h"
#include "HQualityType.h"

HE_DATA_BEGIN_NAMESPACE

class IQuality;

class IQualityCollection : public IDataCollection<IQuality>
{
public:
    using IDataCollection::IDataCollection;

public:
    // 检验
    virtual HQualityReport check(QVariantMap value, QVariantMap *color = nullptr) = 0;
    // 颜色
    virtual QColor color(HQualityReport value) = 0;
    // 偏差
    virtual double drift(QString type, QVariant value) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IQUALITYCOLLECTION_H
