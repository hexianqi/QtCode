#include "HModel7000_p.h"
#include "HeData/IConfigManage.h"

HModel7000::HModel7000(QObject *parent) :
    HIntegrateModel(*new HModel7000Private, parent)
{
}

HModel7000::~HModel7000() = default;

QString HModel7000::typeName()
{
    return "HModel7000";
}

void HModel7000::syncTestData(quint32 type)
{
    if ((type & IConfigManage::ContainLocation) != 0u)
    {
        addAction(ACT_RESET_LOCATION);
    }
    HIntegrateModel::syncTestData(type);
}

void HModel7000::syncDeviceAll()
{
    HIntegrateModel::syncDeviceAll();
    addAction(ACT_RESET_LOCATION);
}


