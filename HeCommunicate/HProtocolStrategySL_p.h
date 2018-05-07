#ifndef HPROTOCOLSTRATEGYSL_P_H
#define HPROTOCOLSTRATEGYSL_P_H

#include "HAbstractProtocolStrategy_p.h"
#include "HProtocolStrategySL.h"
#include <QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolStrategySLPrivate : public HAbstractProtocolStrategyPrivate
{
public:
    HProtocolStrategySLPrivate();

public:
    void setEncrypt(QVector<bool> value);
    void setCheckCode(QVector<bool> value);
    bool isEncrypt(int n);
    bool isCheckCode(int n);

public:
    QVector<bool> encrypts;
    QVector<bool> checkCodes;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLSTRATEGYSL_P_H
