/***************************************************************************************************
**      2018-06-19  HSpecPelsWave 像元波长数据类。
***************************************************************************************************/

#ifndef HSPECPELSWAVE_H
#define HSPECPELSWAVE_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate;

class HSpecPelsWave : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecPelsWave)

public:
    explicit HSpecPelsWave();
    ~HSpecPelsWave();

public:
    virtual void restoreDefault() override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

public:
    void setData(QPolygonF value);
    QPolygonF data();

public:
    double toWave(double value);
    double toPels(double value);

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECPELSWAVE_H
