/***************************************************************************************************
**      2020-09-10  HOpenGLShaderProgram
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include "glad/glad.h"
#include <QtCore/QObject>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLShaderPrivate;

class HOpenGLShader : public QObject
{
    Q_OBJECT

public:
    enum ShaderTypeBit
    {
        Vertex                 = 0x0001,
        Fragment               = 0x0002
    };
    Q_DECLARE_FLAGS(ShaderType, ShaderTypeBit)

public:
    explicit HOpenGLShader(ShaderType type, QObject *parent = nullptr);
    ~HOpenGLShader() override;

public:
    ShaderType shaderType() const;
    GLuint shaderId() const;
    bool isCompiled() const;
    QString log() const;
    QByteArray sourceCode() const;

public:
    bool compileSourceCode(const char *source);
    bool compileSourceCode(const QByteArray &source);
    bool compileSourceCode(const QString &source);
    bool compileSourceFile(const QString &fileName);

protected:
    bool create();
    bool compile();
    void free();

protected:
    QScopedPointer<HOpenGLShaderPrivate> d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(HOpenGLShader::ShaderType)

class HOpenGLShaderProgramPrivate;

class HOpenGLShaderProgram : public QObject
{
    Q_OBJECT

public:
    explicit HOpenGLShaderProgram(QObject *parent = nullptr);
    ~HOpenGLShaderProgram() override;

public:
    GLuint programId() const;
    bool isLinked() const;
    QString log() const;
    QList<HOpenGLShader *> shaders() const;

public:
    bool addShader(HOpenGLShader *);
    bool addShaderFromSourceCode(HOpenGLShader::ShaderType type, const char *source);
    bool addShaderFromSourceCode(HOpenGLShader::ShaderType type, const QByteArray &source);
    bool addShaderFromSourceCode(HOpenGLShader::ShaderType type, const QString &source);
    bool addShaderFromSourceFile(HOpenGLShader::ShaderType type, const QString &fileName);
    void removeShader(HOpenGLShader *);
    void removeAllShaders();

public:
    bool create();
    bool link();
    bool bind();
    void release();
    void free();

public:
    void bindAttributeLocation(const char *name, int location);
    void bindAttributeLocation(const QByteArray &name, int location);
    void bindAttributeLocation(const QString &name, int location);
    int attributeLocation(const char *name) const;
    int attributeLocation(const QByteArray &name) const;
    int attributeLocation(const QString &name) const;
    int uniformLocation(const char *name) const;
    int uniformLocation(const QByteArray &name) const;
    int uniformLocation(const QString &name) const;

protected:
    bool init();
    void shaderDestroyed();

protected:
    QScopedPointer<HOpenGLShaderProgramPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

