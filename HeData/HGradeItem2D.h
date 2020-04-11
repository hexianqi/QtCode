/***************************************************************************************************
**      2019-04-18  HGradeItem2D 分级数据项（二维）。
***************************************************************************************************/

#ifndef HGRADEITEM2D_H
#define HGRADEITEM2D_H

#include "IGradeItem.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItem2DPrivate;

class HGradeItem2D : public IGradeItem
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

HE_DATA_END_NAMESPACE

#endif // HGRADEITEM2D_H
