#include "HOpenGLHelper.h"
#include "glad/glad.h"
#include <QtGui/QImage>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

unsigned int HOpenGLHelper::loadTexture(const QString &fileName, bool gamma)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    auto image = QImage(fileName);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    image = image.mirrored();
    auto data = image.constBits();
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, gamma ? GL_SRGB_ALPHA : GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        qDebug() << "Failed to load texture.";
    }
    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order: +X (right) -X (left) +Y (top) -Y (bottom) +Z (front) -Z (back)
unsigned int HOpenGLHelper::loadCubemap(const QStringList &fileNames)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (int i = 0; i < fileNames.size(); i++)
    {
        auto image = QImage(fileNames.at(i));
        image = image.convertToFormat(QImage::Format_RGBA8888);
        //        image = image.mirrored();
        auto data = image.constBits();
        if (data)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            qDebug() << "Failed to load texture.";
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
}

HE_REFERENCE_END_NAMESPACE
