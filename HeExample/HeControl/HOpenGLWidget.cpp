#include "HOpenGLWidget_p.h"
#include "HOpenGLCamera.h"
#include "HGeometryEngine.h"
#include "HShaderEngine.h"
#include "HShaderEngine_PBR.h"
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QtMath>
#include <QtGui/QOpenGLFunctions_3_3_Core>
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

HOpenGLWidgetPrivate::HOpenGLWidgetPrivate()
{
    attenuations.insert(   7, QVector3D(1.0, 0.7, 1.8));
    attenuations.insert(  13, QVector3D(1.0, 0.35, 0.44));
    attenuations.insert(  20, QVector3D(1.0, 0.22, 0.20));
    attenuations.insert(  32, QVector3D(1.0, 0.14, 0.07));
    attenuations.insert(  50, QVector3D(1.0, 0.09, 0.032));
    attenuations.insert(  65, QVector3D(1.0, 0.07, 0.017));
    attenuations.insert( 100, QVector3D(1.0, 0.045, 0.0075));
    attenuations.insert( 160, QVector3D(1.0, 0.027, 0.0028));
    attenuations.insert( 200, QVector3D(1.0, 0.022, 0.0019));
    attenuations.insert( 325, QVector3D(1.0, 0.014, 0.0007));
    attenuations.insert( 600, QVector3D(1.0, 0.007, 0.0002));
    attenuations.insert(3250, QVector3D(1.0, 0.0014, 0.000007));

    modelFileName = "objects\\cyborg\\cyborg.obj";
    lightPos = QVector3D(2.0f, 2.0f, 2.0f);
    lightColor = QVector3D(1.0f, 1.0f, 1.0f);
    auto cubeWorldPosition = QList<QVector3D>()
                             << QVector3D( 0.0f,  0.0f,  0.0f)
                             << QVector3D( 2.0f,  5.0f, -15.0f)
                             << QVector3D(-1.5f, -2.2f, -2.5f)
                             << QVector3D(-3.8f, -2.0f, -12.3f)
                             << QVector3D( 2.4f, -0.4f, -3.5f)
                             << QVector3D(-1.7f,  3.0f, -7.5f)
                             << QVector3D( 1.3f, -2.0f, -2.5f)
                             << QVector3D( 1.5f,  2.0f, -2.5f)
                             << QVector3D( 1.5f,  0.2f, -1.5f)
                             << QVector3D(-1.3f,  1.0f, -1.5f);
    globalParam.insert("materialPosition",  QVariant::fromValue(cubeWorldPosition));
    globalParam.insert("lightDirection",    QVector3D(-0.2f, -1.0f, -0.3f));
    globalParam.insert("lightAttenuation",  findAttenuation(5.0));
}

QVector3D HOpenGLWidgetPrivate::findAttenuation(double distance)
{
    for (auto i = attenuations.cbegin(); i != attenuations.cend(); i++)
    {
        if (i.key() >= distance)
            return i.value();
    }
    return attenuations.last();
}

HOpenGLWidget::HOpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    d_ptr(new HOpenGLWidgetPrivate)
{
    init();
}

HOpenGLWidget::HOpenGLWidget(HOpenGLWidgetPrivate &p, QWidget *parent) :
    QOpenGLWidget(parent),
    d_ptr(&p)
{
    init();
}

HOpenGLWidget::~HOpenGLWidget()
{
    d_ptr->timer->stop();
    makeCurrent();
    qDeleteAll(d_ptr->shaders);
    d_ptr->shaders.clear();
    delete d_ptr->geometry;
    doneCurrent();
}

void HOpenGLWidget::setLineMode(bool b)
{
    d_ptr->funcs->glPolygonMode(GL_FRONT_AND_BACK, b ? GL_LINE : GL_FILL);
}

void HOpenGLWidget::setLightPosLoop(bool b)
{
    d_ptr->lightPosLoop = b;
}

void HOpenGLWidget::setLightColorLoop(bool b)
{
    d_ptr->lightColorLoop = b;
}

void HOpenGLWidget::setLinearize(bool b)
{
    d_ptr->linearize = b;
}

void HOpenGLWidget::setBlinn(bool b)
{
    d_ptr->blinn = b;
}

