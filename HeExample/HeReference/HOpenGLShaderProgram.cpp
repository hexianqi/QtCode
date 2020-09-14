#include "HOpenGLShaderProgram_p.h"
#include "GLFW/glfw3.h"
#include <QtCore/QFile>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

HOpenGLShader::HOpenGLShader(ShaderType type, QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLShaderPrivate)
{
    d_ptr->shaderType = type;
    create();
}

HOpenGLShader::~HOpenGLShader()
{
    free();
}

HOpenGLShader::ShaderType HOpenGLShader::shaderType() const
{
    return d_ptr->shaderType;
}

GLuint HOpenGLShader::shaderId() const
{
    return d_ptr->shaderId;
}

bool HOpenGLShader::isCompiled() const
{
    return d_ptr->compiled;
}

QString HOpenGLShader::log() const
{
    return d_ptr->log;
}

QByteArray HOpenGLShader::sourceCode() const
{
    if (!d_ptr->shaderId)
        return {};
    GLint size = 0;
    glGetShaderiv(d_ptr->shaderId, GL_SHADER_SOURCE_LENGTH, &size);
    if (size <= 0)
        return {};
    GLint len = 0;
    auto source = new char[size];
    glGetShaderSource(d_ptr->shaderId, size, &len, source);
    QByteArray src(source);
    delete [] source;
    return src;
}

bool HOpenGLShader::compileSourceCode(const char *source)
{
    if (!d_ptr->shaderId && !source)
        return false;
    glShaderSource(d_ptr->shaderId, 1, &source, nullptr);
    return compile();
}

bool HOpenGLShader::compileSourceCode(const QByteArray &source)
{
    return compileSourceCode(source.constData());
}

bool HOpenGLShader::compileSourceCode(const QString &source)
{
    return compileSourceCode(source.toLatin1().constData());
}

bool HOpenGLShader::compileSourceFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        qWarning() << "HOpenGLShader: Unable to open file" << fileName;
        return false;
    }
    auto contents = file.readAll();
    return compileSourceCode(contents.constData());
}

bool HOpenGLShader::create()
{
    d_ptr->shaderId = 0;
    if (d_ptr->shaderType == Vertex)
        d_ptr->shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if (d_ptr->shaderType == Fragment)
        d_ptr->shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (!d_ptr->shaderId)
    {
        qWarning("HOpenGLShader: could not create shader");
        return false;
    }
    return true;
}

bool HOpenGLShader::compile()
{
    if (!d_ptr->shaderId)
        return false;

    // Try to compile shader
    glCompileShader(d_ptr->shaderId);
    // Get compilation status
    GLint value = 0;
    glGetShaderiv(d_ptr->shaderId, GL_COMPILE_STATUS, &value);
    d_ptr->compiled = (value != 0);
    if (d_ptr->compiled)
        return true;

    // Compilation failed, try to provide some information about the failure
    GLint infoLogLength = 0;
    GLint sourceCodeLength = 0;
    GLint temp;
    char *logBuffer = nullptr;
    char *sourceCodeBuffer = nullptr;
    auto name = objectName();
    auto type = d_ptr->shaderType == Vertex ? "Vertex" : "Fragment";
    // Get the compilation info log
    glGetShaderiv(d_ptr->shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1)
    {
        logBuffer = new char[infoLogLength];
        glGetShaderInfoLog(d_ptr->shaderId, infoLogLength, &temp, logBuffer);
    }
    // Get the source code
    glGetShaderiv(d_ptr->shaderId, GL_SHADER_SOURCE_LENGTH, &sourceCodeLength);
    if (sourceCodeLength > 1)
    {
        sourceCodeBuffer = new char [sourceCodeLength];
        glGetShaderSource(d_ptr->shaderId, sourceCodeLength, &temp, sourceCodeBuffer);
    }
    d_ptr->log = logBuffer ? QString::fromLatin1(logBuffer) : QLatin1String("failed");
    // Print error
    if (name.isEmpty())
        qWarning("HOpenGLShader::compile(%s): %s", type, qPrintable(d_ptr->log));
    else
        qWarning("HOpenGLShader::compile(%s)[%s]: %s", type, qPrintable(name), qPrintable(d_ptr->log));
    // Dump the source code if we got it
    if (sourceCodeBuffer)
    {
        qWarning("*** Problematic %s shader source code ***\n"
                 "%ls\n"
                 "***",
                 type, qUtf16Printable(QString::fromLatin1(sourceCodeBuffer)));
    }
    // Cleanup
    delete [] logBuffer;
    delete [] sourceCodeBuffer;
    return false;
}

