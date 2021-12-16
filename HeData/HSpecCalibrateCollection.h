/***************************************************************************************************
**      2018-06-19  HSpecCalibrateCollection 光谱校准数据集合类。
***************************************************************************************************/

#pragma once

#include "ISpecCalibrateCollection.h"

HE_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate;

class HSpecCalibrateCollection : public ISpecCalibrateCollection
{
    Q_DECLARE_PRIVATE(HSpecCalibrateCollection)

public:
    explicit HSpecCalibrateCollection();
    ~HSpecCalibrateCollection();

public:
    QString typeName() override;

public:
    IDataStream *dataStream() override;

protected:
    HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &);
};

HE_END_NAMESPACE
