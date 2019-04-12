#include "HSpecFittingTest_p.h"
#include "HeAlgorithm/HInterp.h"
#include <QDataStream>

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecFittingTest::HSpecFittingTest() :
    HSpecFitting(*new HSpecFittingTestPrivate)
{
    restoreDefault();
}

HSpecFittingTest::~HSpecFittingTest()
{
}

QString HSpecFittingTest::typeName()
{
    return "HSpecFittingTest";
}

void HSpecFittingTest::restoreDefault()
{
    Q_D(HSpecFittingTest);
    HSpecFitting::restoreDefault();
    d->allFittingPoints.clear();
}

void HSpecFittingTest::readContent(QDataStream &s)
{
    Q_D(HSpecFittingTest);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->allFittingPoints;
}

void HSpecFittingTest::writeContent(QDataStream &s)
{
    Q_D(HSpecFittingTest);
    s << quint32(1);
    s << d->datas;
    s << d->allFittingPoints;
}

void HSpecFittingTest::setFittingPoints(QPolygonF value)
{
    Q_D(HSpecFittingTest);
    HSpecFitting::setFittingPoints(value);
    d->allFittingPoints.append(d->fittingPoints);
}

QVector<double> HSpecFittingTest::handle(QVector<double> value, bool abovezero)
{
    QVector<double> r;
    for (int i = 0; i < value.size(); i++)
        r << handle(i, value[i], abovezero);
    return value;

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
    i = i % d->allFittingPoints.size();
    if (d->allFittingPoints[i].size() < 3)
        return 1.0;

    auto range = data("[光谱拟合有效范围]").toPointF();
    value = qBound(range.x(), value, range.y());
    return HInterp::eval(d->allFittingPoints[i], value, HInterpType::Cspline);
}

HE_DATA_END_NAMESPACE