void HOpenGLShader::free()
{
    if (d_ptr->shaderId)
        glDeleteShader(d_ptr->shaderId);
}

HOpenGLShaderProgram::HOpenGLShaderProgram(QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLShaderProgramPrivate)
{
}

HOpenGLShaderProgram::~HOpenGLShaderProgram()
{
    free();
}

GLuint HOpenGLShaderProgram::programId() const
{
    if (d_ptr->programId)
        return d_ptr->programId;
    if (!const_cast<HOpenGLShaderProgram *>(this)->init())
        return 0;
    return d_ptr->programId;
}

bool HOpenGLShaderProgram::isLinked() const
{
    return d_ptr->linked;
}

QString HOpenGLShaderProgram::log() const
{
    return d_ptr->log;
}

QList<HOpenGLShader *> HOpenGLShaderProgram::shaders() const
{
    return d_ptr->shaders;
}

bool HOpenGLShaderProgram::addShader(HOpenGLShader *p)
{
    if (!init() || p == nullptr || !p->shaderId())
        return false;
    if (d_ptr->shaders.contains(p))
        return true;

    glAttachShader(d_ptr->programId, p->shaderId());
    d_ptr->linked = false;
    d_ptr->shaders.append(p);
    connect(p, &HOpenGLShader::destroyed, this, &HOpenGLShaderProgram::shaderDestroyed);
    return true;
}

bool HOpenGLShaderProgram::addShaderFromSourceCode(HOpenGLShader::ShaderType type, const char *source)
{
    if (!init())
        return false;
    auto shader = new HOpenGLShader(type, this);
    if (!shader->compileSourceCode(source))
    {
        d_ptr->log = shader->log();
        delete shader;
        return false;
    }
    return addShader(shader);
}

bool HOpenGLShaderProgram::addShaderFromSourceCode(HOpenGLShader::ShaderType type, const QByteArray &source)
{
    return addShaderFromSourceCode(type, source.constData());
}

bool HOpenGLShaderProgram::addShaderFromSourceCode(HOpenGLShader::ShaderType type, const QString &source)
{
    return addShaderFromSourceCode(type, source.toLatin1().constData());
}

bool HOpenGLShaderProgram::addShaderFromSourceFile(HOpenGLShader::ShaderType type, const QString &fileName)
{
    if (!init())
        return false;
    auto *shader = new HOpenGLShader(type, this);
    if (!shader->compileSourceFile(fileName))
    {
        d_ptr->log = shader->log();
        delete shader;
        return false;
    }
    return addShader(shader);
}

void HOpenGLShaderProgram::removeShader(HOpenGLShader *p)
{
    if (d_ptr->programId && p && p->shaderId())
        glDetachShader(d_ptr->programId, p->shaderId());
    d_ptr->linked = false;
    if (p)
    {
        d_ptr->shaders.removeAll(p);
        disconnect(p, &HOpenGLShader::destroyed, this, &HOpenGLShaderProgram::shaderDestroyed);
    }
}

void HOpenGLShaderProgram::removeAllShaders()
{
    d_ptr->removingShaders = true;
    for (auto p : d_ptr->shaders)
    {
        if (d_ptr->programId && p && p->shaderId())
            glDetachShader(d_ptr->programId, p->shaderId());
    }
    d_ptr->shaders.clear();
    d_ptr->linked = false;
    d_ptr->removingShaders = false;
}

