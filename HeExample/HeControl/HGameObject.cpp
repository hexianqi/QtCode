#include "HGameObject_p.h"
#include "HSpriteRenderer.h"
#include <QtCore/QRectF>
#include <QtGui/QOpenGLTexture>

HE_BEGIN_NAMESPACE

HGameObject::HGameObject(QObject *parent) :
    QObject(parent),
    d_ptr(new HGameObjectPrivate)
{
}

HGameObject::HGameObject(HGameObjectPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HGameObject::~HGameObject()
{
}

QVector2D HGameObject::position()
{
    return d_ptr->position;
}

QVector2D HGameObject::size()
{
    return d_ptr->size;
}

QVector2D HGameObject::velocity()
{
    return d_ptr->velocity;
}

QVector2D HGameObject::center()
{
    return QVector2D(d_ptr->position.x() + d_ptr->size.x() / 2.0f, d_ptr->position.y() + d_ptr->size.y() / 2.0f);
}

QRectF HGameObject::geometry()
{
    return QRectF(d_ptr->position.x(), d_ptr->position.y(), d_ptr->size.x(), d_ptr->size.y());
}

void HGameObject::setPosition(QVector2D value)
{
    d_ptr->position = value;
}

void HGameObject::setSize(QVector2D value)
{
    d_ptr->size = value;
}

void HGameObject::setVelocity(QVector2D value)
{
    d_ptr->velocity = value;
}

void HGameObject::setColor(QVector3D value)
{
    d_ptr->color = value;
}

void HGameObject::setTexture(QOpenGLTexture *p)
{
    d_ptr->texture = p;
}

void HGameObject::draw(HSpriteRenderer *p)
{
    d_ptr->texture->bind(0);
    p->draw(d_ptr->position, d_ptr->size, d_ptr->rotate, d_ptr->color);
}

// AABB rect collision
bool HGameObject::checkCollision(HGameObject *other)
{
    //return this->geometry().intersects(other->geometry());
    // collision x-axis?
    bool collisionX = this->position().x() + this->size().x() >= other->position().x() &&
                      other->position().x() + other->size().x() >= this->position().x();
    // collision y-axis?
    bool collisionY = this->position().y() + this->size().y() >= other->position().y() &&
                      other->position().y() + other->size().y() >= this->position().y();
    // collision only if on both axes
    return collisionX && collisionY;
}

HE_END_NAMESPACE
