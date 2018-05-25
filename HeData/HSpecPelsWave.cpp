#include "HSpecPelsWave_p.h"
#include "HeAlgorithm/HMath.h"
#include <QDataStream>

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecPelsWave::HSpecPelsWave()
    : d_ptr(new HSpecPelsWavePrivate)
{
    restoreDefault();
}

HSpecPelsWave::HSpecPelsWave(HSpecPelsWavePrivate &p)
    : d_ptr(&p)
{
    restoreDefault();
}

HSpecPelsWave::~HSpecPelsWave()
{
}

void HSpecPelsWave::restoreDefault()
{
    d_ptr->datas = QPolygonF() << QPointF(124, 404.7)
                               << QPointF(300, 435.8)
                               << QPointF(432, 546.1)
                               << QPointF(900, 632.8)
                               << QPointF(1275, 696.5)
                               << QPointF(1540, 750.4)
                               << QPointF(1760, 763.5);
}

void HSpecPelsWave::setData(QPolygonF value)
{
    d_ptr->datas = value;
}

QPolygonF HSpecPelsWave::data()
{
    return d_ptr->datas;
}

double HSpecPelsWave::toWave(double value)
{
    return HMath::interpolate(value, d_ptr->datas);
}

double HSpecPelsWave::toPels(double value)
{
    return HMath::interpolateY(value, d_ptr->datas);
}

QDataStream &operator>>(QDataStream &s, HSpecPelsWave &spec)
{
    quint32 version;
    s >> version;
    s >> spec.d_ptr->datas;
    return s;
}

QDataStream &operator<<(QDataStream &s, const HSpecPelsWave &spec)
{
    s << quint32(1);
    s << spec.d_ptr->datas;
    return s;
}

HE_DATA_END_NAMESPACE
