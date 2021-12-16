#pragma once

#include "HMemento.h"

HE_BEGIN_NAMESPACE

class IDataStream;
class ITestData;
class IModel;

class HMementoPrivate
{
public:
    HMementoPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IModel *model = nullptr;
    ITestData *testData = nullptr;
    IDataStream *stream = nullptr;
    QString fileName;
    QStringList types;
    QVariantMap datas;
};

HE_END_NAMESPACE

