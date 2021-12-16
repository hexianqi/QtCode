/***************************************************************************************************
**      2020-12-08  HSpriteRenderer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HSpriteRendererPrivate;

class HSpriteRenderer : public QObject
{
    Q_OBJECT

public:
    explicit HSpriteRenderer(HOpenGLShaderProgram *shader, QObject *parent = nullptr);
    ~HSpriteRenderer() override;

public:
    void draw(QVector2D position, QVector2D size = QVector2D(10.0, 10.0), float rotate = 0.0f, QVector3D color = QVector3D(1.0, 1.0, 1.0));

protected:
    HSpriteRenderer(HSpriteRendererPrivate &p, QObject *parent = nullptr);

protected:
    void init();

protected:
    QScopedPointer<HSpriteRendererPrivate> d_ptr;
};

HE_END_NAMESPACE

