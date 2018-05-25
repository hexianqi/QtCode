#include "HSpecLuminous_p.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecLuminous::HSpecLuminous()
    : d_ptr(new HSpecLuminousPrivate)
{
    restoreDefault();
}

HSpecLuminous::HSpecLuminous(HSpecLuminousPrivate &p)
    : d_ptr(&p)
{
    restoreDefault();
}

HSpecLuminous::~HSpecLuminous()
{
}

void HSpecLuminous::restoreDefault()
{
    setData("[标准光谱光通量]", 0);
    setData("[光谱光通量系数]", 0);
}

void HSpecLuminous::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

QVariant HSpecLuminous::data(QString name)
{
    return d_ptr->datas.value(name);
}

double HSpecLuminous::handle(double value)
{
    return data("[光谱光通量系数]").toDouble() * value;
}

QDataStream &operator>>(QDataStream &s, HSpecLuminous &spec)
{
    quint32 version;
    s >> version;
    s >> spec.d_ptr->datas;
    return s;
}

QDataStream &operator<<(QDataStream &s, const HSpecLuminous &spec)
{
    s << quint32(1);
    s << spec.d_ptr->datas;
    return s;
}

HE_DATA_END_NAMESPACE
