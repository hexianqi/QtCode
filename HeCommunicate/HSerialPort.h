/***************************************************************************************************
**      2018-06-19  HSerialPort 串口端口类。
***************************************************************************************************/

#ifndef HSERIALPORT_H
#define HSERIALPORT_H

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

public:
    HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;
    HErrorType clear() override;

public:
    void setBaudRate(int value);

protected:
    HSerialPort(HSerialPortPrivate &);

protected:
    HErrorType openPort(int portNum) override;
    HErrorType closePort() override;
    HErrorType writeData(uchar *data, int maxSize) override;
    HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSERIALPORT_H
