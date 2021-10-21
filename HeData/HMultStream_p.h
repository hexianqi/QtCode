#pragma once

#include "HMultStream.h"
#include "HAbstractStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class HMultStreamPrivate : public HAbstractStreamPrivate
{
public:
    IStream *findStream(QString fileName);

public:
    QMap<QString, IStream *> streams;
    IStream *defaultStream = nullptr;
};

HE_DATA_END_NAMESPACE

