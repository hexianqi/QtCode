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

public:
    QString typeName() override;

public:
    int calcLevel(QVariantMap value, QString *text) override;
};

HE_DATA_END_NAMESPACE

#endif // HPARALLELGRADE_H
