/***************************************************************************************************
**      2018-06-19  HAbstractPort 抽象端口类。
***************************************************************************************************/

#pragma once

#include "IPort.h"

HE_BEGIN_NAMESPACE

class HAbstractPortPrivate;

class HAbstractPort : public IPort
{
public:
    explicit HAbstractPort();
    virtual ~HAbstractPort();

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    bool isConnected() override;
    void setTimeOut(int value) override;
    bool open(int portNum = 1) override;
    bool close() override;
    bool clear() override;
    int write(QVector<uchar> data) override;
    int read(QVector<uchar> &data) override;
    bool transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;

protected:
    HAbstractPort(HAbstractPortPrivate &);

protected:
    virtual bool openPort(int portNum) = 0;
    virtual bool closePort() = 0;
    virtual int writeData(uchar *data, int maxSize) = 0;
    virtual int readData(uchar *data, int maxSize) = 0;

protected:
    QScopedPointer<HAbstractPortPrivate> d_ptr;
};

HE_END_NAMESPACE
