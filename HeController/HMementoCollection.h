/***************************************************************************************************
**      2022-02-10  HMementoCollection
***************************************************************************************************/

#pragma once

#include "IMementoCollection.h"

HE_BEGIN_NAMESPACE

class HMementoCollectionPrivate;

class HMementoCollection : public IMementoCollection
{
    Q_DECLARE_PRIVATE(HMementoCollection)

public:
    explicit HMementoCollection();
    ~HMementoCollection();

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName = QString()) override;

protected:
    HMementoCollection(HMementoCollectionPrivate &);
};

HE_END_NAMESPACE


