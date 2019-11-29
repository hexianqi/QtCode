#include "HSpecSqlPrint_p.h"
#include "HSqlPainterHelper.h"
#include "HeCore/HCore.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include "HePlugin/HCie1931Widget.h"
#include <QtGui/QPolygonF>
#include <QtGui/QPainter>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSpecSqlPrint::HSpecSqlPrint(QObject *parent) :
    HAbstractSqlPrint(*new HSpecSqlPrintPrivate, parent)
{

}

HSpecSqlPrint::HSpecSqlPrint(HSpecSqlPrintPrivate &p, QObject *parent) :
    HAbstractSqlPrint(p, parent)
{

}

HSpecSqlPrint::~HSpecSqlPrint()
{
    qDebug() << __func__;
}

void HSpecSqlPrint::initialize(QVariantMap /*param*/)
{

}

QString HSpecSqlPrint::typeName()
{
    return "HSpecSqlPrint";
}

QString HSpecSqlPrint::textForExcel()
{
    QString text;
    QTextStream out(&text);
    auto poly = toPolygonF("EnergyGraph");
    out << tr("测试数据")               << endl;
    out << toWhole("Manufacturer")      << "\t" << toWhole("ProductName")       << "\t" << toWhole("ProductModel")  << endl;
    out << toWhole("Tester")            << "\t" << toWhole("TestInstitute")     << "\t" << toWhole("SampleNumber")  << endl;
    out << toWhole("TestDate")          << "\t" << toWhole("TestTime")          << endl;
    out << toWhole("Temperature")       << "\t" << toWhole("Humidity")          << endl;
    out << toWhole("LuminousFluxSpec")  << "\t" << toWhole("LuminousPower")     << endl;
    out << toWhole("PeakWave")          << "\t" << toWhole("PeakBandwidth")     << "\t" << toWhole("DominantWave")  << endl;
    out << toWhole("ColorPurity")       << "\t" << toWhole("ColorTemperature")  << endl;
    out << toWhole("CC_xy")             << "\t" << toWhole("CC_uvp")            << "\t" << toWhole("Duv")           << endl;
    out << toWhole("RedRatio")          << "\t" << toWhole("GreenRadio")        << "\t" << toWhole("BlueRatio")     << endl;
    out << toWhole("Ra")                << "\t" << toWhole("Rx")                << endl;
    out << endl;
    out << tr("光谱数据")                           << endl;
    out << tr("波长(nm)\t能量百分比(%)")            << endl;
    for (auto p : poly)
        out << HCore::toString("[波长]", p.x()) << "\t" << HCore::toString("[百分比]", p.y()) << endl;
    return text;
}

int HSpecSqlPrint::pageCount()
{
    return 1;
}

void HSpecSqlPrint::paintPage(QPainter *painter, int page)
{
    auto y1 = paintHeader(painter, tr("松朗光电测试报告"));
    y1 = paintTitle(painter, tr("光谱测试报告"), y1);
    auto y2 = paintFooter(painter, tr(" - %1 - ").arg(page + 1));
    paintBody(painter, y1, y2, page);
}

double HSpecSqlPrint::paintFooter(QPainter *painter, QString /*text*/)
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
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("ProductModel"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("ProductName"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("TestInstitute"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("Tester"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("SampleNumber"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("TestDateTime"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("Temperature"));
    painter->drawText(QRectF(x2, y2 , w, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("Humidity"));
    y2 += h;
    painter->drawText(QRectF(x1, y2 , w * 2, h), Qt::AlignLeft | Qt::AlignVCenter, toWhole("Manufacturer"));
    return y1;
}

void HSpecSqlPrint::paintBody(QPainter *painter, double y1, double y2, int /*page*/)
{
    auto gap = 8.0;
    auto font1 = QFont("宋体", 12, QFont::Bold);
    auto font2 = QFont("宋体", 10);
    auto h1 = QFontMetrics(font1).height() + gap * 2.0;
    auto h2 = QFontMetrics(font2).height() + gap * 2.0;
    auto w = painter->viewport().width() - gap * 2.0;
    auto x = gap;
    auto y = y1;
    auto text = tr("");
    auto rx = toString("Rx").split(" ", QString::SkipEmptyParts);

    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("颜色参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 色品坐标：x = %1    y = %2    u' = %3    v' = %4    duv = %5")
            .arg(toString("CC_x")).arg(toString("CC_y")).arg(toString("CC_up")).arg(toString("CC_vp")).arg(toString("Duv"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 相关色温：Tc = %1 K    主波长：λd = %2 nm    色纯度：Purity = %3")
            .arg(toString("ColorTemperature")).arg(toString("DominantWave")).arg(toString("ColorPurity"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr("色比：R = %1 ％  G = %2 ％  B = %3 ％ 峰值波长：λp = %4 nm   峰值带宽：Δλd = %5 nm")
            .arg(toString("RedRatio")).arg(toString("GreenRadio")).arg(toString("BlueRatio"))
            .arg(toString("PeakWave")).arg(toString("PeakBandwidth"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 显色指数：Ra = %1").arg(toString("Ra"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    if (rx.size() > 13)
    {
        text = tr("  R1 = %1    R2 = %2    R3 = %3    R4 = %4    R5 = %5    R6 = %6    R7 = %7")
                .arg(rx[0]).arg(rx[1]).arg(rx[2]).arg(rx[3]).arg(rx[4]).arg(rx[5]).arg(rx[6]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
        text = tr("  R8 = %1    R9 = %2    R10 = %3   R11 = %4   R12 = %5   R13 = %6   R14 = %7")
                .arg(rx[7]).arg(rx[8]).arg(rx[9]).arg(rx[10]).arg(rx[11]).arg(rx[12]).arg(rx[13]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
    }
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("光度参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 光通量：Φ = %1 lm    光功率：Φ e = %2").arg(toString("LuminousFluxSpec")).arg(toString("LuminousPower"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;

    y += 20;
    auto wr = painter->viewport().width() / 2.0 - gap * 2.0;
    auto hr = y2 - y;
    auto xr1 = gap;
    auto xr2 = painter->viewport().width() / 2.0 + gap;
    drawChartSpec(painter, QRectF(xr1, y, wr, hr), toPolygonF("EnergyGraph"));
    drawChartCie(painter, QRectF(xr2, y, wr, hr), recordValue("CC_xy").toPointF());
}

QPointF HSpecSqlPrint::drawChartSpec(QPainter *painter, QRectF rect, QPolygonF poly)
{
    Q_D(HSpecSqlPrint);
    if (d->specWidget == nullptr)
    {
        d->specWidget = new HSpecDiagramWidget;
        d->specWidget->setMargins(40, 25, 25, 35);
        d->specWidget->setBrushBackground(Qt::white);
    }
    if (!poly.isEmpty())
        d->specWidget->setWaveRange(QPointF(poly.first().x(), poly.last().x()));
    d->specWidget->addPolygon(0, poly);
    return HSqlPainterHelper::drawChart(painter, rect, tr("相对光谱能量分布"), d->specWidget);
}

QPointF HSpecSqlPrint::drawChartCie(QPainter *painter, QRectF rect, QPointF point)
{
    Q_D(HSpecSqlPrint);
    if (d->cieWidget == nullptr)
    {
        d->cieWidget = new HCie1931Widget;
        d->cieWidget->setMargins(40, 25, 25, 35);
        d->cieWidget->setBrushBackground(Qt::white);
    }
    d->cieWidget->setPointFocus(point);
    return HSqlPainterHelper::drawChart(painter, rect, tr("CIE1931色品图"), d->cieWidget);
}

HE_SQL_END_NAMESPACE
