/***************************************************************************************************
**      2021-10-25  HSpecPrintTemplate 光谱打印模版。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeData/HAbstractPrintTemplate.h"

class QPainter;

HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecPrintTemplatePrivate;

class HE_GUI_EXPORT HSpecPrintTemplate : public HAbstractPrintTemplate
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
    virtual double paintHeader(QPainter *painter);
    virtual double paintTitle(QPainter *painter, double y);
    virtual double paintFooter(QPainter *painter, int page);
    virtual void paintBody(QPainter *painter, QRectF rect, int page);

protected:
    QPointF drawChartSpec(QPainter *painter, QRectF rect, QPolygonF poly);
    QPointF drawChartCie(QPainter *painter, QRectF rect, QPointF point);

private:
    void init();
};

HE_GUI_END_NAMESPACE

