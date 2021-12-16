/***************************************************************************************************
**      2019-04-17  HParallelGrade 并行分级数据类。
***************************************************************************************************/

#pragma once

#include "HAbstractGrade.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
