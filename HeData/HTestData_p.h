#pragma once

#include "HTestData.h"

HE_BEGIN_NAMESPACE

class HTestDataPrivate
{
public:
    void setData(const QString &type, const QVariant &value);
    void setData(QVariantMap value);
    void addData(const QString &type, const QVariant &value);
    void addData(QVariantMap value);
    QVariant data(const QString &type);

public:
    ITestData *successor = nullptr;
    QVariantMap datas;
};

HE_END_NAMESPACE
