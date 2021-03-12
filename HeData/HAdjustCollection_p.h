#pragma once

#include "HAdjustCollection.h"
#include "IXlsxStream.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustCollectionPrivate : public HDataCollectionPrivate<IAdjust>
{
public:
    HAdjustCollectionPrivate();

public:
    void readContent(QDataStream &);
    void readContent(Document *);
    void writeContent(QDataStream &);
    void writeContent(Document *);
};

HE_DATA_END_NAMESPACE
