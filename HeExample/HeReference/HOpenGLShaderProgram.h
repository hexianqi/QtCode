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
        Fragment               = 0x0002,
        Geometry               = 0x0004
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
    int attributeLocation(const char *name) const;
    int attributeLocation(const QByteArray &name) const;
    int attributeLocation(const QString &name) const;
    void bindAttributeLocation(const char *name, int location);
    void bindAttributeLocation(const QByteArray &name, int location);
    void bindAttributeLocation(const QString &name, int location);
    void enableAttributeArray(int location);
    void enableAttributeArray(const char *name);
    void disableAttributeArray(int location);
    void disableAttributeArray(const char *name);
    void setAttributeValue(int location, GLfloat value);
    void setAttributeValue(int location, GLfloat x, GLfloat y);
    void setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z);
    void setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setAttributeValue(int location, const QVector2D &value);
    void setAttributeValue(int location, const QVector3D &value);
    void setAttributeValue(int location, const QVector4D &value);
    void setAttributeValue(int location, const QColor &value);
    void setAttributeValue(int location, const GLfloat *values, int columns, int rows);
    void setAttributeValue(const char *name, GLfloat value);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setAttributeValue(const char *name, const QVector2D &value);
    void setAttributeValue(const char *name, const QVector3D &value);
    void setAttributeValue(const char *name, const QVector4D &value);
    void setAttributeValue(const char *name, const QColor &value);
    void setAttributeValue(const char *name, const GLfloat *values, int columns, int rows);
    void setAttributeArray(int location, const GLfloat *values, int tupleSize, int stride = 0);
    void setAttributeArray(int location, const QVector2D *values, int stride = 0);
    void setAttributeArray(int location, const QVector3D *values, int stride = 0);
    void setAttributeArray(int location, const QVector4D *values, int stride = 0);
    void setAttributeArray(int location, GLenum type, const void *values, int tupleSize, int stride = 0);
    void setAttributeArray(const char *name, const GLfloat *values, int tupleSize, int stride = 0);
    void setAttributeArray(const char *name, const QVector2D *values, int stride = 0);
    void setAttributeArray(const char *name, const QVector3D *values, int stride = 0);
    void setAttributeArray(const char *name, const QVector4D *values, int stride = 0);
    void setAttributeArray(const char *name, GLenum type, const void *values, int tupleSize, int stride = 0);
    void setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride = 0);
    void setAttributeBuffer(const char *name, GLenum type, int offset, int tupleSize, int stride = 0);

public:
    void bindUniformBlock(const char *name, int block);
    void bindUniformBlock(const QByteArray &name, int block);
    void bindUniformBlock(const QString &name, int block);
    int uniformLocation(const char *name) const;
    int uniformLocation(const QByteArray &name) const;
    int uniformLocation(const QString &name) const;
    void setUniformValue(int location, GLint value);
    void setUniformValue(int location, GLuint value);
    void setUniformValue(int location, GLfloat value);
    void setUniformValue(int location, GLfloat x, GLfloat y);
    void setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z);
    void setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformValue(int location, const QVector2D &value);
    void setUniformValue(int location, const QVector3D &value);
    void setUniformValue(int location, const QVector4D &value);
    void setUniformValue(int location, const QColor &value);
    void setUniformValue(int location, const QMatrix4x4 &value);
    void setUniformValue(const char *name, GLint value);
    void setUniformValue(const char *name, GLuint value);
    void setUniformValue(const char *name, GLfloat value);
    void setUniformValue(const char *name, GLfloat x, GLfloat y);
    void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z);
    void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformValue(const char *name, const QVector2D &value);
    void setUniformValue(const char *name, const QVector3D &value);
    void setUniformValue(const char *name, const QVector4D &value);
    void setUniformValue(const char *name, const QColor &value);
    void setUniformValue(const char *name, const QMatrix4x4 &value);
    void setUniformValueArray(int location, const GLint *values, int count);
    void setUniformValueArray(int location, const GLuint *values, int count);
    void setUniformValueArray(int location, const GLfloat *values, int count, int tupleSize);
    void setUniformValueArray(int location, const QVector2D *values, int count);
    void setUniformValueArray(int location, const QVector3D *values, int count);
    void setUniformValueArray(int location, const QVector4D *values, int count);
    void setUniformValueArray(const char *name, const GLint *values, int count);
    void setUniformValueArray(const char *name, const GLuint *values, int count);
    void setUniformValueArray(const char *name, const GLfloat *values, int count, int tupleSize);
    void setUniformValueArray(const char *name, const QVector2D *values, int count);
    void setUniformValueArray(const char *name, const QVector3D *values, int count);
    void setUniformValueArray(const char *name, const QVector4D *values, int count);

protected:
    bool init();
    void shaderDestroyed();

protected:
    QScopedPointer<HOpenGLShaderProgramPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

