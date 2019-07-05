#include "HSpecStdCurve_p.h"
#include "HDataHelper.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecStdCurve::HSpecStdCurve() :
    HAbstractDataItem(*new HSpecStdCurvePrivate)
{
    restoreDefault();
}

HSpecStdCurve::HSpecStdCurve(HSpecStdCurvePrivate &p) :
    HAbstractDataItem(p)
{
}

HSpecStdCurve::~HSpecStdCurve()
{
}

QString HSpecStdCurve::typeName()
{
    return "HSpecStdCurve";
}

void HSpecStdCurve::readContent(QDataStream &s)
{
    Q_D(HSpecStdCurve);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->curve;
}

void HSpecStdCurve::writeContent(QDataStream &s)
{
    Q_D(HSpecStdCurve);
    s << quint32(1);
    s << d->datas;
    s << d->curve;
}

QVector<uchar> HSpecStdCurve::toBinaryData()
{
    Q_D(HSpecStdCurve);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)  // 版本
                               << HDataHelper::writeUInt16(d->curve.size());
    for (auto p : d->curve)
        r << HDataHelper::writeUInt16(p);
    r[0] = r.size() / 256;
    r[1] = r.size() % 256;
    return r;
}

bool HSpecStdCurve::fromBinaryData(QVector<uchar> data, int &pos)
{
    Q_D(HSpecStdCurve);
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    d->curve.clear();
    auto size = HDataHelper::readUInt16(data, pos);
    for (int i = 0; i < size; i++)
        d->curve << HDataHelper::readUInt16(data, pos);
    return true;
}

void HSpecStdCurve::restoreDefault()
{
    Q_D(HSpecStdCurve);
    d->curve.clear();
}

void HSpecStdCurve::setCurve(QVector<double> value)
{
    Q_D(HSpecStdCurve);
    d->curve = value;
}

QVector<double> HSpecStdCurve::curve()
{
    Q_D(HSpecStdCurve);
    return d->curve;
}

HE_DATA_END_NAMESPACE
