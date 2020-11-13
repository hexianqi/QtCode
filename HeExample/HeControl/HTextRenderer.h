/***************************************************************************************************
**      2020-12-21  HTextRenderer
***************************************************************************************************/

#pragma once

#include "HAbstractRenderer.h"
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_CONTROL_BEGIN_NAMESPACE

class HTextRendererPrivate;

class HTextRenderer : public HAbstractRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTextRenderer)

public:
    explicit HTextRenderer(QOpenGLShaderProgram *, QObject *parent = nullptr);
    ~HTextRenderer() override;

public:
    bool setFont(const QString &, int pixelSize);

public:
    void draw(const QString &text, QVector2D position = QVector2D(), int pixelSize = -1, QVector3D color = QVector3D(1.0f, 1.0f, 1.0f));
};

HE_CONTROL_END_NAMESPACE

