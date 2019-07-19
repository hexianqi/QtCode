/***************************************************************************************************
**      2019-06-12  HStyleFactory 样式工厂。
***************************************************************************************************/

#ifndef HSTYLEFACTORY_H
#define HSTYLEFACTORY_H

#include "IStyleFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HStyleFactoryPrivate;

class HE_CONTROL_EXPORT HStyleFactory : public QObject, public IStyleFactory
{
    Q_OBJECT

public:
    explicit HStyleFactory(QObject *parent = nullptr);
    ~HStyleFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList keys() override;
    IStyle *create(QString type, QVariantMap param = QVariantMap()) override;
    IQssStyle *createQss(QString type, QVariantMap param = QVariantMap()) override;
    ICustomStyle *createCustom(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HStyleFactory(HStyleFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HStyleFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HSTYLEFACTORY_H
