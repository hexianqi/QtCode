#ifndef IMODEL_H
#define IMODEL_H

#include "HControllerGlobal.h"
#include "HeCommunicate/HCommunicateGlobal.h"
#include "HeCore/HActionType.h"
#include <QObject>

HE_COMMUNICATE_BEGIN_NAMESPACE
class IProtocolStrategy;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IModel : public QObject
{
    Q_OBJECT

public:
    virtual void initialize(QVariantMap param) = 0;

public:
    virtual IProtocolStrategy *protocolStrategy(QString name) = 0;

public:
    virtual void addAction(HActionType action) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // IMODEL_H
