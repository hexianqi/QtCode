#include "HMagicFish_p.h"
#include <QtCore/QTimer>
#include <QtCore/QtMath>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HMagicFish::HMagicFish(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HMagicFishPrivate)
{
    init();
}

HMagicFish::HMagicFish(HMagicFishPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HMagicFish::~HMagicFish()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HMagicFish::sizeHint() const
{
    return {200, 200};
}

QSize HMagicFish::minimumSizeHint() const
{
    return {20, 20};
}

QColor HMagicFish::baseColor() const
{
    return d_ptr->baseColor;
}

QColor HMagicFish::headColor() const
{
    return d_ptr->headColor;
}

QColor HMagicFish::bodyColor() const
{
    return d_ptr->bodyColor;
}

QColor HMagicFish::finColor() const
{
    return d_ptr->finColor;
}

QColor HMagicFish::tailColor() const
{
    return d_ptr->tailColor;
}

bool HMagicFish::isFinMoveEnable() const
{
    return d_ptr->finMoveEnable;
}

int HMagicFish::speed() const
{
    return d_ptr->speed;
}

double HMagicFish::wave() const
{
    return d_ptr->wave;
}

double HMagicFish::angle() const
{
    return d_ptr->angle;
}

double HMagicFish::getLength() const
{
    return d_ptr->headLen;
}

void HMagicFish::setBaseColor(const QColor &value)
{
    if (d_ptr->baseColor == value)
        return;
    d_ptr->baseColor = value;
    d_ptr->baseColor.setAlpha(200);
    d_ptr->headColor = d_ptr->baseColor;
    d_ptr->baseColor.setAlpha(220);
    d_ptr->bodyColor = d_ptr->baseColor;
    d_ptr->baseColor.setAlpha(150);
    d_ptr->finColor = d_ptr->baseColor;
    d_ptr->baseColor.setAlpha(180);
    d_ptr->tailColor = d_ptr->baseColor;
    d_ptr->baseColor = value;
    update();
}

void HMagicFish::setHeadColor(const QColor &value)
{
    if (d_ptr->headColor == value)
        return;
    d_ptr->headColor = value;
    update();
}

void HMagicFish::setBodyColor(const QColor &value)
{
    if (d_ptr->bodyColor == value)
        return;
    d_ptr->bodyColor = value;
    update();
}

void HMagicFish::setFinColor(const QColor &value)
{
    if (d_ptr->finColor == value)
        return;
    d_ptr->finColor = value;
    update();
}

void HMagicFish::setTailColor(const QColor &value)
{
    if (d_ptr->tailColor == value)
        return;
    d_ptr->tailColor = value;
    update();
}

void HMagicFish::setFinMoveEnable(bool b)
{
    if (d_ptr->finMoveEnable == b)
        return;
    d_ptr->finMoveEnable = b;
    update();
}

void HMagicFish::setSpeed(int value)
{
    if (d_ptr->speed == value)
        return;
    d_ptr->speed = value;
    update();
}

void HMagicFish::setWave(double value)
{
    if (qFuzzyCompare(d_ptr->wave, value))
        return;
    d_ptr->wave = value;
    update();
}

void HMagicFish::setAngle(double value)
{
    if (qFuzzyCompare(d_ptr->angle, value))
        return;
    d_ptr->angle = value;
    update();
}

void HMagicFish::setLength(double value)
{
    if (qFuzzyCompare(d_ptr->headLen, value))
        return;
    d_ptr->headLen = value;
    d_ptr->finLen = value * 1.8;
    d_ptr->bodyLen = value * 5.2;
    d_ptr->tailLen = value * 0.8;
    update();
}

void HMagicFish::resizeEvent(QResizeEvent *)
{
    setLength(qMin(width(), height()) / 10.0);
}

void HMagicFish::paintEvent(QPaintEvent *)
{
    d_ptr->headPos = calcPoint(QPointF(0, 0), d_ptr->bodyLen / 1.5, 0);
    auto angle = qSin(calcWaveRadians(1.2)) * 2;
    auto pos = calcPoint(d_ptr->headPos, d_ptr->bodyLen, angle - 180);
    auto left = calcPoint(d_ptr->headPos, d_ptr->headLen * 0.9, angle + 110);
    auto right = calcPoint(d_ptr->headPos, d_ptr->headLen * 0.9, angle - 110);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.rotate(d_ptr->angle);
    drawHead(&painter);
    drawBody(&painter, pos, angle);
    drawFin(&painter, left, angle, true);
    drawFin(&painter, right, angle, false);
    drawTail(&painter, pos, angle);
}

void HMagicFish::drawHead(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->headColor);
    painter->drawEllipse(d_ptr->headPos, d_ptr->headLen, d_ptr->headLen);
    painter->restore();
}

void HMagicFish::drawBody(QPainter *painter, const QPointF &pos, double angle)
{
    auto pos1 = calcPoint(d_ptr->headPos, d_ptr->headLen, angle - 80);
    auto pos2 = calcPoint(pos, d_ptr->headLen * 0.8, angle - 90);
    auto pos3 = calcPoint(pos, d_ptr->headLen * 0.8, angle + 90);
    auto pos4 = calcPoint(d_ptr->headPos, d_ptr->headLen, angle + 80);
    auto left = calcPoint(d_ptr->headPos, d_ptr->bodyLen * 0.56, angle - 130);
    auto right = calcPoint(d_ptr->headPos, d_ptr->bodyLen * 0.56, angle + 130);
    QPainterPath path;
    path.moveTo(pos1);
    path.quadTo(left, pos2);
    path.lineTo(pos3);
    path.quadTo(right, pos4);
    path.lineTo(pos1);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->bodyColor);
    painter->drawPath(path);
    painter->restore();
}

