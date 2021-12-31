#include "HSpecPrintTemplate_p.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include "HePlugin/HTm30CvgWidget.h"
#include "HePlugin/HTm30GamutWidget.h"
#include "HePlugin/HTm30SpdChartView.h"
#include "HePlugin/HTm30RfiChartView.h"
#include "HePlugin/HTm30RfRgChartView.h"
#include "HePlugin/HTm30RxhjWidget.h"
#include "HePlugin/HPainterHelper.h"
#include <QtGui/QPainter>
#include <QtPrintSupport/QPrinter>

HE_BEGIN_NAMESPACE

HSpecPrintTemplatePrivate::HSpecPrintTemplatePrivate()
{
    prefix = "SpecPrintTemplate";
}

HSpecPrintTemplate::HSpecPrintTemplate(QObject *parent) :
    HAbstractPrintTemplate(*new HSpecPrintTemplatePrivate, parent)
{
    init();
}

HSpecPrintTemplate::HSpecPrintTemplate(HSpecPrintTemplatePrivate &p, QObject *parent) :
    HAbstractPrintTemplate(p, parent)
{
}

HSpecPrintTemplate::~HSpecPrintTemplate()
{
    Q_D(HSpecPrintTemplate);
    delete d->specWidget;
    delete d->cieWidget;
    delete d->spdWidget;
    delete d->cvgWidget;
    delete d->rxhjWidget;
    delete d->rfiWidget;
    delete d->gamutWidget;
    delete d->rfrgWidget;
}

QString HSpecPrintTemplate::typeName()
{
    return "HSpecPrintTemplate";
}

bool HSpecPrintTemplate::printPages(QPrinter *printer)
{
    printer->setPageMargins(13, 13, 5, 5, QPrinter::Millimeter);
    QPainter painter(printer);
    auto y1 = paintHeader(&painter);
    auto y2 = paintFooter(&painter, 0);
    y1 = paintTitle(&painter, y1);
    paintBody(&painter, QRectF(0, y1, painter.viewport().width(), y2 - y1), 0);
    for (int i = 1; i < 3; i++)
    {
        printer->newPage();
        y1 = paintHeader(&painter);
        y2 = paintFooterTM30(&painter, i + 1);
        paintBodyTM30(&painter, QRectF(0, y1, painter.viewport().width(), y2 - y1), i);
    }
    return true;
}

double HSpecPrintTemplate::paintHeader(QPainter *painter)
{
    Q_D(HSpecPrintTemplate);
    painter->setFont(QFont("宋体", 12));
    return HPainterHelper::paintHeader(painter, d->params);
}

double HSpecPrintTemplate::paintFooter(QPainter *painter, int /*page*/)
{
    auto gap = 4.0;
    auto font = QFont("宋体", 10, QFont::Bold);
    auto h = QFontMetrics(font).height() + gap * 2.0;
    auto w = painter->viewport().width() / 2.0 - gap * 2.0;
    auto x1 = gap;
    auto x2 = painter->viewport().width() / 2.0 + gap;
    auto y1 = painter->viewport().height() - h * 5 - 20;
    auto y2 = y1;

    painter->setFont(font);
    painter->drawLine(QLineF(0, y1, painter->viewport().width(), y1));
    y2 += 5;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[产品型号]"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[产品名称]"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[测试单位]"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[测试员]"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[样品编号]"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[测量日期时间]"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[环境温度]"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[环境湿度]"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w * 2, h), Qt::AlignLeft | Qt::AlignVCenter, toStringWhole("[制造厂商]"));
    return y1;
}

double HSpecPrintTemplate::paintTitle(QPainter *painter, double y)
{
    Q_D(HSpecPrintTemplate);
    auto text = d->params.value("Title").toString();
    painter->setFont(QFont(tr("宋体"), 16, QFont::Bold));
    return HPainterHelper::drawText(painter, 0, y, text, Qt::AlignHCenter | Qt::TextWordWrap).y() + 10;
}

