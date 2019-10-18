/***************************************************************************************************
**      2019-10-15  HElecCalibrateCollection 电校准数据集合类。
***************************************************************************************************/

#ifndef HELECCALIBRATECOLLECTION_H
#define HELECCALIBRATECOLLECTION_H

#include "IElecCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HElecCalibrateCollectionPrivate;

class HElecCalibrateCollection : public IElecCalibrateCollection
{
    Q_DECLARE_PRIVATE(HElecCalibrateCollection)

public:
    explicit HElecCalibrateCollection();
    virtual ~HElecCalibrateCollection();

public:
    QString typeName() override;

public:
    IFileStream *fileStream() override;

protected:
    HElecCalibrateCollection(HElecCalibrateCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HELECCALIBRATECOLLECTION_H
