#include "HTestWidget2000AC_p.h"
#include "HeCore/HCore.h"
#include "HTestSetWidget2000AC.h"
#include "HDetailWidget2000AC.h"

HTestWidget2000ACPrivate::HTestWidget2000ACPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|交流电信息|" << "|光度信息3|" << "|光谱信息4|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    displays = QStringList() << "[分级]" << HCore::membership(list);
}

HTestWidget2000AC::HTestWidget2000AC(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2000ACPrivate, parent)
{
    init();
}

HTestWidget2000AC::~HTestWidget2000AC() = default;

QString HTestWidget2000AC::typeName()
{
    return "HTestWidget2000AC";
}

void HTestWidget2000AC::createWidget()
{
    Q_D(HTestWidget2000AC);
    HSpecTestWidget::createWidget();
    d->testSetWidget = new HTestSetWidget2000AC;
    d->detailWidget = new HDetailWidget2000AC;
}
