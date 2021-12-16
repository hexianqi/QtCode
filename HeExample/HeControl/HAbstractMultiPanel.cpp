#include "HAbstractMultiPanel_p.h"
#include <QtCore/QEvent>

HE_BEGIN_NAMESPACE

HAbstractMultiPanel::HAbstractMultiPanel(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractMultiPanelPrivate)
{
}

HAbstractMultiPanel::HAbstractMultiPanel(HAbstractMultiPanelPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HAbstractMultiPanel::~HAbstractMultiPanel() = default;

int HAbstractMultiPanel::currentIndex() const
{
    return d_ptr->currentIndex;
}

void HAbstractMultiPanel::addWidget(QWidget *widget, const QString &title)
{
    insertWidget(count(), widget, title);
}

void HAbstractMultiPanel::addWidget(QWidget *widget, const QIcon &icon, const QString &title)
{
    insertWidget(count(), widget, icon, title);
}

void HAbstractMultiPanel::insertWidget(int index, QWidget *widget, const QString &title)
{
    insertWidget(index, widget, QIcon(), title);
}

void HAbstractMultiPanel::insertWidget(int /*index*/, QWidget *widget, const QIcon &icon, const QString &title)
{
    if (!title.isNull())
        widget->setWindowTitle(title);
    if (!icon.isNull())
        widget->setWindowIcon(icon);
    widget->installEventFilter(this);
}

bool HAbstractMultiPanel::removeWidget(int index)
{
    if (index < 0 || index >= count())
        return false;
    widget(index)->removeEventFilter(this);
    return true;
}

bool HAbstractMultiPanel::removeWidget(QWidget *p)
{
    return removeWidget(indexOf(p));
}

bool HAbstractMultiPanel::setCurrentIndex(int value)
{
    if (value == currentIndex() || value < 0 || value >= count())
        return false;
    d_ptr->currentIndex = value;
    emit currentIndexChanged(value);
    return true;
}

bool HAbstractMultiPanel::setCurrentWidget(QWidget *p)
{
    return setCurrentIndex(indexOf(p));
}

bool HAbstractMultiPanel::setWidgetIcon(int index, const QIcon &icon)
{
    auto w = widget(index);
    if (w == nullptr)
        return false;
    w->setWindowIcon(icon);
    return true;
}

bool HAbstractMultiPanel::setWidgetTitle(int index, const QString &title)
{
    auto w = widget(index);
    if (w == nullptr)
        return false;
    w->setWindowTitle(title);
    return true;
}

bool HAbstractMultiPanel::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::WindowTitleChange || event->type() == QEvent::WindowIconChange)
    {
        auto w = qobject_cast<QWidget *>(object);
        auto i = indexOf(w);
        if (event->type() == QEvent::WindowTitleChange)
            setWidgetTitle(i, w->windowTitle());
        if (event->type() == QEvent::WindowIconChange)
            setWidgetIcon(i, w->windowIcon());
    }
    return QWidget::eventFilter(object, event);
}

HE_END_NAMESPACE
