#pragma once

#include "HShaderEngine.h"
#include "HAbstractShaderEngine_p.h"
#include <QtGui/QVector3D>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtCore/QSharedPointer>

class QOpenGLExtraFunctions;

HE_BEGIN_NAMESPACE

class HOpenGLModel;
class HTextEngine;

class HShaderEngine_TrianglePrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_TexturePrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_TextureBlendPrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_CoordinateSystemPrivate : public HAbstractShaderEnginePrivate
{
public:
    QList<QVector3D> cubePosition;
};

class HShaderEngine_ColorPrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_LightPrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_LightMaterialsPrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_LightMapsPrivate : public HAbstractShaderEnginePrivate
{

};

class HShaderEngine_LightCasterDirectionalPrivate : public HAbstractShaderEnginePrivate
{
public:
    QList<QVector3D> cubePosition;
    QVector3D lightDirection = QVector3D(-0.2f, -1.0f, -0.3f);
};

class HShaderEngine_LightCasterPointPrivate : public HAbstractShaderEnginePrivate
{
public:
    QList<QVector3D> cubePosition;
    QVector3D lightAttenuation = QVector3D(1.0f, 0.7f, 1.8f);
};

class HShaderEngine_LightCasterSpotPrivate : public HAbstractShaderEnginePrivate
{
public:
    QList<QVector3D> cubePosition;
    QVector3D lightAttenuation = QVector3D(1.0f, 0.7f, 1.8f);
};

class HShaderEngine_LightCasterMultiPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_LightCasterMultiPrivate();

public:
    QList<QVector3D> cubePosition;
    QList<QVector3D> lightPosition;
    QVector3D lightDirection = QVector3D(-0.2f, -1.0f, -0.3f);
    QVector3D lightAttenuation = QVector3D(1.0f, 0.7f, 1.8f);
};

class HShaderEngine_LightBlinnPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_LightGammaPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_LightGammaPrivate();

public:
    QVector<QVector3D> lightColor;
    QVector<QVector3D> lightPosition;
};

class HShaderEngine_ModelPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_DepthPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_DepthPrivate();

public:
    QList<QVector3D> cubePosition;
};

class HShaderEngine_StencilPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_StencilPrivate();

public:
    QList<QVector3D> cubePosition;
};

class HShaderEngine_BlendingPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_BlendingPrivate();

public:
    QList<QVector3D> cubePosition;
    QList<QVector3D> windowPosition;
};

class HShaderEngine_FramebufferPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_FramebufferPrivate();

public:
    QSharedPointer<QOpenGLFramebufferObject> fbo;
    QList<QVector3D> cubePosition;
};

class HShaderEngine_CubemapsPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_UboPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_UboPrivate();

public:
    void bindUniformBlock(GLuint id, const char *name, int block);

public:
    unsigned int ubo;
    QList<QVector3D> cubePosition;
};

class HShaderEngine_GeometryHousePrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_GeometryHousePrivate();

public:
    QOpenGLVertexArrayObject vao;
};

class HShaderEngine_GeometryExplodePrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_GeometryNormalPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_InstancingPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_InstancingPrivate();

public:
    QOpenGLExtraFunctions *funcs;
    QOpenGLVertexArrayObject vao;
};

class HShaderEngine_InstancingModelPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_InstancingModelPrivate();

public:
    HOpenGLModel *model1 = nullptr;
    HOpenGLModel *model2 = nullptr;
};

class HShaderEngine_AntiAliasingPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_AntiAliasingPrivate();

public:
    QOpenGLFramebufferObjectFormat format1;
    QOpenGLFramebufferObjectFormat format2;
    QSharedPointer<QOpenGLFramebufferObject> fbo1;
    QSharedPointer<QOpenGLFramebufferObject> fbo2;
};

class HShaderEngine_ShadowDepthPrivate : public HAbstractShaderEnginePrivate
{
public:
    QSharedPointer<QOpenGLFramebufferObject> fbo;
};

class HShaderEngine_ShadowMappingPrivate : public HAbstractShaderEnginePrivate
{
public:
    QSharedPointer<QOpenGLFramebufferObject> fbo;
};

class HShaderEngine_ShadowPointPrivate : public HAbstractShaderEnginePrivate
{
public:
    unsigned int fbo = 0;
    unsigned int texture = 0;
    unsigned int shadowWidth = 1024;
    unsigned int shadowHeight = 1024;
};

class HShaderEngine_NormalMappingPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_ParallaxMappingPrivate : public HAbstractShaderEnginePrivate
{
};

class HShaderEngine_HDRPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_HDRPrivate();

public:
    QVector<QVector3D> lightPosition;
    QVector<QVector3D> lightColor;
    QSharedPointer<QOpenGLFramebufferObject> fbo;
};

class HShaderEngine_BloomPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_BloomPrivate();

public:
    QVector<QVector3D> lightPosition;
    QVector<QVector3D> lightColor;
    QVector<QMatrix4x4> cubeModel;
    QSharedPointer<QOpenGLFramebufferObject> hdrFbo;
    QSharedPointer<QOpenGLFramebufferObject> pingFbo;
    QSharedPointer<QOpenGLFramebufferObject> pongFbo;
};

class HShaderEngine_DeferredShadingPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_DeferredShadingPrivate();

public:
    QVector<QVector3D> objectPosition;
    QVector<QVector3D> lightPosition;
    QVector<QVector3D> lightColor;
    QVector3D lightAttenuation = QVector3D(1.0f, 0.7f, 1.8f);
    QVector<QMatrix4x4> cubeModel;
    QSharedPointer<QOpenGLFramebufferObject> fbo;
};

class HShaderEngine_SSAOPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_SSAOPrivate();

public:
    QSharedPointer<QOpenGLFramebufferObject> gbufferFbo;
    QSharedPointer<QOpenGLFramebufferObject> ssaoFbo;
    QSharedPointer<QOpenGLFramebufferObject> blurFbo;
    QVector<QVector3D> ssaoKernel;
    QVector<QVector3D> ssaoNoise;
    QOpenGLTexture *noiseTexture = nullptr;
};

class HShaderEngine_TextPrivate : public HAbstractShaderEnginePrivate
{
public:
    HTextEngine *engine = nullptr;
};

HE_END_NAMESPACE
