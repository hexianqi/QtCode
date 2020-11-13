/***************************************************************************************************
**      2020-12-08  HSpriteRenderer
***************************************************************************************************/

#pragma once

#include "HAbstractRenderer.h"
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_CONTROL_BEGIN_NAMESPACE

class HSpriteRendererPrivate;

class HSpriteRenderer : public HAbstractRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpriteRenderer);

public:
    explicit HSpriteRenderer(QOpenGLShaderProgram *shader, QObject *parent = nullptr);
    ~HSpriteRenderer() override;

public:
    void draw(QVector2D position, QVector2D size = QVector2D(10.0, 10.0), float rotate = 0.0f, QVector3D color = QVector3D(1.0, 1.0, 1.0));

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

