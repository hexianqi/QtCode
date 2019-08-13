#include "HAbstractMultiWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractMultiWidget::HAbstractMultiWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractMultiWidgetPrivate)
{
}

HAbstractMultiWidget::HAbstractMultiWidget(HAbstractMultiWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HAbstractMultiWidget::~HAbstractMultiWidget()
{
}

int HAbstractMultiWidget::currentIndex() const
{
    return d_ptr->currentIndex;
}

void HAbstractMultiWidget::addWidget(QWidget *widget, const QString &title)
{
    addWidget(widget, QIcon(), title);
}

void HAbstractMultiWidget::addWidget(QWidget *widget, const QIcon &icon, const QString &title)
{
    insertWidget(count(), widget, icon, title);
}

void HAbstractMultiWidget::insertWidget(int index, QWidget *widget, const QString &title)
{
    insertWidget(index, widget, QIcon(), title);
}

void HAbstractMultiWidget::insertWidget(int /*index*/, QWidget *widget, const QIcon &icon, const QString &title)
{
    if (!title.isNull())
        widget->setWindowTitle(title);
    if (!icon.isNull())
        widget->setWindowIcon(icon);
}

void HAbstractMultiWidget::removeWidget(QWidget *p)
{
    removeWidget(indexOf(p));
}

bool HAbstractMultiWidget::setCurrentIndex(int value)
{
    if (value == currentIndex() || value < 0 || value >= count())
        return false;
    d_ptr->currentIndex = value;
    emit currentIndexChanged(value);
    return true;
}

bool HAbstractMultiWidget::setCurrentWidget(QWidget *p)
{
    return setCurrentIndex(indexOf(p));
}

bool HAbstractMultiWidget::setWidgetIcon(int index, const QIcon &icon)
{
    auto w = widget(index);
    if (w == nullptr)
        return false;
    w->setWindowIcon(icon);
    return true;
}

bool HAbstractMultiWidget::setWidgetTitle(int index, const QString &title)
{
    auto w = widget(index);
    if (w == nullptr)
        return false;
    w->setWindowTitle(title);
    return true;
}

HE_CONTROL_END_NAMESPACE
