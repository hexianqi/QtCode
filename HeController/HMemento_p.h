#pragma once

#include "HMemento.h"

HE_BEGIN_NAMESPACE

class ITestData;
class IModel;

class HMementoPrivate
{
public:
    HMementoPrivate();

public:
    IModel *model = nullptr;
    ITestData *testData = nullptr;
    QStringList types;
    QVariantMap datas;
};

HE_END_NAMESPACE

