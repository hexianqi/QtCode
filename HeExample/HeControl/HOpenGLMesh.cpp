#include "HOpenGLMesh_p.h"
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLExtraFunctions>

HE_CONTROL_BEGIN_NAMESPACE

HHOpenGLMeshPrivate::HHOpenGLMeshPrivate()
{
    funcs = QOpenGLContext::currentContext()->extraFunctions();
}

void HHOpenGLMeshPrivate::setup()
{
    QOpenGLVertexArrayObject::Binder binder(&vao);
    auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    auto ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices.data(), vertices.size() * sizeof(Vertex));
    ebo->create();
    ebo->bind();
    ebo->allocate(indices.data(), indices.size() * sizeof(unsigned int));
    funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    funcs->glEnableVertexAttribArray(0);
    funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    funcs->glEnableVertexAttribArray(1);
    funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    funcs->glEnableVertexAttribArray(2);
    funcs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    funcs->glEnableVertexAttribArray(3);
    funcs->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    funcs->glEnableVertexAttribArray(4);
}

void HHOpenGLMeshPrivate::buildTexture(QOpenGLShaderProgram *p)
{
    int i = 0;
    for (auto it = textures.begin(); it != textures.end(); it++)
    {
        p->setUniformValue(it.key().toStdString().c_str(), i);
        it.value()->bind(i);
        i++;
    }
}

HOpenGLMesh::HOpenGLMesh(QVector<Vertex> vertices, QVector<unsigned int> indices, QHash<QString, QOpenGLTexture *> textures, QObject *parent) :
    QObject(parent),
    d_ptr(new HHOpenGLMeshPrivate)
{
    d_ptr->vertices = vertices;
    d_ptr->indices = indices;
    d_ptr->textures = textures;
    d_ptr->setup();
}

HOpenGLMesh::~HOpenGLMesh()
{
}

void HOpenGLMesh::draw(QOpenGLShaderProgram *p, int amount)
{
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->vao);
    d_ptr->buildTexture(p);
    if (amount < 1)
        d_ptr->funcs->glDrawElements(GL_TRIANGLES, d_ptr->indices.size(), GL_UNSIGNED_INT, 0);
    else
        d_ptr->funcs->glDrawElementsInstanced(GL_TRIANGLES, d_ptr->indices.size(), GL_UNSIGNED_INT, 0, amount);
    // always good practice to set everything back to defaults once configured.
    d_ptr->funcs->glActiveTexture(GL_TEXTURE0);
}

void HOpenGLMesh::setInstancedMatrix(int location)
{
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->vao);
    for (int i = 0; i < 4; i++)
    {
        d_ptr->funcs->glEnableVertexAttribArray(location + i);
        d_ptr->funcs->glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(QVector4D) * 4, (void*)(i * sizeof(QVector4D)));
        d_ptr->funcs->glVertexAttribDivisor(location + i, 1);
    }
}

HE_CONTROL_END_NAMESPACE
