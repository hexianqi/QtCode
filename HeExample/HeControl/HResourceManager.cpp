#include "HResourceManager.h"
#include <QtCore/QMap>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLShaderProgram>

HE_BEGIN_NAMESPACE

QMap<QString, QOpenGLShaderProgram *> HResourceManager::__shaders;
QMap<QString, QOpenGLTexture *> HResourceManager::__textures;

void HResourceManager::clear()
{
    qDeleteAll(__shaders);
    qDeleteAll(__textures);
}

QOpenGLShaderProgram *HResourceManager::shader(const QString &name)
{
    return __shaders.value(name, nullptr);
}

QOpenGLShaderProgram *HResourceManager::loadShader(const QString &name, const QString &fileNameV, const QString &fileNameF, const QString &fileNameG)
{
    if (__shaders.contains(name))
        delete __shaders.take(name);
    auto shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,     fileNameV);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,   fileNameF);
    if (!fileNameG.isEmpty())
        shader->addShaderFromSourceFile(QOpenGLShader::Geometry,   fileNameG);
    __shaders.insert(name, shader);
    return __shaders[name];
}

QOpenGLTexture *HResourceManager::texture(const QString &name)
{
    return __textures.value(name, nullptr);
}

QOpenGLTexture *HResourceManager::loadTexture(const QString &name, const QString &fileName)
{
    if (__textures.contains(name))
        delete __textures.take(name);

    QImage image(fileName);
    __textures.insert(name, new QOpenGLTexture(image));
    return __textures[name];
}

void HResourceManager::play(const QString &/*name*/)
{
    //    QtConcurrent::run([=] {
    //        __player->stop();
    //        __player->setMedia(QUrl::fromLocalFile(name));
    //        __player->play();
    //    });
}

HE_END_NAMESPACE
