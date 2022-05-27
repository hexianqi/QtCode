#include "HLogRedirectService_p.h"
#include <QtCore/QMutexLocker>

HE_BEGIN_NAMESPACE

// 日志重定向
void log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁，防止多线程中qdebug太频繁导致崩溃
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    QString content;
    auto service = HLogRedirectService::instance();

    if (!service->isFilter(type))
        return;

    switch (type)
    {
    case QtDebugMsg:
        content = QString("Debug:\t%1").arg(msg);
        break;
    case QtInfoMsg:
        content = QString("Info:\t%1").arg(msg);
        break;
    case QtWarningMsg:
        content = QString("Warning:\t%1").arg(msg);
        break;
    case QtCriticalMsg:
        content = QString("Critical:\t%1").arg(msg);
        break;
    case QtFatalMsg:
        content = QString("Fatal:\t%1").arg(msg);
        break;
    }
    if (content.isEmpty())
        return;
    if (service->isUseContext())
        content += QString("\n%1:%2, %3").arg(context.file).arg(context.line).arg(context.function);
    service->save(content);
}

HLogRedirectService::HLogRedirectService(QObject *parent) :
    HAbstractService(*new HLogRedirectServicePrivate, parent)
{
}

HLogRedirectService::~HLogRedirectService()
{
    stop();
}

bool HLogRedirectService::start()
{
    if (!HAbstractService::start())
        return false;
    qInstallMessageHandler(log);
    return true;
}

bool HLogRedirectService::stop()
{
    if (!HAbstractService::stop())
        return false;
    qInstallMessageHandler(nullptr);
    return true;
}

bool HLogRedirectService::isFilter(const QtMsgType &type)
{
    Q_D(HLogRedirectService);
    switch (type)
    {
    case QtDebugMsg:
        return d->msgType & MsgType_Debug;
    case QtInfoMsg:
        return d->msgType & MsgType_Info;
    case QtWarningMsg:
        return d->msgType & MsgType_Warning;
    case QtCriticalMsg:
        return d->msgType & MsgType_Critical;
    case QtFatalMsg:
        return d->msgType & MsgType_Fatal;
    }
    return false;
}

bool HLogRedirectService::isUseContext()
{
    Q_D(HLogRedirectService);
    return d->useContext;
}

void HLogRedirectService::setMsgType(const MsgType &value)
{
    Q_D(HLogRedirectService);
    d->msgType = value;
}

void HLogRedirectService::setUseContext(bool b)
{
    Q_D(HLogRedirectService);
    d->useContext = b;
}

void HLogRedirectService::save(const QString &content)
{
    emit output(content);
}
HE_END_NAMESPACE
