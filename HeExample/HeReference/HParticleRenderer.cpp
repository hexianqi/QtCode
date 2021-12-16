#include "HParticleRenderer_p.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLTexture2D.h"
#include "HGameObject.h"
#include <QtCore/QRandomGenerator>

HE_BEGIN_NAMESPACE

void HParticle::update(float dt)
{
    Life -= dt * 3;
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

HParticleRenderer::HParticleRenderer(HOpenGLShaderProgram *shader, int amount, QObject *parent) :
    QObject(parent),
    d_ptr(new HParticleRendererPrivate)
{
    d_ptr->shader = shader;
    init(amount);
}

HParticleRenderer::~HParticleRenderer()
{
    qDeleteAll(d_ptr->particles);
}

void HParticleRenderer::setTexture(HOpenGLTexture2D *p)
{
    d_ptr->texture = p;
}

void HParticleRenderer::update(float dt)
{
    for (auto p : d_ptr->particles)
        p->update(dt);
}

void HParticleRenderer::respawn(HGameObject *obj, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        auto p = d_ptr->unusedParticle();
        if (p == nullptr)
            break;
        p->respawn(obj->position(), obj->velocity(), obj->size() / 4.0f);
    }
}

void HParticleRenderer::draw()
{
    // use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBindVertexArray(d_ptr->vao);
    d_ptr->texture->bind(0);
    d_ptr->shader->bind();
    for (auto p : d_ptr->particles)
    {
        if (p->Life <= 0.0f)
            continue;
        d_ptr->shader->setUniformValue("offset", p->Position);
        d_ptr->shader->setUniformValue("color", p->Color);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);
    // don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void HParticleRenderer::init(int amount)
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

    for (int i = 0; i < amount; i++)
        d_ptr->particles << new HParticle;
}

HE_END_NAMESPACE
