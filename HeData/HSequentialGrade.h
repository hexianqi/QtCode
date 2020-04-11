/***************************************************************************************************
**      2019-04-17  HSequentialGrade 连续的分级数据。
***************************************************************************************************/

#ifndef HSEQUENTIALGRADE_H
#define HSEQUENTIALGRADE_H

#include "HAbstractGrade.h"

HE_DATA_BEGIN_NAMESPACE

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

HE_DATA_END_NAMESPACE

#endif // HSEQUENTIALGRADE_H
