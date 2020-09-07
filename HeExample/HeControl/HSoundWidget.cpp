#include "HSoundWidget_p.h"
#include "HDrawHelper.h"
#include "HSoundSlider.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QMenu>
#include <QtWidgets/QWidgetAction>
#include <QtWidgets/QBoxLayout>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HSoundWidget::HSoundWidget(bool shiny, bool special, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSoundWidgetPrivate)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    d_ptr->label = new QLabel(this);
    d_ptr->label->setPixmap(HDrawHelper::loadSvgToPixmap(":/image/svg/volume-medium.svg", QSize(16, 16)));
    d_ptr->label->installEventFilter(this);

    QVBoxLayout *subLayout;
    if (special)
    {
        shiny = false;
        d_ptr->frame = new QFrame(this);
        subLayout = new QVBoxLayout(d_ptr->frame);
        subLayout->setContentsMargins(4, 4, 4, 4);
        auto action = new QWidgetAction(d_ptr->frame);
        action->setDefaultWidget(d_ptr->frame);
        d_ptr->menu = new QMenu(this);
        d_ptr->menu->addAction(action);
        mainLayout->addWidget(d_ptr->label);
    }
    else
        mainLayout->addWidget(d_ptr->label, 0, shiny ? Qt::AlignBottom : Qt::AlignCenter);

    if (shiny)
    {
        d_ptr->slider = new HSoundSlider(this);
    }
    else
    {
        d_ptr->slider = new QSlider;
        d_ptr->slider->setAttribute( Qt::WA_MacSmallSize);
        d_ptr->slider->setOrientation(special ? Qt::Vertical : Qt::Horizontal);

    }
    d_ptr->slider->setMaximum(d_ptr->volumeMax);
    d_ptr->slider->setFocusPolicy(Qt::NoFocus);
    if (special)
        subLayout->addWidget(d_ptr->slider);
    else
        mainLayout->addWidget(d_ptr->slider, 0, shiny ? Qt::AlignBottom : Qt::AlignCenter);
    d_ptr->slider->setTracking(true);
    connect(d_ptr->slider, &QAbstractSlider::valueChanged, this, &HSoundWidget::handleValueChanged);
}

HSoundWidget::~HSoundWidget()
{
}

void HSoundWidget::setMuted(bool b)
{
    if (d_ptr->muted == b)
        return;
    d_ptr->muted = b;
    auto slider = qobject_cast<HSoundSlider *>(d_ptr->slider);
    if (slider)
        slider->setMuted(b);
    refreshLabels();
    emit mutedChanged(b);
}

void HSoundWidget::setVolume(int value)
{
    d_ptr->slider->setValue(value);
}

bool HSoundWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == d_ptr->label && event->type() == QEvent::MouseButtonPress)
    {
        auto e = static_cast<QMouseEvent *>(event);
        if (e->button() == Qt::LeftButton)
        {
            if (d_ptr->slider->orientation() == Qt::Vertical)
                showVolumeMenu(e->pos());
            else
                setMuted(!d_ptr->muted);
            event->accept();
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}

void HSoundWidget::refreshLabels()
{
    QString path;
    QString tip;
    if (d_ptr->muted)
    {
        path = ":/image/svg/volume-muted.svg";
        tip = tr("取消静音");
    }
    else
    {
        auto volume = d_ptr->slider->value();
        if( volume < d_ptr->volumeMax / 3)
            path = ":/image/svg/volume-low.svg";
        else if ( volume > d_ptr->volumeMax * 2 / 3)
            path = ":/image/svg/volume-high.svg";
        else
            path = ":/image/svg/volume-medium.svg";
        tip = tr("静音");
    }

    d_ptr->label->setPixmap(HDrawHelper::loadSvgToPixmap(path, QSize(16, 16)));
    d_ptr->label->setToolTip(tip);
}

void HSoundWidget::showVolumeMenu(QPoint pos)
{
    d_ptr->menu->setFixedHeight(d_ptr->menu->sizeHint().height());
    d_ptr->menu->exec(QCursor::pos() - pos - QPoint(0, d_ptr->menu->height() / 2) + QPoint(width(), height() / 2));
}

void HSoundWidget::handleValueChanged(int value)
{
    setMuted(false);
    refreshLabels();
    emit volumeChanged(value);
}

HE_CONTROL_END_NAMESPACE
