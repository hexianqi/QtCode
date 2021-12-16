#include "HShaderEngine_p.h"
#include "HGeometryEngine.h"
#include "HTextEngine.h"
#include "HOpenGLModel.h"
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLExtraFunctions>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

HE_BEGIN_NAMESPACE

HShaderEngine_Triangle::HShaderEngine_Triangle(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_TrianglePrivate, parent)
{
}

HShaderEngine_Triangle::~HShaderEngine_Triangle() = default;

void HShaderEngine_Triangle::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Triangle);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/triangle.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/triangle.fs");
    s->bind();
    d->shaders.append(s);
}

QString HShaderEngine_Triangle::typeName()
{
    return "HShaderEngine_Triangle";
}

void HShaderEngine_Triangle::draw(HGeometryEngine *p, QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Triangle);
    auto s = d->shaders.first();
    s->bind();
    p->renderTriangle(s);
}

HShaderEngine_Texture::HShaderEngine_Texture(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_TexturePrivate, parent)
{
}

HShaderEngine_Texture::~HShaderEngine_Texture()
{

}

void HShaderEngine_Texture::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Texture);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/texture_color.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/texture_color.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders.append(s);
    addTexture(":/textures/container.png");
}

QString HShaderEngine_Texture::typeName()
{
    return "HShaderEngine_Texture";
}

void HShaderEngine_Texture::draw(HGeometryEngine *p, QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Texture);
    auto s = d->shaders.first();
    buildTexture();
    s->bind();
    p->renderRect(s);
}

HShaderEngine_TextureBlend::HShaderEngine_TextureBlend(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_TextureBlendPrivate, parent)
{
}

HShaderEngine_TextureBlend::~HShaderEngine_TextureBlend() = default;

void HShaderEngine_TextureBlend::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_TextureBlend);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/texture_color.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/texture_blend.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    s->setUniformValue("texture2", 1);
    d->shaders.append(s);
    addTexture(":/textures/awesomeface.png");
    addTexture(":/textures/container.png");
}

QString HShaderEngine_TextureBlend::typeName()
{
    return "HShaderEngine_Texture2";
}

void HShaderEngine_TextureBlend::draw(HGeometryEngine *p, QVariantMap /*param*/)
{
    Q_D(HShaderEngine_TextureBlend);
    auto s = d->shaders.first();
    buildTexture();
    s->bind();
    p->renderRect(s);
}

HShaderEngine_CoordinateSystem::HShaderEngine_CoordinateSystem(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_CoordinateSystemPrivate, parent)
{
}

HShaderEngine_CoordinateSystem::~HShaderEngine_CoordinateSystem() = default;

void HShaderEngine_CoordinateSystem::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_CoordinateSystem);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/coordinate_systems.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/coordinate_systems.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    s->setUniformValue("texture2", 1);
    d->shaders.append(s);
    addTexture(":/textures/awesomeface.png");
    addTexture(":/textures/container.png");
}

QString HShaderEngine_CoordinateSystem::typeName()
{
    return "HShaderEngine_CoordinateSystem";
}

void HShaderEngine_CoordinateSystem::setData(QVariantMap value)
{
    Q_D(HShaderEngine_CoordinateSystem);
    if (value.contains("materialPosition"))
        d->cubePosition = value.value("materialPosition").value<QList<QVector3D>>();
}

void HShaderEngine_CoordinateSystem::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_CoordinateSystem);
    QMatrix4x4 model;
    auto s = d->shaders.first();
    buildTexture();
    s->bind();
    s->setUniformValue("projection", param.value("projection").value<QMatrix4x4>());
    s->setUniformValue("view", param.value("view").value<QMatrix4x4>());
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.rotate(secs() * 6, 1.0f, 0.0f);
        model.translate(d->cubePosition.at(i));
        model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
        s->setUniformValue("model", model);
        p->renderCube(s);
    }
}

HShaderEngine_Color::HShaderEngine_Color(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ColorPrivate, parent)
{
}

HShaderEngine_Color::~HShaderEngine_Color() = default;

void HShaderEngine_Color::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Color);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_object.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_object.fs");
    s1->bind();
    s1->setUniformValue("objectColor", 1.0f, 0.5f, 0.31f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_Color::typeName()
{
    return "HShaderEngine_Color";
}

void HShaderEngine_Color::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Color);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("lightColor", lightColor);
    p->renderCube(s1);
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_Light::HShaderEngine_Light(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightPrivate, parent)
{
}

HShaderEngine_Light::~HShaderEngine_Light() = default;

void HShaderEngine_Light::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Light);
    if (d->initialized)
        return;
    d->initialized = true;
    // light_phong      冯氏着色（世界空间）;
    // light_phong2     冯氏着色（观察空间）;
    // light_gouraud    Gouraud着色;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_phong.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_phong.fs");
    s1->bind();
    s1->setUniformValue("objectColor", 1.0f, 0.5f, 0.31f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_Light::typeName()
{
    return "HShaderEngine_Light";
}

void HShaderEngine_Light::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Light);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("lightPos", lightPos);
    s1->setUniformValue("lightColor", lightColor);
    p->renderCube(s1);
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_LightMaterials::HShaderEngine_LightMaterials(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightMaterialsPrivate, parent)
{
}

HShaderEngine_LightMaterials::~HShaderEngine_LightMaterials() = default;

void HShaderEngine_LightMaterials::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_LightMaterials);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_materials.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_materials.fs");
    s1->bind();
    s1->setUniformValue("objectColor", 1.0f, 0.5f, 0.31f);
    s1->setUniformValue("material.ambient", 1.0f, 0.5f, 0.31f);
    s1->setUniformValue("material.diffuse", 1.0f, 0.5f, 0.31f);
    s1->setUniformValue("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
    s1->setUniformValue("material.shininess", 32.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_LightMaterials::typeName()
{
    return "HShaderEngine_Light";
}

void HShaderEngine_LightMaterials::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightMaterials);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.5f;
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("light.position", lightPos);
    s1->setUniformValue("light.ambient", lightAmbient);
    s1->setUniformValue("light.diffuse", lightDiffuse);
    s1->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    p->renderCube(s1);
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_LightMaps::HShaderEngine_LightMaps(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightMapsPrivate, parent)
{
}

HShaderEngine_LightMaps::~HShaderEngine_LightMaps() = default;

void HShaderEngine_LightMaps::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_LightMaps);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_maps.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_maps.fs");
    s1->bind();
    s1->setUniformValue("material.diffuse", 0);
    s1->setUniformValue("material.specular", 1);
    s1->setUniformValue("material.emission", 2);
    s1->setUniformValue("material.shininess", 64.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/container.png");
    addTexture(":/textures/container_specular.png");
    addTexture(":/textures/matrix.jpg");
}

QString HShaderEngine_LightMaps::typeName()
{
    return "HShaderEngine_LightMaps";
}

void HShaderEngine_LightMaps::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightMaps);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.5f;
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    buildTexture();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("light.position", lightPos);
    s1->setUniformValue("light.ambient", lightAmbient);
    s1->setUniformValue("light.diffuse", lightDiffuse);
    s1->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    p->renderCube(s1);
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_LightCasterDirectional::HShaderEngine_LightCasterDirectional(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightCasterDirectionalPrivate, parent)
{
}

HShaderEngine_LightCasterDirectional::~HShaderEngine_LightCasterDirectional() = default;

void HShaderEngine_LightCasterDirectional::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterDirectional);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_caster_directional.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_caster_directional.fs");
    s->bind();
    s->setUniformValue("material.diffuse", 0);
    s->setUniformValue("material.specular", 1);
    s->setUniformValue("material.shininess", 64.0f);
    d->shaders.append(s);
    addTexture(":/textures/container.png");
    addTexture(":/textures/container_specular.png");
}

QString HShaderEngine_LightCasterDirectional::typeName()
{
    return "HShaderEngine_LightCasterDirectional";
}

void HShaderEngine_LightCasterDirectional::setData(QVariantMap value)
{
    Q_D(HShaderEngine_LightCasterDirectional);
    if (value.contains("materialPosition"))
        d->cubePosition = value.value("materialPosition").value<QList<QVector3D>>();
    if (value.contains("lightDirection"))
        d->lightDirection = value.value("lightDirection").value<QVector3D>();
}

