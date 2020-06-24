/***************************************************************************************************
**      2019-07-16  HTcpClient TCP客户端。
***************************************************************************************************/

#ifndef HTCPCLIENT_H
#define HTCPCLIENT_H

#include "HControlGlobal.h"
#include <QtNetwork/QTcpSocket>

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientPrivate;

class HTcpClient : public QTcpSocket
{
    Q_OBJECT

public:
    explicit HTcpClient(QObject *parent = nullptr);
    ~HTcpClient() override;

signals:
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QByteArray &data);

public:
    QString address();
    int port();

public slots:
    void sendData(const QByteArray &value);

protected:
    HTcpClient(HTcpClientPrivate &p, QObject *parent = nullptr);

protected:
    void handleReadyRead();

protected:
    QScopedPointer<HTcpClientPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPCLIENT_H
