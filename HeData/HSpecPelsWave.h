#ifndef HSPECPELSWAVE_H
#define HSPECPELSWAVE_H

#include "HDataGlobal.h"
#include <QVariant>

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate;

class HSpecPelsWave
{
public:
    explicit HSpecPelsWave();
    ~HSpecPelsWave();

public:
    void restoreDefault();
    void setData(QPolygonF value);
    QPolygonF data();

public:
    double toWave(double value);
    double toPels(double value);

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &p);

protected:
    QScopedPointer<HSpecPelsWavePrivate> d_ptr;

private:
    friend QDataStream &operator<<(QDataStream &, const HSpecPelsWave &);
    friend QDataStream &operator>>(QDataStream &, HSpecPelsWave &);
};

HE_DATA_END_NAMESPACE

#endif // HSPECPELSWAVE_H
