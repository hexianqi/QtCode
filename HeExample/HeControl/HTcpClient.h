/***************************************************************************************************
**      2019-07-16  HTcpClient TCP客户端。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class QTcpSocket;

HE_BEGIN_NAMESPACE

class HTcpClientPrivate;

class HTcpClient : public QObject
{
    Q_OBJECT

public:
    explicit HTcpClient(QTcpSocket *socket, QObject *parent = nullptr);
    ~HTcpClient() override;

signals:
    void disconnected(const QString &ip, int port);
    void error(const QString &address, int port, const QString &error);
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QByteArray &data);

public:
    QString address();
    int port();

public slots:
    void sendData(const QByteArray &value);
    void disconnectFromHost();
    void abort();

protected slots:
    void handleError();
    void handleDisconnected();
    void handleReadyRead();

protected:
    QScopedPointer<HTcpClientPrivate> d_ptr;
};

HE_END_NAMESPACE
