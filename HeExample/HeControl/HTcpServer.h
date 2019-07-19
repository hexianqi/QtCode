/***************************************************************************************************
**      2019-07-17  HTcpServer
***************************************************************************************************/

#ifndef HTCPSERVER_H
#define HTCPSERVER_H

#include "HControlGlobal.h"
#include <QtNetwork/QTcpServer>

HE_CONTROL_BEGIN_NAMESPACE

class HTcpServerPrivate;

class HTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit HTcpServer(QObject *parent = nullptr);
    ~HTcpServer() override;

signals:
    void clientConnected(const QString &ip, int port);
    void clientDisconnected(const QString &ip, int port);
    void sentData(QString ip, int port, QByteArray data);
    void receiveData(QString ip, int port, QByteArray data);

public slots:
    // 启动服务
    bool start();
    // 停止服务
    void stop();
    // 设置监听端口
    void setListenPort(quint16 value);
    // 指定连接发送数据
    void sendData(QString ip, int port, QByteArray data);
    // 对所有连接发送数据
    void sendData(QByteArray data);
    // 断开连接
    void disconnectClient(QString ip, int port);

protected:
    HTcpServer(HTcpServerPrivate &p, QObject *parent = nullptr);

protected:
    void incomingConnection(int handle) override;
    void handleClientDisconnected();

protected:
    QScopedPointer<HTcpServerPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPSERVER_H
