#include "HNetworkLog_p.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <mutex>

HE_CONTROL_BEGIN_NAMESPACE

QScopedPointer<HNetworkLog> HNetworkLog::__instance;
static std::once_flag __oc; // 用于call_once的局部静态变量

HNetworkLog *HNetworkLog::instance(QObject *parent)
{
    std::call_once(__oc, [&]{ __instance.reset(new HNetworkLog(parent)); });
    return __instance.data();
}

HNetworkLog::HNetworkLog(QObject *parent) :
    QObject(parent),
    d_ptr(new HNetworkLogPrivate)
{
    init();
}

HNetworkLog::HNetworkLog(HNetworkLogPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HNetworkLog::~HNetworkLog()
{
    if (d_ptr->socket != nullptr)
        d_ptr->socket->disconnectFromHost();
    d_ptr->server->close();
}

void HNetworkLog::send(const QString &value)
{
    if (d_ptr->socket == nullptr || !d_ptr->socket->isOpen())
        return;
    d_ptr->socket->write(value.toUtf8());
    d_ptr->socket->flush();
}

void HNetworkLog::init()
{
    d_ptr->socket = nullptr;
    d_ptr->server = new QTcpServer(this);
    connect(d_ptr->server, &QTcpServer::newConnection, this, &HNetworkLog::handleNewConnection);
    d_ptr->server->listen(QHostAddress::AnyIPv4, 6000);
}

void HNetworkLog::handleNewConnection()
{
    while (d_ptr->server->hasPendingConnections())
        d_ptr->socket = d_ptr->server->nextPendingConnection();
}


HE_CONTROL_END_NAMESPACE
