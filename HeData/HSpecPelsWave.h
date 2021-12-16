/***************************************************************************************************
**      2018-06-19  HSpecPelsWave 像元波长数据类。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWavePrivate;

class HSpecPelsWave : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecPelsWave)

public:
    explicit HSpecPelsWave();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    QVector<uchar> toBinaryData();
    bool fromBinaryData(const QVector<uchar> &data, int &pos);

public:
    void restoreDefault();
    void setPelsWave(const QPolygonF &value);
    QPolygonF pelsWave();
    double handle(double value);

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &p);
};

HE_END_NAMESPACE
