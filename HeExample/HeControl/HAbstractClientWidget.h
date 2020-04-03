/***************************************************************************************************
**      2019-12-11  HAbstractClientWidget
***************************************************************************************************/

#ifndef HABSTRACTCLIENTWIDGET_H
#define HABSTRACTCLIENTWIDGET_H

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractClientWidgetPrivate;

class HAbstractClientWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractClientWidget)
    Q_PROPERTY(QString serverIP READ serverIP WRITE setServerIP)
    Q_PROPERTY(int serverPort READ serverPort WRITE setServerPort)

public:
    explicit HAbstractClientWidget(QWidget *parent = nullptr);
    ~HAbstractClientWidget() override;

public:
    QString serverIP() const;
    int serverPort() const;

public slots:
    void setServerIP(const QString &value);
    void setServerPort(int value);

protected:
    HAbstractClientWidget(HAbstractClientWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void readSettings() override;
    void writeSettings() override;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTCLIENTWIDGET_H
