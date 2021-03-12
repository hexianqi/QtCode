/***************************************************************************************************
**      2019-12-11  HAbstractClientWidget
***************************************************************************************************/

#pragma once

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractClientWidgetPrivate;

class HAbstractClientWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractClientWidget)
    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress)
    Q_PROPERTY(int serverPort READ serverPort WRITE setServerPort)

public:
    explicit HAbstractClientWidget(QWidget *parent = nullptr);

public:
    QString serverAddress() const;
    int serverPort() const;

public slots:
    void setServerAddress(const QString &value);
    void setServerPort(int value);

protected:
    HAbstractClientWidget(HAbstractClientWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void readSettings() override;
    void writeSettings() override;
};

HE_CONTROL_END_NAMESPACE
