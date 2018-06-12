#include "HAbstractDomain_p.h"
#include <QtMath>

HAbstractDomain::HAbstractDomain(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractDomainPrivate)
{
}

HAbstractDomain::HAbstractDomain(HAbstractDomainPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractDomain::~HAbstractDomain()
{
}

//algorithm defined by Paul S.Heckbert GraphicalGems I
void HAbstractDomain::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount)
{
    auto range = niceNumber(max - min, true); //range with ceiling
    auto step = niceNumber(range / (ticksCount - 1), false);
    min = qFloor(min / step);
    max = qCeil(max / step);
    ticksCount = int(max - min) + 1;
    min *= step;
    max *= step;
}

//nice numbers can be expressed as form of 1*10^n, 2* 10^n or 5*10^n
double HAbstractDomain::niceNumber(double x, bool ceiling)
{
    auto z = qPow(10.0, qFloor(std::log10(x))); //find corresponding number of the form of 10^n than is smaller than x
    auto q = x / z; //q<10 && q>=1;

    if (ceiling)
    {
        if (q <= 1.0) q = 1;
        else if (q <= 2.0) q = 2;
        else if (q <= 5.0) q = 5;
        else q = 10;
    }
    else
    {
        if (q < 1.5) q = 1;
        else if (q < 3.0) q = 2;
        else if (q < 7.0) q = 5;
        else q = 10;
    }
    return q * z;
}
