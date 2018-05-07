#ifndef HABSTRACTPROTOCOL_H
#define HABSTRACTPROTOCOL_H

#include "IProtocol.h"
#include <QObject>
#include <QScopedPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate;

class HE_COMMUNICATE_EXPORT HAbstractProtocol : public QObject, public IProtocol
{
    Q_OBJECT

public:
    explicit HAbstractProtocol(QObject *parent = nullptr);
    ~HAbstractProtocol();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setProtocolInfo(IProtocolInfo *info) override;
    virtual HErrorType open() override;
    virtual HErrorType close() override;

public:
    virtual HErrorType setData(HActionType action, int value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, double value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, uint value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<double> value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) override;

public:
    virtual HErrorType getData(HActionType action, int &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, double &value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, uint &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<double> &value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) override;

protected:
    HAbstractProtocol(HAbstractProtocolPrivate &p, QObject *parent = nullptr);

protected:
    virtual HErrorType openPort(int num);
    virtual HErrorType checkDevice() = 0;
    virtual HErrorType interactionSet(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual HErrorType interactionGet(HActionType action, QVector<uchar> &value, int delay = 0) = 0;

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_H
