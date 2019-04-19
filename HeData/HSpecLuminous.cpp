#include "HSpecLuminous_p.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecLuminous::HSpecLuminous()
    : HAbstractDataItem(*new HSpecLuminousPrivate)
{
    restoreDefault();
}

HSpecLuminous::HSpecLuminous(HSpecLuminousPrivate &p)
    : HAbstractDataItem(p)
{
}

HSpecLuminous::~HSpecLuminous()
{
}

QString HSpecLuminous::typeName()
{
    return "HSpecLuminous";
}

void HSpecLuminous::readContent(QDataStream &s)
{
    Q_D(HSpecLuminous);
    quint32 version;
    s >> version;
    s >> d->datas;
}

void HSpecLuminous::writeContent(QDataStream &s)
{
    Q_D(HSpecLuminous);
    s << quint32(1);
    s << d->datas;
}

void HSpecLuminous::restoreDefault()
{
    setData("[标准光谱光通量]", 0);
    setData("[光谱光通量系数]", 0);
}

double HSpecLuminous::handle(double value)
{
    return data("[光谱光通量系数]").toDouble() * value;
}

HE_DATA_END_NAMESPACE
