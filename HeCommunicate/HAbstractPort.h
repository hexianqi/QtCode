#ifndef HABSTRACTPORT_H
#define HABSTRACTPORT_H

#include "IPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractPortPrivate;

class HAbstractPort : public IPort
{
public:
    explicit HAbstractPort();
    ~HAbstractPort();

public:
    virtual void initialize(QVariantMap param) override;
    virtual bool isConnected() override;
    virtual HErrorType open(int portNum = 1) override;
    virtual HErrorType close() override;
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;
    virtual HErrorType write(QVector<uchar> data) override;
    virtual HErrorType read(QVector<uchar> &data) override;
    virtual HErrorType clear() override;

protected:
    HAbstractPort(HAbstractPortPrivate &p);

protected:
    virtual HErrorType openPort(int portNum) = 0;
    virtual HErrorType closePort() = 0;
    virtual HErrorType writeData(uchar *data, int maxSize) = 0;
    virtual HErrorType readData(uchar *data, int maxSize) = 0;

protected:
    QScopedPointer<HAbstractPortPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPORT_H