void HSpecPrintTemplate::paintBody(QPainter *painter, QRectF rect, int /*page*/)
{
    auto gap = 8.0;
    rect.adjust(gap, gap, -gap, -gap);
    auto font1 = QFont("宋体", 12, QFont::Bold);
    auto font2 = QFont("宋体", 10);
    auto h1 = QFontMetrics(font1).height() + gap * 2.0;
    auto h2 = QFontMetrics(font2).height() + gap * 2.0;
    auto w = rect.width();
    auto x = rect.left();
    auto y = rect.top();
    auto text = QString();
    auto rx = toString("[显色指数Rx]").split(" ", QString::SkipEmptyParts);

    // 颜色参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("颜色参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 色品坐标：x = %1    y = %2    u' = %3    v' = %4    duv = %5")
               .arg(toString("[色坐标x]"), toString("[色坐标y]"), toString("[色坐标up]"), toString("[色坐标vp]"), toString("[Duv]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 相关色温：Tc = %1K    主波长：λd = %2nm    色纯度：Purity = %3    色容差：%4SDCM")
               .arg(toString("[色温]"), toString("[主波长]"), toString("[色纯度]"), toString("[色容差]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 色比：R = %1%  G = %2%  B = %3%    峰值波长：λp = %4nm   峰值带宽：Δλd = %5nm")
               .arg(toString("[红色比]"), toString("[绿色比]"), toString("[蓝色比]"), toString("[峰值波长]"), toString("[峰值带宽]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    if (rx.size() > 14)
    {
        text = tr(" 显色指数：Ra = %1    R9 = %2").arg(toString("[显色指数Ra]"), toString("[显色指数R9]"));
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
        text = tr("  R01 = %1  R02 = %2  R03 = %3  R04 = %4  R05 = %5  R06 = %6  R07 = %7  R08 = %8")
                   .arg(rx[0], rx[1], rx[2], rx[3], rx[4], rx[5], rx[6], rx[7]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
        text = tr("  R09 = %1  R10 = %2  R11 = %3  R12 = %4  R13 = %5  R14 = %6  R15 = %7")
                   .arg(rx[8], rx[9], rx[10], rx[11], rx[12], rx[13], rx[14]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
    }
    // 光度参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("光度参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 光通量：Φ = %1lm    光功率：Φ e = %2mW").arg(toString("[光谱光通量]"), toString("[光功率]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    // 图像
    auto xr1 = rect.left();
    auto xr2 = rect.center().x() + gap;
    auto yr = y + 20;
    auto wr = rect.width() / 2.0 - gap;
    auto hr = rect.bottom() - yr;
    drawChartSpec(painter, QRectF(xr1, yr, wr, hr));
    drawChartCie(painter, QRectF(xr2, yr, wr, hr));
}

double HSpecPrintTemplate::paintFooterTM30(QPainter *painter, int page)
{
    painter->setFont(QFont(tr("宋体"), 8));
    return HPainterHelper::paintFooter(painter, QString::number(page));
}

void HSpecPrintTemplate::paintBodyTM30(QPainter *painter, QRectF rect, int page)
{
    auto gap = 8.0;
    if (page == 1)
    {
        auto x1 = rect.left() + gap;
        auto x2 = rect.center().x() + gap;
        auto y1 = rect.top() + gap;
        auto y2 = rect.top() + gap + rect.height() / 4.0;
        auto w1 = rect.width() * 0.5 -  2 * gap;
        auto w2 = rect.width() * 1.0 -  2 * gap;
        auto h1 = rect.height() * 0.25 - 2 * gap;
        auto h2 = rect.height() * 0.50 - 2 * gap;
        auto h3 = rect.height() * 0.75 - 2 * gap;
        drawChartTm30Spd(painter, QRectF(x1, y1, w1, h1));
        drawChartTm30Cvg(painter, QRectF(x1, y2, w1, h2));
        drawChartTm30Rxhj(painter, QRectF(x2, y1, w1, h3));
        drawChartTm30Rfi(painter, QRectF(x1, y1, w2, h1));
        return;
    }
    if (page == 2)
    {
        return;
    }
    if (page == 3)
    {
        return;
    }

//    d->spdWidget->setTest(d->testData->data("[光谱能量曲线]").value<QPolygonF>());
//    d->spdWidget->setReference(d->testData->data("[光谱反射曲线]").value<QPolygonF>());
//    d->cvgWidget->setData(d->testData->select(d->cvgWidget->dataType()));
//    d->rfiWidget->chart()->setBarValue(d->testData->data("[TM30_Rfi]").value<QList<double>>());
//    d->rfhjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rf]").value<QList<double>>());
//    d->rcshjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rcs]").value<QList<double>>());
//    d->rhshjWidget->chart()->setBarValue(d->testData->data("[TM30_hj_Rhs]").value<QList<double>>());
}

QPointF HSpecPrintTemplate::drawChartSpec(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->specWidget == nullptr)
    {
        d->specWidget = new HSpecDiagramWidget;
        d->specWidget->setMargins(40, 25, 25, 35);
        d->specWidget->setBrushBackground(Qt::white);
        d->specWidget->setDrawRibbon(d->params.value("DrawRibbon", true).toBool());
        d->specWidget->setWindowTitle(tr("相对光谱能量分布"));
    }
    auto poly = d->datas.value("[光谱能量曲线]").value<QPolygonF>();
    if (!poly.isEmpty())
        d->specWidget->setWaveRange(QPointF(poly.first().x(), poly.last().x()));
    d->specWidget->addPolygon(0, poly);
    return HPainterHelper::drawChart(painter, rect, d->specWidget);
}

QPointF HSpecPrintTemplate::drawChartCie(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->cieWidget == nullptr)
    {
        d->cieWidget = new HCie1931Widget;
        d->cieWidget->setMargins(40, 25, 25, 35);
        d->cieWidget->setBrushBackground(Qt::white);
        d->cieWidget->setWindowTitle(tr("CIE1931色品图"));
    }
    d->cieWidget->setPointFocus(d->datas.value("[色坐标]").toPointF());
    return HPainterHelper::drawChart(painter, rect, d->cieWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Spd(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->spdWidget == nullptr)
        d->spdWidget = new HTm30SpdChartView;

    d->spdWidget->setTest(d->datas.value("[光谱能量曲线]").value<QPolygonF>());
    d->spdWidget->setReference(d->datas.value("[光谱反射曲线]").value<QPolygonF>());
    return HPainterHelper::drawChart(painter, rect, d->spdWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Cvg(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->cvgWidget == nullptr)
        d->cvgWidget = new HTm30CvgWidget;
    d->cvgWidget->setData(d->datas);
    return HPainterHelper::drawChart(painter, rect, d->cvgWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Rxhj(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->rxhjWidget == nullptr)
        d->rxhjWidget = new HTm30RxhjWidget;
    d->rxhjWidget->setRfhj(d->datas.value("[TM30_hj_Rf]").value<QList<double>>());
    d->rxhjWidget->setRcshj(d->datas.value("[TM30_hj_Rcs]").value<QList<double>>());
    d->rxhjWidget->setRhshj(d->datas.value("[TM30_hj_Rhs]").value<QList<double>>());
    return HPainterHelper::drawChart(painter, rect, d->rxhjWidget);
}

void HSpecPrintTemplate::init()
{
    Q_D(HSpecPrintTemplate);
    d->types = QStringList() << "[制造厂商]" << "[产品名称]" << "[产品型号]"  << "[样品编号]" << "[测试单位]" << "[测试员]"
                             << "[环境温度]" << "[环境湿度]" << "[测量日期时间]"
                             << "[色坐标]" <<  "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[色温]" << "[色纯度]" << "[色容差]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" << "[显色指数Rx]"
                             << "[光谱光通量]" << "[光功率]";
    d->params.insert("Header",      tr("松朗光电测试报告"));
    d->params.insert("Title",       tr("光谱测试报告"));
    d->params.insert("DrawHeader",  true);
    d->params.insert("DrawLogo",    true);
    d->params.insert("DrawRibbon",  true);
}

HE_END_NAMESPACE
