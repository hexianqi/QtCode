/***************************************************************************************************
**      2020-05-22  HLuminousCalibrateCollection 光校准数据集合类。
***************************************************************************************************/

#pragma once

#include "ILuminousCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HLuminousCalibrateCollectionPrivate;

class HLuminousCalibrateCollection : public ILuminousCalibrateCollection
{
    Q_DECLARE_PRIVATE(HLuminousCalibrateCollection)

public:
    explicit HLuminousCalibrateCollection();
    virtual ~HLuminousCalibrateCollection() = default;

public:
    QString typeName() override;

public:
    IFileStream *fileStream() override;

protected:
    HLuminousCalibrateCollection(HLuminousCalibrateCollectionPrivate &);
};

HE_DATA_END_NAMESPACE
