#include "HTestWidget1000I_p.h"
#include "HeCore/HCore.h"

HTestWidget1000IPrivate::HTestWidget1000IPrivate()
{
    auto list = QStringList() << "|时间信息2|" << "|产品信息3|" << "|环境信息|"  << "|直流电信息|";
    displays = QStringList() << "[调整组]" << "[分级]" << HCore::membership(list);

}


HTestWidget1000I::HTestWidget1000I(QWidget *parent) :
    HTestWidget(*new HTestWidget1000IPrivate, parent)
{
    init();
}

HTestWidget1000I::~HTestWidget1000I() = default;

QString HTestWidget1000I::typeName()
{
    return "HTestWidget1000I";
}



