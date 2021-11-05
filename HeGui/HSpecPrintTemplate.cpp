#include "HSpecPrintTemplate_p.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include "HePlugin/HPainterHelper.h"
#include <QtGui/QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

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
    qDebug() << __func__;
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
    y1 = paintTitle(&painter, y1);
    auto y2 = paintFooter(&painter, 1);
    paintBody(&painter, QRectF(0, y1, painter.viewport().width(), y2 - y1), 1);
    return true;
}

double HSpecPrintTemplate::paintHeader(QPainter *painter)
{
    Q_D(HSpecPrintTemplate);
    painter->setFont(QFont("宋体", 12));
    if (d->params.value("DrawHeader", true).toBool())
        HPainterHelper::drawText(painter, 20, 5, d->params.value("Header").toString());
    if (d->params.value("DrawLogo", true).toBool())
        HPainterHelper::drawLogo(painter, QRectF(painter->viewport().width() - 180, 0, 162, 30));
    painter->drawLine(0, 35, painter->viewport().width(), 35);
    return 50;
}

double HSpecPrintTemplate::paintTitle(QPainter *painter, double y)
{
    Q_D(HSpecPrintTemplate);
    auto text = d->params.value("Title").toString();
    painter->setFont(QFont(tr("宋体"), 16, QFont::Bold));
    return HPainterHelper::drawText(painter, 0, y, text, Qt::AlignHCenter | Qt::TextWordWrap).y() + 10;
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

void HSpecPrintTemplate::paintBody(QPainter *painter, QRectF rect, int /*page*/)
{
    Q_D(HSpecPrintTemplate);
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
    drawChartSpec(painter, QRectF(xr1, yr, wr, hr), d->datas.value("[光谱能量曲线]").value<QPolygonF>());
    drawChartCie(painter, QRectF(xr2, yr, wr, hr), d->datas.value("[色坐标]").toPointF());
}

QPointF HSpecPrintTemplate::drawChartSpec(QPainter *painter, QRectF rect, QPolygonF poly)
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
    if (!poly.isEmpty())
        d->specWidget->setWaveRange(QPointF(poly.first().x(), poly.last().x()));
    d->specWidget->addPolygon(0, poly);
    return HPainterHelper::drawChart(painter, rect, d->specWidget);
}

QPointF HSpecPrintTemplate::drawChartCie(QPainter *painter, QRectF rect, QPointF point)
{
    Q_D(HSpecPrintTemplate);
    if (d->cieWidget == nullptr)
    {
        d->cieWidget = new HCie1931Widget;
        d->cieWidget->setMargins(40, 25, 25, 35);
        d->cieWidget->setBrushBackground(Qt::white);
        d->cieWidget->setWindowTitle(tr("CIE1931色品图"));
    }
    d->cieWidget->setPointFocus(point);
    return HPainterHelper::drawChart(painter, rect, d->cieWidget);
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
    readSettings();
}

HE_GUI_END_NAMESPACE
