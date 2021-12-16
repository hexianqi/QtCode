#pragma once

#include "HEffectRenderer.h"
#include "HAbstractRenderer_p.h"
#include <QtCore/QSharedPointer>
#include <QtGui/QOpenGLFramebufferObject>

HE_BEGIN_NAMESPACE

class HEffectRendererPrivate : public HAbstractRendererPrivate
{
public:
    HEffectRendererPrivate();

public:
    int width = 0;
    int height = 0;
    bool confuse = false;
    bool chaos = false;
    bool shake = false;
    float shakeTime = 0.0f;

public:
    QOpenGLFramebufferObjectFormat format1;
    QOpenGLFramebufferObjectFormat format2;
    QSharedPointer<QOpenGLFramebufferObject> fbo1;
    QSharedPointer<QOpenGLFramebufferObject> fbo2;
};

HE_END_NAMESPACE

