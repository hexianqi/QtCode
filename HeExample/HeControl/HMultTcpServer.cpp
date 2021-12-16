#include "HMultTcpServer_p.h"
#include <QtNetwork/QTcpSocket>

HE_BEGIN_NAMESPACE

HMultTcpServer::HMultTcpServer(QObject *parent) :
    QTcpServer(parent),
    d_ptr(new HMultTcpServerPrivate)
{
}

HMultTcpServer::HMultTcpServer(HMultTcpServerPrivate &p, QObject *parent) :
    QTcpServer(parent),
    d_ptr(&p)
{
}

HMultTcpServer::~HMultTcpServer()
{
    for (auto c : d_ptr->clients)
    {
        c->disconnectFromHost();
        auto h = c->socketDescriptor();
        c->deleteLater();
        // 告知其他调用者当前socket断开，避免有需要在socket后执行的方法
        emit clientDisconnected(h);
    }
    close();
}

void HMultTcpServer::initiativeDisconnectClient(qintptr handle)
{
    if (!d_ptr->clients.contains(handle))
        return;
    d_ptr->clients.value(handle)->disconnectFromHost();
}

void HMultTcpServer::incomingConnection(qintptr handle)
{
    if (d_ptr->clients.size() > maxPendingConnections())
        return;

    auto s = new QTcpSocket(this);
    s->setSocketDescriptor(handle);
    d_ptr->clients.insert(handle, s);
    connect(s, &QTcpSocket::disconnected, this, &HMultTcpServer::handleClientDisconnected);
    emit clientConnected(handle, s);
}

void HMultTcpServer::handleClientDisconnected()
{
    auto s = qobject_cast<QTcpSocket *>(sender());
    if (s == nullptr)
        return;
    auto d = s->socketDescriptor();
    d_ptr->clients.remove(d);
    s->deleteLater();
    emit clientDisconnected(d);
}

HE_END_NAMESPACE
