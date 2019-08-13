#include "HNavigationBar_p.h"
#include <QtGui/QtEvents>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QBoxLayout>
#include <QtDebug>

HE_CONTROL_BEGIN_NAMESPACE

HNavigationBar::HNavigationBar(QWidget *parent) :
    HAbstractMultiWidget(*new HNavigationBarPrivate, parent)
{
    init();
}

HNavigationBar::HNavigationBar(HNavigationBarPrivate &p, QWidget *parent) :
    HAbstractMultiWidget(p, parent)
{
    init();
}

HNavigationBar::~HNavigationBar()
{
}

int HNavigationBar::count() const
{
    Q_D(const HNavigationBar);
    return d->stack->count();
}

int HNavigationBar::indexOf(QWidget *p) const
{
    Q_D(const HNavigationBar);
    return d->stack->indexOf(p);
}

QWidget *HNavigationBar::widget(int index) const
{
    Q_D(const HNavigationBar);
    return d->stack->widget(index);
}

QWidget *HNavigationBar::currentWidget() const
{
    Q_D(const HNavigationBar);
    return d->stack->currentWidget();
}

bool HNavigationBar::topWidgetIsVisible() const
{
    Q_D(const HNavigationBar);
    return d->topButton->isVisible();
}

QPushButton *HNavigationBar::button(int index) const
{
    Q_D(const HNavigationBar);
    if (index < 0 || index >= d->buttons.count())
        return nullptr;
    return d->buttons.at(index);
}

void HNavigationBar::insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    Q_D(HNavigationBar);
    HAbstractMultiWidget::insertWidget(index, widget, icon, label);
    widget->installEventFilter(this);

    auto b = new QPushButton;
    b->setText(widget->windowTitle());
    b->setIcon(widget->windowIcon());
    b->updateGeometry();
    connect(b, &QPushButton::clicked, this, &HNavigationBar::handleButtonClicked);

    d->stack->insertWidget(index, widget);
    d->buttonLayout->insertWidget(index, b);
    d->buttons.insert(index, b);
    int h = d->buttonLayout->parentWidget()->sizeHint().height();
    d->buttonLayout->parentWidget()->setMaximumSize(16777215, h);
    if (count() == 1)
        setCurrentIndex(0);
}

void HNavigationBar::removeWidget(int index)
{
    Q_D(HNavigationBar);
    if (index < 0 || index >= count())
        return;

    auto w = widget(index);
    w->removeEventFilter(this);
    d->stack->removeWidget(w);
    delete d->buttons.at(index);
    d->buttons.removeAt(index);
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
}

bool HNavigationBar::setCurrentIndex(int value)
{
    Q_D(HNavigationBar);
    if (!HAbstractMultiWidget::setCurrentIndex(value))
        return false;

    auto b = button(value);
    d->topButton->setText(b->text());
    d->topButton->setIcon(b->icon());
    d->stack->setCurrentIndex(value);
    return true;
}

bool HNavigationBar::setWidgetIcon(int index, const QIcon &icon)
{
    Q_D(HNavigationBar);
    if (!HAbstractMultiWidget::setWidgetIcon(index, icon))
        return false;
    auto b = button(index);
    b->setIcon(icon);
    if (index == currentIndex())
        d->topButton->setIcon(icon);
    return true;
}

bool HNavigationBar::setWidgetTitle(int index, const QString &title)
{
    Q_D(HNavigationBar);
    if (!HAbstractMultiWidget::setWidgetTitle(index, title))
        return false;
    auto b = button(index);
    b->setText(title);
    if (index == currentIndex())
        d->topButton->setText(title);
    return true;
}

void HNavigationBar::setTopWidgetVisible(bool b)
{
    Q_D(HNavigationBar);
    d->topButton->setVisible(b);
}

void HNavigationBar::actionEvent(QActionEvent *e)
{
    Q_D(HNavigationBar);
    if (e->type() == QEvent::ActionAdded)
    {
        if (e->before() == nullptr)
        {
            addToolButton(0, e->action());
            return;
        }
        else
        {
            findToolButton(e->before(), [=](int index, QToolButton */*tb*/) { addToolButton(index, e->action()); });
            return;
        }
    }
    if (e->type() == QEvent::ActionRemoved)
    {
        findToolButton(e->before(), [=](int /*index*/, QToolButton *tb) { d->bottomLayout->removeWidget(tb); delete tb; });
        return;
    }
    QWidget::actionEvent(e);
}

bool HNavigationBar::eventFilter(QObject *object, QEvent *event)
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

void HNavigationBar::addToolButton(int index, QAction *action)
{
    Q_D(HNavigationBar);
    auto tb = new QToolButton;
    tb->setDefaultAction(action);
    tb->setAutoRaise(true);
    d->bottomLayout->insertWidget(index, tb);
}

void HNavigationBar::findToolButton(QAction *action, std::function<void (int, QToolButton *)> func)
{
    Q_D(HNavigationBar);
    for (int i = 0; i< d->bottomLayout->count(); i++)
    {
        auto item = d->bottomLayout->itemAt(i);
        if (item == nullptr)
            return;
        auto tb = qobject_cast<QToolButton *>(item->widget());
        if (tb != nullptr && action == tb->defaultAction())
        {
            func(i, tb);
            return;
        }
    }
}

void HNavigationBar::init()
{
    Q_D(HNavigationBar);
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

    auto vl = new QVBoxLayout(this);
    vl->setSpacing(0);
    vl->setMargin(2);
    vl->addWidget(d->topButton);
    vl->addWidget(splitter);
    vl->addWidget(frame);
    setWindowIcon(QIcon(":/image/ww/navigationbar.png"));
}

void HNavigationBar::handleButtonClicked()
{
    Q_D(HNavigationBar);
    auto b = qobject_cast<QPushButton *>(sender());
    setCurrentIndex(d->buttons.indexOf(b));
}

HE_CONTROL_END_NAMESPACE