void HShaderEngine_LightCasterDirectional::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterDirectional);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.8f;
    auto s = d->shaders.first();
    buildTexture();
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("viewPos", viewPos);
    s->setUniformValue("light.direction", d->lightDirection);
    s->setUniformValue("light.ambient", lightAmbient);
    s->setUniformValue("light.diffuse", lightDiffuse);
    s->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.rotate(secs() * 6, 1.0f, 0.0f);
        model.translate(d->cubePosition.at(i));
        model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
        s->setUniformValue("model", model);
        p->renderCube(s);
    }
}

HShaderEngine_LightCasterPoint::HShaderEngine_LightCasterPoint(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightCasterPointPrivate, parent)
{
}

HShaderEngine_LightCasterPoint::~HShaderEngine_LightCasterPoint() = default;

void HShaderEngine_LightCasterPoint::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterPoint);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_caster_point.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_caster_point.fs");
    s1->bind();
    s1->setUniformValue("material.diffuse", 0);
    s1->setUniformValue("material.specular", 1);
    s1->setUniformValue("material.shininess", 64.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/container.png");
    addTexture(":/textures/container_specular.png");
}

QString HShaderEngine_LightCasterPoint::typeName()
{
    return "HShaderEngine_LightCasterPoint";
}

void HShaderEngine_LightCasterPoint::setData(QVariantMap value)
{
    Q_D(HShaderEngine_LightCasterPoint);
    if (value.contains("materialPosition"))
        d->cubePosition = value.value("materialPosition").value<QList<QVector3D>>();
    if (value.contains("lightAttenuation"))
        d->lightAttenuation = value.value("lightAttenuation").value<QVector3D>();
}

void HShaderEngine_LightCasterPoint::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterPoint);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.8f;
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    buildTexture();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("light.position", lightPos);
    s1->setUniformValue("light.ambient", lightAmbient);
    s1->setUniformValue("light.diffuse", lightDiffuse);
    s1->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    s1->setUniformValue("light.constant", d->lightAttenuation.x());
    s1->setUniformValue("light.linear", d->lightAttenuation.y());
    s1->setUniformValue("light.quadratic", d->lightAttenuation.z());
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.rotate(secs() * 6, 1.0f, 0.0f);
        model.translate(d->cubePosition.at(i));
        model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_LightCasterSpot::HShaderEngine_LightCasterSpot(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightCasterSpotPrivate, parent)
{
}

HShaderEngine_LightCasterSpot::~HShaderEngine_LightCasterSpot() = default;

void HShaderEngine_LightCasterSpot::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterSpot);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_caster_spot.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_caster_spot.fs");
    s->bind();
    s->setUniformValue("material.diffuse", 0);
    s->setUniformValue("material.specular", 1);
    s->setUniformValue("material.shininess", 32.0f);
    d->shaders << s;
    addTexture(":/textures/container.png");
    addTexture(":/textures/container_specular.png");
}

QString HShaderEngine_LightCasterSpot::typeName()
{
    return "HShaderEngine_LightCasterSpot";
}

void HShaderEngine_LightCasterSpot::setData(QVariantMap value)
{
    Q_D(HShaderEngine_LightCasterSpot);
    if (value.contains("materialPosition"))
        d->cubePosition = value.value("materialPosition").value<QList<QVector3D>>();
    if (value.contains("lightAttenuation"))
        d->lightAttenuation = value.value("lightAttenuation").value<QVector3D>();
}

void HShaderEngine_LightCasterSpot::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterSpot);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto viewFront = param.value("viewFront").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.8f;
    auto s = d->shaders.at(0);
    buildTexture();
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("viewPos", viewPos);
    s->setUniformValue("light.position", viewPos);
    s->setUniformValue("light.direction", viewFront);
    s->setUniformValue("light.ambient", lightAmbient);
    s->setUniformValue("light.diffuse", lightDiffuse);
    s->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    s->setUniformValue("light.constant", d->lightAttenuation.x());
    s->setUniformValue("light.linear", d->lightAttenuation.y());
    s->setUniformValue("light.quadratic", d->lightAttenuation.z());
    s->setUniformValue("light.innerCutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
    s->setUniformValue("light.outerCutOff", (GLfloat)cos(qDegreesToRadians(17.5)));
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.rotate(secs() * 6, 1.0f, 0.0f);
        model.translate(d->cubePosition.at(i));
        model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
        s->setUniformValue("model", model);
        p->renderCube(s);
    }
}

HShaderEngine_LightCasterMultiPrivate::HShaderEngine_LightCasterMultiPrivate()
{
    lightPosition << QVector3D( 0.7f,  0.2f,  2.0f)
                  << QVector3D( 2.3f, -3.3f, -4.0f)
                  << QVector3D(-4.0f,  2.0f, -12.0f)
                  << QVector3D( 0.0f,  0.0f, -3.0f);
}

HShaderEngine_LightCasterMulti::HShaderEngine_LightCasterMulti(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightCasterMultiPrivate, parent)
{
}

HShaderEngine_LightCasterMulti::~HShaderEngine_LightCasterMulti() = default;

void HShaderEngine_LightCasterMulti::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterMulti);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_caster_multi.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_caster_multi.fs");
    s1->bind();
    s1->setUniformValue("material.diffuse", 0);
    s1->setUniformValue("material.specular", 1);
    s1->setUniformValue("material.shininess", 32.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/container.png");
    addTexture(":/textures/container_specular.png");
}

QString HShaderEngine_LightCasterMulti::typeName()
{
    return "HShaderEngine_LightCasterMulti";
}

void HShaderEngine_LightCasterMulti::setData(QVariantMap value)
{
    Q_D(HShaderEngine_LightCasterMulti);
    if (value.contains("materialPosition"))
        d->cubePosition = value.value("materialPosition").value<QList<QVector3D>>();
    if (value.contains("lightDirection"))
        d->lightDirection = value.value("lightDirection").value<QVector3D>();
    if (value.contains("lightAttenuation"))
        d->lightAttenuation = value.value("lightAttenuation").value<QVector3D>();
}

void HShaderEngine_LightCasterMulti::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightCasterMulti);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto viewFront = param.value("viewFront").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    buildTexture();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("dirLight.direction", d->lightDirection);
    s1->setUniformValue("dirLight.ambient", lightColor * 0.05f);
    s1->setUniformValue("dirLight.diffuse", lightColor * 0.4f);
    s1->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        s1->setUniformValue(QString("pointLights[%1].position").arg(i).toStdString().c_str(), d->lightPosition[i]);
        s1->setUniformValue(QString("pointLights[%1].ambient").arg(i).toStdString().c_str(), lightColor * 0.05f);
        s1->setUniformValue(QString("pointLights[%1].diffuse").arg(i).toStdString().c_str(), lightColor * 0.8f);
        s1->setUniformValue(QString("pointLights[%1].specular").arg(i).toStdString().c_str(), 1.0f, 1.0f, 1.0f);
        s1->setUniformValue(QString("pointLights[%1].constant").arg(i).toStdString().c_str(), d->lightAttenuation.x());
        s1->setUniformValue(QString("pointLights[%1].linear").arg(i).toStdString().c_str(), d->lightAttenuation.y());
        s1->setUniformValue(QString("pointLights[%1].quadratic").arg(i).toStdString().c_str(), d->lightAttenuation.z());
    }
    s1->setUniformValue("spotLight.position", viewPos);
    s1->setUniformValue("spotLight.direction", viewFront);
    s1->setUniformValue("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    s1->setUniformValue("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    s1->setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
    s1->setUniformValue("spotLight.constant", d->lightAttenuation.x());
    s1->setUniformValue("spotLight.linear", d->lightAttenuation.y());
    s1->setUniformValue("spotLight.quadratic", d->lightAttenuation.z());
    s1->setUniformValue("spotLight.innerCutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
    s1->setUniformValue("spotLight.outerCutOff", (GLfloat)cos(qDegreesToRadians(15.0)));
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.rotate(secs() * 6, 1.0f, 0.0f);
        model.translate(d->cubePosition.at(i));
        model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->lightPosition.at(i));
        model.scale(0.2f);
        s2->setUniformValue("model", model);
        p->renderSphere(s2);
    }
}

HShaderEngine_LightBlinn::HShaderEngine_LightBlinn(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightBlinnPrivate, parent)
{
}

HShaderEngine_LightBlinn::~HShaderEngine_LightBlinn() = default;

void HShaderEngine_LightBlinn::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_LightBlinn);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_blinn.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_blinn.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders << s;
    addTexture(":/textures/wood.png");
}

