#pragma once

#include "HMementoCollection.h"

HE_BEGIN_NAMESPACE

class IControllerFactory;
class IDataStream;

class HMementoCollectionPrivate : public HCollectionPrivate<IMemento>
{
public:
    HMementoCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IControllerFactory *factory = nullptr;
    IDataStream *dataStream = nullptr;
    QString fileName;
};

HE_END_NAMESPACE



