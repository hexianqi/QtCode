/***************************************************************************************************
**      2019-06-20  HWaitFactory
***************************************************************************************************/

#ifndef HWAITFACTORY_H
#define HWAITFACTORY_H

#include "IWaitFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HWaitFactoryPrivate;

class HWaitFactory : public QObject, public IWaitFactory
{
    Q_OBJECT

public:
    explicit HWaitFactory(QObject *parent = nullptr);
    ~HWaitFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList keys() override;
    QString alias(QString type) override;
    IWait *create(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HWaitFactory(HWaitFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HWaitFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HWAITFACTORY_H
