#include "HSpriteRenderer_p.h"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

HE_BEGIN_NAMESPACE

HSpriteRenderer::HSpriteRenderer(QOpenGLShaderProgram *shader, QObject *parent) :
    HAbstractRenderer(*new HSpriteRendererPrivate, shader, parent)
{
    init();
}

HSpriteRenderer::~HSpriteRenderer() = default;

void HSpriteRenderer::draw(QVector2D position, QVector2D size, float rotate, QVector3D color)
{
    Q_D(HSpriteRenderer);
    QMatrix4x4 model;
    model.translate(position);
    model.translate(size * 0.5);
    model.rotate(rotate, 0.0, 0.0, 1.0);
    model.translate(size * -0.5);
    model.scale(size);
    d_ptr->shader->bind();
    d_ptr->shader->setUniformValue("model", model);
    d_ptr->shader->setUniformValue("color", color);
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    d->funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
}

void HSpriteRenderer::init()
{
    Q_D(HSpriteRenderer);
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices, sizeof(vertices));
    d->funcs->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    d->funcs->glEnableVertexAttribArray(0);
}

HE_END_NAMESPACE
