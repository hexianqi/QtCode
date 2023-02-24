/***************************************************************************************************
**      2023-02-22  HSpecPelsWave
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
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    virtual QVector<uchar> toBinaryData();
    virtual bool fromBinaryData(const QVector<uchar> &data, int &pos);

public:
    virtual void restoreDefault();
    virtual void setPoints(const QPolygonF &value);
    virtual QPolygonF points();
    virtual double handle(double value) = 0;

protected:
    HSpecPelsWave(HSpecPelsWavePrivate &);
};

HE_END_NAMESPACE

