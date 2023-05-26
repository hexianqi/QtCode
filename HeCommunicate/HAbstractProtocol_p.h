#pragma once

#include "HAbstractProtocol.h"

class QMutex;

HE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate
{
public:
    HAbstractProtocolPrivate();
    ~HAbstractProtocolPrivate();

public:
    IDevice *device = nullptr;
    IUCharConvert *convert = nullptr;
    QMutex *mutex = nullptr;
};

HE_END_NAMESPACE
