/***************************************************************************************************
**      2019-07-17  HTcpServer TCP服务端。
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
    void sentData(const QString &ip, int port, const QByteArray &data);
    void receiveData(const QString &ip, int port, const QByteArray &data);

public slots:
    // 是否运行
    bool isRunning();
    // 启动服务
    bool start();
    // 停止服务
    void stop();
    // 设置监听IP
    void setListenIP(const QString &value);
    // 设置监听端口
    void setListenPort(int value);
    // 发送数据
    void sendData(const QByteArray &data);
    void sendData(const QString &ip, int port, const QByteArray &data);
    // 断开连接
    void disconnectClient();
    void disconnectClient(const QString &ip, int port);

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
