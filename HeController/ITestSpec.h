#ifndef ITESTSPEC_H
#define ITESTSPEC_H

#include "HControllerGlobal.h"
#include <QVariant>

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec
{
public:
    virtual void setTestData(QString type, QVariant value) = 0;

public:
    virtual QVariant testData(QString type) = 0;

};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTSPECTRUM_H
