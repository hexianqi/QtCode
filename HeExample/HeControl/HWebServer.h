/***************************************************************************************************
**      2022-08-01  HWebServer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWebSockets/QWebSocketServer>

HE_BEGIN_NAMESPACE

class HWebServerPrivate;

class HWebServer : public QWebSocketServer
{
    Q_OBJECT

public:
    explicit HWebServer(const QString &serverName = QString(), QWebSocketServer::SslMode secureMode = QWebSocketServer::NonSecureMode, QObject *parent = nullptr);
    ~HWebServer() override;

signals:
    void connected(const QString &address, int port);
    void disconnected(const QString &address, int port);
    void error(const QString &address, int port, const QString &error);
    void sentData(const QString &address, int port, const QString &data);
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QString &data);
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
    void sendData(const QString &data);
    void sendData(const QByteArray &data);
    void sendData(const QString &address, int port, const QString &data);
    void sendData(const QString &address, int port, const QByteArray &data);
    // 断开连接
    void disconnectClient();
    void disconnectClient(const QString &address, int port);

protected:
    void handleNewConnection();
    void handleDisconnected();

protected:
    QScopedPointer<HWebServerPrivate> d_ptr;
};

HE_END_NAMESPACE

