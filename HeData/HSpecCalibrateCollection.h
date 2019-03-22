/***************************************************************************************************
**      2018-06-19  HSpecCalibrateCollection 光谱校准数据集合类。
***************************************************************************************************/

#ifndef HSPECCALIBRATECOLLECTION_H
#define HSPECCALIBRATECOLLECTION_H

#include "ISpecCalibrateCollection.h"
#include "HeCore/HCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class HSpecCalibrateCollectionPrivate;

class HSpecCalibrateCollection : public HCollection<ISpecCalibrate>, public ISpecCalibrateCollection
{
    Q_DECLARE_PRIVATE(HSpecCalibrateCollection)

public:
    explicit HSpecCalibrateCollection(IDataFactory *);
    virtual ~HSpecCalibrateCollection();

public:
    QString typeName() override;

public:
    IFileStream *fileStream() override;

protected:
    HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &);

protected:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

protected:
    QScopedPointer<HSpecCalibrateCollectionPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATECOLLECTION_H
