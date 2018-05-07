#ifndef HABSTRACTPROTOCOLSTRATEGY_P_H
#define HABSTRACTPROTOCOLSTRATEGY_P_H

#include "HAbstractProtocolStrategy.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractProtocolStrategyPrivate
{
public:
    IPort *port;
    int portNum;
    bool portNumScan;
    int deviceID;
    QMap<HActionType, QList<uchar>> actionParam;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOLSTRATEGY_P_H
