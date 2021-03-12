#include "HResourceManager.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLTexture2D.h"
#include "stb_image.h"
#include <QtCore/QMap>
#include <QtCore/QFile>

HE_REFERENCE_BEGIN_NAMESPACE

QMap<QString, HOpenGLShaderProgram *> HResourceManager::__shaders;
QMap<QString, HOpenGLTexture2D *> HResourceManager::__textures;

void HResourceManager::clear()
{
    qDeleteAll(__shaders);
    qDeleteAll(__textures);
}

HOpenGLShaderProgram *HResourceManager::shader(const QString &name)
{
    return __shaders.value(name, nullptr);
}

HOpenGLShaderProgram *HResourceManager::loadShader(const QString &name, const QString &fileNameV, const QString &fileNameF, const QString &fileNameG)
{
    if (__shaders.contains(name))
        delete __shaders.take(name);
    auto shader = new HOpenGLShaderProgram();
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     fileNameV);
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   fileNameF);
    if (!fileNameG.isEmpty())
        shader->addShaderFromSourceFile(HOpenGLShader::Geometry,   fileNameG);
    __shaders.insert(name, shader);
    return __shaders[name];
}

HOpenGLTexture2D *HResourceManager::texture(const QString &name)
{
    return __textures.value(name, nullptr);
}

HOpenGLTexture2D *HResourceManager::loadTexture(const QString &name, const QString &fileName, bool alpha)
{
    if (__textures.contains(name))
        delete __textures.take(name);

    int width, height, channels;
    unsigned char *data = nullptr;
    if (fileName.startsWith(":/"))
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly))
        {
            auto buffer = file.readAll();
            data = stbi_load_from_memory((unsigned char *)buffer.data(), buffer.size(), &width, &height, &channels, 0);
            file.close();
        }
    }
    else
        data = stbi_load(fileName.toStdString().c_str(), &width, &height, &channels, 0);

    if (data == nullptr)
        return nullptr;

    auto texture = new HOpenGLTexture2D();
    if (alpha)
        texture->setFormat(GL_RGBA, GL_RGBA);
    texture->generate(width, height, data);
    stbi_image_free(data);

    __textures.insert(name, texture);
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

HE_REFERENCE_END_NAMESPACE

