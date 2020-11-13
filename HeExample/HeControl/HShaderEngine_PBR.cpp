#include "HShaderEngine_PBR_p.h"
#include "HGeometryEngine.h"
#include "stb_image.h"
#include <QtCore/QFile>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLExtraFunctions>
#include <QtGui/QOpenGLFramebufferObject>

HE_CONTROL_BEGIN_NAMESPACE

HShaderEngine_PBRPrivate::HShaderEngine_PBRPrivate()
{
    lightPosition << QVector3D(-10.0f,  10.0f, 10.0f)
                  << QVector3D( 10.0f,  10.0f, 10.0f)
                  << QVector3D(-10.0f, -10.0f, 10.0f)
                  << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColor << QVector3D(300.0f, 300.0f, 300.0f)
               << QVector3D(300.0f, 300.0f, 300.0f)
               << QVector3D(300.0f, 300.0f, 300.0f)
               << QVector3D(300.0f, 300.0f, 300.0f);
}

HShaderEngine_PBR::HShaderEngine_PBR(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_PBRPrivate, parent)
{
}

HShaderEngine_PBR::HShaderEngine_PBR(HShaderEngine_PBRPrivate &p, QObject *parent) :
    HAbstractShaderEngine(p, parent)
{
}

HShaderEngine_PBR::~HShaderEngine_PBR() = default;

void HShaderEngine_PBR::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr.fs");
    s1->bind();
    s1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    s1->setUniformValue("ao", 1.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
}

QString HShaderEngine_PBR::typeName()
{
    return "HShaderEngine_PBR";
}

void HShaderEngine_PBR::draw(HGeometryEngine *p, QVariantMap param)
{
    beforeDrawSpheres(p, param);
    drawSpheres(p, param);
    afterDrawSpheres(p, param);
}

void HShaderEngine_PBR::beforeDrawSpheres(HGeometryEngine *, QVariantMap /*param*/)
{

}

void HShaderEngine_PBR::afterDrawSpheres(HGeometryEngine *, QVariantMap /*param*/)
{

}

void HShaderEngine_PBR::drawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR);
    QMatrix4x4 model;
    QVector<QVector3D> lightPosition;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    auto rows    = 7;
    auto columns = 7;
    auto spacing = 2.5;
    for (auto pos : d->lightPosition)
        lightPosition << pos + QVector3D(sin(secs() * 5.0) * 5.0, 0.0, 0.0);

    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValueArray("lightPositions", lightPosition.data(), 4);
    s1->setUniformValueArray("lightColors", d->lightColor.data(), 4);
    for (int row = 0; row < rows; ++row)
    {
        s1->setUniformValue("metallic", 1.0f * row / rows);
        for (int col = 0; col < columns; ++col)
        {
            model.setToIdentity();
            model.translate((col - (columns / 2)) * spacing, (row - (rows / 2)) * spacing, 0.0f);
            // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
            s1->setUniformValue("roughness", qBound(0.05f, 1.0f * col / columns, 1.0f));
            s1->setUniformValue("model", model);
            p->renderSphere(s1);
        }
    }
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    for (int i = 0; i < lightPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(lightPosition[i]);
        model.scale(0.5f);
        s2->setUniformValue("model", model);
        s2->setUniformValue("lightColor", d->lightColor[i]);
        p->renderSphere(s2);
    }
}

HShaderEngine_PBR2::HShaderEngine_PBR2(QObject *parent) :
    HAbstractShaderEngine(*new HShaderEngine_PBR2Private, parent)
{
}

HShaderEngine_PBR2::~HShaderEngine_PBR2() = default;

void HShaderEngine_PBR2::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR2);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr2.fs");
    s1->bind();
    s1->setUniformValue("albedoMap", 0);
    s1->setUniformValue("normalMap", 1);
    s1->setUniformValue("metallicMap", 2);
    s1->setUniformValue("roughnessMap", 3);
    s1->setUniformValue("aoMap", 4);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    d->shaders << s1 << s2;
    addTexture(":/textures/pbr/rusted_iron/albedo.png");
    addTexture(":/textures/pbr/rusted_iron/normal.png");
    addTexture(":/textures/pbr/rusted_iron/metallic.png");
    addTexture(":/textures/pbr/rusted_iron/roughness.png");
    addTexture(":/textures/pbr/rusted_iron/ao.png");
}

QString HShaderEngine_PBR2::typeName()
{
    return "HShaderEngine_PBR2";
}

