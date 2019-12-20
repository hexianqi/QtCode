#include "HBackgroundEventFilter_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

HE_CONTROL_BEGIN_NAMESPACE

HBackgroundEventFilterPrivate::HBackgroundEventFilterPrivate()
{
    imageFiles << QString(":/image/background1.png") << QString(":/image/background2.png") << QString(":/image/background3.png") << QString(":/image/background4.png") << QString(":/image/background5.png");
}

HBackgroundEventFilter::HBackgroundEventFilter(QObject *parent) :
    HAbstractMouseEventFilter(*new HBackgroundEventFilterPrivate, parent)
{
}

HBackgroundEventFilter::HBackgroundEventFilter(HBackgroundEventFilterPrivate &p, QObject *parent) :
    HAbstractMouseEventFilter(p, parent)
{
}

HBackgroundEventFilter::~HBackgroundEventFilter()
{
}

void HBackgroundEventFilter::initialize(QVariantMap param)
{
    if (param.contains("backgroundImage"))
        setBackgroundImage(param.value("backgroundImage").toStringList());
    if (param.contains("backgroundRepeated"))
        setBackgroundRepeated(param.value("backgroundRepeated").toBool());
    if (param.contains("backgroundImage"))
        setBackgroundStretched(param.value("backgroundStretched").toBool());
}

QString HBackgroundEventFilter::typeName()
{
    return "HBackgroundEventFilter";
}

bool HBackgroundEventFilter::addWatched(QObject *p)
{
    if (!HAbstractMouseEventFilter::addWatched(p))
        return false;

    auto widget = qobject_cast<QWidget *>(p);
    // 添加背景窗体并把现有的控件移动到窗体内
    if (!widget->findChild<QWidget *>("background"))
    {
        auto background = new QWidget(widget);
        background->setObjectName("background");
        background->setLayout(widget->layout());
        auto l = new QHBoxLayout(widget);
        l->addWidget(background);
    }
    updateStyleSheet(widget);
    return true;
}

void HBackgroundEventFilter::setBackgroundImage(QStringList value)
{
    Q_D(HBackgroundEventFilter);
    if (d->imageFiles == value || value.isEmpty())
        return;
    d->imageFiles = value;
    d->index = 0;
    updateStyleSheet();
}

void HBackgroundEventFilter::setBackgroundRepeated(bool b)
{
    Q_D(HBackgroundEventFilter);
    if (d->repeated == b)
        return;
    d->repeated = b;
    updateStyleSheet();
}

void HBackgroundEventFilter::setBackgroundStretched(bool b)
{
    Q_D(HBackgroundEventFilter);
    if (d->stretched == b)
        return;
    d->stretched = b;
    updateStyleSheet();
}

bool HBackgroundEventFilter::mousePressEvent(QWidget *widget, QMouseEvent *event)
{
    Q_D(HBackgroundEventFilter);
    if (event->button() != Qt::LeftButton)
        return false;
    if (!widget->rect().contains(event->pos()))
        return false;
    d->pressed = true;
    d->index++;
    if (d->index >= d->imageFiles.count())
        d->index = 0;
    updateStyleSheet(widget);
    return false;
}

bool HBackgroundEventFilter::mouseReleaseEvent(QWidget *, QMouseEvent *event)
{
    Q_D(HBackgroundEventFilter);
    if (event->button() != Qt::LeftButton || !d->pressed)
        return false;
    d->pressed = false;
    return false;
}

bool HBackgroundEventFilter::mouseMoveEvent(QWidget *, QMouseEvent *)
{
    return false;
}

void HBackgroundEventFilter::updateStyleSheet()
{
    Q_D(HBackgroundEventFilter);
    for (auto obj : d->watcheds)
        updateStyleSheet(qobject_cast<QWidget *>(obj));
}

void HBackgroundEventFilter::updateStyleSheet(QWidget *widget)
{
    Q_D(HBackgroundEventFilter);
    auto background = widget->findChild<QWidget *>("background");
    auto image = d->imageFiles.at(d->index);
    if (d->stretched)
        background->setStyleSheet(QString("QWidget#background { border-image:url(%1); }").arg(image));
    else if (d->repeated)
        background->setStyleSheet(QString("QWidget#background { background-image:url(%1); background-repeat:repeat-xy; background-position:top left; }").arg(image));
    else
        background->setStyleSheet(QString("QWidget#background { background-image:url(%1); background-repeat:no-repeat; background-position:center; }").arg(image));
}

HE_CONTROL_END_NAMESPACE
