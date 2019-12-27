/***************************************************************************************************
**      2019-12-27  HNtpClient
***************************************************************************************************/

#ifndef HNTPCLIENT_H
#define HNTPCLIENT_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HNtpClientPrivate;

class HNtpClient : public QObject
{
    Q_OBJECT

public:
    explicit HNtpClient(QObject *parent = nullptr);
    ~HNtpClient() override;

signals:
    void receiveTime(const QDateTime &value);

public slots:
    void setHost(const QString &value);
    void getDateTime();

protected:
    HNtpClient(HNtpClientPrivate &p, QObject *parent = nullptr);

protected slots:
    void sendData();
    void readData();

protected:
    QScopedPointer<HNtpClientPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HNTPCLIENT_H
