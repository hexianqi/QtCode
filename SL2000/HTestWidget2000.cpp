#include "HTestWidget2000_p.h"
#include "HTestSetWidget2000.h"
#include "HDetailWidget2000.h"

HTestWidget2000Private::HTestWidget2000Private()
{
    displays = QStringList() << "[测量日期]" << "[测量时间]"
                             << "[分级]"
                             << "[色容差]"
                             << "[光谱光通量]" << "[光功率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标]" << ("[色坐标uvp]") << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数Ra]" <<"[显色指数Rx]";
}

HTestWidget2000::HTestWidget2000(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2000Private, parent)
{
    init();
}

HTestWidget2000::~HTestWidget2000() = default;

QString HTestWidget2000::typeName()
{
    return "HTestWidget2000";
}

void HTestWidget2000::createWidget()
{
     Q_D(HTestWidget2000);
     d->testSetWidget = new HTestSetWidget2000;
     d->detailWidget = new HDetailWidget2000;
     HSpecTestWidget::createWidget();
}
