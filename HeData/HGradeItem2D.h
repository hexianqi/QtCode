/***************************************************************************************************
**      2019-04-18  HGradeItem2D 分级数据项（二维）。
***************************************************************************************************/

#pragma once

#include "IGradeItem.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HGradeItem2DPrivate;

class HGradeItem2D : public HAbstractDataItem, public virtual IGradeItem
{
    Q_DECLARE_PRIVATE(HGradeItem2D)

public:
    explicit HGradeItem2D();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setLevels(QVariant value) override;
    QVariant levels() override;
    QSet<int> indexOf(QVariant value) override;
    int count() override;
    QStringList headers() override;
    QStringList types() override;
    QStringList level(int i) override;

protected:
    HGradeItem2D(HGradeItem2DPrivate &);
};

HE_END_NAMESPACE
