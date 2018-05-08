#include "HAbstractThread_p.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IProtocol.h"
#include "IModel.h"
#include <QSettings>
#include <QWaitCondition>
#include <QMutexLocker>

HE_CORE_USE_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE


HAbstractThreadPrivate::HAbstractThreadPrivate()
{
    mutex = new QMutex;
    waitConditionAction = new QWaitCondition;
}

void HAbstractThreadPrivate::enqueueAction(HActionType action)
{
    QMutexLocker locker(mutex);
    actionQueue.enqueue(action);
    waitConditionAction->wakeOne();
}

HActionType HAbstractThreadPrivate::dequeueAction()
{
    QMutexLocker locker(mutex);
    if (actionQueue.isEmpty())
        waitConditionAction->wait(mutex);
    return actionQueue.dequeue();
}

void HAbstractThreadPrivate::clearAction()
{
    QMutexLocker locker(mutex);
    actionQueue.clear();
}

HAbstractThread::HAbstractThread(IModel *model, QObject *parent)
    : IThread(parent), d_ptr(new HAbstractThreadPrivate)
{
    d_ptr->model = model;
    readSettings();
}

HAbstractThread::HAbstractThread(HAbstractThreadPrivate &p, QObject *parent)
    : IThread(parent), d_ptr(&p)
{
    readSettings();
}

HAbstractThread::~HAbstractThread()
{
    writeSettings();
    stop();
}

void HAbstractThread::initialize(QVariantMap param)
{
    if (param.contains("runMode"))
        d_ptr->runMode = param.value("iRunMode", 2).toInt();
    if (param.contains("retry"))
        d_ptr->retry = param.value("retry", 3).toInt();
    if (param.contains("sleepTime"))
        d_ptr->sleepTime = param.value("sleepTime", 1000).toUInt();
}

void HAbstractThread::stop()
{
    if (!d_ptr->running)
        return;
    clearAction();
    addAction(ACT_EXIT);
    wait(1000);
}

void HAbstractThread::addAction(HActionType action)
{
    if (!checkAction(action))
        return;
    d_ptr->enqueueAction(action);
}

void HAbstractThread::clearAction()
{
    d_ptr->clearAction();
}

void HAbstractThread::run()
{
    d_ptr->running = true;
    if (d_ptr->runMode == 0)
        debugMode();
    if (d_ptr->runMode == 1)
        offLineMode();
    if (d_ptr->runMode == 2)
        normalMode();
    d_ptr->running = false;
}

bool HAbstractThread::checkAction(HActionType action)
{
    return action < 0x00000100 || d_ptr->actionSupport.contains(action);
}

void HAbstractThread::readSettings()
{
    auto settings =  HAppContext::instance()->createSettings();
    settings->beginGroup("Thread");
    d_ptr->runMode = settings->value("iRunMode", 2).toInt();
    d_ptr->retry = settings->value("iRetry", 3).toInt();
    d_ptr->sleepTime = settings->value("iSleepTime", 1000).toUInt();
    settings->endGroup();
}

void HAbstractThread::writeSettings()
{
    auto settings = HAppContext::instance()->createSettings();
    settings->beginGroup("Thread");
    settings->setValue("iRunMode", d_ptr->runMode);
    settings->setValue("iRetry", d_ptr->retry);
    settings->setValue("iSleepTime", d_ptr->sleepTime);
    settings->endGroup();
}

void HAbstractThread::debugMode()
{
    HActionType action;
    HErrorType error = openProtocol();
    if (error != E_OK)
        emit protocolFailed(error);
    else
        emit protocolOpened();

    forever
    {
        action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        error = handleAction(action);
        if (error != E_OK)
            emit actionDealFailed(action, error);
        emit actionDealFinished(action);
    }
    closeProtocol();
}

void HAbstractThread::offLineMode()
{
    forever
    {
        auto action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        emit actionDealFinished(action);
    }
}

void HAbstractThread::normalMode()
{
    int i;
    HActionType action;
    HErrorType error = openProtocol();
    if (error != E_OK)
    {
        emit protocolFailed(error);
        return;
    }
    emit protocolOpened();

    forever
    {
        action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        for (i = 0; i < d_ptr->retry; i++)
        {
            error = handleAction(action);
            if (error == E_OK)
            {
                emit actionDealFinished(action);
                break;
            }
            msleep(d_ptr->sleepTime);
        }
        if (i >= d_ptr->retry)
        {
            emit actionDealFailed(action, error);
            break;
        }
    }
    closeProtocol();
}

HErrorType HAbstractThread::openProtocol()
{
    HErrorType error;
    QList<IProtocol *> list;
    for (auto p : d_ptr->protocols)
    {
        auto startegy = d_ptr->model->protocolStrategy(p->objectName());
        if (startegy == nullptr)
            return E_MODEL_NO_PROTOCOL_STRATEGY;
        p->setStrategy(startegy);
        error = p->open();
        if (error != E_OK)
        {
            for (auto l : list)
                l->close();
            return error;
        }
        list.append(p);
    }
    return E_OK;


//    HErrorType error;
//    foreach(d_ptr->protocols.keys())
//    {


//    }
//    for (auto p : d_ptr->protocols)
//    {
//        auto startegy = d_ptr->model->protocolStrategy(p->
//        p->setStrategy(d_ptr->model->)
//        error = p->open();
//    }

//    if (m_pItem->itemSize() != m_pProtocolList.size())
//        return E_DEVICE_MAPPED_ERROR;

//    int i,j;
//    ErrorType err;

//    err = E_OK;
//    for (i = 0; i < m_pItem->itemSize(); i++)
//    {
//        err = m_pProtocolList[i]->openProtocol(m_pItem->item(i));
//        if (err != E_OK)
//        {
//            m_nErrPortType = m_pItem->item(i)->portType();
//            m_nErrorModules = m_pProtocolList[i]->errorModule();
//            if (close)
//            {
//                for (j = 0; j < i; j++)
//                    m_pProtocolList[j]->closeProtocol();
//                return err;
//            }
//        }
//    }

//    return err;

}

void HAbstractThread::closeProtocol()
{
    for (auto p : d_ptr->protocols)
        p->close();
    emit protocolClosed();
}
