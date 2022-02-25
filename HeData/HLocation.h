/***************************************************************************************************
**      2022-01-26  HLocation
***************************************************************************************************/

#pragma once

#include "ILocation.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HLocationPrivate;

class HLocation : public HAbstractDataItem, public virtual ILocation
{
    Q_DECLARE_PRIVATE(HLocation)

public:
    explicit HLocation();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    QPolygon polygon() override;
    QVector<QVector<int>> layout() override;
    void setLayout(QVector<QVector<int>>) override;

protected:
    HLocation(HLocationPrivate &);
};

HE_END_NAMESPACE

