#include "HTestWidget2000_p.h"
#include "HeCore/HCore.h"
#include "HTestSetWidget2000.h"
#include "HDetailWidget2000.h"

HTestWidget2000Private::HTestWidget2000Private()
{
    productEditable = false;
    auto list = QStringList() << "|时间信息2|" << "|光度信息4|" << "|光谱信息4|" << "|色容差信息2|";
    displays = QStringList() << "[分级]" << HCore::membership(list);
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
