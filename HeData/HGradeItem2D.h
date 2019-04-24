/***************************************************************************************************
**      2019-04-18  HGradeItem2D 分级数据子项（二维）。
***************************************************************************************************/

#ifndef HGRADEITEM2D_H
#define HGRADEITEM2D_H

#include "HAbstractGradeItem.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItem2DPrivate;

class HGradeItem2D : public HAbstractGradeItem
{
    Q_DECLARE_PRIVATE(HGradeItem2D)

public:
    explicit HGradeItem2D();
    ~HGradeItem2D() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setLevels(QVariant value) override;
    QSet<int> indexOf(QVariant value) override;
    int count() override;
    QStringList headers() override;
    QStringList types() override;
    QVariant levels() override;
    QStringList level(int i) override;
};

HE_DATA_END_NAMESPACE

#endif // HGRADEITEM2D_H
