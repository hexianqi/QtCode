/***************************************************************************************************
**      2020-12-16  HAbstractRenderer
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QOpenGLShaderProgram;

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractRendererPrivate;

class HAbstractRenderer : public QObject
{
    Q_OBJECT

public:
    explicit HAbstractRenderer(QOpenGLShaderProgram *shader, QObject *parent = nullptr);
    ~HAbstractRenderer() override;

protected:
    HAbstractRenderer(HAbstractRendererPrivate &p, QOpenGLShaderProgram *shader, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractRendererPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

