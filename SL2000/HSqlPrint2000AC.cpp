#include "HSqlPrint2000AC_p.h"
#include "HeCore/HCore.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>

HSqlPrint2000AC::HSqlPrint2000AC(QObject *parent) :
    HSpecSqlPrint(*new HSqlPrint2000ACPrivate, parent)
{
}

HSqlPrint2000AC::HSqlPrint2000AC(HSqlPrint2000ACPrivate &p, QObject *parent) :
    HSpecSqlPrint(p, parent)
{
}

HSqlPrint2000AC::~HSqlPrint2000AC()
{
    qDebug() << __func__;
}

QString HSqlPrint2000AC::typeName()
{
    return "HSqlPrint2000AC";
}

QString HSqlPrint2000AC::textForExcel()
{
    QString text;
    QTextStream out(&text);
    auto poly = toPolygonF("EnergyGraph");
    out << tr("测试数据")               << endl;
    out << toWhole("Manufacturer")      << "\t" << toWhole("ProductName")       << "\t" << toWhole("ProductModel")          << endl;
    out << toWhole("Tester")            << "\t" << toWhole("TestInstitute")     << "\t" << toWhole("SampleNumber")          << endl;
    out << toWhole("TestDate")          << "\t" << toWhole("TestTime")          << endl;
    out << toWhole("Temperature")       << "\t" << toWhole("Humidity")          << endl;
    out << toWhole("ACVoltage")         << "\t" << toWhole("ACCurrent")         << endl;
    out << toWhole("ACPower")           << "\t" << toWhole("ACFactor")          << endl;
    out << toWhole("LuminousFluxSpec")  << "\t" << toWhole("LuminousPower")     << "\t" << toWhole("LuminousEfficiency")    << endl;
    out << toWhole("PeakWave")          << "\t" << toWhole("PeakBandwidth")     << "\t" << toWhole("DominantWave")          << endl;
    out << toWhole("ColorPurity")       << "\t" << toWhole("ColorTemperature")  << "\t" << toWhole("SDCM")                  << endl;
    out << toWhole("CC_xy")             << "\t" << toWhole("CC_uvp")            << "\t" << toWhole("Duv")                   << endl;
    out << toWhole("RedRatio")          << "\t" << toWhole("GreenRadio")        << "\t" << toWhole("BlueRatio")             << endl;
    out << toWhole("Ra")                << "\t" << toWhole("R9")                << "\t" << toWhole("Rx")                    << endl;
    out << toWhole("Photon380_780")     << "\t" << toWhole("Photon400_700")     << "\t" << toWhole("Photon700_800")         << endl;
    out << toWhole("PPF")               << "\t" << toWhole("PRF")               << "\t" << toWhole("PPFE")                  << endl;
    out << toWhole("FluorescenceEfficiency")                                    << "\t" << toWhole("FluorescenceRatio")     << endl;
    out << endl;
    out << tr("光谱数据")                           << endl;
    out << tr("波长(nm)\t能量百分比(%)")            << endl;
    for (auto p : poly)
        out << HCore::toString("[波长]", p.x()) << "\t" << HCore::toString("[百分比]", p.y()) << endl;
    return text;
}

void HSqlPrint2000AC::paintPage(QPainter *painter, int page)
{
    auto y1 = paintHeader(painter, tr("松朗光色电综合测试报告"));
    y1 = paintTitle(painter, tr("光色电综合测试报告"), y1);
    auto y2 = paintFooter(painter, tr(" - %1 - ").arg(page + 1));
    paintBody(painter, y1, y2, page);
}

void HSqlPrint2000AC::paintBody(QPainter *painter, double y1, double y2, int /*page*/)
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
    text = tr(" 交流电压：%1V    交流电流：%2A ").arg(toString("ACVoltage"), toString("ACCurrent"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 交流电功率：%1W    功率因数：%2 ").arg(toString("ACPower"), toString("ACFactor"));
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
    text = tr(" 相关色温：Tc = %1K    主波长：λd = %2nm    色纯度：Purity = %3    色容差：%4SDCM")
               .arg(toString("ColorTemperature"), toString("DominantWave"), toString("ColorPurity"), toString("SDCM"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 色比：R = %1％  G = %2％  B = %3％    峰值波长：λp = %4nm    峰值带宽：Δλd = %5nm")
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
    text = tr(" 光通量：Φ = %1lm    光功率：Φ e = %2    光效率：%3lm/W").arg(toString("LuminousFluxSpec"), toString("LuminousPower"), toString("LuminousEfficiency"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光量子(umol/s)：%1[380-780nm]  %2[400-700nm]  %3[700-800nm]").arg(toString("Photon380_780"), toString("Photon400_700"), toString("Photon700_800"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光合光量子通量PPF：%1umol/s    光合有效辐射通量PRF：%2mW").arg(toString("PPF"), toString("PRF"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光合光子通量效率Eff(PPF)：%1umol/s/W    荧光效能：%2    荧光蓝光比：%3").arg(toString("PPFE"), toString("FluorescenceEfficiency"), toString("FluorescenceRatio"));
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