QString HShaderEngine_LightBlinn::typeName()
{
    return "HShaderEngine_LightBlinn";
}

void HShaderEngine_LightBlinn::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightBlinn);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto blinn = param.value("blinn", false).toBool();
    auto s = d->shaders.at(0);
    buildTexture();
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("viewPos", viewPos);
    s->setUniformValue("lightPos", lightPos);
    s->setUniformValue("blinn", blinn);
    p->renderPlane(s);
}

HShaderEngine_LightGammaPrivate::HShaderEngine_LightGammaPrivate()
{
    lightPosition << QVector3D(-3.0f, 0.0f, 0.0f)
                  << QVector3D(-1.0f, 0.0f, 0.0f)
                  << QVector3D( 1.0f, 0.0f, 0.0f)
                  << QVector3D( 3.0f, 0.0f, 0.0f);
    lightColor << QVector3D(0.25, 0.25, 0.25)
               << QVector3D(0.50, 0.50, 0.50)
               << QVector3D(0.75, 0.75, 0.75)
               << QVector3D(1.00, 1.00, 1.00);
}

HShaderEngine_LightGamma::HShaderEngine_LightGamma(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_LightGammaPrivate, parent)
{
}

HShaderEngine_LightGamma::~HShaderEngine_LightGamma() = default;

void HShaderEngine_LightGamma::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_LightGamma);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_gamma.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_gamma.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders << s;
    addTexture(":/textures/wood.png");
    addTexture(":/textures/wood.png", true);
}

QString HShaderEngine_LightGamma::typeName()
{
    return "HShaderEngine_LightGamma";
}

void HShaderEngine_LightGamma::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_LightGamma);
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto gamma = param.value("gamma", false).toBool();
    auto s = d->shaders.at(0);
    auto i = gamma ? 1 : 0;
    d->textures.at(i)->bind(0);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("viewPos", viewPos);
    s->setUniformValueArray("lightPositions", d->lightPosition.data(), 4);
    s->setUniformValueArray("lightColors", d->lightColor.data(), 4);
    s->setUniformValue("gamma", gamma);
    p->renderPlane(s);
}

HShaderEngine_Model::HShaderEngine_Model(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ModelPrivate, parent)
{
}

HShaderEngine_Model::~HShaderEngine_Model() = default;

void HShaderEngine_Model::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Model);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/model_light.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/model_light.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_Model::typeName()
{
    return "HShaderEngine_Model";
}

void HShaderEngine_Model::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Model);
    QMatrix4x4 model;
    auto fileName = param.value("modelFileName").toString();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto lightAmbient = lightColor * 0.1f;
    auto lightDiffuse = lightColor * 0.5f;
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("light.position", lightPos);
    s1->setUniformValue("light.ambient", lightAmbient);
    s1->setUniformValue("light.diffuse", lightDiffuse);
    s1->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    p->renderModel(s1, fileName);
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_DepthPrivate::HShaderEngine_DepthPrivate()
{
    cubePosition << QVector3D(-1.0f, 0.0f, -1.0f)
                 << QVector3D( 2.0f, 0.0f,  0.0f);
}

HShaderEngine_Depth::HShaderEngine_Depth(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_DepthPrivate, parent)
{
}

HShaderEngine_Depth::~HShaderEngine_Depth() = default;

void HShaderEngine_Depth::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Depth);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/test_depth_view.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/test_depth_view.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders << s;
    addTexture(":/textures/marble.jpg");
    addTexture(":/textures/metal.png");
}

QString HShaderEngine_Depth::typeName()
{
    return "HShaderEngine_Depth";
}

void HShaderEngine_Depth::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Depth);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto linearize = param.value("linearize", true).toBool();
    auto s = d->shaders.at(0);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("linearize", linearize);
    d->textures.at(0)->bind(0);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        s->setUniformValue("model", model);
        p->renderCube(s);
    }
    d->textures.at(1)->bind(0);
    model.setToIdentity();
    s->setUniformValue("model", model);
    p->renderPlane(s);
}

HShaderEngine_StencilPrivate::HShaderEngine_StencilPrivate()
{
    cubePosition << QVector3D(-1.0f, 1.0f, -1.0f)
                 << QVector3D( 2.0f, 1.0f,  0.0f);
}

HShaderEngine_Stencil::HShaderEngine_Stencil(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_StencilPrivate, parent)
{
}

HShaderEngine_Stencil::~HShaderEngine_Stencil() = default;

void HShaderEngine_Stencil::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Stencil);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/texture_obj.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/texture_obj.fs");
    s1->bind();
    s1->setUniformValue("texture1", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/test_stencil_single_color.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/test_stencil_single_color.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/marble.jpg");
    addTexture(":/textures/metal.png");
    d->funcs->glEnable(GL_STENCIL_TEST);
    d->funcs->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

QString HShaderEngine_Stencil::typeName()
{
    return "HShaderEngine_Stencil";
}

void HShaderEngine_Stencil::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Stencil);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    d->funcs->glClear(GL_STENCIL_BUFFER_BIT);
    // draw plane
    d->textures.at(1)->bind(0);
    d->funcs->glStencilMask(0x00);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    p->renderPlane(s1);
    // draw box
    d->textures.at(0)->bind(0);
    d->funcs->glStencilFunc(GL_ALWAYS, 1, 0xFF);
    d->funcs->glStencilMask(0xFF);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    // draw edge
    d->funcs->glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    d->funcs->glStencilMask(0x00);
    d->funcs->glDisable(GL_DEPTH_TEST);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        model.scale(1.1);
        s2->setUniformValue("model", model);
        p->renderCube(s2);
    }
    // restore
    d->funcs->glStencilMask(0xFF);
    d->funcs->glStencilFunc(GL_ALWAYS, 0, 0xFF);
    d->funcs->glEnable(GL_DEPTH_TEST);
}

HShaderEngine_BlendingPrivate::HShaderEngine_BlendingPrivate()
{
    cubePosition << QVector3D(-2.0f, 1.0f, -2.0f)
                 << QVector3D( 4.0f, 1.0f,  0.0f);
    windowPosition << QVector3D(-1.5f, 1.0f, -0.48f)
                   << QVector3D( 1.5f, 1.0f,  0.51f)
                   << QVector3D( 0.0f, 1.0f,  0.7f)
                   << QVector3D(-0.3f, 1.0f, -2.3f)
                   << QVector3D( 0.5f, 1.0f, -0.6f);
}

HShaderEngine_Blending::HShaderEngine_Blending(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_BlendingPrivate, parent)
{
}

HShaderEngine_Blending::~HShaderEngine_Blending() = default;

void HShaderEngine_Blending::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Blending);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/blending2.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/blending2.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders << s;
    addTexture(":/textures/marble.jpg");
    addTexture(":/textures/metal.png");
    addTexture(":/textures/window.png");
    d->funcs->glEnable(GL_BLEND);
    d->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

QString HShaderEngine_Blending::typeName()
{
    return "HShaderEngine_Blending";
}

void HShaderEngine_Blending::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Blending);
    QMap<float, QVector3D> map;
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto s = d->shaders.at(0);
    for (int i = 0; i < d->windowPosition.size(); i++)
    {
        auto distance = -1.0 * viewPos.distanceToPoint(d->windowPosition.at(i));
        map[distance] = d->windowPosition[i];
    }
    // draw plane
    d->textures.at(1)->bind(0);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("model", model);
    p->renderPlane(s);
    // draw box
    d->textures.at(0)->bind(0);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        s->setUniformValue("model", model);
        p->renderCube(s);
    }
    // draw windows
    d->textures.at(2)->bind(0);
    for (auto it : map)
    {
        model.setToIdentity();
        model.translate(it);
        s->setUniformValue("model", model);
        p->renderRect(s);
    }
}

HShaderEngine_FramebufferPrivate::HShaderEngine_FramebufferPrivate()
{
    cubePosition << QVector3D(-2.0f, 1.0f, -2.0f)
                 << QVector3D( 4.0f, 1.0f,  0.0f);
}

HShaderEngine_Framebuffer::HShaderEngine_Framebuffer(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_FramebufferPrivate, parent)
{
}

HShaderEngine_Framebuffer::~HShaderEngine_Framebuffer() = default;

void HShaderEngine_Framebuffer::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Framebuffer);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/texture_obj.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/texture_obj.fs");
    s1->bind();
    s1->setUniformValue("texture1", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/framebuffer.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/framebuffer.fs");
    s2->bind();
    s2->setUniformValue("texture1", 0);
    d->shaders << s1 << s2;
    addTexture(":/textures/marble.jpg");
    addTexture(":/textures/metal.png");
}

