#pragma once

#include "HMemento.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IDataStream;
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

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
    QStringList items;
    QVariantMap datas;
};

HE_CONTROLLER_END_NAMESPACE

