#include "HRunTimeService_p.h"
#include "HLogFile.h"
#include "HControlHelper.h"
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

HE_BEGIN_NAMESPACE

HRunTimeService::HRunTimeService(QObject *parent) :
    HAbstractService(*new HRunTimeServicePrivate, parent)
{
    init();
}


HRunTimeService::~HRunTimeService()
{
    stop();
}

ILogFile *HRunTimeService::file()
{
    Q_D(HRunTimeService);
    return d->file;
}

bool HRunTimeService::start()
{
    Q_D(HRunTimeService);
    if (!HAbstractService::start())
        return false;

    d->startTime = QDateTime::currentDateTime();
    d->timer->start();
    initLog();
    appendLog();
    saveLog();
    return true;
}

bool HRunTimeService::stop()
{
    Q_D(HRunTimeService);
    if (!HAbstractService::stop())
        return false;
    d->timer->stop();
    saveLog();
    return true;
}

void HRunTimeService::setInterval(int value)
{
    Q_D(HRunTimeService);
    if (d->timer->interval() == value)
        return;
    d->timer->setInterval(value);
}
// 判断日志内容是否存在，
// 不存在则新建并且写入标题,
// 存在则自动读取最后一行的id号。
// 日志内容格式：
// 编号      开始时间            结束时间         已运行时间
// 1	2022-05-26 09:17:53 2022-05-26 09:38:15 0 天 0 时 20 分 0秒
void HRunTimeService::initLog()
{
    Q_D(HRunTimeService);
    auto list = d->file->readLines();
    if (list.size() < 1)
    {
        d->lastId = 1;
        d->file->write(tr("编号\t开始时间\t\t结束时间\t\t已运行时间"));
    }
    else
        d->lastId = list.last().split("\t").at(0).toInt() + 1;
}

void HRunTimeService::appendLog()
{
    Q_D(HRunTimeService);
    auto current = QDateTime::currentDateTime();
    auto content = QString("%1").arg(d->lastId) + QString("\t%1\t%2\t%3").arg(d->startTime.toString("yyyy-MM-dd HH:mm:ss"), current.toString("yyyy-MM-dd HH:mm:ss"), HControlHelper::runTime(d->startTime, current));
    d->file->append(content);
    emit dataChanged(content, true);
}

void HRunTimeService::saveLog()
{
    Q_D(HRunTimeService);
    auto list = d->file->readLines();
    if (list.size() < 2)
    {
        initLog();
        appendLog();
        return;
    }
    // 重新拼接最后一行
    auto texts = list.last().split("\t");
    auto current = QDateTime::currentDateTime();
    texts[2] = current.toString("yyyy-MM-dd HH:mm:ss");
    texts[3] = HControlHelper::runTime(d->startTime, current);
    auto content = texts.join("\t");
    list[list.size() - 1] = content;
    d->file->write(list);
    emit dataChanged(content, false);
}

void HRunTimeService::init()
{
    Q_D(HRunTimeService);
    d->lastId = 0;
    d->startTime = QDateTime::currentDateTime();
    d->file = new HLogFile(this);
    d->file->setDataTimeFormat("yyyy");
    d->timer = new QTimer(this);
    d->timer->setInterval(60 * 1000);
    connect(d->timer, &QTimer::timeout, this, &HRunTimeService::saveLog);
    connect(QApplication::instance(), &QApplication::aboutToQuit, this, &HRunTimeService::stop);
}

HE_END_NAMESPACE
