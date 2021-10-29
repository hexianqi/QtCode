/***************************************************************************************************
**      2020-09-09  HMemento
***************************************************************************************************/

#pragma once

#include "IMemento.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HMementoPrivate;

class HMemento : public QObject, public IMemento
{
    Q_OBJECT

public:
    explicit HMemento(QObject *parent = nullptr);
    ~HMemento() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    bool readFile(QString fileName) override;
    bool writeFile() override;

public:
    void setDataTypes(QStringList) override;

public:
    void save() override;
    void restore() override;

protected:
    HMemento(HMementoPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HMementoPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