void HMagicFish::drawFin(QPainter *painter, const QPointF &pos, double angle, bool left)
{
    auto sign = left ? 1.0 : -1.0;
    auto controlAngle = 115;
    auto finAngle = d_ptr->finMoveEnable ? qSin(calcWaveRadians(16.1)) * 12.0 : 2.0;
    auto endPos = calcPoint(pos, d_ptr->finLen, angle + (finAngle + 180) * sign);
    auto controlPos = calcPoint(pos, d_ptr->finLen * 1.8, angle + (controlAngle + finAngle) * sign);
    QPainterPath path;
    path.moveTo(pos);
    path.quadTo(controlPos, endPos);
    path.lineTo(pos);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->finColor);
    painter->drawPath(path);
    painter->restore();
}

void HMagicFish::drawTail(QPainter *painter, const QPointF &pos, double angle)
{
    auto flag = 0.6;
    auto length = d_ptr->tailLen * (flag + 1);
    auto tailAngle = angle + qCos(calcWaveRadians(1.5)) * 15;
    auto endPos = calcPoint(pos, length, tailAngle - 180);
    auto pos1 = calcPoint(pos, d_ptr->tailLen, tailAngle - 90);
    auto pos2 = calcPoint(endPos, d_ptr->tailLen * flag, tailAngle - 90);
    auto pos3 = calcPoint(endPos, d_ptr->tailLen * flag, tailAngle + 90);
    auto pos4 = calcPoint(pos, d_ptr->tailLen, tailAngle + 90);
    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->tailColor);
    // 鱼尾关节大圆
    painter->drawEllipse(pos, d_ptr->tailLen, d_ptr->tailLen);
    // 鱼尾关节小圆
    painter->drawEllipse(endPos, d_ptr->tailLen * flag, d_ptr->tailLen * flag);
    // 鱼尾肉部分路径
    painter->drawPath(path);
    painter->restore();
    // 绘制鱼尾关节
    drawTail1(painter, endPos, tailAngle);
}

void HMagicFish::drawTail1(QPainter *painter, const QPointF &pos, double angle)
{
    auto flag = 0.4;
    auto len = d_ptr->tailLen * 0.6;
    auto length = len * (flag + 2.7);
    auto tailAngle = angle + qSin(calcWaveRadians(1.7)) * 35;
    auto endPos = calcPoint(pos, length, tailAngle - 180);
    auto pos1 = calcPoint(pos, len, tailAngle - 90);
    auto pos2 = calcPoint(endPos, len * flag, tailAngle - 90);
    auto pos3 = calcPoint(endPos, len * flag, tailAngle + 90);
    auto pos4 = calcPoint(pos, len, tailAngle + 90);
    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->tailColor);
    painter->drawPath(path);
    painter->restore();
    // 绘制鱼尾鱼鳍
    drawTail2(painter, pos, tailAngle);
}

void HMagicFish::drawTail2(QPainter *painter, const QPointF &pos, double angle)
{
    auto flag = 0.4;
    auto len = d_ptr->tailLen * 0.6;
    auto length = len * (flag + 2.7);
    auto tailWidth = qAbs(qSin(calcWaveRadians(1.9)) * len + d_ptr->headLen * 3.0 / 5);
    auto endPos1 = calcPoint(pos, length, angle - 180);
    auto endPos2 = calcPoint(pos, length - 10, angle - 180);
    auto pos1 = calcPoint(endPos1, tailWidth, angle - 90);
    auto pos2 = calcPoint(endPos1, tailWidth, angle + 90);
    auto pos3 = calcPoint(endPos2, tailWidth - d_ptr->headLen / 1.5, angle - 90);
    auto pos4 = calcPoint(endPos2, tailWidth - d_ptr->headLen / 1.5, angle + 90);
    QPainterPath path1;
    path1.moveTo(pos);
    path1.lineTo(pos3);
    path1.lineTo(pos4);
    path1.lineTo(pos);
    QPainterPath path2;
    path2.moveTo(pos);
    path2.lineTo(pos1);
    path2.lineTo(pos2);
    path2.lineTo(pos);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->tailColor);
    painter->drawPath(path1);
    painter->drawPath(path2);
    painter->restore();
}

QPointF HMagicFish::calcPoint(const QPointF &pos, double len, double angle)
{
    auto x = qCos(qDegreesToRadians(angle)) * len;
    auto y = qSin(qDegreesToRadians(angle - 180)) * len;
    return pos + QPointF(x, y);
}

double HMagicFish::calcWaveRadians(double value)
{
    return qDegreesToRadians(d_ptr->currentValue * d_ptr->wave * value);
}

void HMagicFish::init()
{
    setLength(10);
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout,this, &HMagicFish::updateValue);
    d_ptr->timer->start(100);
}

void HMagicFish::updateValue()
{
    d_ptr->currentValue = (d_ptr->currentValue + d_ptr->speed) % 54000;
    update();
}

HE_CONTROL_END_NAMESPACE
