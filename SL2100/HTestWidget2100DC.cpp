#include "HTestWidget2100DC_p.h"
#include "HeCore/HCore.h"
#include "HTestSetWidget2100DC.h"
#include "HDetailWidget2100DC.h"

HTestWidget2100DCPrivate::HTestWidget2100DCPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息2|" << "|光度信息3|" << "|光谱信息4|" << "|色容差信息2|" << "|光合信息|" << "|TM30信息2|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list);
}

HTestWidget2100DC::HTestWidget2100DC(QWidget *parent) :
    HSpecTestWidget(*new HTestWidget2100DCPrivate, parent)
{
    init();
}

HTestWidget2100DC::~HTestWidget2100DC() = default;

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