QString HShaderEngine_Framebuffer::typeName()
{
    return "HShaderEngine_Framebuffer";
}

void HShaderEngine_Framebuffer::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Framebuffer);
    QMatrix4x4 model;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    if (d->fbo.isNull() || d->fbo->size() != size)
        d->fbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::Depth));
    // draw into framebuffer
    d->fbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->textures.at(1)->bind(0);
    model.setToIdentity();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    p->renderPlane(s1);
    d->textures.at(0)->bind(0);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    d->fbo->release();
    // draw as normal
    d->textures.at(1)->bind(0);
    model.setToIdentity();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    p->renderPlane(s1);
    d->textures.at(0)->bind(0);
    for (int i = 0; i < d->cubePosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    // now draw the mirror quad with screen texture
    d->funcs->glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->texture());
    s2->bind();
    model.setToIdentity();
    model.translate(0.7, 0.7);
    model.scale(0.3);
    s2->setUniformValue("model", model);
    s2->setUniformValue("processing", 1);
    p->renderScreen(s2);
    d->funcs->glEnable(GL_DEPTH_TEST);
}

HShaderEngine_Cubemaps::HShaderEngine_Cubemaps(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_CubemapsPrivate, parent)
{
}

HShaderEngine_Cubemaps::~HShaderEngine_Cubemaps() = default;

void HShaderEngine_Cubemaps::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Cubemaps);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/environment_maps.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/environment_maps.fs");
    s1->bind();
    s1->setUniformValue("texture1", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/skybox.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/skybox.fs");
    s2->bind();
    s2->setUniformValue("texture1", 0);
    d->shaders << s1 << s2;
    addTexture(QStringList() << ":/textures/skybox/right.jpg"
                             << ":/textures/skybox/left.jpg"
                             << ":/textures/skybox/top.jpg"
                             << ":/textures/skybox/bottom.jpg"
                             << ":/textures/skybox/front.jpg"
                             << ":/textures/skybox/back.jpg");
}

QString HShaderEngine_Cubemaps::typeName()
{
    return "HShaderEngine_Cubemaps";
}

void HShaderEngine_Cubemaps::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Cubemaps);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    d->textures.at(0)->bind(0);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    p->renderCube(s1);
    view = QMatrix4x4(view.toGenericMatrix<3, 3>());    // remove translation from the view matrix
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    p->renderSkybox(s2);
}

HShaderEngine_UboPrivate::HShaderEngine_UboPrivate()
{
    funcs->glGenBuffers(1, &ubo);
    funcs->glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    // 因为我们要绑定的是两个简单的4x4矩阵，所以声明8个4维向量的大小即可。
    // 为什么不用sizeof(QMatrix4x4)呢，因为
    // sizeof(QMatrix4x4) = 68; 多了4个字节应该是文件头之类的玩意吧，惊喜吧
    // sizeof(QVector4D) = 16;
    // glBufferData(GL_UNIFORM_BUFFER, sizeof(QMatrix4x4) * 2, nullptr, GL_STATIC_DRAW);
    funcs->glBufferData(GL_UNIFORM_BUFFER, sizeof(QVector4D) * 4 * 2, nullptr, GL_STATIC_DRAW);
    funcs->glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    funcs->glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, sizeof(QVector4D) * 4 * 2);
    cubePosition << QVector3D(-0.75f,  0.75f, 0.0f)
                 << QVector3D( 0.75f,  0.75f, 0.0f)
                 << QVector3D( 0.75f, -0.75f, 0.0f)
                 << QVector3D(-0.75f, -0.75f, 0.0f);
}

void HShaderEngine_UboPrivate::bindUniformBlock(GLuint id, const char *name, int block)
{
    auto index = funcs->glGetUniformBlockIndex(id, name);
    funcs->glUniformBlockBinding(id, index, block);
}

HShaderEngine_Ubo::HShaderEngine_Ubo(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_UboPrivate, parent)
{
}

HShaderEngine_Ubo::~HShaderEngine_Ubo() = default;

void HShaderEngine_Ubo::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Ubo);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ubo.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ubo_red.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ubo.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ubo_green.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ubo.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ubo_blue.fs");
    s3->bind();
    auto s4 = new QOpenGLShaderProgram(this);
    s4->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ubo.vs");
    s4->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ubo_yellow.fs");
    s4->bind();
    d->shaders << s1 << s2 << s3 << s4;
    for (auto s : d->shaders)
        d->bindUniformBlock(s->programId(), "Matrices", 0);
}

QString HShaderEngine_Ubo::typeName()
{
    return "HShaderEngine_Ubo";
}

void HShaderEngine_Ubo::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Ubo);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    d->funcs->glBindBuffer(GL_UNIFORM_BUFFER, d->ubo);
    d->funcs->glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(QVector4D) * 4, projection.data());
    d->funcs->glBufferSubData(GL_UNIFORM_BUFFER, sizeof(QVector4D) * 4, sizeof(QVector4D) * 4, view.data());
    d->funcs->glBindBuffer(GL_UNIFORM_BUFFER, 0);
    for (int i = 0; i < d->shaders.size(); i++)
    {
        auto s = d->shaders.at(i);
        model.setToIdentity();
        model.translate(d->cubePosition.at(i));
        model.scale(0.5);
        s->bind();
        d->shaders.at(i)->setUniformValue("model", model);
        p->renderCube(s);
    }
}

HShaderEngine_GeometryHousePrivate::HShaderEngine_GeometryHousePrivate()
{
    GLfloat points[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };

    QOpenGLVertexArrayObject::Binder binder(&vao);
    auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(points, sizeof(points));
    funcs->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    funcs->glEnableVertexAttribArray(0);
    funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    funcs->glEnableVertexAttribArray(1);
}

HShaderEngine_GeometryHouse::HShaderEngine_GeometryHouse(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_GeometryHousePrivate, parent)
{
}

HShaderEngine_GeometryHouse::~HShaderEngine_GeometryHouse() = default;

void HShaderEngine_GeometryHouse::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_GeometryHouse);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/geometry_house.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/geometry_house.fs");
    s->addShaderFromSourceFile(QOpenGLShader::Geometry,   ":/glsl/geometry_house.gs");
    d->shaders << s;
}

QString HShaderEngine_GeometryHouse::typeName()
{
    return "HShaderEngine_GeometryHouse";
}

void HShaderEngine_GeometryHouse::draw(HGeometryEngine *, QVariantMap /*param*/)
{
    Q_D(HShaderEngine_GeometryHouse);
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    auto s = d->shaders.at(0);
    s->bind();
    d->funcs->glDrawArrays(GL_POINTS, 0, 4);
}

HShaderEngine_GeometryExplode::HShaderEngine_GeometryExplode(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_GeometryExplodePrivate, parent)
{
}

HShaderEngine_GeometryExplode::~HShaderEngine_GeometryExplode() = default;

void HShaderEngine_GeometryExplode::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_GeometryExplode);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/geometry_explode.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/geometry_explode.fs");
    s->addShaderFromSourceFile(QOpenGLShader::Geometry,   ":/glsl/geometry_explode.gs");
    d->shaders << s;
}

QString HShaderEngine_GeometryExplode::typeName()
{
    return "HShaderEngine_GeometryExplode";
}

void HShaderEngine_GeometryExplode::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_GeometryExplode);
    QMatrix4x4 model;
    auto fileName = param.value("modelFileName").toString();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s = d->shaders.at(0);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    s->setUniformValue("model", model);
    s->setUniformValue("time", (float)secs());
    p->renderModel(s, fileName);
}

HShaderEngine_GeometryNormal::HShaderEngine_GeometryNormal(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_GeometryNormalPrivate, parent)
{
}

HShaderEngine_GeometryNormal::~HShaderEngine_GeometryNormal() = default;

void HShaderEngine_GeometryNormal::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_GeometryNormal);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/model_show.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/model_show.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/geometry_normal.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/geometry_normal.fs");
    s2->addShaderFromSourceFile(QOpenGLShader::Geometry,   ":/glsl/geometry_normal.gs");
    d->shaders << s1 << s2;
}

QString HShaderEngine_GeometryNormal::typeName()
{
    return "HShaderEngine_GeometryNormal";
}

