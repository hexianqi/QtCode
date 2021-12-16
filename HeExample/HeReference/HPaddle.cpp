#include "HPaddle_p.h"

HE_BEGIN_NAMESPACE

HPaddle::HPaddle(QObject *parent) :
    HGameObject(*new HPaddlePrivate, parent)
{
}

HPaddle::HPaddle(HPaddlePrivate &p, QObject *parent) :
    HGameObject(p, parent)
{
}

HPaddle::~HPaddle()
{
}

void HPaddle::move(float x, QVector2D scope)
{
    Q_D(HPaddle);
    d->position.setX(qBound(scope.x(), d->position.x() + x, scope.y() - d->size.x()));
}

void HPaddle::increase(float x, QVector2D scope)
{
    Q_D(HPaddle);
    d->size.setX(d->size.x() + x);
    d->position.setX(qBound(scope.x(), d->position.x() - x / 2, scope.y() - d->size.x()));
}

void HPaddle::reset(QVector2D position, QVector2D size, QVector3D color)
{
    setPosition(position);
    setSize(size);
    setColor(color);
}

HE_END_NAMESPACE
