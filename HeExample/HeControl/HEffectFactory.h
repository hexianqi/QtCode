/***************************************************************************************************
**      2019-07-24  HEffectFactory
***************************************************************************************************/

#ifndef HEFFECTFACTORY_H
#define HEFFECTFACTORY_H

#include "IEffectFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HEffectFactoryPrivate;

class HEffectFactory : public QObject, public IEffectFactory
{
    Q_OBJECT

public:
    explicit HEffectFactory(QObject *parent = nullptr);
    ~HEffectFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList keys() override;
    IShaderEffect *create(QString type, QVariantMap param = QVariantMap()) override;
    QActionGroup *toActionGroup() override;

protected:
    HEffectFactory(HEffectFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HEffectFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HEFFECTFACTORY_H
