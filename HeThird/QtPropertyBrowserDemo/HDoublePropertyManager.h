/***************************************************************************************************
**      2022-06-23  HDoublePropertyManager
***************************************************************************************************/

#pragma once

#include "qtpropertymanager.h"

class HDoublePropertyManagerPrivate;

class HDoublePropertyManager : public QtDoublePropertyManager
{
    Q_OBJECT

public:
    explicit HDoublePropertyManager(QObject *parent = nullptr);
    ~HDoublePropertyManager() override;

signals:
    void prefixChanged(QtProperty *property, const QString &prefix);
    void suffixChanged(QtProperty *property, const QString &suffix);

public:
    QString prefix(const QtProperty *property) const;
    QString suffix(const QtProperty *property) const;

public slots:
    void setPrefix(QtProperty *property, const QString &prefix);
    void setSuffix(QtProperty *property, const QString &suffix);

protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;

protected:
    HDoublePropertyManager(HDoublePropertyManagerPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HDoublePropertyManagerPrivate> d_ptr;
};



