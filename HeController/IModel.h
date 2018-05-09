#ifndef IMODEL_H
#define IMODEL_H

#include "HControllerGlobal.h"
#include "HeCommunicate/HCommunicateGlobal.h"
#include "HeCore/HActionType.h"
#include <QObject>
#include <QVariant>

HE_COMMUNICATE_BEGIN_NAMESPACE
class IDevice;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec;

class HE_CONTROLLER_EXPORT IModel : public QObject
{
    Q_OBJECT

public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void addAction(HActionType action) = 0;
    virtual void setTestData(QString type, QVariant value) = 0;

public:
    virtual IDevice *device(QString name) = 0;
    virtual ITestSpec *testSpec();
    virtual QVariant testData(QString type) = 0;

};

HE_CONTROLLER_END_NAMESPACE

#endif // IMODEL_H
