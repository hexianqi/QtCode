/***************************************************************************************************
**      2019-06-20  HCircularFactory
***************************************************************************************************/

#ifndef HCIRCULARFACTORY_H
#define HCIRCULARFACTORY_H

#include "ICircularFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCircularFactoryPrivate;

class HCircularFactory : public QObject, public ICircularFactory
{
    Q_OBJECT

public:
    explicit HCircularFactory(QObject *parent = nullptr);
    ~HCircularFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList keys() override;
    QString alias(QString type) override;
    ICircular *create(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HCircularFactory(HCircularFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HCircularFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCULARFACTORY_H
