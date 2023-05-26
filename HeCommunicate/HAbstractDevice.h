/***************************************************************************************************
**      2018-06-19  HAbstractDevice 抽象设备类。
***************************************************************************************************/

#pragma once

#include "IDevice.h"

HE_BEGIN_NAMESPACE

class HAbstractDevicePrivate;

class HAbstractDevice : public QObject, public IDevice
{
    Q_OBJECT

public:
    explicit HAbstractDevice(QObject *parent = nullptr);
    ~HAbstractDevice() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QString portType() override;
    bool isSupport(HActionType action) override;
    void setPort(IPort *port, int num = 0, bool scan = true) override;
    void setDeviceID(int value) override;
    void addActionParam(HActionType action, QList<uchar> value) override;

public:
    bool open() override;
    bool close() override;

protected:
    HAbstractDevice(HAbstractDevicePrivate &, QObject *parent = nullptr);

protected:
    virtual bool open(int num);
    virtual bool tryOpen(int num);
    virtual bool checkDevice();
    virtual void transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);

protected:
    QScopedPointer<HAbstractDevicePrivate> d_ptr;
};

HE_END_NAMESPACE