void HShaderEngine_GeometryNormal::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_GeometryNormal);
    QMatrix4x4 model;
    auto fileName = param.value("modelFileName").toString();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    p->renderModel(s1, fileName);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    p->renderModel(s2, fileName);
}

HShaderEngine_InstancingPrivate::HShaderEngine_InstancingPrivate()
{
    float points[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    QVector<QVector2D> translations(100);
    int index = 0;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            translations[index++] = QVector2D(x / 10.0 + 0.1, y / 10.0 + 0.1);
        }
    }

    funcs = QOpenGLContext::currentContext()->extraFunctions();
    QOpenGLVertexArrayObject::Binder binder(&vao);
    auto vbo1 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo1->create();
    vbo1->bind();
    vbo1->allocate(points, sizeof(points));
    funcs->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    funcs->glEnableVertexAttribArray(0);
    funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    funcs->glEnableVertexAttribArray(1);
    auto vbo2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo2->create();
    vbo2->bind();
    vbo2->allocate(&translations[0], sizeof(QVector2D) * 100);
    funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    funcs->glEnableVertexAttribArray(2);
    funcs->glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
}

HShaderEngine_Instancing::HShaderEngine_Instancing(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_InstancingPrivate, parent)
{
}

HShaderEngine_Instancing::~HShaderEngine_Instancing() = default;

void HShaderEngine_Instancing::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Instancing);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/instancing.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/instancing.fs");
    d->shaders << s;
}

QString HShaderEngine_Instancing::typeName()
{
    return "HShaderEngine_Instancing";
}

void HShaderEngine_Instancing::draw(HGeometryEngine *, QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Instancing);
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    auto s = d->shaders.at(0);
    s->bind();
    d->funcs->glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}

HShaderEngine_InstancingModelPrivate::HShaderEngine_InstancingModelPrivate()
{

}

HShaderEngine_InstancingModel::HShaderEngine_InstancingModel(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_InstancingModelPrivate, parent)
{
}

HShaderEngine_InstancingModel::~HShaderEngine_InstancingModel() = default;

void HShaderEngine_InstancingModel::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_InstancingModel);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/model_instance.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/model_show.fs");
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/model_show.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/model_show.fs");
    d->shaders << s1 << s2;

    // generate a large list of semi-random model transformation matrices
    int amount = 10000;
    float radius = 50.0;
    float offset = 2.5f;
    QRandomGenerator random;
    QVector<QMatrix4x4> models(amount);
    for (int i = 0; i < amount; i++)
    {
        QMatrix4x4 model;
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = 360.0 * i / amount;
        float x = sin(angle) * radius + random.bounded(2 * offset) - offset;
        float y = (random.bounded(2 * offset) - offset) * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        float z = cos(angle) * radius + random.bounded(2 * offset) - offset;
        model.translate(x, y, z);
        // 2. scale: Scale between 0.05 and 0.25f
        model.scale(random.bounded(0.2) + 0.05);
        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        model.rotate(random.bounded(360.0), 0.4f, 0.6f, 0.8f);
        // 4. now add to list of matrices
        models[i] = model;
    }
    d->model1 = new HOpenGLModel(this);
    d->model1->load("objects\\rock\\rock.obj");
    d->model1->setInstancedMatrix(3, models);
    d->model2 = new HOpenGLModel(this);
    d->model2->load("objects\\planet\\planet.obj");
}

QString HShaderEngine_InstancingModel::typeName()
{
    return "HShaderEngine_InstancingModel";
}

void HShaderEngine_InstancingModel::draw(HGeometryEngine *, QVariantMap param)
{
    Q_D(HShaderEngine_InstancingModel);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    d->model1->draw(s1, 10000);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    d->model2->draw(s2);
}

HShaderEngine_AntiAliasingPrivate::HShaderEngine_AntiAliasingPrivate()
{
    format1.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format1.setMipmap(true);
    format1.setSamples(4);
    format1.setTextureTarget(GL_TEXTURE_2D);
    format1.setInternalTextureFormat(GL_RGBA32F_ARB);
    format2.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format2.setMipmap(true);
    format2.setTextureTarget(GL_TEXTURE_2D);
    format2.setInternalTextureFormat(GL_RGBA32F_ARB);
}

HShaderEngine_AntiAliasing::HShaderEngine_AntiAliasing(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_AntiAliasingPrivate, parent)
{
}

HShaderEngine_AntiAliasing::~HShaderEngine_AntiAliasing() = default;

void HShaderEngine_AntiAliasing::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_AntiAliasing);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/anti_aliasing.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/anti_aliasing.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/framebuffer.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/framebuffer.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_AntiAliasing::typeName()
{
    return "HShaderEngine_AntiAliasing";
}

void HShaderEngine_AntiAliasing::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_AntiAliasing);
    QMatrix4x4 model;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    if (d->fbo1.isNull() || d->fbo1->size() != size)
        d->fbo1.reset(new QOpenGLFramebufferObject(size, d->format1));
    if (d->fbo2.isNull() || d->fbo2->size() != size)
        d->fbo2.reset(new QOpenGLFramebufferObject(size, d->format2));
    // draw into framebuffer
    d->fbo1->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    p->renderCube(s1);
    QOpenGLFramebufferObject::blitFramebuffer(d->fbo2.data(), d->fbo1.data(), GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT, GL_NEAREST);
    d->fbo1->release();
    d->funcs->glDisable(GL_DEPTH_TEST);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo2->texture());
    s2->bind();
    s2->setUniformValue("model", model);
    s2->setUniformValue("processing", 0);
    p->renderScreen(s2);
    d->funcs->glEnable(GL_DEPTH_TEST);
}

HShaderEngine_ShadowDepth::HShaderEngine_ShadowDepth(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ShadowDepthPrivate, parent)
{
}

HShaderEngine_ShadowDepth::~HShaderEngine_ShadowDepth() = default;

void HShaderEngine_ShadowDepth::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_ShadowDepth);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/shadow_mapping_depth.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/shadow_mapping_depth.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/debug_quad_depth.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/debug_quad_depth.fs");
    s2->bind();
    s2->setUniformValue("texture1", 0);
    d->shaders << s1 << s2;
    addTexture(":/textures/wood.png");
    d->fbo = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(1024, 1024, QOpenGLFramebufferObject::Depth));
}

QString HShaderEngine_ShadowDepth::typeName()
{
    return "HShaderEngine_ShadowDepth";
}

void HShaderEngine_ShadowDepth::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_ShadowDepth);
    QMatrix4x4 lightProjection, lightView, lightSpaceMatrix;
    auto nearPlane = 1.0f;
    auto farPlane = 7.5f;
    auto size = param.value("size").toSize();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    d->funcs->glViewport(0, 0, d->fbo->width(), d->fbo->height());
    d->fbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->textures.at(0)->bind();
    s1->bind();
    s1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
    p->renderScene(s1);
    d->fbo->release();
    d->funcs->glViewport(0, 0, size.width(), size.height());
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->texture());
    s2->bind();
    s2->setUniformValue("nearPlane", nearPlane);
    s2->setUniformValue("farPlane", farPlane);
    p->renderScreen(s2);
}

HShaderEngine_ShadowMapping::HShaderEngine_ShadowMapping(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ShadowMappingPrivate, parent)
{
}

HShaderEngine_ShadowMapping::~HShaderEngine_ShadowMapping() = default;

void HShaderEngine_ShadowMapping::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_ShadowMapping);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/shadow_mapping2.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/shadow_mapping2.fs");
    s1->bind();
    s1->setUniformValue("diffuseTexture", 0);
    s1->setUniformValue("shadowTexture", 1);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/shadow_mapping_depth.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/shadow_mapping_depth.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/wood.png");
    d->fbo = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(4096, 4096, QOpenGLFramebufferObject::Depth));
}

QString HShaderEngine_ShadowMapping::typeName()
{
    return "HShaderEngine_ShadowMapping";
}

void HShaderEngine_ShadowMapping::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_ShadowMapping);
    QMatrix4x4 lightProjection, lightView, lightSpaceMatrix;
    auto nearPlane = 1.0f;
    auto farPlane = 7.5f;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    d->funcs->glViewport(0, 0, d->fbo->width(), d->fbo->height());
    d->fbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->textures.at(0)->bind();
    s2->bind();
    s2->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
    p->renderScene(s2);
    d->fbo->release();
    d->funcs->glViewport(0, 0, size.width(), size.height());
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->textures.at(0)->textureId());
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->texture());
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("lightPos", lightPos);
    s1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
    p->renderScene(s1);
}

