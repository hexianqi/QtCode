#pragma once

#include "HOpenGLShaderProgram.h"

HE_BEGIN_NAMESPACE

class HOpenGLShaderPrivate
{
public:
    HOpenGLShader::ShaderType shaderType;
    GLuint shaderId = 0;
    bool compiled = false;
    QString log;
};

class HOpenGLShaderProgramPrivate
{
public:
    GLuint programId = 0;
    bool linked = false;
    bool removingShaders = false;
    QString log;
    QList<HOpenGLShader *> shaders;
};

HE_END_NAMESPACE

