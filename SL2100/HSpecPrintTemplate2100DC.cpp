#include "HSpecPrintTemplate2100DC_p.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>

HSpecPrintTemplate2100DC::HSpecPrintTemplate2100DC(QObject *parent) :
    HSpecPrintTemplate(*new HSpecPrintTemplate2100DCPrivate, parent)
{
    init();
}

HSpecPrintTemplate2100DC::HSpecPrintTemplate2100DC(HSpecPrintTemplate2100DCPrivate &p, QObject *parent) :
    HSpecPrintTemplate(p, parent)
{
}

HSpecPrintTemplate2100DC::~HSpecPrintTemplate2100DC()
{
    qDebug() << __func__;
}


QString HSpecPrintTemplate2100DC::typeName()
{
    return "HSpecPrintTemplate2100DC";
}

void HSpecPrintTemplate2100DC::paintBody(QPainter *painter, QRectF rect, int /*page*/)
{
    Q_D(HSpecPrintTemplate2100DC);
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

    // 电参数
    painter->setFont(font1);
    painter->drawText(QRectF(x, y , w, h1), Qt::AlignLeft | Qt::AlignVCenter, tr("电参数："));
    y += h1;
    painter->setFont(font2);
    text = tr(" 输出电压：%1V    输出电流：%2mA ").arg(toString("[输出电压]"), toString("[输出电流]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 实测电压：%1V    实测电流：%2mA    电功率：%3W").arg(toString("[实测电压]"), toString("[实测电流]"), toString("[电功率]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
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
    text = tr(" 光通量：Φ = %1lm    光功率：Φ e = %2mW    光效率：%3lm/W").arg(toString("[光谱光通量]"), toString("[光功率]"), toString("[光效率]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光量子(umol/s)：%1[380-780nm]  %2[400-700nm]  %3[700-800nm]").arg(toString("[光量子(380-780)]"), toString("[光量子(400-700)]"), toString("[光量子(700-800)]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光合光量子通量PPF：%1umol/s    光合有效辐射通量PRF：%2mW").arg(toString("[光合光量子通量]"), toString("[光合有效辐射通量]"));
    painter->drawText(QRectF(x, y , w, h2), Qt::AlignLeft | Qt::AlignVCenter, text);
    y += h2;
    text = tr(" 光合光子通量效率Eff(PPF)：%1umol/s/W    荧光效能：%2    荧光蓝光比：%3").arg(toString("[光合光子通量效率]"), toString("[荧光效能]"), toString("[荧光蓝光比]"));
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

void HSpecPrintTemplate2100DC::init()
{
    Q_D(HSpecPrintTemplate2100DC);
    d->types = QStringList() << "[制造厂商]" << "[产品名称]" << "[产品型号]"  << "[样品编号]" << "[测试单位]" << "[测试员]"
                             << "[环境温度]" << "[环境湿度]" << "[测量日期时间]"
                             << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[电功率]"
                             << "[色坐标]" <<  "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[色温]" << "[色纯度]" << "[色容差]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" << "[显色指数Rx]"
                             << "[光谱光通量]" << "[光功率]" << "[光效率]"
                             << "[光量子(380-780)]" << "[光量子(400-700)]" << "[光量子(700-800)]"
                             << "[光合光量子通量]" << "[光合有效辐射通量]" << "[光合光子通量效率]"
                             << "[荧光效能]" << "[荧光蓝光比]";
    d->params.insert("header",      tr("松朗光色电综合测试报告"));
    d->params.insert("title",       tr("光色电综合测试报告"));
    d->params.insert("drawHeader",  true);
    d->params.insert("drawLogo",    true);
    d->params.insert("drawRibbon",  true);
    readSettings();
}
