#pragma once

#include "HAbstractCodec_p.h"
#include "HSlCodec.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HSlCodecPrivate : public HAbstractCodecPrivate
{
public:
    HSlCodecPrivate();

public:
    QVector<bool> encrypts;
    QVector<bool> checkCodes;
};

HE_END_NAMESPACE
