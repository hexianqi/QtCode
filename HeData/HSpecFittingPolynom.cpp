#include "HSpecFittingPolynom_p.h"
#include "HDataHelper.h"
#include "HeAlgorithm/HMath.h"
#include "HeAlgorithm/HMultiFit.h"
#include <QtCore/QDataStream>
#include <QtCore/QtMath>

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecFittingPolynom::HSpecFittingPolynom() :
    HSpecFitting(*new HSpecFittingPolynomPrivate)
{
    init();
}

HSpecFittingPolynom::HSpecFittingPolynom(HSpecFittingPolynomPrivate &p) :
    HSpecFitting(p)
{
}

HSpecFittingPolynom::~HSpecFittingPolynom()
{
}

QString HSpecFittingPolynom::typeName()
{
    return "HSpecFittingPolynom";
}

void HSpecFittingPolynom::readContent(QDataStream &s)
{
    Q_D(HSpecFittingPolynom);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->fittingPoints;
    s >> d->ca;
    s >> d->cova;
}

void HSpecFittingPolynom::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingPolynom);
    s << quint32(1);
    s << d->datas;
    s << d->fittingPoints;
    s << d->ca;
    s << d->cova;
}

QVector<uchar> HSpecFittingPolynom::toBinaryData()
{
    Q_D(HSpecFittingPolynom);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)  // 版本
                               << HDataHelper::writeUInt16(static_cast<quint16>(d->fittingPoints.size()));
    for (auto p : d->fittingPoints)
        r << HDataHelper::writeUInt16(static_cast<quint16>(p.x())) << HDataHelper::writeUInt16(static_cast<quint16>(p.y() * 10000));
    r << HDataHelper::writeUInt16(data("[光谱拟合多项式项数]").toInt());
    r[0] = static_cast<uchar>(r.size() / 256);
    r[1] = static_cast<uchar>(r.size() % 256);
    return r;
}

bool HSpecFittingPolynom::fromBinaryData(QVector<uchar> data, int &pos)
{
    Q_D(HSpecFittingPolynom);
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
    setData("[光谱拟合多项式项数]", HDataHelper::readUInt16(data, pos));
    setData("[光谱拟合取样次数]", size);
    setData("[光谱拟合有效范围]", QPointF(d->fittingPoints.first().x(), d->fittingPoints.last().x()));
    calcLinear();
    return true;
}

void HSpecFittingPolynom::clear()
{
    Q_D(HSpecFittingPolynom);
    HSpecFitting::clear();
    d->ca.clear();
    d->cova.clear();
}

void HSpecFittingPolynom::setFittingPoints(QPolygonF value)
{
    HSpecFitting::setFittingPoints(value);
    calcLinear();
}

void HSpecFittingPolynom::init()
{
    Q_D(HSpecFittingPolynom);
    HSpecFitting::init();
    setData("[光谱拟合多项式项数]", 7);
    d->ca.clear();
    d->cova.clear();
}

double HSpecFittingPolynom::calcRate(double value)
{
    auto range = data("[光谱拟合有效范围]").toPointF();
    if (value >= range.x() && value <= range.y())
        return calcPolynom(value);

    double x1, x2, y1, y2;
    if (value < range.x())
    {
        x1 = range.x();
        x2 = range.x() + 50;
    }
    else
    {
        x1 = range.y() - 50;
        x2 = range.y();
    }

    y1 = calcPolynom(x1);
    y2 = calcPolynom(x2);
    return HMath::interpolate(value, x1, y1, x2, y2);
}

double HSpecFittingPolynom::calcPolynom(double value)
{
    Q_D(HSpecFittingPolynom);
    if (d->ca.size() < 2)
        return 1.0;
    double y, error;
    HMultiFit::linear_est(value, d->ca, d->cova, &y, &error);
    return  y;
}

void HSpecFittingPolynom::calcLinear()
{
    Q_D(HSpecFittingPolynom);
    double chisq;
    d->ca.clear();
    d->cova.clear();
    d->ca.resize(data("[光谱拟合多项式项数]").toInt());
    HMultiFit::linear(d->fittingPoints, d->ca, d->cova, &chisq);
}

HE_DATA_END_NAMESPACE
