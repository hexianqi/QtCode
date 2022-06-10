#include "HTestWidget1000A_p.h"
#include "HTestSetWidget1000A.h"
#include "HDetailWidget1000A.h"
#include "HeCore/HCore.h"
#include "HeGui/HSpecEnergyWidget.h"

HTestWidget1000APrivate::HTestWidget1000APrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|" << "|光度信息|" << "|光谱信息5|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list);
}

HTestWidget1000A::HTestWidget1000A(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget1000APrivate, parent)
{
    init();
}

HTestWidget1000A::~HTestWidget1000A() = default;

QString HTestWidget1000A::typeName()
{
    return "HTestWidget1000A";
}

void HTestWidget1000A::createWidget()
{
    Q_D(HTestWidget1000A);
    HSpecTestWidget::createWidget();
    d->testSetWidget = new HTestSetWidget1000A;
    d->detailWidget = new HDetailWidget1000A;
    d->energyWidget->addProgressBar("[光采样比率]");
}
