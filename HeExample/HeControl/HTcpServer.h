/***************************************************************************************************
**      2019-07-17  HTcpServer TCP服务端。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtNetwork/QTcpServer>

HE_BEGIN_NAMESPACE

class HTcpServerPrivate;

class HTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit HTcpServer(QObject *parent = nullptr);
    ~HTcpServer() override;

signals:
    void connected(const QString &address, int port);
    void disconnected(const QString &address, int port);
    void error(const QString &address, int port, const QString &error);
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QByteArray &data);

public slots:
    // 是否运行
    bool isRunning();
    // 启动服务
    bool start();
    // 停止服务
    void stop();
    // 设置监听地址
    void setListenAddress(const QString &value);
    // 设置监听端口
    void setListenPort(int value);
    // 发送数据
    void sendData(const QByteArray &data);
    void sendData(const QString &address, int port, const QByteArray &data);
    // 断开连接
    void disconnectClient();
    void disconnectClient(const QString &address, int port);

protected:
    HTcpServer(HTcpServerPrivate &p, QObject *parent = nullptr);

protected:
    void handleNewConnection();
    void handleDisconnected();

protected:
    QScopedPointer<HTcpServerPrivate> d_ptr;
};

HE_END_NAMESPACE