void HOpenGLWidget::setGamma(bool b)
{
    d_ptr->gamma = b;
}

void HOpenGLWidget::setHdr(bool b)
{
    d_ptr->hdr = b;
}

void HOpenGLWidget::setBloom(bool b)
{
    d_ptr->bloom = b;
}

void HOpenGLWidget::setShadows(bool b)
{
    d_ptr->shadows = b;
}

void HOpenGLWidget::setExposure(double value)
{
    d_ptr->exposure = value;
}

void HOpenGLWidget::setHeightScale(double value)
{
    d_ptr->heightScale = value;
}

void HOpenGLWidget::setDisplay(const QString &key)
{
    if (!d_ptr->shaders.contains(key) || d_ptr->shaders.value(key) == d_ptr->shader)
        return;
    makeCurrent();
    d_ptr->shader = d_ptr->shaders.value(key);
    d_ptr->shader->initialize(d_ptr->globalParam);
    doneCurrent();
}

void HOpenGLWidget::initializeGL()
{
    d_ptr->funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    d_ptr->funcs->initializeOpenGLFunctions();
    d_ptr->funcs->glClearColor(0.1, 0.1, 0.1, 1);
    d_ptr->funcs->glEnable(GL_DEPTH_TEST);
    d_ptr->funcs->glEnable(GL_MULTISAMPLE);
    d_ptr->funcs->glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    d_ptr->camera = new HOpenGLCamera(this);
    d_ptr->camera->setPosition(QVector3D(0.0, 0.0, 5.0));
    d_ptr->camera->addWatched(this);
    d_ptr->geometry = new HGeometryEngine;
    d_ptr->shaders.insert("Triangle",               new HShaderEngine_Triangle);
    d_ptr->shaders.insert("Texture",                new HShaderEngine_Texture);
    d_ptr->shaders.insert("TextureBlend",           new HShaderEngine_TextureBlend);
    d_ptr->shaders.insert("CoordinateSystem",       new HShaderEngine_CoordinateSystem);
    d_ptr->shaders.insert("Color",                  new HShaderEngine_Color);
    d_ptr->shaders.insert("Light",                  new HShaderEngine_Light);
    d_ptr->shaders.insert("LightMaterials",         new HShaderEngine_LightMaterials);
    d_ptr->shaders.insert("LightMaps",              new HShaderEngine_LightMaps);
    d_ptr->shaders.insert("LightCasterDirectional", new HShaderEngine_LightCasterDirectional);
    d_ptr->shaders.insert("LightCasterPoint",       new HShaderEngine_LightCasterPoint);
    d_ptr->shaders.insert("LightCasterSpot",        new HShaderEngine_LightCasterSpot);
    d_ptr->shaders.insert("LightCasterMulti",       new HShaderEngine_LightCasterMulti);
    d_ptr->shaders.insert("Model",                  new HShaderEngine_Model);
    d_ptr->shaders.insert("Depth",                  new HShaderEngine_Depth);
    d_ptr->shaders.insert("Stencil",                new HShaderEngine_Stencil);
    d_ptr->shaders.insert("Blending",               new HShaderEngine_Blending);
    d_ptr->shaders.insert("Framebuffer",            new HShaderEngine_Framebuffer);
    d_ptr->shaders.insert("Cubemaps",               new HShaderEngine_Cubemaps);
    d_ptr->shaders.insert("Ubo",                    new HShaderEngine_Ubo);
    d_ptr->shaders.insert("GeometryHouse",          new HShaderEngine_GeometryHouse);
    d_ptr->shaders.insert("GeometryExplode",        new HShaderEngine_GeometryExplode);
    d_ptr->shaders.insert("GeometryNormal",         new HShaderEngine_GeometryNormal);
    d_ptr->shaders.insert("Instancing",             new HShaderEngine_Instancing);
    d_ptr->shaders.insert("InstancingModel",        new HShaderEngine_InstancingModel);
    d_ptr->shaders.insert("AntiAliasing",           new HShaderEngine_AntiAliasing);
    d_ptr->shaders.insert("LightBlinn",             new HShaderEngine_LightBlinn);
    d_ptr->shaders.insert("LightGamma",             new HShaderEngine_LightGamma);
    d_ptr->shaders.insert("ShadowDepth",            new HShaderEngine_ShadowDepth);
    d_ptr->shaders.insert("ShadowMapping",          new HShaderEngine_ShadowMapping);
    d_ptr->shaders.insert("ShadowPoint",            new HShaderEngine_ShadowPoint);
    d_ptr->shaders.insert("NormalMapping",          new HShaderEngine_NormalMapping);
    d_ptr->shaders.insert("ParallaxMapping",        new HShaderEngine_ParallaxMapping);
    d_ptr->shaders.insert("HDR",                    new HShaderEngine_HDR);
    d_ptr->shaders.insert("Bloom",                  new HShaderEngine_Bloom);
    d_ptr->shaders.insert("DeferredShading",        new HShaderEngine_DeferredShading);
    d_ptr->shaders.insert("SSAO",                   new HShaderEngine_SSAO);
    d_ptr->shaders.insert("PBR",                    new HShaderEngine_PBR);
    d_ptr->shaders.insert("PBR2",                   new HShaderEngine_PBR2);
    d_ptr->shaders.insert("PBR3",                   new HShaderEngine_PBR3);
    d_ptr->shaders.insert("PBR4",                   new HShaderEngine_PBR4);
    d_ptr->shaders.insert("PBR5",                   new HShaderEngine_PBR5);
    d_ptr->shaders.insert("PBR6",                   new HShaderEngine_PBR6);
    d_ptr->shaders.insert("Text",                   new HShaderEngine_Text);

    d_ptr->timer = new QTimer(this);
    setDisplay("Text");
    connect(d_ptr->timer, &QTimer::timeout, this, QOverload<>::of(&HOpenGLWidget::update));
    connect(this, &HOpenGLWidget::frameSwapped, d_ptr->camera, &HOpenGLCamera::updateDelta);
    d_ptr->timer->start(18);
}

