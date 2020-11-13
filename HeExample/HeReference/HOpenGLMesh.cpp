#include "HOpenGLMesh_p.h"
#include "HOpenGLShaderProgram.h"
#include "glad/glad.h"
#include <QtGui/QMatrix4x4>

HE_REFERENCE_BEGIN_NAMESPACE

void HOpenGLMeshPrivate::setup()
{
    // create buffers/arrays
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    // load data into vertex buffers
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    glEnableVertexAttribArray(4);
    glBindVertexArray(0);
}

HOpenGLMesh::HOpenGLMesh(QVector<Vertex> vertices, QVector<unsigned int> indices, QVector<Texture> textures, QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLMeshPrivate)
{
    d_ptr->vertices = vertices;
    d_ptr->indices = indices;
    d_ptr->textures = textures;
    d_ptr->setup();
}

HOpenGLMesh::~HOpenGLMesh()
{
    glDeleteVertexArrays(1, &d_ptr->vao);
    glDeleteBuffers(1, &d_ptr->vbo);
    glDeleteBuffers(1, &d_ptr->ebo);
}

void HOpenGLMesh::setInstancedMatrix(int location)
{
    glBindVertexArray(d_ptr->vao);
    for (int i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(location + i);
        glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(QVector4D) * 4, (void*)(i * sizeof(QVector4D)));
        glVertexAttribDivisor(location + i, 1);
    }
    glBindVertexArray(0);
}

void HOpenGLMesh::draw(HOpenGLShaderProgram *shader, int amount)
{
    // bind appropriate textures
    unsigned int diffuse  = 1;
    unsigned int specular = 1;
    unsigned int normal   = 1;
    unsigned int height   = 1;
    for (int i = 0; i < d_ptr->textures.size(); i++)
    {
        // retrieve texture number (the N in diffuse_textureN)
        QString name;
        auto type = d_ptr->textures[i].Type;
        if (type == "texture_diffuse")
            name = QString("%1%2").arg(type).arg(diffuse++);
        else if (type == "texture_specular")
            name = QString("%1%2").arg(type).arg(specular++);
        else if (type == "texture_normal")
            name = QString("%1%2").arg(type).arg(normal++);
        else if (type == "texture_height")
            name = QString("%1%2").arg(type).arg(height++);
        // active proper texture unit before binding
        glActiveTexture(GL_TEXTURE0 + i);
        // now set the sampler to the correct texture unit
        shader->setUniformValue(name.toStdString().c_str(), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, d_ptr->textures[i].Id);
    }

    // draw mesh
    glBindVertexArray(d_ptr->vao);
    if (amount > 0)
        glDrawElementsInstanced(GL_TRIANGLES, d_ptr->indices.size(), GL_UNSIGNED_INT, 0, amount);
    else
        glDrawElements(GL_TRIANGLES, d_ptr->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

HE_REFERENCE_END_NAMESPACE
