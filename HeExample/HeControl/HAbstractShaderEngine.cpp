#include "HAbstractShaderEngine_p.h"
#include <QtCore/QTime>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLExtraFunctions>

HE_BEGIN_NAMESPACE

HAbstractShaderEnginePrivate::HAbstractShaderEnginePrivate()
{
    funcs = QOpenGLContext::currentContext()->extraFunctions();
    funcs->initializeOpenGLFunctions();
}

HAbstractShaderEngine::HAbstractShaderEngine(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractShaderEnginePrivate)
{
}

HAbstractShaderEngine::HAbstractShaderEngine(HAbstractShaderEnginePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractShaderEngine::~HAbstractShaderEngine()
{
    qDeleteAll(d_ptr->textures);
    d_ptr->textures.clear();
}

void HAbstractShaderEngine::initialize(QVariantMap /*param*/)
{

}

void HAbstractShaderEngine::setData(QVariantMap /*value*/)
{

}

void HAbstractShaderEngine::addTexture(const QString &fileName, bool gamma, QOpenGLTexture::WrapMode mode)
{
    auto texture = createTexture(fileName, gamma, mode);
    d_ptr->textures.append(texture);
}

void HAbstractShaderEngine::addTexture(const QStringList &fileNames)
{
    QList<QImage> images;
    for (auto name : fileNames)
        images << QImage(name).convertToFormat(QImage::Format_RGBA8888);

    auto texture = createTexture(images.first().width(), images.first().height(), QOpenGLTexture::TargetCubeMap, QOpenGLTexture::RGBA8_UNorm);
    for (int i = 0; i < images.size(); i++)
        texture->setData(0, 0, QOpenGLTexture::CubeMapFace(QOpenGLTexture::CubeMapPositiveX + i), QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, images.at(i).constBits());
    d_ptr->textures.append(texture);
}

void HAbstractShaderEngine::buildTexture()
{
    for (int i = 0; i < d_ptr->textures.size(); i++)
        d_ptr->textures.at(i)->bind(i);
}

QOpenGLTexture *HAbstractShaderEngine::createTexture(const QString &fileName, bool gamma, QOpenGLTexture::WrapMode mode)
{
    auto image = QImage(fileName).mirrored().convertToFormat(QImage::Format_RGBA8888);
    auto texture = createTexture(image.width(), image.height(),
                                 QOpenGLTexture::Target2D, gamma ? QOpenGLTexture::SRGB8_Alpha8 : QOpenGLTexture::RGBA8_UNorm,
                                 mode, QOpenGLTexture::LinearMipMapLinear);
    texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, image.constBits());
    return texture;
}

QOpenGLTexture *HAbstractShaderEngine::createTexture(int width, int height, QOpenGLTexture::Target target, QOpenGLTexture::TextureFormat format, QOpenGLTexture::WrapMode mode, QOpenGLTexture::Filter magFilter)
{
    auto texture = new QOpenGLTexture(target);
    texture->setSize(width, height);
    texture->setFormat(format);
    texture->setWrapMode(mode);
    texture->setMinMagFilters(magFilter, QOpenGLTexture::Linear);
    if (magFilter >= QOpenGLTexture::NearestMipMapNearest)
        texture->setMipLevels(texture->maximumMipLevels());
    texture->allocateStorage();
    return texture;
}

double HAbstractShaderEngine::secs()
{
    return QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
}

HE_END_NAMESPACE
