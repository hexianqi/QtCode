/***************************************************************************************************
**      2019-12-10  HNetworkHelper 网络帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtNetwork/QAbstractSocket>

HE_BEGIN_NAMESPACE

class HNetworkHelper
{
public:
    // 本地IP
    static QStringList localIP(QAbstractSocket::NetworkLayerProtocol type = QAbstractSocket::IPv4Protocol);
    // 地址转字符串
    static QString toString(QHostAddress);
};

HE_END_NAMESPACE
