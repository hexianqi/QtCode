#include "HSqlPrint2100DC_p.h"
#include "HeCore/HCore.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>

HSqlPrint2100DC::HSqlPrint2100DC(QObject *parent) :
    HSpecSqlPrint(*new HSqlPrint2100DCPrivate, parent)
{
}

HSqlPrint2100DC::HSqlPrint2100DC(HSqlPrint2100DCPrivate &p, QObject *parent) :
    HSpecSqlPrint(p, parent)
{
}

HSqlPrint2100DC::~HSqlPrint2100DC()
{
    qDebug() << __func__;
}

QString HSqlPrint2100DC::typeName()
{
    return "HSqlPrint2100DC";
}

QString HSqlPrint2100DC::textForExcel()
{
    QString text;
    QTextStream out(&text);
    auto poly = toPolygonF("EnergyGraph");
    out << tr("测试数据")               << endl;
    out << toWhole("Manufacturer")      << "\t" << toWhole("ProductName")       << "\t" << toWhole("ProductModel")          << endl;
    out << toWhole("Tester")            << "\t" << toWhole("TestInstitute")     << "\t" << toWhole("SampleNumber")          << endl;
    out << toWhole("TestDate")          << "\t" << toWhole("TestTime")          << endl;
    out << toWhole("Temperature")       << "\t" << toWhole("Humidity")          << endl;
    out << toWhole("OutputVoltage")     << "\t" << toWhole("OutputCurrent")     << endl;
    out << toWhole("MeasuredVoltage")   << "\t" << toWhole("MeasuredCurrent")   << "\t" << toWhole("ElecPower")             << endl;
    out << toWhole("LuminousFlux")      << "\t" << toWhole("LuminousPower")     << "\t" << toWhole("LuminousEfficiency")    << endl;
    out << toWhole("PeakWave")          << "\t" << toWhole("PeakBandwidth")     << "\t" << toWhole("DominantWave")          << endl;
    out << toWhole("ColorPurity")       << "\t" << toWhole("ColorTemperature")  << endl;
    out << toWhole("CC_xy")             << "\t" << toWhole("CC_uvp")            << "\t" << toWhole("Duv")                   << endl;
    out << toWhole("RedRatio")          << "\t" << toWhole("GreenRadio")        << "\t" << toWhole("BlueRatio")             << endl;
    out << toWhole("Ra")                << "\t" << toWhole("R9")                << "\t" << toWhole("Rx")                << endl;
    out << endl;
    out << tr("光谱数据")                           << endl;
    out << tr("波长(nm)\t能量百分比(%)")            << endl;
    for (auto p : poly)
        out << HCore::toString("[波长]", p.x()) << "\t" << HCore::toString("[百分比]", p.y()) << endl;
    return text;
}

void HSqlPrint2100DC::paintPage(QPainter *painter, int page)
{
    auto y1 = paintHeader(painter, tr("松朗光色电综合测试报告"));
    y1 = paintTitle(painter, tr("光色电综合测试报告"), y1);
    auto y2 = paintFooter(painter, tr(" - %1 - ").arg(page + 1));
    paintBody(painter, y1, y2, page);
}

void HSqlPrint2100DC::paintBody(QPainter *painter, double y1, double y2, int /*page*/)
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

    // 电参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("电参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 输出电压：%1 V    输出电流：%2 mA ").arg(toString("OutputVoltage"), toString("OutputCurrent"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 实测电压：%1 V    实测电流：%2 mA    电功率：%3 W").arg(toString("MeasuredVoltage"), toString("MeasuredCurrent"), toString("ElecPower"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    // 颜色参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("颜色参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 色品坐标：x = %1    y = %2    u' = %3    v' = %4    duv = %5")
               .arg(toString("CC_x"), toString("CC_y"), toString("CC_up"), toString("CC_vp"), toString("Duv"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft |  Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 相关色温：Tc = %1 K    主波长：λd = %2 nm    色纯度：Purity = %3")
               .arg(toString("ColorTemperature"), toString("DominantWave"), toString("ColorPurity"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr("色比：R = %1 ％  G = %2 ％  B = %3 ％    峰值波长：λp = %4 nm    峰值带宽：Δλd = %5 nm")
               .arg(toString("RedRatio"), toString("GreenRadio"), toString("BlueRatio"), toString("PeakWave"), toString("PeakBandwidth"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    if (rx.size() > 14)
    {
        text = tr(" 显色指数：Ra = %1    R9 = %2").arg(toString("Ra"), rx[8]);
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
    text = tr(" 光通量：Φ = %1 lm    光功率：Φ e = %2    光效率：%3 lm/W").arg(toString("LuminousFlux"), toString("LuminousPower"), toString("LuminousEfficiency"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;

    // 图像
    y += 20;
    auto wr = painter->viewport().width() / 2.0 - gap * 2.0;
    auto hr = y2 - y;
    auto xr1 = gap;
    auto xr2 = painter->viewport().width() / 2.0 + gap;
    drawChartSpec(painter, QRectF(xr1, y, wr, hr), toPolygonF("EnergyGraph"));
    drawChartCie(painter, QRectF(xr2, y, wr, hr), recordValue("CC_xy").toPointF());
}
