#include "HTestWidget2100DC_p.h"
#include "HTestSetWidget2100DC.h"
#include "HDetailWidget2100DC.h"
#include <QtCore/QDebug>

HTestWidget2100DCPrivate::HTestWidget2100DCPrivate()
{
    displays = QStringList() << "[测量日期]" << "[测量时间]" << "[制造厂商]" << "[产品型号]" << "[测试员]" << "[样品编号]" << "[备注]" << "[环境温度]" << "[环境湿度]"
                             << "[分级]"
                             << "[输出电压]" << "[实测电压]" << "[输出电流]" << "[实测电流]" << "[电功率]"
                             << "[色容差]"
                             << "[光谱光通量]" << "[光功率]" << "[光效率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标x]" << "[色坐标y]" << "[色坐标up]" << "[色坐标vp]" << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" << "[显色指数R9]" <<"[显色指数Rx]";
}

HTestWidget2100DC::HTestWidget2100DC(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2100DCPrivate, parent)
{
    init();
}

HTestWidget2100DC::~HTestWidget2100DC()
{
    qDebug() << __func__;
}

void HTestWidget2100DC::initialize(QVariantMap /*param*/)
{

}

QString HTestWidget2100DC::typeName()
{
    return "HTestWidget2100DC";
}

void HTestWidget2100DC::createWidget()
{
    Q_D(HTestWidget2100DC);
    d->testSetWidget = new HTestSetWidget2100DC;
    d->detailWidget = new HDetailWidget2100DC;
    HSpecTestWidget::createWidget();
}
