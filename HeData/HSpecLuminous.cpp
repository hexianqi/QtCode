#include "HSpecLuminous_p.h"
#include "HDataHelper.h"
#include <QtCore/QDataStream>
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSpecLuminous::HSpecLuminous() :
    HAbstractDataItem(*new HSpecLuminousPrivate)
{
    restoreDefault();
}

HSpecLuminous::HSpecLuminous(HSpecLuminousPrivate &p):
    HAbstractDataItem(p)
{
}

QString HSpecLuminous::typeName()
{
    return "HSpecLuminous";
}
/***************************************************************************************************
**      2018-09-01  版本02    增加selfAbsorption。
***************************************************************************************************/
void HSpecLuminous::readContent(QDataStream &s)
{
    Q_D(HSpecLuminous);
    quint32 version;
    s >> version;
    s >> d->datas;
    if (version >= 2)
        s >> d->selfAbsorption;
}

void HSpecLuminous::writeContent(QDataStream &s)
{
    Q_D(HSpecLuminous);
    s << quint32(2);
    s << d->datas;
    s << d->selfAbsorption;
}

QVector<uchar> HSpecLuminous::toBinaryData()
{
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)   // 版本
                               << HDataHelper::writeDouble(data("[标准光谱光通量]").toDouble())
                               << HDataHelper::writeDouble(data("[光谱光通量系数]").toDouble());
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecLuminous::fromBinaryData(const QVector<uchar> &data, int &pos)
{
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;
    setData("[标准光谱光通量]", HDataHelper::readDouble(data, pos));
    setData("[光谱光通量系数]", HDataHelper::readDouble(data, pos));
    return true;
}

void HSpecLuminous::restoreDefault()
{
    setData("[标准光谱光通量]", 0);
    setData("[光谱光通量系数]", 0);
    setData("[自吸收启用]", false);
    setData("[自吸收选项]", QString());
}

double HSpecLuminous::handle(double value)
{
    Q_D(HSpecLuminous);
    auto r = data("[光谱光通量系数]").toDouble() * value;
    auto b = data("[自吸收启用]").toBool();
    auto c = data("[自吸收选项]").toString();
    if (b && d->selfAbsorption.contains(c))
        r *= d->selfAbsorption.value(c);
    return r;
}

void HSpecLuminous::setSelfAbsorption(const QMap<QString, double> &value)
{
    Q_D(HSpecLuminous);
    d->selfAbsorption = value;
}

QMap<QString, double> HSpecLuminous::selfAbsorption()
{
    Q_D(HSpecLuminous);
    return d->selfAbsorption;
}

HE_END_NAMESPACE
