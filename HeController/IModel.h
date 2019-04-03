/***************************************************************************************************
**      2018-06-19  IModel 模型接口。
***************************************************************************************************/

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
    void threadInitFinished(QStringList list);
    void threadStartFailed(QString text);
    void threadStateChanged(QString name, int state);
    void actionFailed(HActionType action, QString text);
    void actionFinished(HActionType action);

public:
    virtual void start() = 0;
    virtual void addAction(HActionType action, ulong delay = 0) = 0;
    virtual void syncTestData(quint32 type) = 0;

public:
    virtual bool openFile() = 0;
    virtual bool saveFile() = 0;
    virtual bool saveAsFile() = 0;
    virtual bool importFile(quint32 type) = 0;
    virtual bool exportFile(quint32 type) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // IMODEL_H