HShaderEngine_ShadowPoint::HShaderEngine_ShadowPoint(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ShadowPointPrivate, parent)
{
}

HShaderEngine_ShadowPoint::~HShaderEngine_ShadowPoint()
{
    Q_D(HShaderEngine_ShadowPoint);
    if (d->fbo != 0)
        d->funcs->glDeleteFramebuffers(1, &d->fbo);
    if (d->texture != 0)
        d->funcs->glDeleteTextures(1, &d->texture);
}

void HShaderEngine_ShadowPoint::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_ShadowPoint);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/shadow_point2.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/shadow_point2.fs");
    s1->bind();
    s1->setUniformValue("diffuseTexture", 0);
    s1->setUniformValue("shadowTexture", 1);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/shadow_point_depth.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/shadow_point_depth.fs");
    s2->addShaderFromSourceFile(QOpenGLShader::Geometry,    ":/glsl/shadow_point_depth.gs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/wood.png");
    // 无法使用
    // d->fbo = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(4096, 4096, QOpenGLFramebufferObject::Depth, QOpenGLTexture::TargetCubeMap));
    d->funcs->glGenTextures(1, &d->texture);
    d->funcs->glBindTexture(GL_TEXTURE_CUBE_MAP, d->texture);
    for (unsigned int i = 0; i < 6; ++i)
        d->funcs->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, d->shadowWidth, d->shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    d->funcs->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    d->funcs->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    d->funcs->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    d->funcs->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    d->funcs->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    d->funcs->glGenFramebuffers(1, &d->fbo);
    d->funcs->glBindFramebuffer(GL_FRAMEBUFFER, d->fbo);
    d->funcs->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, d->texture, 0);
    d->funcs->glReadBuffer(GL_NONE);
    d->funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

QString HShaderEngine_ShadowPoint::typeName()
{
    return "HShaderEngine_ShadowPoint";
}

void HShaderEngine_ShadowPoint::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_ShadowPoint);
    QMatrix4x4 shadowProjection;
    QVector<QMatrix4x4> shadowView(6), shadowTransforms(6);
    QVector3D lightPos;
    auto nearPlane = 1.0f;
    auto farPlane = 25.0f;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto shadows = param.value("shadows", false).toBool();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    lightPos.setZ(sin(secs() * 0.5) * 3.0);
    shadowProjection.perspective(90.0f, 1.0 * d->shadowWidth / d->shadowHeight, nearPlane, farPlane);
    shadowView[0].lookAt(lightPos, lightPos + QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    shadowView[1].lookAt(lightPos, lightPos + QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    shadowView[2].lookAt(lightPos, lightPos + QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    shadowView[3].lookAt(lightPos, lightPos + QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    shadowView[4].lookAt(lightPos, lightPos + QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    shadowView[5].lookAt(lightPos, lightPos + QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    for (int i = 0; i < 6; i++)
        shadowTransforms[i] = shadowProjection * shadowView[i];

    d->funcs->glViewport(0, 0, d->shadowWidth, d->shadowHeight);
    d->funcs->glBindFramebuffer(GL_FRAMEBUFFER, d->fbo);
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    s2->bind();
    s2->setUniformValueArray("shadowMatrices", shadowTransforms.data(), 6);
    s2->setUniformValue("farPlane", farPlane);
    s2->setUniformValue("lightPos", lightPos);
    p->renderRoom(s2);
    d->funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    d->funcs->glViewport(0, 0, size.width(), size.height());
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("lightPos", lightPos);
    s1->setUniformValue("farPlane", farPlane);
    s1->setUniformValue("shadows", shadows);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->textures.at(0)->textureId());
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_CUBE_MAP, d->texture);
    p->renderRoom(s1);
}

HShaderEngine_NormalMapping::HShaderEngine_NormalMapping(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_NormalMappingPrivate, parent)
{
}

HShaderEngine_NormalMapping::~HShaderEngine_NormalMapping() = default;

void HShaderEngine_NormalMapping::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_NormalMapping);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/normal_mapping.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/normal_mapping.fs");
    s1->bind();
    s1->setUniformValue("texture_diffuse1", 0);
    s1->setUniformValue("texture_normal1", 1);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/brickwall.jpg");
    addTexture(":/textures/brickwall_normal.jpg");
}

QString HShaderEngine_NormalMapping::typeName()
{
    return "HShaderEngine_NormalMapping";
}

void HShaderEngine_NormalMapping::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_NormalMapping);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    buildTexture();
    model.rotate(secs() * -10.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("lightPos", lightPos);
    s1->setUniformValue("viewPos", viewPos);
    p->renderQuad(s1);
    model.setToIdentity();
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
    p->renderSphere(s2);
}

HShaderEngine_ParallaxMapping::HShaderEngine_ParallaxMapping(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_ParallaxMappingPrivate, parent)
{
}

HShaderEngine_ParallaxMapping::~HShaderEngine_ParallaxMapping() = default;

void HShaderEngine_ParallaxMapping::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_ParallaxMapping);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/parallax_mapping.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/parallax_mapping3.fs");
    s1->bind();
    s1->setUniformValue("texture_diffuse1", 0);
    s1->setUniformValue("texture_normal1", 1);
    s1->setUniformValue("texture_depth1", 2);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/bricks2.jpg");
    addTexture(":/textures/bricks2_normal.jpg");
    addTexture(":/textures/bricks2_disp.jpg");
}

QString HShaderEngine_ParallaxMapping::typeName()
{
    return "HShaderEngine_ParallaxMapping";
}

void HShaderEngine_ParallaxMapping::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_ParallaxMapping);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPos = param.value("lightPos").value<QVector3D>();
    auto lightColor = param.value("lightColor").value<QVector3D>();
    auto heightScale = param.value("heightScale", 1.0).toFloat();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    buildTexture();
    model.rotate(secs() * -10.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("lightPos", lightPos);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("heightScale", heightScale);
    p->renderQuad(s1);
    model.setToIdentity();
    model.translate(lightPos);
    model.scale(0.2);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", lightColor);
    p->renderSphere(s2);
}

HShaderEngine_HDRPrivate::HShaderEngine_HDRPrivate()
{
    lightPosition << QVector3D( 0.0f,  0.0f, 49.5f)
                  << QVector3D(-1.4f, -1.9f, 9.0f)
                  << QVector3D( 0.0f, -1.8f, 4.0f)
                  << QVector3D( 0.8f, -1.7f, 6.0f);
    lightColor << QVector3D(200.0f, 200.0f, 200.0f)
               << QVector3D(0.1f, 0.0f, 0.0f)
               << QVector3D(0.0f, 0.0f, 0.2f)
               << QVector3D(0.0f, 0.1f, 0.0f);
}

HShaderEngine_HDR::HShaderEngine_HDR(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_HDRPrivate, parent)
{
}

HShaderEngine_HDR::~HShaderEngine_HDR() = default;

void HShaderEngine_HDR::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_HDR);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/lighting.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/lighting.fs");
    s1->bind();
    s1->setUniformValue("texture1", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/hdr.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/hdr.fs");
    s2->bind();
    s2->setUniformValue("texture1", 0);
    d->shaders << s1 << s2;
    addTexture(":/textures/wood.png", true);
}

QString HShaderEngine_HDR::typeName()
{
    return "HShaderEngine_HDR";
}

void HShaderEngine_HDR::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_HDR);
    QMatrix4x4 model;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto hdr = param.value("hdr", true).toBool();
    auto exposure = param.value("exposure", 1.0).toFloat();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    model.translate(0.0f, 0.0f, 25.0f);
    model.scale(2.5f, 2.5f, 27.5f);

    if (d->fbo.isNull() || d->fbo->size() != size)
        d->fbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::Depth, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));
    d->fbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->textures.at(0)->bind(0);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("inverseNormals", true);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        s1->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), d->lightPosition[i]);
        s1->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), d->lightColor[i]);
    }
    p->renderCube(s1);
    d->fbo->release();
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->texture());
    s2->bind();
    s2->setUniformValue("hdr", hdr);
    s2->setUniformValue("exposure", exposure);
    p->renderScreen(s2);
}

