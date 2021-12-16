/***************************************************************************************************
**      2020-12-11  HEffectRenderer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HEffectRendererPrivate;

class HEffectRenderer : public QObject
{
    Q_OBJECT

public:
    explicit HEffectRenderer(HOpenGLShaderProgram *shader, int width, int height, QObject *parent = nullptr);
    ~HEffectRenderer() override;

public:
    void setConfuse(bool b);
    void setChaos(bool b);
    void updateShake(float);
    void setShakeTime(float);
    void reset();

public:
    void begin();
    void end();
    void draw(float time);

protected:
    void init();

protected:
    QScopedPointer<HEffectRendererPrivate> d_ptr;
};

HE_END_NAMESPACE

