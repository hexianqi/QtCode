#include "HTaskPanel_p.h"
#include "HTaskWidget.h"
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QBoxLayout>

HE_BEGIN_NAMESPACE

HTaskPanel::HTaskPanel(QWidget *parent) :
    HAbstractMultiPanel(*new HTaskPanelPrivate, parent)
{
    init();
}

HTaskPanel::HTaskPanel(HTaskPanelPrivate &p, QWidget *parent) :
    HAbstractMultiPanel(p, parent)
{
    init();
}

int HTaskPanel::count() const
{
    Q_D(const HTaskPanel);
    return d->tasks.count();
}

int HTaskPanel::indexOf(QWidget *p) const
{
    Q_D(const HTaskPanel);
    for (int i = 0; i < d->tasks.count(); i++)
    {
        if (d->tasks.at(i)->body() == p)
            return i;
    }
    return -1;
}

QWidget *HTaskPanel::widget(int index) const
{
    Q_D(const HTaskPanel);
    if (index < 0 || index >= count())
        return nullptr;
    return d->tasks.at(index)->body();
}

QWidget *HTaskPanel::currentWidget() const
{
    return widget(currentIndex());
}

bool HTaskPanel::isAnimated() const
{
    Q_D(const HTaskPanel);
    return d->animated;
}

QIcon HTaskPanel::toggleIcon() const
{
    Q_D(const HTaskPanel);
    return d->toggleIcon;
}

void HTaskPanel::insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    Q_D(HTaskPanel);
    HAbstractMultiPanel::insertWidget(index, widget, icon, label);

    auto task = new HTaskWidget(widget);
    task->setToggleIcon(d->toggleIcon);
    d->layout->insertWidget(index, task);
    d->tasks.insert(index, task);
    if (count() == 1)
        setCurrentIndex(0);
    task->show();
}

bool HTaskPanel::removeWidget(int index)
{
    Q_D(HTaskPanel);
    if (!HAbstractMultiPanel::removeWidget(index))
        return false;

    auto task = d->tasks.at(index);
    d->tasks.removeAt(index);
    if (count() <= index)
        setCurrentIndex(count() - 1);
    auto body = task->body();
    body->setParent(this);
    delete task;
    return true;
}

bool HTaskPanel::setCurrentIndex(int value)
{
    Q_D(HTaskPanel);
    if (value < 0 || value >= count() || value == currentIndex())
        return false;

    if (currentIndex() != -1)
        d->tasks.at(currentIndex())->setOpen(false);
    d_ptr->currentIndex = value;
    d->tasks.at(value)->setOpen(true);
    return true;
}

bool HTaskPanel::setWidgetIcon(int index, const QIcon &icon)
{
    Q_D(HTaskPanel);
    if (index < 0 || index >= count())
        return false;
    d->tasks.at(index)->setIcon(icon);
    return true;
}

bool HTaskPanel::setWidgetTitle(int index, const QString &title)
{
    Q_D(HTaskPanel);
    if (index < 0 || index >= count())
        return false;
    d->tasks.at(index)->setName(title);
    return true;
}

void HTaskPanel::setToggleIcon(const QIcon &value)
{
    Q_D(HTaskPanel);
    d->toggleIcon = value;
    for (auto w : d->tasks)
        w->setToggleIcon(value);
}

void HTaskPanel::setAnimated(bool b)
{
    Q_D(HTaskPanel);
    d->animated = b;
}

void HTaskPanel::init()
{
    Q_D(HTaskPanel);
    auto sa = new QScrollArea(this);
    d->panel = new QWidget(sa->viewport());
    d->panel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
    d->layout = new QVBoxLayout(d->panel);
    d->layout->addStretch();
    sa->setWidget(d->panel);
    sa->setWidgetResizable(true);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(sa);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
}

HE_END_NAMESPACE
