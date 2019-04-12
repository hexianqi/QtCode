#ifndef HCODECSL_P_H
#define HCODECSL_P_H

#include "HAbstractCodec_p.h"
#include "HCodecSL.h"
#include <QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCodecSLPrivate : public HAbstractCodecPrivate
{
public:
    HCodecSLPrivate();

public:
    QVector<bool> encrypts;
    QVector<bool> checkCodes;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HCODECSL_P_H
