/***************************************************************************************************
**      2021-10-28  HSpecPrintTemplate2000DC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecPrintTemplate.h"

HE_GUI_USE_NAMESPACE

class HSpecPrintTemplate2000DCPrivate;

class HSpecPrintTemplate2000DC : public HSpecPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintTemplate2000DC)

public:
    explicit HSpecPrintTemplate2000DC(QObject *parent = nullptr);
    ~HSpecPrintTemplate2000DC() override;

public:
    QString typeName() override;

protected:
    HSpecPrintTemplate2000DC(HSpecPrintTemplate2000DCPrivate &p, QObject *parent = nullptr);

protected:
    void paintBody(QPainter *painter, QRectF rect, int page) override;

private:
    void init();
};
