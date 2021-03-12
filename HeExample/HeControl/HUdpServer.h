/***************************************************************************************************
**      2019-12-11  HUdpServer
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServerPrivate;

class HUdpServer : public QObject
{
    Q_OBJECT

public:
    explicit HUdpServer(QObject *parent = nullptr);
    ~HUdpServer() override;

signals:
    void clientConnected(const QString &address, int port);
    void clientDisconnected(const QString &address, int port);
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
    void sendData(const QString &ip, int port, const QByteArray &data);
    // 新连接
    void incomingConnection(const QString &ip, int port);
    // 断开连接
    void disconnectClient();
    void disconnectClient(const QString &ip, int port);

protected:
    HUdpServer(HUdpServerPrivate &p, QObject *parent = nullptr);

protected slots:
    void handleReadyRead();

protected:
    QScopedPointer<HUdpServerPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
