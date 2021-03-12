/***************************************************************************************************
**      2018-06-19  HDeviceCollection 设备集合类。
***************************************************************************************************/

#pragma once

#include "IDeviceCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceCollectionPrivate;

class HDeviceCollection : public IDeviceCollection
{
    Q_DECLARE_PRIVATE(HDeviceCollection)

public:
    explicit HDeviceCollection();
    virtual ~HDeviceCollection();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void addSupport(HActionType action) override;
    bool isSupport(HActionType action) override;

protected:
    HDeviceCollection(HDeviceCollectionPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE
