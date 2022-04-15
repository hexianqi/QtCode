#include "HAnglePrintTemplate_p.h"
#include "HeCore/HCore.h"
#include "HePlugin/HDynamicChartView.h"
#include "HePlugin/HPolarChartView.h"
#include "HePlugin/HPainterHelper.h"
#include <QtCharts/QValueAxis>
#include <QtGui/QPainter>
#include <QtPrintSupport/QPrinter>


HE_BEGIN_NAMESPACE

HAnglePrintTemplatePrivate::HAnglePrintTemplatePrivate()
{
    prefix = "AnglePrintTemplate";
}

HAnglePrintTemplate::HAnglePrintTemplate(QObject *parent) :
    HAbstractPrintTemplate(*new HAnglePrintTemplatePrivate, parent)
{
    init();
}

HAnglePrintTemplate::HAnglePrintTemplate(HAnglePrintTemplatePrivate &p, QObject *parent) :
    HAbstractPrintTemplate(p, parent)
{
}

HAnglePrintTemplate::~HAnglePrintTemplate()
{
    Q_D(HAnglePrintTemplate);
    delete d->cartesianChartView;
    delete d->polarChartView;
}

QString HAnglePrintTemplate::typeName()
{
    return "HAnglePrintTemplate";
}

bool HAnglePrintTemplate::printPages(QPrinter *printer)
{
    return true;
}

QPointF HAnglePrintTemplate::drawChartCartesian(QPainter *painter, QRectF rect)
{
    Q_D(HAnglePrintTemplate);
    if (d->cartesianChartView == nullptr)
    {
        d->cartesianChartView = new HDynamicChartView;
        d->cartesianChartView->axisX()->setRange(0, 180);
        d->cartesianChartView->axisX()->setLabelFormat("%d");
        d->cartesianChartView->axisY()->setLabelFormat("%d");
        d->cartesianChartView->setWindowTitle(tr("光强角度分布图1"));
    }
    auto poly = d->datas.value("[光强角度分布]").value<QPolygonF>();
    d->cartesianChartView->replace(poly);
    return HPainterHelper::drawChart(painter, rect, d->cartesianChartView);
}

QPointF HAnglePrintTemplate::drawChartPolar(QPainter *painter, QRectF rect)
{
    Q_D(HAnglePrintTemplate);
    if (d->polarChartView == nullptr)
    {
        d->polarChartView = new HPolarChartView;
        d->polarChartView->axisAngular()->setLabelFormat("%d");
        d->polarChartView->axisRadial()->setLabelFormat("%d");
        d->polarChartView->setWindowTitle(tr("光强角度分布图2"));
    }
    auto poly = d->datas.value("[光强角度分布]").value<QPolygonF>();
    d->polarChartView->replace(poly);
    return HPainterHelper::drawChart(painter, rect, d->polarChartView);
}

void HAnglePrintTemplate::init()
{
    Q_D(HAnglePrintTemplate);
    d->types = HCore::membership("|光强角度信息|");
    d->params.insert("Header",      tr("松朗光电测试报告"));
    d->params.insert("Title",       tr("光强角度分布测试报告"));
    d->params.insert("DrawHeader",  true);
    d->params.insert("DrawLogo",    true);
}

HE_END_NAMESPACE
