#include "HSpecElecSqlPrint_p.h"
#include "HeCore/HCore.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSpecElecSqlPrint::HSpecElecSqlPrint(QObject *parent) :
    HSpecSqlPrint(*new HSpecElecSqlPrintPrivate, parent)
{
}

HSpecElecSqlPrint::HSpecElecSqlPrint(HSpecElecSqlPrintPrivate &p, QObject *parent) :
    HSpecSqlPrint(p, parent)
{
}

HSpecElecSqlPrint::~HSpecElecSqlPrint()
{
    qDebug() << __func__;
}

QString HSpecElecSqlPrint::typeName()
{
    return "HSpecElecSqlPrint";
}

QString HSpecElecSqlPrint::textForExcel()
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
    out << toWhole("ReverseVoltage")    << "\t" << toWhole("ReverseCurrent")    << endl;
    out << toWhole("LuminousFluxSpec")  << "\t" << toWhole("LuminousPower")     << "\t" << toWhole("LuminousEfficiency")    << endl;
    out << toWhole("PeakWave")          << "\t" << toWhole("PeakBandwidth")     << "\t" << toWhole("DominantWave")          << endl;
    out << toWhole("ColorPurity")       << "\t" << toWhole("ColorTemperature")  << endl;
    out << toWhole("CC_xy")             << "\t" << toWhole("CC_uvp")            << "\t" << toWhole("Duv")                   << endl;
    out << toWhole("RedRatio")          << "\t" << toWhole("GreenRadio")        << "\t" << toWhole("BlueRatio")             << endl;
    out << toWhole("Ra")                << "\t" << toWhole("Rx")                << endl;
    out << endl;
    out << tr("光谱数据")                           << endl;
    out << tr("波长(nm)\t能量百分比(%)")            << endl;
    for (auto p : poly)
        out << HCore::toString("[波长]", p.x()) << "\t" << HCore::toString("[百分比]", p.y()) << endl;
    return text;
}

void HSpecElecSqlPrint::paintPage(QPainter *painter, int page)
{
    auto y1 = paintHeader(painter, tr("松朗光电测试报告"));
    y1 = paintTitle(painter, tr("光色电测试报告"), y1);
    auto y2 = paintFooter(painter, tr(" - %1 - ").arg(page + 1));
    paintBody(painter, y1, y2, page);
}

void HSpecElecSqlPrint::paintBody(QPainter *painter, double y1, double y2, int /*page*/)
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
    text = tr(" 输出电压：%1 V   输出电流：%2 mA ").arg(toString("OutputVoltage"), toString("OutputCurrent"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 实测电压：%1 V   实测电流：%2 mA  电功率：%3 W").arg(toString("MeasuredVoltage"), toString("MeasuredCurrent"), toString("ElecPower"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 反向电压：%1 V   反向漏流：%2 mA  光效率：%3").arg(toString("ReverseVoltage"), toString("ReverseCurrent"));
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
    text = tr("色比：R = %1 ％  G = %2 ％  B = %3 ％ 峰值波长：λp = %4 nm   峰值带宽：Δλd = %5 nm")
            .arg(toString("RedRatio"), toString("GreenRadio"), toString("BlueRatio"), toString("PeakWave"), toString("PeakBandwidth"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 显色指数：Ra = %1").arg(toString("Ra"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    if (rx.size() > 13)
    {
        text = tr("  R1 = %1    R2 = %2    R3 = %3    R4 = %4    R5 = %5    R6 = %6    R7 = %7")
                .arg(rx[0], rx[1], rx[2], rx[3], rx[4], rx[5], rx[6]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
        text = tr("  R8 = %1    R9 = %2    R10 = %3   R11 = %4   R12 = %5   R13 = %6   R14 = %7")
                .arg(rx[7], rx[8], rx[9], rx[10], rx[11], rx[12], rx[13]);
        painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
        y += h2;
    }
    // 光度参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("光度参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 光通量：Φ = %1 lm    光功率：Φ e = %2   光效率：%3 lm/W").arg(toString("LuminousFluxSpec"), toString("LuminousPower"), toString("LuminousEfficiency"));
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

HE_SQL_END_NAMESPACE
