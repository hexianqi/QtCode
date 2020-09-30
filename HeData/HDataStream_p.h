#pragma once

#include "HDataStream.h"
#include "HAbstractStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class HDataStreamPrivate : public HAbstractStreamPrivate
{
public:
    HDataStreamPrivate();

public:
    quint32 magicNumber;
    quint32 fileVersion;

public:
    std::function<void(QDataStream &)> readContent = nullptr;
    std::function<void(QDataStream &)> writeContent = nullptr;
};

HE_DATA_END_NAMESPACE

