#include "HSpriteRenderer_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>

HE_REFERENCE_BEGIN_NAMESPACE

HSpriteRenderer::HSpriteRenderer(HOpenGLShaderProgram *shader, QObject *parent) :
    QObject(parent),
    d_ptr(new HSpriteRendererPrivate)
{
    d_ptr->shader = shader;
    init();
}

HSpriteRenderer::~HSpriteRenderer()
{
    glDeleteVertexArrays(1, &d_ptr->vao);
}

void HSpriteRenderer::draw(QVector2D position, QVector2D size, float rotate, QVector3D color)
{
    QMatrix4x4 model;
    model.translate(position);
    model.translate(size * 0.5);
    model.rotate(rotate, 0.0, 0.0, 1.0);
    model.translate(size * -0.5);
    model.scale(size);
    d_ptr->shader->bind();
    d_ptr->shader->setUniformValue("model", model);
    d_ptr->shader->setUniformValue("color", color);
    glBindVertexArray(d_ptr->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void HSpriteRenderer::init()
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int vbo;
    glGenVertexArrays(1, &d_ptr->vao);
    glBindVertexArray(d_ptr->vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

HE_REFERENCE_END_NAMESPACE
