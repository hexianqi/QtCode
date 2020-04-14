#include "HNavigationPanel_p.h"
#include <QtGui/QtEvents>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QBoxLayout>
#include <QtDebug>

HE_CONTROL_BEGIN_NAMESPACE

HNavigationPanel::HNavigationPanel(QWidget *parent) :
    HAbstractMultiPanel(*new HNavigationPanelPrivate, parent)
{
    init();
}

HNavigationPanel::HNavigationPanel(HNavigationPanelPrivate &p, QWidget *parent) :
    HAbstractMultiPanel(p, parent)
{
    init();
}

int HNavigationPanel::count() const
{
    Q_D(const HNavigationPanel);
    return d->stack->count();
}

int HNavigationPanel::indexOf(QWidget *p) const
{
    Q_D(const HNavigationPanel);
    return d->stack->indexOf(p);
}

QWidget *HNavigationPanel::widget(int index) const
{
    Q_D(const HNavigationPanel);
    return d->stack->widget(index);
}

QWidget *HNavigationPanel::currentWidget() const
{
    Q_D(const HNavigationPanel);
    return d->stack->currentWidget();
}

bool HNavigationPanel::topWidgetIsVisible() const
{
    Q_D(const HNavigationPanel);
    return d->topButton->isVisible();
}

QPushButton *HNavigationPanel::button(int index) const
{
    Q_D(const HNavigationPanel);
    if (index < 0 || index >= d->buttons.count())
        return nullptr;
    return d->buttons.at(index);
}

void HNavigationPanel::insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    Q_D(HNavigationPanel);
    HAbstractMultiPanel::insertWidget(index, widget, icon, label);

    auto b = new QPushButton(widget->windowIcon(), widget->windowTitle());
    b->updateGeometry();
    connect(b, &QPushButton::clicked, this, &HNavigationPanel::handleButtonClicked);

    d->stack->insertWidget(index, widget);
    d->buttons.insert(index, b);
    d->buttonLayout->insertWidget(index, b);
    d->buttonLayout->parentWidget()->setMaximumSize(16777215, d->buttonLayout->parentWidget()->sizeHint().height());
    if (count() == 1)
        setCurrentIndex(0);
}

bool HNavigationPanel::removeWidget(int index)
{
    Q_D(HNavigationPanel);
    if (!HAbstractMultiPanel::removeWidget(index))
        return false;

    auto w = widget(index);
    d->stack->removeWidget(w);
    delete w;
    delete d->buttons.takeAt(index);

    d->currentIndex = d->stack->currentIndex();
    if (d->currentIndex > -1)
    {
        auto b = button(d->currentIndex);
        d->topButton->setText(b->text());
        d->topButton->setIcon(b->icon());
    }
    else
    {
        d->topButton->setText(QString());
        d->topButton->setIcon(QIcon());
    }
    return true;
}

bool HNavigationPanel::setCurrentIndex(int value)
{
    Q_D(HNavigationPanel);
    if (!HAbstractMultiPanel::setCurrentIndex(value))
        return false;

    auto b = button(value);
    d->topButton->setText(b->text());
    d->topButton->setIcon(b->icon());
    d->stack->setCurrentIndex(value);
    return true;
}

bool HNavigationPanel::setWidgetIcon(int index, const QIcon &icon)
{
    Q_D(HNavigationPanel);
    if (!HAbstractMultiPanel::setWidgetIcon(index, icon))
        return false;
    button(index)->setIcon(icon);
    if (index == currentIndex())
        d->topButton->setIcon(icon);
    return true;
}

bool HNavigationPanel::setWidgetTitle(int index, const QString &title)
{
    Q_D(HNavigationPanel);
    if (!HAbstractMultiPanel::setWidgetTitle(index, title))
        return false;
    button(index)->setText(title);
    if (index == currentIndex())
        d->topButton->setText(title);
    return true;
}

void HNavigationPanel::setTopWidgetVisible(bool b)
{
    Q_D(HNavigationPanel);
    d->topButton->setVisible(b);
}

void HNavigationPanel::actionEvent(QActionEvent *e)
{
    Q_D(HNavigationPanel);
    if (e->type() == QEvent::ActionAdded)
    {
        if (e->before() == nullptr)
            addToolButton(0, e->action());
        else
            findToolButton(e->before(), [=](int index, QToolButton */*button*/) { addToolButton(index, e->action()); });
    }
    if (e->type() == QEvent::ActionRemoved)
    {
        findToolButton(e->before(), [=](int /*index*/, QToolButton *button) { d->bottomLayout->removeWidget(button); delete button; });
        return;
    }
    QWidget::actionEvent(e);
}

void HNavigationPanel::addToolButton(int index, QAction *action)
{
    Q_D(HNavigationPanel);
    auto tb = new QToolButton;
    tb->setDefaultAction(action);
    tb->setAutoRaise(true);
    d->bottomLayout->insertWidget(index, tb);
}

void HNavigationPanel::findToolButton(QAction *action, const std::function<void (int, QToolButton *)> &func)
{
    Q_D(HNavigationPanel);
    for (int i = 0; i< d->bottomLayout->count(); i++)
    {
        auto button = qobject_cast<QToolButton *>(d->bottomLayout->itemAt(i)->widget());
        if (button != nullptr && action == button->defaultAction())
        {
            func(i, button);
            return;
        }
    }
}

void HNavigationPanel::init()
{
    Q_D(HNavigationPanel);
    d->topButton = new QPushButton;
    d->topButton->setFlat(true);
    d->stack = new QStackedWidget;

    auto widget = new QWidget;
    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    d->buttonLayout = new QVBoxLayout(widget);
    d->buttonLayout->setSpacing(0);
    d->buttonLayout->setMargin(0);
    auto splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(d->stack);
    splitter->addWidget(widget);

    auto frame = new QFrame;
    frame->setFrameShape(QFrame::NoFrame);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    d->bottomLayout = new QHBoxLayout(frame);
    d->bottomLayout->setSpacing(2);
    d->bottomLayout->setMargin(1);
    d->bottomLayout->addStretch(1);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(2);
    layout->addWidget(d->topButton);
    layout->addWidget(splitter);
    layout->addWidget(frame);
    setWindowIcon(QIcon(":/image/ww/navigationbar.png"));
}

void HNavigationPanel::handleButtonClicked()
{
    Q_D(HNavigationPanel);
    auto b = qobject_cast<QPushButton *>(sender());
    setCurrentIndex(d->buttons.indexOf(b));
}

HE_CONTROL_END_NAMESPACE
