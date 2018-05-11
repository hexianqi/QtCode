#ifndef ITESTDATA_H
#define ITESTDATA_H

#include "HControllerGlobal.h"
#include <QVariant>

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestData
{
public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void setSuccessor(ITestData *successor);
    virtual void setTestData(QString type, QVariant value) = 0;

public:
    virtual QVariant testData(QString type) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTDATA_H
