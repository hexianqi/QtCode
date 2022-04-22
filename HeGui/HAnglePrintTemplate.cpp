#include "HAnglePrintTemplate_p.h"
#include "HeCore/HCore.h"
#include "HePlugin/HDynamicChartView.h"
#include "HePlugin/HPolarChartView.h"
#include "HePlugin/HPainterHelper.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
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
    Q_D(HAnglePrintTemplate);
    QPainter painter(printer);
    printer->setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
    painter.setFont(QFont("宋体", 12));
    auto y1 = HPainterHelper::paintHeader(&painter, d->params);
    painter.setFont(QFont(tr("宋体"), 8));
    auto y2 = HPainterHelper::paintFooter(&painter, "1");
    painter.setFont(QFont(tr("宋体"), 16, QFont::Bold));
    y1 = HPainterHelper::paintTitle(&painter, d->params.value("Title").toString(), y1);
    paintBody(&painter, QRectF(0, y1, painter.viewport().width(), y2 - y1));
    return true;
}

void HAnglePrintTemplate::paintBody(QPainter *painter, QRectF rect)
{
    auto gap = 8.0;
    rect.adjust(gap, gap, -gap, -gap);
    auto font = QFont("宋体", 10);
    auto h = QFontMetrics(font).height() + gap * 2.0;
    auto w = rect.width();
    auto x = rect.left();
    auto y = rect.top();
    auto text = QString();

    // 角分布参数
    painter->setFont(font);
    text = QString(" %1  %2  %3  %4").arg(toStringWhole("[最大光强度角]"), toStringWhole("[最大光强度]"), toStringWhole("[法向光强度]"), toStringWhole("[角度光通量]"));
    painter->drawText(QRectF(x, y , w, h), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h;
    text = QString(" %1  %2  %3").arg(toStringWhole("[左半光强度角]"), toStringWhole("[右半光强度角]"), toStringWhole("[半光强度夹角]"));
    painter->drawText(QRectF(x, y , w, h), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h;
    text = QString(" %1  %2  %3").arg(toStringWhole("[左1/5光强度角]"), toStringWhole("[右1/5光强度角]"), toStringWhole("[1/5光强度夹角]"));
    painter->drawText(QRectF(x, y , w, h), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h;
    // 图像
    auto xr1 = rect.left();
    auto xr2 = rect.center().x();
    auto yr = y + 40;
    auto wr = rect.width() / 2.0;
    auto hr = rect.bottom() - yr;
    auto wh = qMin(wr, hr);
    drawChartCartesian(painter, QRectF(xr1, yr, wh, wh));
    drawChartPolar(painter, QRectF(xr2, yr, wh, wh));
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
        d->cartesianChartView->scatterSeries()->setVisible(false);
        d->cartesianChartView->setWindowTitle(tr("光强角度分布图1"));
        d->cartesianChartView->chart()->legend()->setVisible(false);
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
