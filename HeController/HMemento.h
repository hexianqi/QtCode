/***************************************************************************************************
**      2020-09-09  HMemento
***************************************************************************************************/

#pragma once

#include "IMemento.h"

HE_BEGIN_NAMESPACE

class HMementoPrivate;

class HMemento : public QObject, public IMemento
{
    Q_OBJECT

public:
    explicit HMemento(QObject *parent = nullptr);
    ~HMemento() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setDataType(QStringList) override;
    QStringList dataType() override;

public:
    void save() override;
    void restore() override;

protected:
    HMemento(HMementoPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HMementoPrivate> d_ptr;
};

HE_END_NAMESPACE

