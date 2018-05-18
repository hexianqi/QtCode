#ifndef ITESTDATA_H
#define ITESTDATA_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestData : public IInitializeable
{
public:
    // 设置后继者
    virtual void setSuccessor(ITestData *successor) = 0;
    virtual void setData(QString type, QVariant value) = 0;

public:
    virtual QVariant data(QString type) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTDATA_H
