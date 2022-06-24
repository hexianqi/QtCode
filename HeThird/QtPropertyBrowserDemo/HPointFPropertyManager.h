/***************************************************************************************************
**      2022-06-23  HDualVariantPropertyManager
***************************************************************************************************/

#pragma once

#include "qtvariantproperty.h"

class HPointFPropertyManagerPrivate;

class HPointFPropertyManager : public QtVariantPropertyManager
{
    Q_OBJECT

public:
    explicit HPointFPropertyManager(QObject *parent = nullptr);
    ~HPointFPropertyManager() override;

public:
    bool isPropertyTypeSupported(int propertyType) const override;
    int valueType(int propertyType) const override;
    QVariant value(const QtProperty *property) const override;
    QString valueText(const QtProperty *property) const override;

public slots:
    void setValue(QtProperty *property, const QVariant &value) override;

protected:
    HPointFPropertyManager(HPointFPropertyManagerPrivate &p, QObject *parent = nullptr);

protected:
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
    void init();

protected slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void slotPropertyDestroyed(QtProperty *property);

protected:
    QScopedPointer<HPointFPropertyManagerPrivate> d_ptr;
};