bool HOpenGLShaderProgram::create()
{
    return init();
}

bool HOpenGLShaderProgram::link()
{
    if (!d_ptr->programId || d_ptr->shaders.isEmpty())
        return false;

    GLint value = 0;
    GLint temp;
    glLinkProgram(d_ptr->programId);
    glGetProgramiv(d_ptr->programId, GL_LINK_STATUS, &value);
    d_ptr->linked = (value != 0);
    d_ptr->log = QString();

    glGetProgramiv(d_ptr->programId, GL_INFO_LOG_LENGTH, &value);
    if (value > 1)
    {
        auto logBuffer = new char[value];
        glGetProgramInfoLog(d_ptr->programId, value, &temp, logBuffer);
        d_ptr->log = QString::fromLatin1(logBuffer);
        if (!d_ptr->linked)
        {
            auto name = objectName();
            if (name.isEmpty())
                qWarning("HOpenGLShader::link: %ls", qUtf16Printable(d_ptr->log));
            else
                qWarning("HOpenGLShader::link[%ls]: %ls", qUtf16Printable(name), qUtf16Printable(d_ptr->log));
        }
        delete [] logBuffer;
    }
    return d_ptr->linked;
}

bool HOpenGLShaderProgram::bind()
{
    if (!d_ptr->programId)
        return false;
    if (!d_ptr->linked && !link())
        return false;
    glUseProgram(d_ptr->programId);
    return true;
}

void HOpenGLShaderProgram::release()
{
    glUseProgram(0);
}

void HOpenGLShaderProgram::free()
{
    if (d_ptr->programId)
        glDeleteProgram(d_ptr->programId);
}

void HOpenGLShaderProgram::bindAttributeLocation(const char *name, int location)
{
    if (!init() || !d_ptr->programId)
        return;
    glBindAttribLocation(d_ptr->programId, location, name);
    d_ptr->linked = false;
}

void HOpenGLShaderProgram::bindAttributeLocation(const QByteArray &name, int location)
{
    bindAttributeLocation(name.constData(), location);
}

void HOpenGLShaderProgram::bindAttributeLocation(const QString &name, int location)
{
    bindAttributeLocation(name.toLatin1().constData(), location);
}

int HOpenGLShaderProgram::attributeLocation(const char *name) const
{
    if (d_ptr->linked && d_ptr->programId)
        return glGetAttribLocation(d_ptr->programId, name);
    qWarning("HOpenGLShaderProgram::attributeLocation(%s): shader program is not linked", name);
    return -1;
}

int HOpenGLShaderProgram::attributeLocation(const QByteArray &name) const
{
    return attributeLocation(name.constData());
}

int HOpenGLShaderProgram::attributeLocation(const QString &name) const
{
    return attributeLocation(name.toLatin1().constData());
}

int HOpenGLShaderProgram::uniformLocation(const char *name) const
{
    if (d_ptr->linked && d_ptr->programId)
        return glGetUniformLocation(d_ptr->programId, name);
    qWarning("HOpenGLShaderProgram::uniformLocation(%s): shader program is not linked", name);
    return -1;
}

int HOpenGLShaderProgram::uniformLocation(const QByteArray &name) const
{
    return uniformLocation(name.constData());
}

int HOpenGLShaderProgram::uniformLocation(const QString &name) const
{
    return uniformLocation(name.toLatin1().constData());
}

bool HOpenGLShaderProgram::init()
{
    if (d_ptr->programId)
        return true;
    d_ptr->programId = glCreateProgram();
    if (!d_ptr->programId)
    {
        qWarning("QOpenGLShaderProgram: could not create shader program");
        return false;
    }
    return true;
}

void HOpenGLShaderProgram::shaderDestroyed()
{
    auto p = qobject_cast<HOpenGLShader *>(sender());
    if (p && !d_ptr->removingShaders)
        removeShader(p);
}

HE_REFERENCE_END_NAMESPACE
