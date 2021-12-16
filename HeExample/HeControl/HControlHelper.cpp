#include "HControlHelper.h"
#include "HMoveEventFilter.h"
#include "HResizeEventFilter.h"
#include "HBackgroundEventFilter.h"
#include <QtCore/QTranslator>
#include <QtCore/QTime>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QAction>

HE_BEGIN_NAMESPACE

void HControlHelper::initTranslator()
{
    // 加载鼠标右键菜单翻译文件
    auto t1 = new QTranslator(QApplication::instance());
    t1->load(":/translator/qt_zh_CN.qm");
    QApplication::installTranslator(t1);

    // 加载富文本框鼠标右键菜单翻译文件
    auto t2 = new QTranslator(QApplication::instance());
    t2->load(":/translator/textEdit.qm");
    QApplication::installTranslator(t2);
}

QString HControlHelper::runTime(const QDateTime &start, const QDateTime &end)
{
    qint64 sec = start.secsTo(end);
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    while (sec > 0)
    {
        second++;
        if (second == 60)
        {
            minute++;
            second = 0;
        }
        if (minute == 60)
        {
            hour++;
            minute = 0;
        }
        if (hour == 24)
        {
            day++;
            hour = 0;
        }
        sec--;
    }
    return tr("%1天 %2时 %3分 %4秒").arg(day).arg(hour).arg(minute).arg(second);
}

QString HControlHelper::secsToTime(qlonglong value)
{
    int hh  = value / 3600;
    int mm  = (value % 3600) / 60;
    int ss  = (value % 60);
    return QString("%1:%2:%3").arg(hh, 2, 10, QChar('0')).arg(mm, 2, 10,  QChar('0')).arg(ss, 2, 10,  QChar('0'));
}

void HControlHelper::centerWidget(QWidget *widget)
{
    auto size = QApplication::primaryScreen()->availableSize();
    widget->move((size.width() - widget->width()) / 2, (size.height() - widget->height()) / 2);
    widget->setFixedSize(widget->width(), widget->height());
}

void HControlHelper::framelessWidget(QWidget *widget, bool moveEnable, bool resizeEnable)
{
    widget->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    if (moveEnable)
    {
        auto filter = new HMoveEventFilter(widget);
        filter->addWatched(widget);
    }
    if (resizeEnable)
    {
        auto filter = new HResizeEventFilter(widget);
        filter->addWatched(widget);
    }
    addClose(widget);
}

void HControlHelper::translucentWidget(QWidget *widget, const QStringList &files, bool moveEnable)
{
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setWindowFlags(Qt::FramelessWindowHint);

    if (moveEnable)
    {
        auto filter = new HMoveEventFilter(widget);
        filter->addWatched(widget);
    }
    {
        auto filter = new HBackgroundEventFilter(widget);
        filter->setBackgroundImage(files);
        filter->addWatched(widget);
    }
    addClose(widget);
}

void HControlHelper::addClose(QWidget *widget)
{
    auto close = new QAction(tr("关闭(&C)"));
    connect(close, &QAction::triggered, widget, &QWidget::close);
    widget->addAction(close);
    widget->setContextMenuPolicy(Qt::ActionsContextMenu);
}

HE_END_NAMESPACE
