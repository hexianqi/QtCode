#include "HModel2100DC_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include <QtCore/QDebug>

HModel2100DC::HModel2100DC(QObject *parent) :
    HSpecModel(*new HModel2100DCPrivate, parent)
{
}

HModel2100DC::HModel2100DC(HModel2100DCPrivate &p, QObject *parent) :
    HSpecModel(p, parent)
{
}

HModel2100DC::~HModel2100DC()
{
    qDebug() << __func__;
}

QString HModel2100DC::typeName()
{
    return "HModel2100DC";
}

void HModel2100DC::syncDeviceAll()
{
    HSpecModel::syncDeviceAll();
    addAction(ACT_SET_OUTPUT_VOLTAGE);
    addAction(ACT_SET_OUTPUT_CURRENT);
    addAction(ACT_SET_SOURCE_MODE);
}
