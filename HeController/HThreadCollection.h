/***************************************************************************************************
**      2018-06-19  HThreadCollection 线程集合类。
***************************************************************************************************/

#pragma once

#include "IThreadCollection.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HThreadCollectionPrivate;

class HThreadCollection : public IThreadCollection
{
    Q_DECLARE_PRIVATE(HThreadCollection)

public:
    explicit HThreadCollection();
    virtual ~HThreadCollection();

public:
    QString typeName() override;

protected:
    HThreadCollection(HThreadCollectionPrivate &);
};

HE_CONTROLLER_END_NAMESPACE
