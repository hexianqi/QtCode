/***************************************************************************************************
**      2022-04-12  HSpecPrintTemplate1000A
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecPrintTemplate.h"

HE_USE_NAMESPACE

class HSpecPrintTemplate1000APrivate;

class HSpecPrintTemplate1000A : public HSpecPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintTemplate1000A)

public:
    explicit HSpecPrintTemplate1000A(QObject *parent = nullptr);
    ~HSpecPrintTemplate1000A() override;

public:
    QString typeName() override;

protected:
    HSpecPrintTemplate1000A(HSpecPrintTemplate1000APrivate &p, QObject *parent = nullptr);

protected:
    void paintBody(QPainter *painter, QRectF rect, int page) override;

private:
    void init();
};



