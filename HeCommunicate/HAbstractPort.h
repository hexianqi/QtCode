/***************************************************************************************************
**      2018-06-19  HAbstractPort 抽象端口类。
***************************************************************************************************/

#ifndef HABSTRACTPORT_H
#define HABSTRACTPORT_H

#include "IPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractPortPrivate;

class HAbstractPort : public IPort
{
public:
    explicit HAbstractPort();
    virtual ~HAbstractPort();

public:
    void initialize(QVariantMap param) override;

public:
    void setTimeOut(int value) override;
    bool isConnected() override;
    HErrorType open(int portNum = 1) override;
    HErrorType close() override;
    HErrorType write(QVector<uchar> data) override;
    HErrorType read(QVector<uchar> &data) override;
    HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;
    HErrorType clear() override;

protected:
    HAbstractPort(HAbstractPortPrivate &);

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
