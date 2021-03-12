/***************************************************************************************************
**      2019-07-12  HMultTcpServer 多客户端Tcp服务器
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtNetwork/QTcpServer>

HE_CONTROL_BEGIN_NAMESPACE

class HMultTcpServerPrivate;

class HMultTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit HMultTcpServer(QObject *parent = nullptr);
    ~HMultTcpServer() override;

signals:
    void clientConnected(qintptr, QTcpSocket*);
    void clientDisconnected(qintptr);

public:
     void initiativeDisconnectClient(qintptr);

protected:
    HMultTcpServer(HMultTcpServerPrivate &p, QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr handle) override;
    void handleClientDisconnected();

protected:
    QScopedPointer<HMultTcpServerPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
