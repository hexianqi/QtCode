/***************************************************************************************************
**      2021-10-19  HTagPrintTemplate2000DC
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractPrintTemplate.h"

class QPainter;

HE_DATA_USE_NAMESPACE

class HTagPrintTemplate2000DCPrivate;

class HTagPrintTemplate2000DC : public HAbstractPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTagPrintTemplate2000DC)

public:
    explicit HTagPrintTemplate2000DC(QObject *parent = nullptr);
    ~HTagPrintTemplate2000DC() override;

public:
    QString typeName() override;

public:
    bool printPages(QPrinter *) override;

protected:
    HTagPrintTemplate2000DC(HTagPrintTemplate2000DCPrivate &p, QObject *parent = nullptr);

protected:
    void drawText(QPainter *painter, double x1, double y1, double x2, double y2, QString text);
};



