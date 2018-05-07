#ifndef HPROTOCOLINFO_P_H
#define HPROTOCOLINFO_P_H

#include "HProtocolInfo.h"
#include <QSharedData>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolInfoPrivate : public QSharedData
{
public:
    IPort *port;
    int portNum;
    bool portNumScan;
    int deviceID;
    QMap<HActionType, QList<uchar>> actionParam;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLINFO_P_H
