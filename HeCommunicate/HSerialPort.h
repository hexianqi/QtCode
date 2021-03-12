/***************************************************************************************************
**      2018-06-19  HSerialPort 串口端口类。
***************************************************************************************************/

#pragma once

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSerialPortPrivate;

class HSerialPort : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HSerialPort)

public:
    explicit HSerialPort();
    ~HSerialPort() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;
    QString portType() override;

public:
    void setBaudRate(ulong value);

protected:
    HSerialPort(HSerialPortPrivate &);

protected:
    bool openPort(int portNum) override;
    bool closePort() override;
    int writeData(uchar *data, int maxSize) override;
    int readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE
