/***************************************************************************************************
**      2019-04-28  HAdjust 调整数据。
***************************************************************************************************/

#pragma once

#include "IAdjust.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustPrivate;

class HAdjust : public IAdjust
{
    Q_DECLARE_PRIVATE(HAdjust)

public:
    explicit HAdjust();
    ~HAdjust();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void readContent(Worksheet *) override;
    void writeContent(QDataStream &) override;
    void writeContent(Worksheet *) override;

public:
    void restoreDefault() override;
    QVariantMap correct(QVariantMap value) override;

protected:
    HAdjust(HAdjustPrivate &);
};

HE_DATA_END_NAMESPACE
