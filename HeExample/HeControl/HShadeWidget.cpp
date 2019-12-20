#include "HShadeWidget_p.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

HE_CONTROL_BEGIN_NAMESPACE

HShadeWidget::HShadeWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HShadeWidgetPrivate)
{
    init();
}

HShadeWidget::HShadeWidget(HShadeWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HShadeWidget::~HShadeWidget()
{
}

void HShadeWidget::addWatched(QWidget *p)
{
    p->installEventFilter(this);
}

void HShadeWidget::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    setStyleSheet(QString("QWidget#%1 { background-color:%2 }").arg(objectName()).arg(value.name()));
}

void HShadeWidget::setOpacity(double value)
{
    if (qFuzzyCompare(d_ptr->opacity, value))
        return;
    d_ptr->opacity = value;
    setWindowOpacity(value);
}

bool HShadeWidget::eventFilter(QObject *watched, QEvent *event)
{
    auto w = static_cast<QWidget *>(watched);
    if (w != nullptr)
    {
        if (w == d_ptr->mainWidget)
        {
            if (event->type() == QEvent::Resize)
                resize(d_ptr->mainWidget->size());
            if (event->type() == QEvent::Move)
                setGeometry(d_ptr->mainWidget->geometry());
        }
        else
        {
            if (event->type() == QEvent::Show)
                show();
            if (event->type() == QEvent::Hide)
                hide();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void HShadeWidget::showEvent(QShowEvent *e)
{
    setGeometry(d_ptr->mainWidget->geometry());
    QWidget::showEvent(e);
}

void HShadeWidget::init()
{
    d_ptr->mainWidget = parentWidget() == nullptr ? qApp->desktop() : parentWidget();
    setObjectName("shade");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setBackground(Qt::black);
    setOpacity(0.5);
    addWatched(d_ptr->mainWidget);
}

HE_CONTROL_END_NAMESPACE
