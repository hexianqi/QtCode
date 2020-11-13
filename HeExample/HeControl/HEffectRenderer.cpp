#include "HEffectRenderer_p.h"
#include <QtCore/QTime>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

HE_CONTROL_BEGIN_NAMESPACE

HEffectRendererPrivate::HEffectRendererPrivate()
{
    format1.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format1.setMipmap(true);
    format1.setSamples(4);
    format1.setTextureTarget(GL_TEXTURE_2D);
    format1.setInternalTextureFormat(GL_RGBA);
    format2.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format2.setMipmap(true);
    format2.setTextureTarget(GL_TEXTURE_2D);
    format2.setInternalTextureFormat(GL_RGBA);
}

HEffectRenderer::HEffectRenderer(int width, int height, QOpenGLShaderProgram *shader, QObject *parent) :
    HAbstractRenderer(*new HEffectRendererPrivate, shader, parent)
{
    init(width, height);
}

HEffectRenderer::~HEffectRenderer()
{
}

void HEffectRenderer::setConfuse(bool b)
{
    Q_D(HEffectRenderer);
    d->confuse = b;
}

void HEffectRenderer::setChaos(bool b)
{
    Q_D(HEffectRenderer);
    d->chaos = b;
}

void HEffectRenderer::updateShake(float dt)
{
    Q_D(HEffectRenderer);
    if (d->shakeTime > 0.0f)
        setShakeTime(d->shakeTime - dt);
}

void HEffectRenderer::setShakeTime(float value)
{
    Q_D(HEffectRenderer);
    d->shakeTime = value;
    d->shake = d->shakeTime > 0.0f;
}

void HEffectRenderer::reset()
{
    setShakeTime(0.0f);
    setChaos(false);
    setConfuse(false);
}

void HEffectRenderer::begin()
{
    Q_D(HEffectRenderer);
    d->fbo1->bind();
    d->funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    d->funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HEffectRenderer::end()
{
    Q_D(HEffectRenderer);
    QOpenGLFramebufferObject::blitFramebuffer(d->fbo2.data(), d->fbo1.data(), GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT, GL_NEAREST);
    d->fbo1->release();
}

void HEffectRenderer::draw()
{
    Q_D(HEffectRenderer);
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    d->shader->bind();
    d->shader->setUniformValue("time", QTime::currentTime().msecsSinceStartOfDay() / 1000.0f);
    d->shader->setUniformValue("confuse", d->confuse);
    d->shader->setUniformValue("chaos", d->chaos);
    d->shader->setUniformValue("shake", d->shake);
    d->funcs->glActiveTexture(GL_TEXTURE0);
    d->funcs->glBindTexture(GL_TEXTURE_2D, d->fbo2->texture());
    d->funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
}

void HEffectRenderer::init(int width, int height)
{
    Q_D(HEffectRenderer);
    d->width = width;
    d->height = height;
    d->fbo1.reset(new QOpenGLFramebufferObject(width, height, d->format1));
    d->fbo2.reset(new QOpenGLFramebufferObject(width, height, d->format2));

    // initialize VAO/VBO
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };

    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices, sizeof(vertices));
    d->funcs->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    d->funcs->glEnableVertexAttribArray(0);

    // initialize render data and uniforms
    float offset = 1.0f / 300.0f;
    float offsets[9][2] = {
        { -offset,  offset  },  // top-left
        {  0.0f,    offset  },  // top-center
        {  offset,  offset  },  // top-right
        { -offset,  0.0f    },  // center-left
        {  0.0f,    0.0f    },  // center-center
        {  offset,  0.0f    },  // center - right
        { -offset, -offset  },  // bottom-left
        {  0.0f,   -offset  },  // bottom-center
        {  offset, -offset  }   // bottom-right
    };
    int edge_kernel[9] = {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };
    float blur_kernel[9] = {
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
        2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    };
    d_ptr->shader->bind();
    d_ptr->shader->setUniformValue("texture1", 0);
    d_ptr->shader->setUniformValueArray("offsets", (float*)offsets, 9, 2);
    d_ptr->shader->setUniformValueArray("edge_kernel", edge_kernel, 9);
    d_ptr->shader->setUniformValueArray("blur_kernel", blur_kernel, 9, 1);
}

HE_CONTROL_END_NAMESPACE
