#include "HTestWidget2000AC_p.h"
#include "HTestSetWidget2000AC.h"
#include "HDetailWidget2000AC.h"
#include <QtCore/QDebug>

HTestWidget2000ACPrivate::HTestWidget2000ACPrivate()
{
    displays = QStringList() << "[测量日期]" << "[测量时间]" << "[制造厂商]" << "[产品型号]" << "[测试员]" << "[样品编号]" << "[备注]" << "[环境温度]" << "[环境湿度]"
                             << "[分级]"
                             << "[交流电压]" << "[交流电流]" << "[交流电功率]" << "[功率因素]"
                             << "[色容差]"
                             << "[光谱光通量]" << "[光功率]" << "[光效率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" <<"[显色指数Rx]"
                             << "[光量子(380-780)]" << "[光量子(400-700)]" << "[光量子(700-800)]"
                             << "[光合光量子通量]" << "[光合有效辐射通量]" << "[光合光子通量效率]" << "[荧光效能]" << "[荧光蓝光比]";
}

HTestWidget2000AC::HTestWidget2000AC(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2000ACPrivate, parent)
{
    init();
}

HTestWidget2000AC::~HTestWidget2000AC()
{
    qDebug() << __func__;
}

void HTestWidget2000AC::initialize(QVariantMap /*param*/)
{

}

QString HTestWidget2000AC::typeName()
{
    return "HTestWidget2000AC";
}

void HTestWidget2000AC::createWidget()
{
    Q_D(HTestWidget2000AC);
    d->testSetWidget = new HTestSetWidget2000AC;
    d->detailWidget = new HDetailWidget2000AC;
    HSpecTestWidget::createWidget();
}
