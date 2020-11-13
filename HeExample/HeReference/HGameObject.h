/***************************************************************************************************
**      2020-12-09  HGameObject
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLTexture2D;
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
    QRectF geometry();
    QVector2D center();

public:
    void setPosition(QVector2D);
    void setSize(QVector2D);
    void setRotate(float);
    void setColor(QVector3D);
    void setTexture(HOpenGLTexture2D *);
    void setVelocity(QVector2D);

public:
    virtual void draw(HSpriteRenderer *);
    virtual bool checkCollision(HGameObject *other);

protected:
    HGameObject(HGameObjectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGameObjectPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

