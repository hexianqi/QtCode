/***************************************************************************************************
**      2019-12-27  HNtpClient
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HNtpClientPrivate;

class HNtpClient : public QObject
{
    Q_OBJECT

public:
    explicit HNtpClient(QObject *parent = nullptr);
    ~HNtpClient() override;

signals:
    void receiveTime(const QDateTime &value);

public:
    QString host() const;

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

HE_END_NAMESPACE
