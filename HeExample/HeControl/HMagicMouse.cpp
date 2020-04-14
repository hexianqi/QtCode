#include "HMagicMouse_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HMagicMouse::HMagicMouse(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HMagicMousePrivate)
{
}

HMagicMouse::HMagicMouse(HMagicMousePrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HMagicMouse::~HMagicMouse() = default;

QSize HMagicMouse::sizeHint() const
{
    return {200, 200};
}

QSize HMagicMouse::minimumSizeHint() const
{
    return {30, 30};
}

double HMagicMouse::angle() const
{
    return d_ptr->angle;
}

QColor HMagicMouse::bodyColor() const
{
    return d_ptr->bodyColor;
}

QColor HMagicMouse::eyeColor() const
{
    return d_ptr->eyeColor;
}

QColor HMagicMouse::eyeballColor() const
{
    return d_ptr->eyeballColor;
}

QColor HMagicMouse::noseColor() const
{
    return d_ptr->noseColor;
}

QColor HMagicMouse::earColor() const
{
    return d_ptr->earColor;
}

QColor HMagicMouse::tailColor() const
{
    return d_ptr->tailColor;
}

void HMagicMouse::setAngle(double value)
{
    if (qFuzzyCompare(d_ptr->angle, value))
        return;
    d_ptr->angle = value;
    update();
}

void HMagicMouse::setBodyColor(const QColor &value)
{
    if (d_ptr->bodyColor == value)
        return;
    d_ptr->bodyColor = value;
    update();
}

void HMagicMouse::setEyeColor(const QColor &value)
{
    if (d_ptr->eyeColor == value)
        return;
    d_ptr->eyeColor = value;
    update();
}

void HMagicMouse::setEyeballColor(const QColor &value)
{
    if (d_ptr->eyeballColor == value)
        return;
    d_ptr->eyeballColor = value;
    update();
}

void HMagicMouse::setNoseColor(const QColor &value)
{
    if (d_ptr->noseColor == value)
        return;
    d_ptr->noseColor = value;
    update();
}

void HMagicMouse::setEarColor(const QColor &value)
{
    if (d_ptr->earColor == value)
        return;
    d_ptr->earColor = value;
    update();
}

void HMagicMouse::setTailColor(const QColor &value)
{
    if (d_ptr->tailColor == value)
        return;
    d_ptr->tailColor = value;
    update();
}

void HMagicMouse::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(side / 100.0, side / 100.0);
    painter.rotate(d_ptr->angle);
    drawBody(&painter);
    drawEye(&painter);
    drawEyeball(&painter);
    drawNose(&painter);
    drawEar(&painter);
    drawTail(&painter);
}

void HMagicMouse::drawBody(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->bodyColor);
    painter->drawEllipse(-20, -40, 40, 65);
    painter->restore();
}

void HMagicMouse::drawEye(QPainter *painter)
{
    int size = 14;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->eyeColor);
    painter->drawEllipse(-16, -38, size, size);
    painter->drawEllipse(2, -38, size, size);
    painter->restore();
}

void HMagicMouse::drawEyeball(QPainter *painter)
{
    int size = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->eyeballColor);
    painter->drawEllipse(-14, -38, size, size);
    painter->drawEllipse(6, -38, size, size);
    painter->restore();
}

void HMagicMouse::drawNose(QPainter *painter)
{
    int size = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->noseColor);
    painter->drawEllipse(-4, -45, size, size);
    painter->restore();
}

void HMagicMouse::drawEar(QPainter *painter)
{
    int size = 26;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->earColor);
    painter->drawEllipse(-27, -28, size, size);
    painter->drawEllipse(1, -28, size, size);
    painter->restore();


}

void HMagicMouse::drawTail(QPainter *painter)
{
    //绘制尾巴
    int x = 5;
    int y = 25;
    auto path = QPainterPath(QPointF(0, y));
    path.cubicTo(-x, y + 2, -x, y + 2, 0, y + 5);
    path.cubicTo(x, y + 7, x, y + 7, 0, y + 10);
    path.cubicTo(-x, y + 12, -x, y + 22, 0, y + 15);
    painter->save();
    painter->setPen(QPen(d_ptr->tailColor, 2, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
