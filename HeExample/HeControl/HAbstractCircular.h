/***************************************************************************************************
**      2019-06-19  HAbstractCircular
***************************************************************************************************/

#pragma once

#include "ICircular.h"

HE_BEGIN_NAMESPACE

class HAbstractCircularPrivate;

class HAbstractCircular : public ICircular
{
    Q_OBJECT

public:
    explicit HAbstractCircular(QObject *parent = nullptr);
    ~HAbstractCircular() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

protected:
    HAbstractCircular(HAbstractCircularPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractCircularPrivate> d_ptr;
};

HE_END_NAMESPACE