void HShaderEngine_PBR2::draw(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR2);
    QMatrix4x4 model;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto lightPosition = d->lightPosition + QVector3D(sin(secs() * 5.0) * 5.0, 0.0, 0.0);
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    auto rows    = 7;
    auto columns = 7;
    auto spacing = 2.5;
    buildTexture();
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValue("lightPositions[0]", lightPosition);
    s1->setUniformValue("lightColors[0]", d->lightColor);
    for (int row = 0; row < rows; ++row)
    {
        s1->setUniformValue("metallic", 1.0f * row / rows);
        for (int col = 0; col < columns; ++col)
        {
            model.setToIdentity();
            model.translate((col - (columns / 2)) * spacing, (row - (rows / 2)) * spacing, 0.0f);
            s1->setUniformValue("model", model);
            p->renderSphere(s1);
        }
    }
    model.setToIdentity();
    model.translate(lightPosition);
    model.scale(0.5f);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    s2->setUniformValue("model", model);
    s2->setUniformValue("lightColor", d->lightColor);
    p->renderSphere(s2);
}

HShaderEngine_PBR3::HShaderEngine_PBR3(QObject *parent) :
    HShaderEngine_PBR(*new HShaderEngine_PBR3Private, parent)
{
}

HShaderEngine_PBR3::HShaderEngine_PBR3(HShaderEngine_PBR3Private &p, QObject *parent) :
    HShaderEngine_PBR(p, parent)
{
}

HShaderEngine_PBR3::~HShaderEngine_PBR3()
{
    Q_D(HShaderEngine_PBR3);
    if (d->envCubemap != 0)
        d->envCubemap->destroy();
}

void HShaderEngine_PBR3::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR3);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr.fs");
    s1->bind();
    s1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    s1->setUniformValue("ao", 1.0f);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/skybox2.fs");
    s3->bind();
    s3->setUniformValue("texture1", 0);
    d->shaders << s1 << s2 << s3;
}

QString HShaderEngine_PBR3::typeName()
{
    return "HShaderEngine_PBR3";
}

void HShaderEngine_PBR3::beforeDrawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR3);
    if (d->envCubemap == nullptr)
    {
        auto size = param.value("size").toSize();
        d->envCubemap = loadCubemapFromHdr(p, ":/textures/hdr/newport_loft.hdr", 512, 512);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
}

void HShaderEngine_PBR3::afterDrawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR3);
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto s = d->shaders.at(2);
    // render skybox (render as last to prevent overdraw)
    d->envCubemap->bind(0);
    s->bind();
    s->setUniformValue("projection", projection);
    s->setUniformValue("view", view);
    p->renderSkybox(s);
}

QOpenGLTexture *HShaderEngine_PBR3::loadCubemapFromHdr(HGeometryEngine *engine, const QString &fileName, int width, int height, QOpenGLTexture::Filter magFilter)
{
    auto shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/cubemap_from_equirectangular.fs");
    auto texture = loadTextureFromHdr(fileName);
    auto cubemap = createTexture(width, height, QOpenGLTexture::TargetCubeMap, QOpenGLTexture::RGB16F, QOpenGLTexture::ClampToEdge, magFilter);
    renderCubemap(shader, engine, texture, cubemap);
    return cubemap;
}

QOpenGLTexture *HShaderEngine_PBR3::loadTextureFromHdr(const QString &fileName)
{
    int width, height, channels;
    float *data = nullptr;
    stbi_set_flip_vertically_on_load(true);
    if (fileName.startsWith(":/"))  // 从资源文件读取
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly))
        {
            auto buffer = file.readAll();
            data = stbi_loadf_from_memory((unsigned char *)buffer.data(), buffer.size(), &width, &height, &channels, 0);
            file.close();
        }
    }
    else
        data = stbi_loadf(fileName.toStdString().c_str(), &width, &height, &channels, 0);

    if (data)
    {
        auto texture = createTexture(width, height, QOpenGLTexture::Target2D, QOpenGLTexture::RGB16F);
        texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::Float32, data);
        stbi_image_free(data);
        return texture;
    }
    qDebug() << "Failed to load HDR image.";
    return nullptr;
}

