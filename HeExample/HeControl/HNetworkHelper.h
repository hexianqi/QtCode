/***************************************************************************************************
**      2019-12-10  HNetworkHelper 网络帮助类。
***************************************************************************************************/

#ifndef HNETWORKHELPER_H
#define HNETWORKHELPER_H

#include "HControlGlobal.h"
#include <QtNetwork/QAbstractSocket>

HE_CONTROL_BEGIN_NAMESPACE

class HNetworkHelper
{
public:
    // 本地IP
    static QStringList localIP(QAbstractSocket::NetworkLayerProtocol type = QAbstractSocket::IPv4Protocol);

};

HE_CONTROL_END_NAMESPACE

#endif // HNETWORKHELPER_H
