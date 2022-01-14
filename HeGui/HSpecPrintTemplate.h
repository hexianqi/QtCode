/***************************************************************************************************
**      2021-10-25  HSpecPrintTemplate 光谱打印模版。
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractPrintTemplate.h"

class QPainter;

HE_BEGIN_NAMESPACE

class HSpecPrintTemplatePrivate;

class HSpecPrintTemplate : public HAbstractPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPrintTemplate)

public:
    explicit HSpecPrintTemplate(QObject *parent = nullptr);
    ~HSpecPrintTemplate() override;

public:
    QString typeName() override;

public:
    bool printPages(QPrinter *) override;

protected:
    HSpecPrintTemplate(HSpecPrintTemplatePrivate &p, QObject *parent = nullptr);

protected:
    virtual void printHome(QPrinter *printer, QPainter *painter);
    virtual void printTM30(QPrinter *printer, QPainter *painter);
    virtual double paintHeader(QPainter *painter);
    virtual double paintFooter(QPainter *painter, int page);
    virtual double paintTitle(QPainter *painter, double y);
    virtual void paintBody(QPainter *painter, QRectF rect, int page);
    virtual double paintFooterTM30(QPainter *painter, int page);
    virtual void paintBodyTM30(QPainter *painter, QRectF rect, int page);

protected:
    QPointF drawChartSpec(QPainter *painter, QRectF rect);
    QPointF drawChartCie(QPainter *painter, QRectF rect);
    QPointF drawChartTm30Spd(QPainter *painter, QRectF rect);
    QPointF drawChartTm30Cvg(QPainter *painter, QRectF rect);
    QPointF drawChartTm30Rxhj(QPainter *painter, QRectF rect);
    QPointF drawChartTm30Rfi(QPainter *painter, QRectF rect);
    QPointF drawChartTm30Gamut(QPainter *painter, QRectF rect);
    QPointF drawChartTm30RfRg(QPainter *painter, QRectF rect);
    QPointF drawTableTm30Rxhj(QPainter *painter, QRectF rect);

private:
    void init();
};

HE_END_NAMESPACE