void HShaderEngine_PBR3::renderCubemap(QOpenGLShaderProgram *shader, HGeometryEngine *engine, QOpenGLTexture *texture1, QOpenGLTexture *texture2)
{
    Q_D(HShaderEngine_PBR3);
    // set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 projection;
    projection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> views(6);
    views[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    views[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    views[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    auto width = texture2->width();
    auto height = texture2->height();
    QScopedPointer<QOpenGLFramebufferObject> fbo(new QOpenGLFramebufferObject(width, height, QOpenGLFramebufferObject::Depth));

    // render cubemap
    fbo->bind();
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("projection", projection);
    texture1->bind(0);
    d->funcs->glViewport(0, 0, width, height);
    for (int i = 0; i < 6; i++)
    {
        shader->setUniformValue("view", views[i]);
        d->funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, texture2->textureId(), 0);
        d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        engine->renderCube(shader);
    }
    if (texture2->mipLevels() > 1)
        texture2->generateMipMaps();
    fbo->release();
}

HShaderEngine_PBR4::HShaderEngine_PBR4(QObject *parent) :
    HShaderEngine_PBR3(*new HShaderEngine_PBR4Private, parent)
{
}

HShaderEngine_PBR4::HShaderEngine_PBR4(HShaderEngine_PBR4Private &p, QObject *parent) :
    HShaderEngine_PBR3(p, parent)
{
}

HShaderEngine_PBR4::~HShaderEngine_PBR4()
{
    Q_D(HShaderEngine_PBR4);
    if (d->irradianceCubemap != 0)
        d->irradianceCubemap->destroy();
}

void HShaderEngine_PBR4::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR4);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr4.fs");
    s1->bind();
    s1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    s1->setUniformValue("ao", 1.0f);
    s1->setUniformValue("irradianceMap", 0);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/skybox2.fs");
    s3->bind();
    s3->setUniformValue("texture1", 0);
    d->shaders << s1 << s2 << s3;
}

QString HShaderEngine_PBR4::typeName()
{
    return "HShaderEngine_PBR4";
}

void HShaderEngine_PBR4::beforeDrawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR4);
    HShaderEngine_PBR3::beforeDrawSpheres(p, param);
    if (d->irradianceCubemap == nullptr)
    {
        auto size = param.value("size").toSize();
        d->irradianceCubemap = createCubemapIrradiance(p, d->envCubemap, 32, 32);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
    d->irradianceCubemap->bind(0);
}

QOpenGLTexture *HShaderEngine_PBR4::createCubemapIrradiance(HGeometryEngine *engine, QOpenGLTexture *texture, int width, int height)
{
    auto shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/cubemap_irradiance_convolution.fs");
    auto cubemap = createTexture(width, height, QOpenGLTexture::TargetCubeMap, QOpenGLTexture::RGB16F, QOpenGLTexture::ClampToEdge);
    renderCubemap(shader, engine, texture, cubemap);
    return cubemap;
}

HShaderEngine_PBR5::HShaderEngine_PBR5(QObject *parent) :
    HShaderEngine_PBR4(*new HShaderEngine_PBR5Private, parent)
{
}

HShaderEngine_PBR5::HShaderEngine_PBR5(HShaderEngine_PBR5Private &p, QObject *parent) :
    HShaderEngine_PBR4(p, parent)
{
}

HShaderEngine_PBR5::~HShaderEngine_PBR5()
{
    Q_D(HShaderEngine_PBR5);
    if (d->prefilterCubemap != 0)
        d->prefilterCubemap->destroy();
    if (d->brdfTexture != 0)
        d->brdfTexture->destroy();
}

void HShaderEngine_PBR5::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR5);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr5.fs");
    s1->bind();
    s1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    s1->setUniformValue("ao", 1.0f);
    s1->setUniformValue("irradianceMap", 0);
    s1->setUniformValue("prefilterMap", 1);
    s1->setUniformValue("brdfLUT", 2);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/skybox2.fs");
    s3->bind();
    s3->setUniformValue("texture1", 0);
    d->shaders << s1 << s2 << s3;
}

QString HShaderEngine_PBR5::typeName()
{
    return "HShaderEngine_PBR5";
}

