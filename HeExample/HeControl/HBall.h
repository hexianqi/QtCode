/***************************************************************************************************
**      2020-12-21  HBall
***************************************************************************************************/

#pragma once

#include "HGameObject.h"
#include <QtGui/QVector2D>

HE_CONTROL_BEGIN_NAMESPACE

class HPaddle;
class HBallPrivate;

class HBall : public HGameObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBall)

public:
    explicit HBall(QObject *parent = nullptr);
    ~HBall() override;

signals:
    void positionChanged(QVector2D);

public:
    float radius();
    bool isStuck();
    bool isPassThrough();

public:
    void setRadius(float);
    void setStuck(bool);
    void setSticky(bool);
    void setPassThrough(bool);
    void speed(float);
    void move(float x, QVector2D scope, bool stuck);
    void collision(HPaddle *, float strength);
    void relocation(QVector2D difference);
    void reset(QVector2D position, QVector2D velocity);

public:
    virtual bool checkCollision(HGameObject *other, QVector2D &difference);

protected:
    HBall(HBallPrivate &p, QObject *parent = nullptr);

protected:
    int calcDirection(QVector2D target);
};

HE_CONTROL_END_NAMESPACE

