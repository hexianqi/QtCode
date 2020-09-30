/***************************************************************************************************
**      2018-06-19  HSpecCalibrateCollection 光谱校准数据集合类。
***************************************************************************************************/

#ifndef HSPECCALIBRATECOLLECTION_H
#define HSPECCALIBRATECOLLECTION_H

#include "ISpecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate;

class HSpecCalibrateCollection : public ISpecCalibrateCollection
{
    Q_DECLARE_PRIVATE(HSpecCalibrateCollection)

public:
    explicit HSpecCalibrateCollection();
    virtual ~HSpecCalibrateCollection() = default;

public:
    QString typeName() override;

public:
    IDataStream *dataStream() override;

protected:
    HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_H
