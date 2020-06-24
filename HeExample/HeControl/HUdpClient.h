/***************************************************************************************************
**      2019-12-10  HUdpClient UDP客户端。
***************************************************************************************************/

#ifndef HUDPCLIENT_H
#define HUDPCLIENT_H

#include "HControlGlobal.h"
#include <QtNetwork/QUdpSocket>

HE_CONTROL_BEGIN_NAMESPACE

class HUdpClientPrivate;

class HUdpClient : public QUdpSocket
{
    Q_OBJECT

public:
    explicit HUdpClient(QObject *parent = nullptr);
    ~HUdpClient() override;

signals:
    void sentData(const QString &address, int port, const QByteArray &data);
    void receiveData(const QString &address, int port, const QByteArray &data);

public slots:
    void sendData(const QString &address, int port, const QByteArray &value);

protected:
    HUdpClient(HUdpClientPrivate &p, QObject *parent = nullptr);

protected:
    void handleReadyRead();

protected:
    QScopedPointer<HUdpClientPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HUDPCLIENT_H
