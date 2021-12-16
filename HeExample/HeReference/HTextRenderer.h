/***************************************************************************************************
**      2020-12-11  HTextRenderer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HTextRendererPrivate;

class HTextRenderer : public QObject
{
    Q_OBJECT

public:
    explicit HTextRenderer(HOpenGLShaderProgram *shader, QObject *parent = nullptr);
    ~HTextRenderer() override;

public:
    bool setFont(const QString &, int pixelSize);

public:
    void draw(const QString &text, QVector2D position = QVector2D(), int pixelSize = -1, QVector3D color = QVector3D(1.0f, 1.0f, 1.0f));

protected:
    QScopedPointer<HTextRendererPrivate> d_ptr;
};

HE_END_NAMESPACE