void HShaderEngine_PBR5::beforeDrawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR5);
    auto size = param.value("size").toSize();
    if (d->envCubemap == nullptr)
    {
        d->envCubemap = loadCubemapFromHdr(p, ":/textures/hdr/newport_loft.hdr", 512, 512, QOpenGLTexture::LinearMipMapLinear);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
    if (d->irradianceCubemap == nullptr)
    {
        d->irradianceCubemap = createCubemapIrradiance(p, d->envCubemap, 32, 32);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
    if (d->prefilterCubemap == nullptr)
    {
        d->prefilterCubemap = createCubemapPrefilter(p, d->envCubemap, 128, 128);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
    if (d->brdfTexture == nullptr)
    {
        d->brdfTexture = createTextureBrdf(p, 512, 512);
        d->funcs->glViewport(0, 0, size.width(), size.height());
    }
    d->irradianceCubemap->bind(0);
    d->prefilterCubemap->bind(1);
    d->brdfTexture->bind(2);
}

QOpenGLTexture *HShaderEngine_PBR5::createCubemapPrefilter(HGeometryEngine *engine, QOpenGLTexture *texture, int width, int height)
{
    Q_D(HShaderEngine_PBR5);
    // set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 projection;
    projection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> views(6);
    views[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    views[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    views[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    auto shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/cubemap_prefilter.fs");

    auto cubemap = createTexture(width, height, QOpenGLTexture::TargetCubeMap, QOpenGLTexture::RGB16F, QOpenGLTexture::ClampToEdge, QOpenGLTexture::LinearMipMapLinear);
    cubemap->generateMipMaps();

    QSharedPointer<QOpenGLFramebufferObject> fbo;
    int maxMipLevels = 5;
    texture->bind(0);
    shader->bind();
    shader->setUniformValue("projection", projection);
    shader->setUniformValue("texture1", 0);
    for (int mip = 0; mip < maxMipLevels; mip++)
    {
        int mipWidth = width * std::pow(0.5, mip);
        int mipHeight = height * std::pow(0.5, mip);
        auto roughness = 1.0f * mip / (maxMipLevels - 1);
        shader->setUniformValue("roughness", roughness);
        fbo.reset(new QOpenGLFramebufferObject(mipWidth, mipHeight, QOpenGLFramebufferObject::Depth));
        fbo->bind();
        d->funcs->glViewport(0, 0, mipWidth, mipHeight);
        for (int i = 0; i < 6; i++)
        {
            shader->setUniformValue("view", views[i]);
            d->funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap->textureId(), mip);
            d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            engine->renderCube(shader);
        }
        fbo->release();
    }
    return cubemap;
}

QOpenGLTexture *HShaderEngine_PBR5::createTextureBrdf(HGeometryEngine *engine, int width, int height)
{
    Q_D(HShaderEngine_PBR5);
    auto shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/brdf.vs");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/brdf.fs");

    auto texture = createTexture(width, height, QOpenGLTexture::Target2D, QOpenGLTexture::RG16F);
    QScopedPointer<QOpenGLFramebufferObject> fbo(new QOpenGLFramebufferObject(width, height, QOpenGLFramebufferObject::Depth));
    fbo->bind();
    shader->bind();
    d->funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->textureId(), 0);
    d->funcs->glViewport(0, 0, width, height);
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    engine->renderScreen(shader);
    fbo->release();
    return texture;
}

HShaderEngine_PBR6Private::HShaderEngine_PBR6Private()
{
    spherePosition.insert("iron",       QVector3D(-5.0, 0.0, 2.0));
    spherePosition.insert("gold",       QVector3D(-3.0, 0.0, 2.0));
    spherePosition.insert("grass",      QVector3D(-1.0, 0.0, 2.0));
    spherePosition.insert("plastic",    QVector3D( 1.0, 0.0, 2.0));
    spherePosition.insert("wall",       QVector3D( 3.0, 0.0, 2.0));
}

HShaderEngine_PBR6::HShaderEngine_PBR6(QObject *parent) :
    HShaderEngine_PBR5(*new HShaderEngine_PBR6Private, parent)
{
}

HShaderEngine_PBR6::~HShaderEngine_PBR6() = default;

void HShaderEngine_PBR6::initialize(QVariantMap /*param*/)
{
    Q_D(HShaderEngine_PBR6);
    if (d->initialized)
        return;
    d->initialized = true;
    auto s1 = new QOpenGLShaderProgram(this);
    s1->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/pbr.vs");
    s1->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/pbr6.fs");
    s1->bind();
    s1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    s1->setUniformValue("ao", 1.0f);
    s1->setUniformValue("irradianceMap", 0);
    s1->setUniformValue("prefilterMap", 1);
    s1->setUniformValue("brdfLUT", 2);
    s1->setUniformValue("albedoMap", 3);
    s1->setUniformValue("normalMap", 4);
    s1->setUniformValue("metallicMap", 5);
    s1->setUniformValue("roughnessMap", 6);
    s1->setUniformValue("aoMap", 7);
    auto s2 = new QOpenGLShaderProgram(this);
    s2->addShaderFromSourceFile(QOpenGLShader::Vertex,      ":/glsl/light_source.vs");
    s2->addShaderFromSourceFile(QOpenGLShader::Fragment,    ":/glsl/light_source.fs");
    s2->bind();
    auto s3 = new QOpenGLShaderProgram(this);
    s3->addShaderFromSourceFile(QOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    s3->addShaderFromSourceFile(QOpenGLShader::Fragment,   ":/glsl/skybox2.fs");
    s3->bind();
    s3->setUniformValue("texture1", 0);
    d->shaders << s1 << s2 << s3;
    d->sphereTexture.insert("iron",     QList<QOpenGLTexture *>() << createTexture(":/textures/pbr/rusted_iron/albedo.png")
                                                              << createTexture(":/textures/pbr/rusted_iron/normal.png")
                                                              << createTexture(":/textures/pbr/rusted_iron/metallic.png")
                                                              << createTexture(":/textures/pbr/rusted_iron/roughness.png")
                                                              << createTexture(":/textures/pbr/rusted_iron/ao.png"));
    d->sphereTexture.insert("gold",     QList<QOpenGLTexture *>() << createTexture(":/textures/pbr/gold/albedo.png")
                                                              << createTexture(":/textures/pbr/gold/normal.png")
                                                              << createTexture(":/textures/pbr/gold/metallic.png")
                                                              << createTexture(":/textures/pbr/gold/roughness.png")
                                                              << createTexture(":/textures/pbr/gold/ao.png"));
    d->sphereTexture.insert("grass",    QList<QOpenGLTexture *>() << createTexture(":/textures/pbr/grass/albedo.png")
                                                               << createTexture(":/textures/pbr/grass/normal.png")
                                                               << createTexture(":/textures/pbr/grass/metallic.png")
                                                               << createTexture(":/textures/pbr/grass/roughness.png")
                                                               << createTexture(":/textures/pbr/grass/ao.png"));
    d->sphereTexture.insert("plastic",  QList<QOpenGLTexture *>() << createTexture(":/textures/pbr/plastic/albedo.png")
                                                                 << createTexture(":/textures/pbr/plastic/normal.png")
                                                                 << createTexture(":/textures/pbr/plastic/metallic.png")
                                                                 << createTexture(":/textures/pbr/plastic/roughness.png")
                                                                 << createTexture(":/textures/pbr/plastic/ao.png"));
    d->sphereTexture.insert("wall",     QList<QOpenGLTexture *>() << createTexture(":/textures/pbr/wall/albedo.png")
                                                              << createTexture(":/textures/pbr/wall/normal.png")
                                                              << createTexture(":/textures/pbr/wall/metallic.png")
                                                              << createTexture(":/textures/pbr/wall/roughness.png")
                                                              << createTexture(":/textures/pbr/wall/ao.png"));
}

QString HShaderEngine_PBR6::typeName()
{
    return "HShaderEngine_PBR6";
}

void HShaderEngine_PBR6::drawSpheres(HGeometryEngine *p, QVariantMap param)
{
    Q_D(HShaderEngine_PBR6);
    QMatrix4x4 model;
    QVector<QVector3D> lightPosition;
    auto projection = param.value("projection").value<QMatrix4x4>();
    auto view = param.value("view").value<QMatrix4x4>();
    auto viewPos = param.value("viewPos").value<QVector3D>();
    auto s1 = d->shaders.at(0);
    auto s2 = d->shaders.at(1);
    for (auto pos : d->lightPosition)
        lightPosition << pos + QVector3D(sin(secs() * 5.0) * 5.0, 0.0, 0.0);
    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("view", view);
    s1->setUniformValue("viewPos", viewPos);
    s1->setUniformValueArray("lightPositions", lightPosition.data(), 4);
    s1->setUniformValueArray("lightColors", d->lightColor.data(), 4);
    for (auto it = d->spherePosition.begin(); it != d->spherePosition.end(); it++)
    {
        auto textures = d->sphereTexture.value(it.key());
        for (int i = 0; i < textures.size(); i++)
            textures.at(i)->bind(i + 3);
        model.setToIdentity();
        model.translate(it.value());
        s1->setUniformValue("model", model);
        p->renderSphere(s1);
    }
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("view", view);
    for (int i = 0; i < lightPosition.size(); i++)
    {
        model.setToIdentity();
        model.translate(lightPosition[i]);
        model.scale(0.5f);
        s2->setUniformValue("model", model);
        s2->setUniformValue("lightColor", d->lightColor[i]);
        p->renderSphere(s2);
    }
}

HE_CONTROL_END_NAMESPACE
