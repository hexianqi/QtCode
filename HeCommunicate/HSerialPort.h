/***************************************************************************************************
**      2018-06-19  HSerialPort 串口端口类。
***************************************************************************************************/

#pragma once

#include "HAbstractPort.h"

HE_BEGIN_NAMESPACE

class HSerialPortPrivate;

class HSerialPort : public HAbstractPort
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSerialPort)

public:
    explicit HSerialPort(QObject *parent = nullptr);
    ~HSerialPort() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;
    QString portType() override;

public:
    void setBaudRate(ulong value);
    void setParity(uchar value);

protected:
    HSerialPort(HSerialPortPrivate &, QObject *parent = nullptr);

protected:
    bool openPort(int portNum) override;
    bool closePort() override;
    int writeData(uchar *data, int maxSize) override;
    int readData(uchar *data, int maxSize) override;
};

HE_END_NAMESPACE
