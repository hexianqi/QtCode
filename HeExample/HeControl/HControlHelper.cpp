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
    t1->load(":/Resources/translator/qt_zh_CN.qm");
    QApplication::installTranslator(t1);

    // 加载富文本框鼠标右键菜单翻译文件
    auto t2 = new QTranslator(QApplication::instance());
    t2->load(":/Resources/translator/textEdit.qm");
    QApplication::installTranslator(t2);
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
