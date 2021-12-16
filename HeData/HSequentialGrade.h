/***************************************************************************************************
**      2019-04-17  HSequentialGrade 连续分级数据。
***************************************************************************************************/

#pragma once

#include "HAbstractGrade.h"

HE_BEGIN_NAMESPACE

class HSequentialGradePrivate;

class HSequentialGrade : public HAbstractGrade
{
    Q_DECLARE_PRIVATE(HSequentialGrade)

public:
    explicit HSequentialGrade();

public:
    QString typeName() override;

public:
    int calcLevel(QVariantMap value, QString *text) override;
};

HE_END_NAMESPACE
