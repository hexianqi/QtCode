/***************************************************************************************************
**      2022-08-01  HWebClient
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class QWebSocket;

HE_BEGIN_NAMESPACE

class HWebClientPrivate;

class HWebClient : public QObject
{
    Q_OBJECT

public:
    explicit HWebClient(QWebSocket *socket, QObject *parent = nullptr);
    ~HWebClient() override;

signals:
    void disconnected(const QString &ip, int port);
    void error(const QString &address, int port, const QString &error);
    void sentData(const QString &address, int port, const QString &data);
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QString &data);
    void receiveData(const QString &address, int port, const QByteArray &data);

public:
    QString address();
    int port();

public slots:
    void sendData(const QString &value);
    void sendData(const QByteArray &value);
    void abort();

protected slots:
    void handleError();
    void handleDisconnected();
    void handleTextMessageReceived(const QString &);
    void handleBinaryMessageReceived(const QByteArray &);

protected:
    QScopedPointer<HWebClientPrivate> d_ptr;
};

HE_END_NAMESPACE

