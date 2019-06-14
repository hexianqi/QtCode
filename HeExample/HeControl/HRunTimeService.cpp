#include "HRunTimeService_p.h"
#include "HControlHelper.h"
#include <QtCore/QTimer>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>
#include <mutex>

HE_CONTROL_BEGIN_NAMESPACE

QScopedPointer<HRunTimeService> HRunTimeService::__instance;
static std::once_flag __oc; // 用于call_once的局部静态变量

HRunTimeServicePrivate::HRunTimeServicePrivate()
{
    path = qApp->applicationDirPath();
    auto list = qApp->applicationFilePath().split("/");
    fileName = list.at(list.count() - 1).split(".").at(0);
    interval = 1 * 60 * 1000;
    lastId = 0;
    startTime = QDateTime::currentDateTime();
}

HRunTimeService *HRunTimeService::instance(QObject *parent)
{
    std::call_once(__oc, [&]{ __instance.reset(new HRunTimeService(parent)); });
    return __instance.data();
}

HRunTimeService::HRunTimeService(QObject *parent) :
    QObject(parent),
    d_ptr(new HRunTimeServicePrivate)
{
    init();
}

HRunTimeService::HRunTimeService(HRunTimeServicePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HRunTimeService::~HRunTimeService()
{
    stop();
}

void HRunTimeService::start()
{
    d_ptr->timer->start(d_ptr->interval);
    initLog();
    appendLog();
    saveLog();
}

void HRunTimeService::stop()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

void HRunTimeService::setPath(QString value)
{
    if (d_ptr->path != value)
        d_ptr->path = value;
}

void HRunTimeService::setFileName(QString value)
{
    if (d_ptr->fileName != value)
        d_ptr->fileName = value;
}

void HRunTimeService::setInterval(int value)
{
    if (d_ptr->interval != value)
        d_ptr->interval = value;
}

// 判断当前年份月份的记事本文件是否存在,不存在则新建并且写入标题
// 存在则自动读取最后一行的id号  记事本文件格式内容
// 编号    开始时间                结束时间                已运行时间
// 1      2016-01-01 12:33:33    2016-02-05 12:12:12     day: 0  hour: 0  minute: 0
void HRunTimeService::initLog()
{
    QFile file(logFile());
    if (file.size() == 0)
    {
        if (!file.open(QFile::WriteOnly | QFile::Text))
            return;
        auto text = tr("编号\t开始时间\t\t结束时间\t\t已运行时间");
        QTextStream stream(&file);
        stream << text << endl;
        file.close();
        d_ptr->lastId = 1;
        return;
    }

    if (!file.open(QFile::ReadOnly))
        return;

    QString text;
    while (!file.atEnd())
        text = file.readLine();
    file.close();
    d_ptr->lastId = text.split("\t").at(0).toInt() + 1;
}

// 写入当前首次运行时间
void HRunTimeService::appendLog()
{
    QFile file(logFile());
    if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text))
        return;

    auto current = QDateTime::currentDateTime();
    auto text = tr("%1\t%2\t%3\t%4")
            .arg(d_ptr->lastId)
            .arg(d_ptr->startTime.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(current.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(HControlHelper::runTime(d_ptr->startTime, current));
    QTextStream stream(&file);
    stream << text << endl;
    file.close();
}

// 每次保存都是将之前的所有文本读取出来,然后替换最后一行即可
void HRunTimeService::saveLog()
{
    QFile file(logFile());

    // 如果日志文件不存在,则初始化一个日志文件
    if (file.size() == 0)
    {
        initLog();
        appendLog();
        return;
    }

    if (file.open(QFile::ReadWrite))
    {
        QStringList content;
        // 一行行读取到链表
        while (!file.atEnd())
            content << file.readLine();
        // 重新清空文件
        file.resize(0);
        // 如果行数小于2则返回
        if (content.count() < 2)
        {
            file.close();
            return;
        }

        // 重新拼接最后一行
        auto text = content.last();
        auto current = QDateTime::currentDateTime();
        auto list = text.split("\t");
        list[2] = current.toString("yyyy-MM-dd HH:mm:ss");
        list[3] = HControlHelper::runTime(d_ptr->startTime, current);
        content[content.count() - 1] = list.join("\t");

        QTextStream stream(&file);
        stream << content.join("") << endl;
        file.close();
    }
}

void HRunTimeService::init()
{
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, &HRunTimeService::saveLog);
}

QString HRunTimeService::logFile()
{
    return QString("%1/%2_%3.txt").arg(d_ptr->path).arg(d_ptr->fileName).arg(QDate::currentDate().toString("hhhhMM"));
}

HE_CONTROL_END_NAMESPACE
