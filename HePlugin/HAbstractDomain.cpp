#include "HAbstractDomain_p.h"

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

void HAbstractDomain::setRangeX(double min, double max)
{
    setRange(min, max, d_ptr->minY, d_ptr->maxY);
}

void HAbstractDomain::setRangeY(double min, double max)
{
    setRange(d_ptr->minX, d_ptr->maxX, min, max);
}

void HAbstractDomain::setMinX(double min)
{
    setRange(min, d_ptr->maxX, d_ptr->minY, d_ptr->maxY);
}

void HAbstractDomain::setMaxX(double max)
{
    setRange(d_ptr->minX, max, d_ptr->minY, d_ptr->maxY);
}

void HAbstractDomain::setMinY(double min)
{
    setRange(d_ptr->minX, d_ptr->maxX, min, d_ptr->maxY);
}

void HAbstractDomain::setMaxY(double max)
{
    setRange(d_ptr->minX, d_ptr->maxX, d_ptr->minY, max);
}

void HAbstractDomain::setBlockRangeSignals(bool b)
{
    if (d_ptr->signalsBlocked == b)
        return;
    d_ptr->signalsBlocked = b;
    if (!b)
    {
        emit rangeHorizontalChanged(d_ptr->minX, d_ptr->maxX);
        emit rangeVerticalChanged(d_ptr->minY, d_ptr->maxY);
    }
}

void HAbstractDomain::zoomReset()
{
    if (!d_ptr->zoomed)
        return;
    setRange(d_ptr->zoomResetMinX, d_ptr->zoomResetMaxX, d_ptr->zoomResetMinY, d_ptr->zoomResetMaxY);
    d_ptr->zoomed = false;
}

void HAbstractDomain::storeZoomReset()
{
    if (d_ptr->zoomed)
        return;
    d_ptr->zoomed = true;
    d_ptr->zoomResetMinX = d_ptr->minX;
    d_ptr->zoomResetMaxX = d_ptr->maxX;
    d_ptr->zoomResetMinY = d_ptr->minY;
    d_ptr->zoomResetMaxY = d_ptr->maxY;
}

double HAbstractDomain::minX() const
{
    return d_ptr->minX;
}

double HAbstractDomain::maxX() const
{
    return d_ptr->maxX;
}

double HAbstractDomain::minY() const
{
    return d_ptr->minY;
}

double HAbstractDomain::maxY() const
{
    return d_ptr->maxY;
}

double HAbstractDomain::spanX() const
{
    Q_ASSERT(d_ptr->maxX >= d_ptr->minX);
    return d_ptr->maxX - d_ptr->minX;
}

double HAbstractDomain::spanY() const
{
    Q_ASSERT(d_ptr->maxY >= d_ptr->minY);
    return d_ptr->maxY - d_ptr->minY;
}

bool HAbstractDomain::isEmpty() const
{
    return qFuzzyCompare(spanX(), 0) || qFuzzyCompare(spanY(), 0);
}

bool HAbstractDomain::isRangeSignalsBlocked() const
{
    return d_ptr->signalsBlocked;
}

bool HAbstractDomain::isZoomed()
{
    return d_ptr->zoomed;
}
