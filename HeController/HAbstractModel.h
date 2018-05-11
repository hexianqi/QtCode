#ifndef HABSTRACTMODEL_H
#define HABSTRACTMODEL_H

#include "IModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractModelPrivate;

class HAbstractModel : public IModel
{
public:
    explicit HAbstractModel(QObject *parent = nullptr);
    ~HAbstractModel();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void addAction(HActionType action) override;

public:
    virtual IDevice *device(QString name) override;

protected:
    HAbstractModel(HAbstractModelPrivate &p, QObject *parent = nullptr);

protected:
    virtual void initDevice() = 0;
    virtual void initThread();
    virtual void startThread();
    virtual void stopThread();

protected:
    QScopedPointer<HAbstractModelPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_H
