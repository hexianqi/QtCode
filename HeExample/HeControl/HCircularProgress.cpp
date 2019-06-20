#include "HCircularProgress_p.h"
#include "HWaitFactory.h"
#include "IWait.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtWidgets/QActionGroup>

HE_CONTROL_BEGIN_NAMESPACE

HCircularProgress::HCircularProgress(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HCircularProgressPrivate)
{
    init();
}

HCircularProgress::HCircularProgress(HCircularProgressPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HCircularProgress::~HCircularProgress()
{
}

QSize HCircularProgress::sizeHint() const
{
    return QSize(100, 100);
}

void HCircularProgress::setReverse(bool b)
{
    if (d_ptr->reverse == b)
        return;
    d_ptr->reverse = b;
    update();
}

void HCircularProgress::step(int value)
{
    if (d_ptr->step == value)
        return;
    d_ptr->step = value;
    update();
}

void HCircularProgress::setDuration(int value)
{
    if (d_ptr->timer->interval() == value)
        return;
    d_ptr->timer->setInterval(value);
}

void HCircularProgress::setWaitStrategy(IWait *p)
{
    if (d_ptr->wait != nullptr)
        disconnect(d_ptr->wait, SIGNAL(dataChanged()), this, SLOT(update()));
    d_ptr->wait = p;
    connect(d_ptr->wait, SIGNAL(dataChanged()), this, SLOT(update()));
}

bool HCircularProgress::isReverse() const
{
    return d_ptr->reverse;
}

int HCircularProgress::step() const
{
    return d_ptr->step;
}

int HCircularProgress::duration() const
{
    return d_ptr->timer->interval();
}

void HCircularProgress::paintEvent(QPaintEvent *)
{
    if (d_ptr->wait == nullptr)
        return;

    QVariantMap param;
    param.insert("width", width());
    param.insert("height", height());
    param.insert("palette", palette());
    param.insert("reverse", d_ptr->reverse);
    param.insert("value", d_ptr->value);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    d_ptr->wait->draw(&painter, param);
}

void HCircularProgress::changeValue()
{
    d_ptr->value += d_ptr->reverse ? -d_ptr->step : d_ptr->step;
    d_ptr->value %= 360;
    update();
}

void HCircularProgress::changeWait(QAction *p)
{
    if (p == nullptr)
        return;
    auto k = p->data().toString();
    if (!d_ptr->waitCache.contains(k))
        d_ptr->waitCache.insert(k, d_ptr->factory->create(k));
    setWaitStrategy(d_ptr->waitCache.value(k));
}

void HCircularProgress::init()
{
    d_ptr->factory = new HWaitFactory(this);
    auto group = new QActionGroup(this);
    for (auto k : d_ptr->factory->keys())
    {
        auto action = group->addAction(d_ptr->factory->alias(k));
        action->setCheckable(true);
        action->setData(k);
    }
    addActions(group->actions());
    connect(group, &QActionGroup::triggered, this, &HCircularProgress::changeWait);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    group->actions().first()->setChecked(true);
    changeWait(group->actions().first());
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(150);
    connect(d_ptr->timer, &QTimer::timeout, this, &HCircularProgress::changeValue);
    d_ptr->timer->start();
}

HE_CONTROL_END_NAMESPACE
