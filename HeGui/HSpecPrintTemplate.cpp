#include "HSpecPrintTemplate_p.h"
#include "HeCore/HCore.h"
#include "HePlugin/HCie1931Widget.h"
#include "HePlugin/HChromatismChartView.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include "HePlugin/HTm30BarChart.h"
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
    delete d->chromatismWidget;
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
    Q_D(HSpecPrintTemplate);
    d->haveTM30 = checkData(HCore::membership("|TM30信息|"));
    printer->setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
    QPainter painter(printer);
    printHome(printer, &painter);
    printTM30(printer, &painter);
    return true;
}

void HSpecPrintTemplate::printHome(QPrinter */*printer*/, QPainter *painter)
{
    auto y1 = paintHeader(painter);
    auto y2 = paintFooter(painter, 0);
    y1 = paintTitle(painter, y1);
    paintBody(painter, QRectF(0, y1, painter->viewport().width(), y2 - y1), 0);
}

void HSpecPrintTemplate::printTM30(QPrinter *printer, QPainter *painter)
{
    Q_D(HSpecPrintTemplate);
    if (!d->haveTM30)
        return;

    double y1, y2;
    for (int i = 1; i < 3; i++)
    {
        printer->newPage();
        y1 = paintHeader(painter);
        y2 = paintFooterTM30(painter, i + 1);
        paintBodyTM30(painter, QRectF(0, y1, painter->viewport().width(), y2 - y1), i);
    }
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
    painter->setFont(QFont("宋体", 16, QFont::Bold));
    return HPainterHelper::drawText(painter, 0, y, text, Qt::AlignHCenter | Qt::TextWordWrap).y() + 10;
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
    // TM30
    if (d->haveTM30)
    {
        text = tr(" TM30 参数：Rf = %1    Rg = %2").arg(toString("[TM30_Rf]"), toString("[TM30_Rg]"));
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
    if (d->params.value("DrawChromatism").toBool())
        drawChartChromatism(painter, QRectF(xr2, yr, wr, hr));
    else
        drawChartCie(painter, QRectF(xr2, yr, wr, hr));
}

double HSpecPrintTemplate::paintFooterTM30(QPainter *painter, int page)
{
    painter->setFont(QFont("宋体", 8));
    return HPainterHelper::paintFooter(painter, QString::number(page));
}

void HSpecPrintTemplate::paintBodyTM30(QPainter *painter, QRectF rect, int page)
{
    if (page == 1)
    {
        auto x1 = rect.left();
        auto x2 = rect.center().x();
        auto y1 = rect.top();
        auto y2 = rect.top() + rect.height() * 0.35;
        auto y3 = rect.top() + rect.height() * 0.75;
        auto y4 = rect.bottom();
        auto w1 = rect.width() * 0.5;
        auto w2 = rect.width() * 1.0;
        drawChartTm30Spd(painter, QRectF(x1, y1, w1, y2 - y1));
        drawChartTm30Cvg(painter, QRectF(x1, y2, w1, y3 - y2));
        drawChartTm30Rxhj(painter, QRectF(x2, y1, w1, y3 - y1));
        drawChartTm30Rfi(painter, QRectF(x1, y3, w2, y4 - y3));
        return;
    }
    if (page == 2)
    {
        auto x1 = rect.left();
        auto x2 = rect.center().x();
        auto x3 = rect.left() + 20;
        auto y1 = rect.top();
        auto y2 = rect.top() + rect.height() * 0.3;
        auto y3 = y2 + 20;
        auto y4 = rect.bottom();;
        auto w1 = rect.width() * 0.5;
        auto w2 = rect.width() - 40;
        drawChartTm30Gamut(painter, QRectF(x1, y1, w1, y2 - y1));
        drawChartTm30RfRg(painter, QRectF(x2, y1, w1, y2 - y1));
        drawTableTm30Rxhj(painter, QRectF(x3, y3, w2, y4 - y3));
        return;
    }
}

QPointF HSpecPrintTemplate::drawChartSpec(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->specWidget == nullptr)
    {
        d->specWidget = new HSpecDiagramWidget;
        d->specWidget->setMargins(40, 25, 25, 35);
        d->specWidget->setBrushBackground(Qt::white);

        d->specWidget->setWindowTitle(tr("相对光谱能量分布"));
    }
    auto poly = d->datas.value("[光谱能量曲线]").value<QPolygonF>();
    if (!poly.isEmpty())
        d->specWidget->setWaveRange(QPointF(poly.first().x(), poly.last().x()));
    d->specWidget->addPolygon(0, poly);
    d->specWidget->setDrawRibbon(d->params.value("DrawRibbon", true).toBool());
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

QPointF HSpecPrintTemplate::drawChartChromatism(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->chromatismWidget == nullptr)
    {
        d->chromatismWidget = new HChromatismChartView;
        d->chromatismWidget->setWindowTitle("");
    }
    d->chromatismWidget->setData(d->datas.value("[色容差详情]").toMap());
    return HPainterHelper::drawChart(painter, rect, d->chromatismWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Spd(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->spdWidget == nullptr)
    {
        d->spdWidget = new HTm30SpdChartView;
        d->spdWidget->setWindowTitle("");
    }
    d->spdWidget->setTest(d->datas.value("[光谱能量曲线]").value<QPolygonF>());
    d->spdWidget->setReference(d->datas.value("[光谱反射曲线]").value<QPolygonF>());
    return HPainterHelper::drawChart(painter, rect, d->spdWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Cvg(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->cvgWidget == nullptr)
    {
        d->cvgWidget = new HTm30CvgWidget;
        d->cvgWidget->setWindowTitle("");
    }
    d->cvgWidget->setData(d->datas);
    return HPainterHelper::drawChart(painter, rect, d->cvgWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Rxhj(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->rxhjWidget == nullptr)
    {
        d->rxhjWidget = new HTm30RxhjWidget;
        d->rxhjWidget->setWindowTitle("");
    }
    d->rxhjWidget->setRfhj(d->datas.value("[TM30_hj_Rf]").value<QList<double>>());
    d->rxhjWidget->setRcshj(d->datas.value("[TM30_hj_Rcs]").value<QList<double>>());
    d->rxhjWidget->setRhshj(d->datas.value("[TM30_hj_Rhs]").value<QList<double>>());
    return HPainterHelper::drawChart(painter, rect, d->rxhjWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Rfi(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->rfiWidget == nullptr)
    {
        d->rfiWidget = new HTm30RfiChartView;
        d->rfiWidget->setWindowTitle("");
    }
    d->rfiWidget->chart()->setBarValue(d->datas.value("[TM30_Rfi]").value<QList<double>>());
    return HPainterHelper::drawChart(painter, rect, d->rfiWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30Gamut(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->gamutWidget == nullptr)
    {
        d->gamutWidget = new HTm30GamutWidget;
        d->gamutWidget->setWindowTitle("");
    }
    d->gamutWidget->setData(d->datas);
    return HPainterHelper::drawChart(painter, rect, d->gamutWidget);
}

QPointF HSpecPrintTemplate::drawChartTm30RfRg(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    if (d->rfrgWidget == nullptr)
    {
        d->rfrgWidget = new HTm30RfRgChartView;
        d->rfrgWidget->setWindowTitle("");
    }
    d->rfrgWidget->setRfRg(d->datas.value("[TM30_Rf]").toDouble(), d->datas.value("[TM30_Rg]").toDouble());
    return HPainterHelper::drawChart(painter, rect, d->rfrgWidget);
}

QPointF HSpecPrintTemplate::drawTableTm30Rxhj(QPainter *painter, QRectF rect)
{
    Q_D(HSpecPrintTemplate);
    int i;
    auto Rf = d->datas.value("[TM30_hj_Rf]").value<QList<double>>();
    auto Rcs = d->datas.value("[TM30_hj_Rcs]").value<QList<double>>();
    auto Rhs = d->datas.value("[TM30_hj_Rhs]").value<QList<double>>();
    auto pens = QList<QPen>() << QPen(Qt::black, 2) << QPen(Qt::black, 1);
    auto fonts = QList<QFont>() << QFont("宋体", 16, QFont::Bold) << QFont("宋体", 10, QFont::Bold) << QFont("宋体", 10);
    auto height = QFontMetrics(fonts[1]).height() + 8.0 * 2;
    auto width = QList<double>() << 0.0 << 0.15 << 0.4 << 0.6 << 0.8 << 1.0;
    QVector<double> x,y;
    for (i = 0; i < 6; i++)
        x << rect.left() + rect.width() * width[i];
    for (i = 0; i < 19; i++)
        y << 35 + rect.top() + height * i;

    painter->setFont(fonts[0]);
    painter->drawText(QRectF(rect.left(), rect.top() , rect.width(), 30), Qt::AlignCenter, tr("数据分析表"));
    painter->setPen(pens[0]);
    painter->drawRect(x[0], y[0], x[5] - x[0], y[18] - y[0]);
    painter->setPen(pens[1]);
    painter->drawLine(x[3], y[0], x[3], y[1]);
    for (i = 1; i < 5; i++)
        painter->drawLine(x[i], y[1], x[i], y[18]);
    for (i = 1; i < 18; i++)
        painter->drawLine(x[0], y[i], x[5], y[i]);
    painter->setFont(fonts[1]);
    painter->drawText(x[3], y[0], x[5] - x[3], height, Qt::AlignCenter, tr("Local Shift"));
    painter->drawText(x[0], y[1], x[1] - x[0], height, Qt::AlignCenter, tr("Hue Bin"));
    painter->drawText(x[1], y[1], x[2] - x[1], height, Qt::AlignCenter, tr("Hue Angle(°)"));
    painter->drawText(x[2], y[1], x[3] - x[2], height, Qt::AlignCenter, tr("Rf"));
    painter->drawText(x[3], y[1], x[4] - x[3], height, Qt::AlignCenter, tr("Chroma(%)"));
    painter->drawText(x[4], y[1], x[5] - x[4], height, Qt::AlignCenter, tr("Hue"));
    painter->setFont(fonts[2]);
    for (i = 0; i < 16; i++)
    {
        painter->drawText(x[0], y[i + 2], x[1] - x[0], height, Qt::AlignCenter, QString::number(i + 1));
        painter->drawText(x[1], y[i + 2], x[2] - x[1], height, Qt::AlignCenter, QString("%1 - %2").arg(22.5 * i, 0, 'f', 1).arg(22.5 * (i + 1), 0, 'f', 1));
        painter->drawText(x[2], y[i + 2], x[3] - x[2], height, Qt::AlignCenter, HCore::toString("[TM30_hj_Rf]", Rf[i]));
        painter->drawText(x[3], y[i + 2], x[4] - x[3], height, Qt::AlignCenter, HCore::toString("[TM30_hj_Rcs]", Rcs[i]));
        painter->drawText(x[4], y[i + 2], x[5] - x[4], height, Qt::AlignCenter, HCore::toString("[TM30_hj_Rhs]", Rhs[i]));
    }
    return QPointF(x[5], y[18]);
}

void HSpecPrintTemplate::init()
{
    Q_D(HSpecPrintTemplate);
    d->types = HCore::membership(QStringList() << "|产品信息2|" << "|环境信息|" << "|时间信息|" << "|光谱信息2|" << "|光度信息2|" << "|色容差信息|" << "|TM30信息|");
    d->params.insert("Header",          tr("松朗光电测试报告"));
    d->params.insert("Title",           tr("光谱测试报告"));
    d->params.insert("DrawHeader",      true);
    d->params.insert("DrawLogo",        true);
    d->params.insert("DrawRibbon",      true);
    d->params.insert("DrawChromatism",  false);
}

HE_END_NAMESPACE
