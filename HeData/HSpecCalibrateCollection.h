#ifndef HSPECCALIBRATECOLLECTION_H
#define HSPECCALIBRATECOLLECTION_H

#include "ISpecCalibrateCollection.h"
#include "HAbstractFileStream.h"
#include "HeCore/HCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibrateCollectionPrivate;

class HSpecCalibrateCollection : public HCollection<ISpecCalibrate>, public HAbstractFileStream, public ISpecCalibrateCollection
{
    Q_DECLARE_PRIVATE(HSpecCalibrateCollection)

public:
    explicit HSpecCalibrateCollection(IDataFactory *);
    ~HSpecCalibrateCollection();

public:
    virtual QString typeName() override;
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

protected:
    HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_H
