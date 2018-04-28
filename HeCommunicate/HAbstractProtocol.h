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
    Q_DECLARE_PRIVATE(HAbstractProtocol)
    Q_DISABLE_COPY(HAbstractProtocol)

public:
    explicit HAbstractProtocol(QObject *parent = nullptr);
    ~HAbstractProtocol();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setPort(IPort *port) override;
    virtual HErrorType setData(HActionType action, int value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, quint32 value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<quint32> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<double> value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, int &value, int delay = 10) override;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 10) override;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 10) override;
    virtual HErrorType getData(HActionType action, QVector<double> &value, int delay = 10) override;

protected:
    HAbstractProtocol(HAbstractProtocolPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_H
