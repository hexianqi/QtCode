#pragma once

#include "HControlGlobal.h"
#include <QtCore/QString>

class QOpenGLShaderProgram;
class QOpenGLTexture;

HE_CONTROL_BEGIN_NAMESPACE

class HResourceManager
{
public:
    static void clear();
    static QOpenGLShaderProgram *shader(const QString &name);
    static QOpenGLShaderProgram *loadShader(const QString &name, const QString &fileNameV, const QString &fileNameF, const QString &fileNameG = QString());
    static QOpenGLTexture *texture(const QString &name);
    static QOpenGLTexture *loadTexture(const QString &name, const QString &fileName);
    static void play(const QString &name);

protected:
    static QMap<QString, QOpenGLShaderProgram *> __shaders;
    static QMap<QString, QOpenGLTexture *> __textures;
};

HE_CONTROL_END_NAMESPACE

