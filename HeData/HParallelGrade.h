/***************************************************************************************************
**      2019-04-17  HParallelGrade 并行分级数据类。
***************************************************************************************************/

#ifndef HPARALLELGRADE_H
#define HPARALLELGRADE_H

#include "HAbstractGrade.h"

HE_DATA_BEGIN_NAMESPACE

class HParallelGradePrivate;

class HParallelGrade : public HAbstractGrade
{
    Q_DECLARE_PRIVATE(HParallelGrade)

public:
    explicit HParallelGrade();
    ~HParallelGrade() override;

public:
    QString typeName() override;

public:
    int calcLevel(QVariantMap value, QString &text) override;

public:
    void readContent(QDataStream &, IDataFactory *) override;
    void writeContent(QDataStream &) override;
};

HE_DATA_END_NAMESPACE

#endif // HPARALLELGRADE_H
