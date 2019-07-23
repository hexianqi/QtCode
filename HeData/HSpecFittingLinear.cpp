#include "HSpecFittingLinear_p.h"
#include "HDataHelper.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HMath.h"

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecFittingLinear::HSpecFittingLinear() :
    HSpecFitting(*new HSpecFittingLinearPrivate)
{
    init();
}

HSpecFittingLinear::HSpecFittingLinear(HSpecFittingLinearPrivate &p) :
    HSpecFitting(p)
{
}

HSpecFittingLinear::~HSpecFittingLinear()
{
}

QString HSpecFittingLinear::typeName()
{
    return "HSpecFittingLinear";
}

QVector<uchar> HSpecFittingLinear::toBinaryData()
{
    Q_D(HSpecFittingLinear);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)  // 版本
                               << HDataHelper::writeUInt16(static_cast<quint16>(d->fittingPoints.size()));
    for (auto p : d->fittingPoints)
        r << HDataHelper::writeUInt16(static_cast<quint16>(p.x())) << HDataHelper::writeUInt16(static_cast<quint16>(p.y() * 10000));
    r[0] = static_cast<uchar>(r.size() / 256);
    r[1] = static_cast<uchar>(r.size() % 256);
    return r;
}

bool HSpecFittingLinear::fromBinaryData(QVector<uchar> data, int &pos)
{
    Q_D(HSpecFittingLinear);
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    d->fittingPoints.clear();
    auto size = HDataHelper::readUInt16(data, pos);
    for (int i = 0; i < size; i++)
    {
        auto x = HDataHelper::readUInt16(data, pos);
        auto y = HDataHelper::readUInt16(data, pos) / 10000.0;
        d->fittingPoints << QPointF(x, y);
    }
    setData("[光谱拟合取样次数]", size);
    setData("[光谱拟合有效范围]", QPointF(d->fittingPoints.first().x(), d->fittingPoints.last().x()));
    return true;
}

double HSpecFittingLinear::calcRate(double value)
{
    Q_D(HSpecFittingLinear);
    if (d->fittingPoints.size() < 3)
        return 1.0;

//    auto range = data("[光谱拟合有效范围]").toPointF();
//    value = qBound(range.x(), value, range.y());
    return HMath::interpolate(value, d->fittingPoints);
//    return HInterp::eval(d->fittingPoints, value, HInterpType::Cspline);
}

HE_DATA_END_NAMESPACE
