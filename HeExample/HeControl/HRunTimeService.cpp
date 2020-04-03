#include "HRunTimeService_p.h"
#include "HControlHelper.h"
#include "HFileLog.h"
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

HE_CONTROL_BEGIN_NAMESPACE

HRunTimeService::HRunTimeService(QObject *parent) :
    QObject(parent),
    d_ptr(new HRunTimeServicePrivate)
{
    init();
}

HRunTimeService::~HRunTimeService()
{
    stop();
}

void HRunTimeService::start()
{
    initLog();
    d_ptr->timer->start();
}

void HRunTimeService::stop()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

void HRunTimeService::setInterval(int value)
{
    if (d_ptr->timer->interval() == value)
        return;
    d_ptr->timer->setInterval(value);
}

// 判断日志内容是否存在，
// 不存在则新建并且写入标题,
// 存在则自动读取最后一行的id号。
// 写入当前首次运行时间
// 日志内容格式：
// 编号    开始时间                结束时间                已运行时间
// 1      2016-01-01 12:33:33    2016-02-05 12:12:12     day: 0  hour: 0  minute: 0
void HRunTimeService::initLog()
{
    QStringList list;
    if (!d_ptr->fileLog->readContent(list))
        return;

    if (list.size() < 2)
    {
        d_ptr->lastId = 1;
        list.clear();
        list << tr("编号\t开始时间\t\t结束时间\t\t已运行时间");
    }
    else
        d_ptr->lastId = list.last().split("\t").at(0).toInt() + 1;

    auto current = QDateTime::currentDateTime();
    list << QString("%1\t%2\t%3\t%4")
            .arg(d_ptr->lastId)
            .arg(d_ptr->startTime.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(current.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(HControlHelper::runTime(d_ptr->startTime, current));
    d_ptr->fileLog->writeContent(list);
}

// 每次保存都是将之前的所有文本读取出来,然后替换最后一行即可
void HRunTimeService::saveLog()
{
    QStringList list;
    if (!d_ptr->fileLog->readContent(list))
        return;

    if (list.size() < 2)
    {
        initLog();
        return;
    }
    // 重新拼接最后一行
    auto texts = list.last().split("\t");
    auto current = QDateTime::currentDateTime();
    texts[2] = current.toString("yyyy-MM-dd HH:mm:ss");
    texts[3] = HControlHelper::runTime(d_ptr->startTime, current);
    list[list.size() - 1] = texts.join("\t");
    d_ptr->fileLog->writeContent(list);
}

void HRunTimeService::init()
{
    d_ptr->lastId = 0;
    d_ptr->startTime = QDateTime::currentDateTime();
    d_ptr->fileLog = new HFileLog(this);
    d_ptr->fileLog->setName("Run");
    d_ptr->fileLog->setDataFormat("hhhhMM");
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(60 * 10000);
    connect(d_ptr->timer, &QTimer::timeout, this, &HRunTimeService::saveLog);
    connect(qApp, &QApplication::aboutToQuit, this, &HRunTimeService::stop);
}

HE_CONTROL_END_NAMESPACE