HShaderEngine_BloomPrivate::HShaderEngine_BloomPrivate()
{
    lightPosition << QVector3D( 0.0f, 0.5f,  1.5f)
                  << QVector3D(-4.0f, 0.5f, -3.0f)
                  << QVector3D( 3.0f, 0.5f,  1.0f)
                  << QVector3D(-0.8f, 2.4f, -1.0f);
    lightColor << QVector3D( 5.0f, 5.0f,  5.0f)
               << QVector3D(10.0f, 0.0f,  0.0f)
               << QVector3D( 0.0f, 0.0f, 15.0f)
               << QVector3D( 0.0f, 5.0f, 0.0f);
    cubeModel.resize(6);
    cubeModel[0].translate(0.0f, 1.5f, 0.0);
    cubeModel[0].scale(0.25f);
    cubeModel[1].translate(2.0f, 0.0f, 1.0);
    cubeModel[1].scale(0.25f);
    cubeModel[2].translate(-1.0f, -1.0f, 2.0);
    cubeModel[2].rotate(60.0f, 1.0, 0.0, 1.0);
    cubeModel[3].translate(0.0f, 2.7f, 4.0);
    cubeModel[3].rotate(23.0f, 1.0, 0.0, 1.0);
    cubeModel[3].scale(0.625);
    cubeModel[4].translate(-2.0f, 1.0f, -3.0);
    cubeModel[4].rotate(124.0f, 1.0, 0.0, 1.0);
    cubeModel[5].translate(-3.0f, 0.0f, 0.0);
    cubeModel[5].scale(0.25f);
}

HShaderEngine_Bloom::HShaderEngine_Bloom(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_BloomPrivate, parent)
{
}

HShaderEngine_Bloom::~HShaderEngine_Bloom() = default;

void HShaderEngine_Bloom::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Bloom);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/bloom.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/bloom.fs");
    s1->bind();
    s1->setUniformValue("texture1", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/bloom.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/bloom_light.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/gaussian_blur.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/gaussian_blur.fs");
    s3->bind();
    s3->setUniformValue("texture1", 0);
    auto s4 = new QOpenGLShaderProgram(this);
    s4->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/bloom_final.vs");
    s4->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/bloom_final.fs");
    s4->bind();
    s4->setUniformValue("scene", 0);
    s4->setUniformValue("bloomBlur", 1);
    d->shaders << s1 << s2 << s3 << s4;
    addTexture(":/textures/wood.png", true);
    addTexture(":/textures/container.png", true);
}

QString HShaderEngine_Bloom::typeName()
{
    return "HShaderEngine_Bloom";
}

void HShaderEngine_Bloom::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_Bloom);
    QMatrix4x4 model;
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto bloom = param.value("bloom", true).toBool();
    auto exposure = param.value("exposure", 1.0).toFloat();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    auto s3 = d->shaders.at(2);
    auto s4 = d->shaders.at(3);

    if (d->hdrFbo.isNull() || d->hdrFbo->size() != size)
    {
        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        d->hdrFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::Depth, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));
        d->hdrFbo->addColorAttachment(size, QOpenGLTexture::RGBA16F);
        d->funcs->glDrawBuffers(2, attachments);
    }
    if (d->pingFbo.isNull() || d->pingFbo->size() != size)
        d->pingFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::NoAttachment, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));
    if (d->pongFbo.isNull() || d->pongFbo->size() != size)
        d->pongFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::NoAttachment, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));

    // 1. render scene into floating point framebuffer
    d->hdrFbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->textures.at(0)->bind(0);
    model.translate(0.0f, -1.0f, 0.0f);
    model.scale(10.0f, 1.0f, 10.0f);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("model", model);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        s1->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), d->lightPosition[i]);
        s1->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), d->lightColor[i]);
    }
    p->renderCube(s1);
    d->textures.at(1)->bind(0);
    for (auto model : d->cubeModel)
    {
        s1->setUniformValue("model", model);
        p->renderCube(s1);
    }
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->lightPosition[i]);
        model.scale(0.25f);
        s2->setUniformValue("model", model);
        s2->setUniformValue("lightColor", d->lightColor[i]);
        p->renderSphere(s2);
    }
    d->hdrFbo->release();

    // 2. blur bright fragments with two-pass Gaussian Blur
    bool first = true;
    bool horizontal = true;
    int amount = 10;
    s3->bind();
    d->funcs->glActiveTexture(GL_TEXTURE0);
    for (int i = 0; i < amount; i++)
    {
        if (horizontal)
        {
            d->pingFbo->bind();
            d->funcs->glBindTexture(GL_TEXTURE_2D, first ? d->hdrFbo->textures().at(1) : d->pongFbo->texture());
        }
        else
        {
            d->pongFbo->bind();
            d->funcs->glBindTexture(GL_TEXTURE_2D, d->pingFbo->texture());
        }
        s3->setUniformValue("horizontal", horizontal);
        p->renderScreen(s3);
        horizontal = !horizontal;
        first = false;
    }
    d->pongFbo->release();

    // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->hdrFbo->texture());
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->pongFbo->texture());
    s4->bind();
    s4->setUniformValue("bloom", bloom);
    s4->setUniformValue("exposure", exposure);
    p->renderScreen(s4);
}

HShaderEngine_DeferredShadingPrivate::HShaderEngine_DeferredShadingPrivate()
{
    objectPosition << QVector3D(-3.0,  -0.5, -3.0)
                   << QVector3D( 0.0,  -0.5, -3.0)
                   << QVector3D( 3.0,  -0.5, -3.0)
                   << QVector3D(-3.0,  -0.5,  0.0)
                   << QVector3D( 0.0,  -0.5,  0.0)
                   << QVector3D( 3.0,  -0.5,  0.0)
                   << QVector3D(-3.0,  -0.5,  3.0)
                   << QVector3D( 0.0,  -0.5,  3.0)
                   << QVector3D( 3.0,  -0.5,  3.0);

    QRandomGenerator random(13);
    for (int i = 0; i < 32; i++)
    {
        float xPos = random.generateDouble() * 6.0 - 3.0;
        float yPos = random.generateDouble() * 6.0 - 4.0;
        float zPos = random.generateDouble() * 6.0 - 3.0;
        lightPosition << QVector3D(xPos, yPos, zPos);
        float rColor = random.generateDouble() * 0.5 + 0.5;
        float gColor = random.generateDouble() * 0.5 + 0.5;
        float bColor = random.generateDouble() * 0.5 + 0.5;
        lightColor << QVector3D(rColor, gColor, bColor);
    }
}

HShaderEngine_DeferredShading::HShaderEngine_DeferredShading(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_DeferredShadingPrivate, parent)
{
}

HShaderEngine_DeferredShading::~HShaderEngine_DeferredShading() = default;

void HShaderEngine_DeferredShading::initialize(QVariantMap param)
{
    Q_D(HShaderEngine_DeferredShading);
    if (d->initialized)
        return;
    d->initialized = true;
    setData(param);
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/deferred_shading_gbuffer.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/deferred_shading_gbuffer.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/deferred_shading.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/deferred_shading.fs");
    s2->bind();
    s2->setUniformValue("gPosition", 0);
    s2->setUniformValue("gNormal", 1);
    s2->setUniformValue("gAlbedoSpec", 2);
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s3->bind();
    d->shaders << s1 << s2 << s3;
}

QString HShaderEngine_DeferredShading::typeName()
{
    return "HShaderEngine_DeferredShading";
}

void HShaderEngine_DeferredShading::setData(QVariantMap value)
{
    Q_D(HShaderEngine_DeferredShading);
    if (value.contains("lightAttenuation"))
        d->lightAttenuation = value.value("lightAttenuation").value<QVector3D>();
}

