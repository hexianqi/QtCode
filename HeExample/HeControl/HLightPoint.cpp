#include "HLightPoint_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HLightPoint::HLightPoint(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLightPointPrivate)
{
    init();
}

HLightPoint::HLightPoint(HLightPointPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLightPoint::~HLightPoint()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HLightPoint::sizeHint() const
{
    return {100, 100};
}

QSize HLightPoint::minimumSizeHint() const
{
    return {5, 5};
}

int HLightPoint::step() const
{
    return d_ptr->step;
}

int HLightPoint::interval() const
{
    return d_ptr->timer->interval();
}

QColor HLightPoint::background() const
{
    return d_ptr->background;
}

void HLightPoint::setStep(int value)
{
    if (d_ptr->step == value)
        return;
    d_ptr->step = value;
    update();
}

void HLightPoint::setInterval(int value)
{
    if (d_ptr->timer->interval() == value)
        return;
    d_ptr->timer->setInterval(value);
}

void HLightPoint::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HLightPoint::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(side / 200.0, side / 200.0);
    drawBackground(&painter);
}

void HLightPoint::drawBackground(QPainter *painter)
{
    auto radius = 99;
    auto color = d_ptr->background;
    auto gradient = QRadialGradient(QPoint(0, 0), radius);
    color.setAlpha(255);
    gradient.setColorAt(0.1, color);
    color.setAlpha(100 + d_ptr->offset);
    gradient.setColorAt(0.3, color);
    color.setAlpha(50 + d_ptr->offset);
    gradient.setColorAt(0.6, color);
    color.setAlpha(0);
    gradient.setColorAt(1.0, color);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HLightPoint::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(100);
    connect(d_ptr->timer, &QTimer::timeout, this, &HLightPoint::updateValue);
    d_ptr->timer->start(100);
}

void HLightPoint::updateValue()
{
    (d_ptr->offset < 70 && d_ptr->add) ? (d_ptr->offset += d_ptr->step) : (d_ptr->add = false);
    (d_ptr->offset > 0 && !d_ptr->add) ? (d_ptr->offset -= d_ptr->step) : (d_ptr->add = true);
    update();
}

HE_CONTROL_END_NAMESPACE
