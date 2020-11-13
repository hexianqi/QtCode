#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QString>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HOpenGLTexture2D;

class HResourceManager
{
public:
    static void clear();
    static HOpenGLShaderProgram *shader(const QString &name);
    static HOpenGLShaderProgram *loadShader(const QString &name, const QString &fileNameV, const QString &fileNameF, const QString &fileNameG = QString());
    static HOpenGLTexture2D *texture(const QString &name);
    static HOpenGLTexture2D *loadTexture(const QString &name, const QString &fileName, bool alpha = false);
    static void play(const QString &name);

protected:
    static QMap<QString, HOpenGLShaderProgram *> __shaders;
    static QMap<QString, HOpenGLTexture2D *> __textures;
};

HE_REFERENCE_END_NAMESPACE

