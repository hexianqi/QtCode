/***************************************************************************************************
**      2019-12-11  HAbstractServerWidget
***************************************************************************************************/

#ifndef HABSTRACTSERVERWIDGET_H
#define HABSTRACTSERVERWIDGET_H

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractServerWidgetPrivate;

class HAbstractServerWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractServerWidget)
    Q_PROPERTY(QString listenIP READ listenIP WRITE setListenIP)
    Q_PROPERTY(int listenPort READ listenPort WRITE setListenPort)

public:
    explicit HAbstractServerWidget(QWidget *parent = nullptr);

public:
    QString listenIP() const;
    int listenPort() const;

public slots:
    void setListenIP(const QString &value);
    void setListenPort(int value);
    virtual void handleClientConnected(const QString &ip, int port) = 0;
    virtual void handleClientDisconnected(const QString &ip, int port) = 0;
    virtual void handleSentData(const QString &ip, int port, const QByteArray &data);
    virtual void handleReceiveData(const QString &ip, int port, const QByteArray &data);
    virtual void append(int type, QString data) = 0;

protected:
    HAbstractServerWidget(HAbstractServerWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void readSettings() override;
    void writeSettings() override;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTSERVERWIDGET_H
