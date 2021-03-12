/***************************************************************************************************
**      2019-12-11  HAbstractServerWidget
***************************************************************************************************/

#pragma once

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractServerWidgetPrivate;

class HAbstractServerWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractServerWidget)
    Q_PROPERTY(QString listenAddress READ listenAddress WRITE setListenAddress)
    Q_PROPERTY(int listenPort READ listenPort WRITE setListenPort)

public:
    explicit HAbstractServerWidget(QWidget *parent = nullptr);

public:
    QString listenAddress() const;
    int listenPort() const;

public slots:
    void setListenAddress(const QString &value);
    void setListenPort(int value);
    virtual void handleClientConnected(const QString &address, int port) = 0;
    virtual void handleClientDisconnected(const QString &address, int port) = 0;
    virtual void handleSentData(const QString &address, int port, const QByteArray &data);
    virtual void handleReceiveData(const QString &address, int port, const QByteArray &data);
    virtual void append(int type, QString data) = 0;

protected:
    HAbstractServerWidget(HAbstractServerWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void readSettings() override;
    void writeSettings() override;
};

HE_CONTROL_END_NAMESPACE
