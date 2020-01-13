#include "HLogService_p.h"
#include "HKeepFileLog.h"
#include "HNetworkLog.h"
#include <QtCore/QMutexLocker>
#include <mutex>

HE_CONTROL_BEGIN_NAMESPACE

QScopedPointer<HLogService> HLogService::__instance;
static std::once_flag __oc; // 用于call_once的局部静态变量

// 日志重定向
void log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁，防止多线程中qdebug太频繁导致崩溃
    QMutex mutex;
    QMutexLocker locker(&mutex);
    QString head;

    switch (type)
    {
    case QtDebugMsg:
        head = "Debug:\t";
        break;
    case QtInfoMsg:
        head = "Info:\t";
        break;
    case QtWarningMsg:
        head = "Warning:\t";
        break;
    case QtCriticalMsg:
        head = "Critical:\t";
        break;
    case QtFatalMsg:
        head = "Fatal:\t";
        break;
    }
    auto text = head + msg + QString(" (%1:%2, %3)\n").arg(context.file).arg(context.line).arg(context.function);
    HLogService::instance()->save(text);
}

HLogService *HLogService::instance()
{
    std::call_once(__oc, [&]{ __instance.reset(new HLogService); });
    return __instance.data();
}

HLogService::HLogService(QObject *parent) :
    QObject(parent),
    d_ptr(new HLogServicePrivate)
{
    init();
}

HLogService::~HLogService()
{
    stop();
}

void HLogService::start()
{
    qInstallMessageHandler(log);
}

void HLogService::stop()
{
    qInstallMessageHandler(nullptr);
}

// 如果重定向输出到网络则通过网络发出去,否则输出到日志文件
void HLogService::save(const QString &value)
{
    if (d_ptr->toNet)
        emit send(value);
    else
        d_ptr->fileLog->appendContent(QStringList() << value);
}

void HLogService::setToNet(bool b)
{
    if (d_ptr->toNet == b)
        return;
    d_ptr->toNet = b;
}

void HLogService::init()
{
    d_ptr->fileLog = new HKeepFileLog(this);
    d_ptr->fileLog->setName("Log");
    // 必须用信号槽形式,不然提示 QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread
    // 估计日志钩子可能单独开了线程
    connect(this, SIGNAL(send(QString)), HNetworkLog::instance(), SLOT(send(QString)));
}

HE_CONTROL_END_NAMESPACE
