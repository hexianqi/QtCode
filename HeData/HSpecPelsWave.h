/***************************************************************************************************
**      2018-06-19  HSpecPelsWave 像元波长数据类。
***************************************************************************************************/

#ifndef HSPECPELSWAVE_H
#define HSPECPELSWAVE_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate;

class HE_DATA_EXPORT HSpecPelsWave : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecPelsWave)

public:
    explicit HSpecPelsWave();
    ~HSpecPelsWave() override;

public:
    void restoreDefault() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setPelsWave(QPolygonF value);
    QPolygonF pelsWave();

public:
    double toWave(double value);
    double toPels(double value);

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECPELSWAVE_H
