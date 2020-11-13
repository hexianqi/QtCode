#include "HParticleRenderer_p.h"
#include "HGameObject.h"
#include <QtCore/QRandomGenerator>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLShaderProgram>

HE_CONTROL_BEGIN_NAMESPACE

void HParticle::update(float dt)
{
    Life -= dt;
    Position -= Velocity * dt;
    Color.setW(Color.w() - dt * 2.5f);
}

void HParticle::respawn(QVector2D position, QVector2D velocity, QVector2D offset)
{
    QRandomGenerator random;
    auto x = random.generateDouble() * 10.0 - 5;
    auto y = random.generateDouble() * 10.0 - 5;
    auto color = 0.5 + random.generateDouble();
    this->Position = position + offset + QVector2D(x, y);
    this->Color = QVector4D(color, color, color, 1.0f);
    this->Life = 1.0f;
    this->Velocity = velocity * 0.1f;
}

HParticle *HParticleRendererPrivate::unusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (int i = lastUsed; i < particles.size(); i++)
    {
        if (particles[i]->Life <= 0.0f)
        {
            lastUsed = i;
            return particles[i];
        }
    }
    // otherwise, do a linear search
    for (int i = 0; i < lastUsed; i++)
    {
        if (particles[i]->Life <= 0.0f)
        {
            lastUsed = i;
            return particles[i];
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsed = 0;
    return nullptr;
}

HParticleRenderer::HParticleRenderer(int amount, QOpenGLShaderProgram *shader, QObject *parent) :
    HAbstractRenderer(*new HParticleRendererPrivate, shader, parent)
{
    init(amount);
}

HParticleRenderer::~HParticleRenderer()
{
    Q_D(HParticleRenderer);
    qDeleteAll(d->particles);
}

void HParticleRenderer::setTexture(QOpenGLTexture *p)
{
    Q_D(HParticleRenderer);
    d->texture = p;
}

void HParticleRenderer::update(float dt)
{
    Q_D(HParticleRenderer);
    for (auto p : d->particles)
        p->update(dt);
}

void HParticleRenderer::respawn(HGameObject *obj, int amount)
{
    Q_D(HParticleRenderer);
    for (int i = 0; i < amount; i++)
    {
        auto p = d->unusedParticle();
        if (p == nullptr)
            break;
        p->respawn(obj->position(), obj->velocity(), obj->size() / 4.0f);
    }
}

void HParticleRenderer::draw()
{
    Q_D(HParticleRenderer);
    // use additive blending to give it a 'glow' effect
    QOpenGLVertexArrayObject::Binder binder(&d->vao);
    d->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    d->texture->bind(0);
    d->shader->bind();
    for (auto p : d->particles)
    {
        if (p->Life <= 0.0f)
            continue;
        d->shader->setUniformValue("offset", p->Position);
        d->shader->setUniformValue("color", p->Color);
        d->funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    // don't forget to reset to default blending mode
    d->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void HParticleRenderer::init(int amount)
{
    Q_D(HParticleRenderer);
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

    for (int i = 0; i < amount; i++)
        d->particles << new HParticle;
}

HE_CONTROL_END_NAMESPACE
