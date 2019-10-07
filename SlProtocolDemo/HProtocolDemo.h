/***************************************************************************************************
**      2019-09-12  HProtocolDemo
***************************************************************************************************/

#ifndef HPROTOCOLDEMO_H
#define HPROTOCOLDEMO_H

#include "HeCommunicate/IProtocol.h"

HE_COMMUNICATE_USE_NAMESPACE

class HProtocolDemoPrivate;

class HProtocolDemo : public IProtocol
{
public:
    explicit HProtocolDemo();
    virtual ~HProtocolDemo();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setDevice(IDevice *) override;
    HErrorType open() override;
    HErrorType close() override;
    HErrorType setIntegralTime(double value);
    HErrorType setSmooth(int times, int range);
    HErrorType setStdCurve(QVector<double> value);
    HErrorType getSpectrumSample(QVector<double> &value);
    HErrorType getSpectrumEnergy(QPolygonF &value, double *percent);

public:
    HErrorType setData(HActionType action, int value, int delay = 0) override;
    HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    HErrorType setData(HActionType action, uint value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) override;
    HErrorType getData(HActionType action, int &value, int delay = 0) override;
    HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    HErrorType getData(HActionType action, uint &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<double> &value, int delay = 0) override;

protected:
    QScopedPointer<HProtocolDemoPrivate> d_ptr;
};

#endif // HPROTOCOLDEMO_H
