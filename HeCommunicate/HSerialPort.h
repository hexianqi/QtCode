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
    ~HSerialPort();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 10) override;
    virtual HErrorType clear() override;

protected:
    HSerialPort(HSerialPortPrivate &p);

protected:
    virtual HErrorType openPort(int portNum) override;
    virtual HErrorType closePort() override;
    virtual HErrorType writeData(uchar *data, int maxSize) override;
    virtual HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSERIALPORT_H
