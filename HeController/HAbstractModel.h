/***************************************************************************************************
**      2018-06-19  HAbstractModel 抽象模型类。
***************************************************************************************************/

#ifndef HABSTRACTMODEL_H
#define HABSTRACTMODEL_H

#include "IModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractModelPrivate;

class HE_CONTROLLER_EXPORT HAbstractModel : public IModel
{
    Q_OBJECT

public:
    explicit HAbstractModel(QObject *parent = nullptr);
    ~HAbstractModel();

public:
    virtual void initialize(QVariantMap param) override;
    virtual bool initConfig() override;
    virtual void addAction(HActionType action) override;

protected:
    HAbstractModel(HAbstractModelPrivate &p, QObject *parent = nullptr);

protected:
    virtual void initThread();
    virtual void startThread();
    virtual void stopThread();

protected:
    QScopedPointer<HAbstractModelPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_H
