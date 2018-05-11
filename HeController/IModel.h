#ifndef IMODEL_H
#define IMODEL_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include "HeCommunicate/HCommunicateGlobal.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE
class IDevice;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IModel : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void deviceFailed(QString text);
    void initThreadFinished(QStringList list);
    void threadStateChanged(QString name, int state);
    void actionFailed(HActionType action, QString text);
    void actionFinished(HActionType action);

public:
    virtual void addAction(HActionType action) = 0;

public:
    virtual IDevice *device(QString name) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // IMODEL_H
