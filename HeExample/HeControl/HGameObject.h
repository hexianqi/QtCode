/***************************************************************************************************
**      2020-12-09  HGameObject
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class QOpenGLTexture;

HE_BEGIN_NAMESPACE

class HSpriteRenderer;
class HGameObjectPrivate;

class HGameObject : public QObject
{
    Q_OBJECT

public:
    explicit HGameObject(QObject *parent = nullptr);
    ~HGameObject() override;

public:
    QVector2D position();
    QVector2D size();
    QVector2D velocity();
    QVector2D center();
    QRectF geometry();

public:
    void setPosition(QVector2D);
    void setSize(QVector2D);
    void setColor(QVector3D);
    void setVelocity(QVector2D);
    void setRotate(float);
    void setTexture(QOpenGLTexture *);

public:
    virtual void draw(HSpriteRenderer *);
    virtual bool checkCollision(HGameObject *other);

protected:
    HGameObject(HGameObjectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGameObjectPrivate> d_ptr;
};

HE_END_NAMESPACE

