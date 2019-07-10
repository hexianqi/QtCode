#include "HSpecFittingPolynom_p.h"
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
    s >> d->ca;
    s >> d->cova;
}

void HSpecFittingPolynom::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingPolynom);
    s << quint32(1);
    s << d->datas;
    s << d->ca;
    s << d->cova;
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
    Q_D(HSpecFittingPolynom);
    HSpecFitting::setFittingPoints(value);

    double chisq;
    d->ca.clear();
    d->cova.clear();
    d->ca.resize(data("[光谱拟合多项式项数]").toInt());
    HMultiFit::linear(d->fittingPoints, d->ca, d->cova, &chisq);
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

//    double r = 1;
//    for (int i = 0; i < d->polynom.size(); i++)
//        r += d->polynom[i] * qPow(value, i);
//    return r - 1;
}

HE_DATA_END_NAMESPACE
