/***************************************************************************************************
**      2018-06-19  HSpecPelsWave 像元波长数据类。
***************************************************************************************************/

#ifndef HSPECPELSWAVE_H
#define HSPECPELSWAVE_H

#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate;

class HE_DATA_EXPORT HSpecPelsWave : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecPelsWave)

public:
    explicit HSpecPelsWave();
    ~HSpecPelsWave() override;

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault();
    void setPelsWave(QPolygonF value);
    QPolygonF pelsWave();
    double handle(double value);

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECPELSWAVE_H
