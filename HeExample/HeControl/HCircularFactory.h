/***************************************************************************************************
**      2019-06-20  HCircularFactory
***************************************************************************************************/

#pragma once

#include "ICircularFactory.h"

HE_BEGIN_NAMESPACE

class HCircularFactoryPrivate;

class HCircularFactory : public QObject, public ICircularFactory
{
    Q_OBJECT

public:
    explicit HCircularFactory(QObject *parent = nullptr);
    ~HCircularFactory() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QStringList keys() override;
    ICircular *create(QString type, QVariantMap param = QVariantMap()) override;
    QActionGroup *toActionGroup() override;

protected:
    HCircularFactory(HCircularFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HCircularFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_END_NAMESPACE
