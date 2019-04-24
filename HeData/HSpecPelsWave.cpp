#include "HSpecPelsWave_p.h"
#include "HeAlgorithm/HMath.h"
#include <QtCore/QDataStream>

HE_ALGORITHM_USE_NAMESPACE
HE_DATA_BEGIN_NAMESPACE

HSpecPelsWave::HSpecPelsWave() :
    HAbstractDataItem(*new HSpecPelsWavePrivate)
{
    restoreDefault();
}

HSpecPelsWave::HSpecPelsWave(HSpecPelsWavePrivate &p) :
    HAbstractDataItem(p)
{
}

HSpecPelsWave::~HSpecPelsWave()
{
}

QString HSpecPelsWave::typeName()
{
    return "HSpecPelsWave";
}

void HSpecPelsWave::readContent(QDataStream &s)
{
    Q_D(HSpecPelsWave);
    quint32 version;
    d->pelsWave.clear();
    s >> version;
    s >> d->datas;
    s >> d->pelsWave;
}

void HSpecPelsWave::writeContent(QDataStream &s)
{
    Q_D(HSpecPelsWave);
    s << quint32(1);
    s << d->datas;
    s << d->pelsWave;
}

void HSpecPelsWave::restoreDefault()
{
    Q_D(HSpecPelsWave);
    d->pelsWave = QPolygonF() << QPointF(124, 404.7)
                              << QPointF(300, 435.8)
                              << QPointF(432, 546.1)
                              << QPointF(900, 632.8)
                              << QPointF(1275, 696.5)
                              << QPointF(1540, 750.4)
                              << QPointF(1760, 763.5);
}

void HSpecPelsWave::setPelsWave(QPolygonF value)
{
    Q_D(HSpecPelsWave);
    d->pelsWave = value;
}

QPolygonF HSpecPelsWave::pelsWave()
{
    Q_D(HSpecPelsWave);
    return d->pelsWave;
}

double HSpecPelsWave::handle(double value)
{
    return HMath::interpolate(value, pelsWave());
}

HE_DATA_END_NAMESPACE