void HOpenGLWidget::resizeGL(int w, int h)
{
    d_ptr->funcs->glViewport(0, 0, w, h);
}

void HOpenGLWidget::paintGL()
{
    QVariantMap param;
    QMatrix4x4 projection;
    projection.perspective(d_ptr->camera->zoom(), 1.0 * width() / height(), 0.1f, 1000.0f);
    param.insert("size",            size());
    param.insert("projection",      projection);
    param.insert("modelFileName",   d_ptr->modelFileName);
    param.insert("view",            d_ptr->camera->view());
    param.insert("viewPos",         d_ptr->camera->position());
    param.insert("viewFront",       d_ptr->camera->front());
    param.insert("lightPos",        lightPos());
    param.insert("lightColor",      lightColor());
    param.insert("linearize",       d_ptr->linearize);
    param.insert("blinn",           d_ptr->blinn);
    param.insert("gamma",           d_ptr->gamma);
    param.insert("shadows",         d_ptr->shadows);
    param.insert("hdr",             d_ptr->hdr);
    param.insert("bloom",           d_ptr->bloom);
    param.insert("exposure",        d_ptr->exposure);
    param.insert("heightScale",     d_ptr->heightScale);
    d_ptr->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d_ptr->shader->draw(d_ptr->geometry, param);
}

QVector3D HOpenGLWidget::lightPos()
{
    if (d_ptr->lightPosLoop)
    {
        auto r = qDegreesToRadians(QTime::currentTime().msecsSinceStartOfDay() * 12 / 1000.0);
        return QVector3D(1.0f + sin(r) * 2.0f,  sin(r / 2.0f) * 1.0f, d_ptr->lightPos.z());
    }
    return d_ptr->lightPos;
}

QVector3D HOpenGLWidget::lightColor()
{
    if (d_ptr->lightColorLoop)
    {
        auto r = qDegreesToRadians(QTime::currentTime().msecsSinceStartOfDay() * 12 / 1000.0);
        return QVector3D(sin(r * 2.0f), sin(r * 0.7f), sin(r * 1.3f));
    }
    return d_ptr->lightColor;
}

void HOpenGLWidget::init()
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24);
    format.setVersion(3, 3);
    format.setSamples(4);
    setFormat(format);
}

HE_END_NAMESPACE
