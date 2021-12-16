/***************************************************************************************************
**      2021-10-29  HSpecPrintTemplate2000AC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecPrintTemplate.h"

HE_USE_NAMESPACE

class HSpecPrintTemplate2000ACPrivate;

class HSpecPrintTemplate2000AC : public HSpecPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintTemplate2000AC)

public:
    explicit HSpecPrintTemplate2000AC(QObject *parent = nullptr);
    ~HSpecPrintTemplate2000AC() override;

public:
    QString typeName() override;

protected:
    HSpecPrintTemplate2000AC(HSpecPrintTemplate2000ACPrivate &p, QObject *parent = nullptr);

protected:
    void paintBody(QPainter *painter, QRectF rect, int page) override;

private:
    void init();
};
