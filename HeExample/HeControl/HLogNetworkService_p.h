#pragma once

#include "HLogNetworkService.h"
#include "HAbstractService_p.h"

class QTcpSocket;
class QTcpServer;

HE_BEGIN_NAMESPACE

class HLogNetworkServicePrivate : public HAbstractServicePrivate
{
public:
    int listenPort = 6000;          // 监听端口
    QTcpSocket *socket = nullptr;   // 网络通信对象
    QTcpServer *server = nullptr;   // 网络监听服务器
};

HE_END_NAMESPACE

