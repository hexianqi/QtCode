/***************************************************************************************************
**      2021-03-09  HAdjust2
***************************************************************************************************/

#pragma once

#include "IAdjust2.h"

HE_BEGIN_NAMESPACE

class HAdjust2Private;

class HAdjust2 : public IAdjust2
{
    Q_DECLARE_PRIVATE(HAdjust2)

public:
    explicit HAdjust2();
    ~HAdjust2();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    QVariantMap correct(double tc, QVariantMap value) override;

protected:
    HAdjust2(HAdjust2Private &);

protected:
    bool matching(double tc);
};

HE_END_NAMESPACE

