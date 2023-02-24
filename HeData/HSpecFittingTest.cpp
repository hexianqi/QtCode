#include "HSpecFittingTest_p.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HMath.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecFittingTest::HSpecFittingTest() :
    HSpecFitting(*new HSpecFittingTestPrivate)
{
    init();
}

QString HSpecFittingTest::typeName()
{
    return "HSpecFittingTest";
}

void HSpecFittingTest::readContent(QDataStream &s)
{
    Q_D(HSpecFittingTest);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->allPoints;
}

void HSpecFittingTest::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingTest);
    s << quint32(1);
    s << d->datas;
    s << d->allPoints;
}

QVector<uchar> HSpecFittingTest::toBinaryData()
{
    return QVector<uchar>();
}

bool HSpecFittingTest::fromBinaryData(QVector<uchar> /*data*/, int &/*pos*/)
{
    return true;
}

void HSpecFittingTest::clear()
{
    Q_D(HSpecFittingTest);
    d->points.clear();
    d->allPoints.clear();
}

void HSpecFittingTest::setPoints(QPolygonF value)
{
    Q_D(HSpecFittingTest);
    HSpecFitting::setPoints(value);
    d->allPoints.append(d->points);
}

QVector<double> HSpecFittingTest::handle(QVector<double> value, bool abovezero)
{
    QVector<double> r;
    for (int i = 0; i < value.size(); i++)
        r << handle(i, value[i], abovezero);
    return r;
}

void HSpecFittingTest::init()
{
    Q_D(HSpecFittingTest);
    HSpecFitting::init();
    d->allPoints.clear();
}

double HSpecFittingTest::handle(double /*value*/, bool /*abovezero*/)
{
    return 1.0;
}

double HSpecFittingTest::calcRate(double /*value*/)
{
    return 1.0;
}

double HSpecFittingTest::handle(int i, double value, bool abovezero)
{
    auto rate = calcRate(i, value);
    value = value / rate;
    if (abovezero)
        value = qMax(0.0, value);
    return value;
}

double HSpecFittingTest::calcRate(int i, double value)
{
    Q_D(HSpecFittingTest);
    if (d->allPoints.isEmpty())
        return 1.0;
    i = i % d->allPoints.size();
    if (d->allPoints[i].size() < 3)
        return 1.0;

    auto range = data("[光谱拟合有效范围]").toPointF();
    value = qBound(range.x(), value, range.y());
    return HMath::interpolate(value, d->allPoints[i]);
//    return HInterp::eval(d->allFittingPoints[i], value, HInterpType::Cspline);
}

HE_END_NAMESPACE
