/***************************************************************************************************
**      2021-10-29  HSpecPrintTemplate2100DC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecPrintTemplate.h"

HE_GUI_USE_NAMESPACE

class HSpecPrintTemplate2100DCPrivate;

class HSpecPrintTemplate2100DC : public HSpecPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintTemplate2100DC)

public:
    explicit HSpecPrintTemplate2100DC(QObject *parent = nullptr);
    ~HSpecPrintTemplate2100DC() override;

public:
    QString typeName() override;

protected:
    HSpecPrintTemplate2100DC(HSpecPrintTemplate2100DCPrivate &p, QObject *parent = nullptr);

protected:
    void paintBody(QPainter *painter, QRectF rect, int page) override;

private:
    void init();
};



