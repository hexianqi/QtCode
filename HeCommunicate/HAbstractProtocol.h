/***************************************************************************************************
**      2019-05-28  HAbstractProtocol 抽象协议类。
***************************************************************************************************/

#pragma once

#include "IProtocol.h"

HE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate;

class HAbstractProtocol : public QObject, public IProtocol
{
    Q_OBJECT

public:
    explicit HAbstractProtocol(QObject *parent = nullptr);
    ~HAbstractProtocol() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QString portType() override;
    void setDevice(IDevice *) override;
    void setConvert(IUCharConvert *) override;
    void setPort(IPort *, int num = 0, bool autoScan = true) override;
    bool open() override;
    bool close() override;

public:
    bool setData(HActionType action) override;
    bool setData(HActionType action, QVariant value, int delay = 0) override;
    bool setData(HActionType action, QVariantList value, int delay = 0) override;
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;

public:
    bool getData(HActionType action) override;
    bool getData(HActionType action, QVariant &value, QVariant::Type type = QVariant::Int, int delay = 0) override;
    bool getData(HActionType action, QVariantList &value, QVariant::Type type = QVariant::Int, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HAbstractProtocol(HAbstractProtocolPrivate &, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_END_NAMESPACE
