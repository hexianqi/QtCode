/***************************************************************************************************
**      2020-12-21  HPaddle
***************************************************************************************************/

#pragma once

#include "HGameObject.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPaddlePrivate;

class HPaddle : public HGameObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPaddle)

public:
    explicit HPaddle(QObject *parent = nullptr);
    ~HPaddle() override;

public:
    void move(float x, QVector2D scope);
    void increase(float x, QVector2D scope);
    void reset(QVector2D position, QVector2D size, QVector3D color);

protected:
    HPaddle(HPaddlePrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