void HShaderEngine_DeferredShading::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_DeferredShading);
    QMatrix4x4 model;
    auto fileName = param.value("modelFileName").toString();
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    auto s3 = d->shaders.at(2);

    if (d->fbo.isNull() || d->fbo->size() != size)
    {
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        d->fbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::Depth, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));
        d->fbo->addColorAttachment(size, QOpenGLTexture::RGBA16F);
        d->fbo->addColorAttachment(size, QOpenGLTexture::RGBA);
        d->funcs->glDrawBuffers(3, attachments);
    }

    // 1. geometry pass: render scene's geometry/color data into gbuffer
    d->fbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    for (int i = 0; i < d->objectPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->objectPosition[i]);
        model.scale(0.5f);
        s1->setUniformValue("model", model);
        p->renderModel(s1, fileName);
    }
    d->fbo->release();

    // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->textures().at(0));
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->textures().at(1));
    d->funcs->glActiveTexture(GL_TEXTURE2);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo->textures().at(2));
    s2->bind();
    s2->setUniformValue("viewPos", viewPos);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        float constant = d->lightAttenuation.x();
        float linear = d->lightAttenuation.y();
        float quadratic = d->lightAttenuation.z();
        float maxBrightness = qMax(qMax(d->lightColor[i].x(), d->lightColor[i].y()), d->lightColor[i].z());
        float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
        s2->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), d->lightPosition[i]);
        s2->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), d->lightColor[i]);
        s2->setUniformValue(tr("lights[%1].Linear").arg(i).toStdString().c_str(), linear);
        s2->setUniformValue(tr("lights[%1].Quadratic").arg(i).toStdString().c_str(), quadratic);
        s2->setUniformValue(tr("lights[%1].Radius").arg(i).toStdString().c_str(), radius);
    }
    p->renderScreen(s2);

    // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
    // 复制前先清除
    d->funcs->glClear(GL_DEPTH_BUFFER_BIT);
    QOpenGLFramebufferObject::blitFramebuffer(nullptr, d->fbo.data(), GL_DEPTH_BUFFER_BIT);

    // 3. render lights on top of scene
    s3->bind();
    s3->setUniformValue("projection", projection);
    s3->setUniformValue("view", view);
    for (int i = 0; i < d->lightPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(d->lightPosition[i]);
        model.scale(0.125f);
        s3->setUniformValue("model", model);
        s3->setUniformValue("lightColor", d->lightColor[i]);
        p->renderSphere(s3);
    }
}

HShaderEngine_SSAOPrivate::HShaderEngine_SSAOPrivate()
{
    QRandomGenerator random;
    for (int i = 0; i < 64; ++i)
    {
        QVector3D sample(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, random.generateDouble());
        sample.normalize();
        sample *= random.generateDouble();
        // scale samples s.t. they're more aligned to center of kernel
        float scale = i / 64.0;
        scale = 0.1 + scale * scale * 0.9;
        sample *= scale;
        ssaoKernel << sample;
    }
    // generate noise texture
    for (int i = 0; i < 16; i++)
        ssaoNoise << QVector3D(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, 0.0f);// rotate around z-axis (in tangent space)
}

HShaderEngine_SSAO::HShaderEngine_SSAO(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_SSAOPrivate, parent)
{
}

HShaderEngine_SSAO::~HShaderEngine_SSAO() = default;

void HShaderEngine_SSAO::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_SSAO);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ssao_geometry.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ssao_geometry.fs");
    s1->bind();
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ssao.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ssao_lighting.fs");
    s2->bind();
    s2->setUniformValue("gPosition", 0);
    s2->setUniformValue("gNormal", 1);
    s2->setUniformValue("gAlbedo", 2);
    s2->setUniformValue("ssao", 3);
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ssao.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ssao.fs");
    s3->bind();
    s3->setUniformValue("gPosition", 0);
    s3->setUniformValue("gNormal", 1);
    s3->setUniformValue("texNoise", 2);
    auto s4 = new QOpenGLShaderProgram(this);
    s4->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/ssao.vs");
    s4->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/ssao_blur.fs");
    s4->bind();
    s4->setUniformValue("ssaoInput", 0);
    d->shaders << s1 << s2 << s3 << s4;
    d->noiseTexture = createTexture(4, 4, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA32F, QOpenGLTexture::Repeat);
    d->noiseTexture->setData(0, QOpenGLTexture::RGB, QOpenGLTexture::Float32, d->ssaoNoise.constData());
}

QString HShaderEngine_SSAO::typeName()
{
    return "HShaderEngine_SSAO";
}

void HShaderEngine_SSAO::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_SSAO);
    QMatrix4x4 model;
    auto fileName = param.value("modelFileName").toString();
    auto size = param.value("size").toSize();
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto lightPos = QVector3D(2.0f, 4.0f, -2.0f);
    auto lightColor = QVector3D(0.2f, 0.2f, 0.7f);
    auto lightAttenuation = QVector3D(1.0f, 0.09f, 0.032f);
    auto lightPosView = QVector3D(view * QVector4D(lightPos, 1.0));
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    auto s3 = d->shaders.at(2);
    auto s4 = d->shaders.at(3);

    if (d->gbufferFbo.isNull() || d->gbufferFbo->size() != size)
    {
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        d->gbufferFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::Depth, QOpenGLTexture::Target2D, QOpenGLTexture::RGBA16F));
        d->gbufferFbo->addColorAttachment(size, QOpenGLTexture::RGBA16F);
        d->gbufferFbo->addColorAttachment(size, QOpenGLTexture::RGBA);
        d->funcs->glDrawBuffers(3, attachments);
    }
    if (d->ssaoFbo.isNull() || d->ssaoFbo->size() != size)
        d->ssaoFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::NoAttachment, QOpenGLTexture::Target2D, QOpenGLTexture::R8_UNorm));
    if (d->blurFbo.isNull() || d->blurFbo->size() != size)
        d->blurFbo.reset(new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::NoAttachment, QOpenGLTexture::Target2D, QOpenGLTexture::R8_UNorm));

    // 1. geometry pass: render scene's geometry/color data into gbuffer
    d->gbufferFbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    s1->bind();
    model.translate(0.0, 7.0f, 0.0f);
    model.scale(7.5f, 7.5f, 7.5f);
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("model", model);
    s1->setUniformValue("invertedNormals", 1);
    p->renderCube(s1);
    model.setToIdentity();
    model.rotate(-90.0f, 1.0, 0.0, 0.0);
    model.scale(1.0f);
    s1->setUniformValue("model", model);
    s1->setUniformValue("invertedNormals", 0);
    p->renderModel(s1, fileName);
    d->gbufferFbo->release();

    // 2. generate SSAO texture
    d->ssaoFbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->gbufferFbo->textures().at(0));
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->gbufferFbo->textures().at(1));
    d->funcs->glActiveTexture(GL_TEXTURE2);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->noiseTexture->textureId());
    s3->bind();
    s3->setUniformValue("projection", projection);
    s3->setUniformValueArray("samples", d->ssaoKernel.data(), 64);
    p->renderScreen(s3);
    d->ssaoFbo->release();

    // 3. blur SSAO texture to remove noise
    d->blurFbo->bind();
    d->funcs->glClear(GL_COLOR_BUFFER_BIT);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->ssaoFbo->texture());
    s4->bind();
    p->renderScreen(s4);
    d->blurFbo->release();

    // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->gbufferFbo->textures().at(0));
    d->funcs->glActiveTexture(GL_TEXTURE1);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->gbufferFbo->textures().at(1));
    d->funcs->glActiveTexture(GL_TEXTURE2);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->gbufferFbo->textures().at(2));
    d->funcs->glActiveTexture(GL_TEXTURE3);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->ssaoFbo->texture());
    s2->bind();
    s2->setUniformValue("light.Position", lightPosView);
    s2->setUniformValue("light.Color", lightColor);
    s2->setUniformValue("light.Linear", lightAttenuation.y());
    s2->setUniformValue("light.Quadratic", lightAttenuation.z());
    p->renderScreen(s2);
}

HShaderEngine_Text::HShaderEngine_Text(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_TextPrivate, parent)
{
}

HShaderEngine_Text::~HShaderEngine_Text() = default;

void HShaderEngine_Text::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_Text);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s = new QOpenGLShaderProgram(this);
    s->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/text.vs");
    s->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/text.fs");
    s->bind();
    s->setUniformValue("texture1", 0);
    d->shaders << s ;
    d->engine = new HTextEngine(this);
    d->engine->setFont("C:\\Windows\\Fonts\\SIMYOU.TTF", 64);
}

QString HShaderEngine_Text::typeName()
{
    return "HShaderEngine_Text";
}

void HShaderEngine_Text::draw(HGeometryEngine */*p*/, QVariantMap param)
{
    Q_D(HShaderEngine_Text);
    QMatrix4x4 projection, model;
    auto size = param.value("size").toSize();
    auto s = d->shaders.at(0);
    projection.ortho(0.0f, size.width(), 0.0f,  size.height(), -1.0 , 1.0f);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("model", model);
    s->setUniformValue("color", QVector3D(0.5, 0.8f, 0.2f));
    d->engine->render("This is sample text", QVector2D(25.0, 25.0));
    s->setUniformValue("color", QVector3D(0.3, 0.7f, 0.9f));
    d->engine->render("测试汉字\n测试行", QVector2D(400, 400.0));
}


HE_END_NAMESPACE
