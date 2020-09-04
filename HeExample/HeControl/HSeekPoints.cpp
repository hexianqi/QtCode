#include "HSeekPoints.h"


HE_CONTROL_BEGIN_NAMESPACE

HSeekPoints::HSeekPoints(QObject *parent) :
    QObject(parent)
{
}

QList<HSeekPoint> HSeekPoints::points()
{
    QList<HSeekPoint> list;
    if (access())
    {
        list = _points;
        release();
    }
    return list;
}

void HSeekPoints::setPoints(QList<HSeekPoint> value)
{
    if (!access())
        return;
    _points = value;
    release();
}

bool HSeekPoints::access()
{
    return _mutex.tryLock(100);
}

void HSeekPoints::release()
{
    _mutex.unlock();
}

HE_CONTROL_END_NAMESPACE
