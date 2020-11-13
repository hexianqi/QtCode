#include "HEffectRenderer_p.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLTexture2D.h"
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

HEffectRenderer::HEffectRenderer(HOpenGLShaderProgram *shader, int width, int height, QObject *parent) :
    QObject(parent),
    d_ptr(new HEffectRendererPrivate)
{
    d_ptr->shader = shader;
    d_ptr->width = width;
    d_ptr->height = height;
    d_ptr->texture = new HOpenGLTexture2D;
    d_ptr->texture->generate(width, height, nullptr);
    init();
}

HEffectRenderer::~HEffectRenderer()
{

}

void HEffectRenderer::setConfuse(bool b)
{
    d_ptr->confuse = b;
}

void HEffectRenderer::setChaos(bool b)
{
    d_ptr->chaos = b;
}

void HEffectRenderer::updateShake(float dt)
{
    if (d_ptr->shakeTime > 0.0f)
        setShakeTime(d_ptr->shakeTime - dt);
}

void HEffectRenderer::setShakeTime(float value)
{
    d_ptr->shakeTime = value;
    d_ptr->shake = d_ptr->shakeTime > 0.0f;
}

void HEffectRenderer::reset()
{
    setShakeTime(0.0f);
    d_ptr->chaos = false;
    d_ptr->confuse = false;
}

void HEffectRenderer::begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, d_ptr->fbo2);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void HEffectRenderer::end()
{
    // now resolve multisampled color-buffer into intermediate FBO to store to texture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, d_ptr->fbo2);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, d_ptr->fbo1);
    glBlitFramebuffer(0, 0, d_ptr->width, d_ptr->height, 0, 0, d_ptr->width, d_ptr->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void HEffectRenderer::draw(float time)
{
    d_ptr->shader->bind();
    d_ptr->shader->setUniformValue("time", time);
    d_ptr->shader->setUniformValue("confuse", d_ptr->confuse);
    d_ptr->shader->setUniformValue("chaos", d_ptr->chaos);
    d_ptr->shader->setUniformValue("shake", d_ptr->shake);
    d_ptr->texture->bind(0);
    glBindVertexArray(d_ptr->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void HEffectRenderer::init()
{
    // initialize renderbuffer/framebuffer object
    glGenFramebuffers(1, &d_ptr->fbo1);
    glGenFramebuffers(1, &d_ptr->fbo2);
    glGenRenderbuffers(1, &d_ptr->rbo);
    // initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
    glBindFramebuffer(GL_FRAMEBUFFER, d_ptr->fbo2);
    glBindRenderbuffer(GL_RENDERBUFFER, d_ptr->rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, d_ptr->width, d_ptr->height); // allocate storage for render buffer object
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, d_ptr->rbo); // attach MS render buffer object to framebuffer
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "HEffectRenderer: Failed to initialize MSFBO";
    // also initialize the FBO/texture to blit multisampled color-buffer to; used for shader operations (for postprocessing effects)
    glBindFramebuffer(GL_FRAMEBUFFER, d_ptr->fbo1);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d_ptr->texture->textureID(), 0); // attach texture to framebuffer as its color attachment
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "HEffectRenderer: Failed to initialize FBO";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure VAO/VBO
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
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

HE_REFERENCE_END_NAMESPACE
