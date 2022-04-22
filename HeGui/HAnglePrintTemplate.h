/***************************************************************************************************
**      2022-04-14  HAnglePrintTemplate 角度打印模版。
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractPrintTemplate.h"

class QPainter;

HE_BEGIN_NAMESPACE

class HAnglePrintTemplatePrivate;

class HAnglePrintTemplate : public HAbstractPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAnglePrintTemplate)

public:
    explicit HAnglePrintTemplate(QObject *parent = nullptr);
    ~HAnglePrintTemplate() override;

public:
    QString typeName() override;

public:
    bool printPages(QPrinter *) override;

protected:
    HAnglePrintTemplate(HAnglePrintTemplatePrivate &p, QObject *parent = nullptr);

protected:
    void paintBody(QPainter *painter, QRectF rect);
    QPointF drawChartCartesian(QPainter *painter, QRectF rect);
    QPointF drawChartPolar(QPainter *painter, QRectF rect);

private:
    void init();
};

HE_END_NAMESPACE

