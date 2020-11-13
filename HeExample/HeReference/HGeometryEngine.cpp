#include "HGeometryEngine_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtCore/QVector>
#include <QtGui/QVector2D>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

HGeometryEngine::HGeometryEngine(QObject *parent) :
    QObject(parent),
    d_ptr(new HGeometryEnginePrivate)
{
}

HGeometryEngine::HGeometryEngine(HGeometryEnginePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HGeometryEngine::~HGeometryEngine()
{
    glDeleteVertexArrays(1, &d_ptr->triangleVao);
    glDeleteVertexArrays(1, &d_ptr->rectVao);
    glDeleteVertexArrays(1, &d_ptr->screenVao);
    glDeleteVertexArrays(1, &d_ptr->planeVao);
    glDeleteVertexArrays(1, &d_ptr->quadVao);
    glDeleteVertexArrays(1, &d_ptr->cubeVao);
    glDeleteVertexArrays(1, &d_ptr->sphereVao);
    glDeleteVertexArrays(1, &d_ptr->skyboxVao);
}

void HGeometryEngine::renderTriangle(HOpenGLShaderProgram *)
{
    if (d_ptr->triangleVao == 0)
    {
        GLfloat positions[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        GLfloat color[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        unsigned int vbo;
        glGenVertexArrays(1, &d_ptr->triangleVao);
        glBindVertexArray(d_ptr->triangleVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(color), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(color), color);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(positions)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->triangleVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void HGeometryEngine::renderRect(HOpenGLShaderProgram *)
{
    if (d_ptr->rectVao == 0)
    {
        GLfloat positions[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f
        };

        GLfloat color[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f
        };

        GLfloat texture[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
        };

        GLuint indice[] = {
            0, 1, 2,
            1, 2, 3
        };

        unsigned int vbo, ebo;
        glGenVertexArrays(1, &d_ptr->rectVao);
        glBindVertexArray(d_ptr->rectVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(color) + sizeof(texture), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(color), color);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(color), sizeof(texture), texture);
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(positions)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(positions) + sizeof(color)));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->rectVao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void HGeometryEngine::renderScreen(HOpenGLShaderProgram *)
{
    if (d_ptr->screenVao == 0)
    {
        GLfloat positions[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, 0.0f
        };

        GLfloat normal[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        GLfloat texture[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
        };

        GLuint indice[] = {
            0, 1, 2,
            1, 2, 3
        };

        unsigned int vbo, ebo;
        glGenVertexArrays(1, &d_ptr->screenVao);
        glBindVertexArray(d_ptr->screenVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normal) + sizeof(texture), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normal), normal);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normal), sizeof(texture), texture);
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(positions)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(positions) + sizeof(normal)));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->screenVao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void HGeometryEngine::renderPlane(HOpenGLShaderProgram *)
{
    if (d_ptr->planeVao == 0)
    {
        GLfloat positions[] = {
            -25.0f, -0.5f,  25.0f,
             25.0f, -0.5f,  25.0f,
            -25.0f, -0.5f, -25.0f,
             25.0f, -0.5f, -25.0f
        };

        GLfloat normal[] = {
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        GLfloat texture[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
        };

        GLuint indice[] = {
            0, 1, 2,
            1, 2, 3
        };

        unsigned int vbo, ebo;
        glGenVertexArrays(1, &d_ptr->planeVao);
        glBindVertexArray(d_ptr->planeVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normal) + sizeof(texture), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normal), normal);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normal), sizeof(texture), texture);
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(positions)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(positions) + sizeof(normal)));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->planeVao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void HGeometryEngine::renderQuad(HOpenGLShaderProgram *)
{
    if (d_ptr->quadVao == 0)
    {
        // positions
        QVector3D pos1(-1.0f,  1.0f, 0.0f);
        QVector3D pos2(-1.0f, -1.0f, 0.0f);
        QVector3D pos3( 1.0f, -1.0f, 0.0f);
        QVector3D pos4( 1.0f,  1.0f, 0.0f);
        // texture coordinates
        QVector2D uv1(0.0f, 1.0f);
        QVector2D uv2(0.0f, 0.0f);
        QVector2D uv3(1.0f, 0.0f);
        QVector2D uv4(1.0f, 1.0f);
        // normal vector
        QVector3D nm(0.0f, 0.0f, 1.0f);

        // calculate tangent/bitangent vectors of both triangles
        QVector3D tangent1, bitangent1;
        QVector3D tangent2, bitangent2;
        // triangle 1
        auto edge1 = pos2 - pos1;
        auto edge2 = pos3 - pos1;
        auto deltaUV1 = uv2 - uv1;
        auto deltaUV2 = uv3 - uv1;
        auto f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());
        tangent1.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent1.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent1.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));
        bitangent1.setX(f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent1.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent1.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));
        // triangle 2
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;
        f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());
        tangent2.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent2.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent2.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));
        bitangent2.setX(f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent2.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent2.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));

        float quadVertices[] = {
            // positions                  // normal               // texcoords      // tangent                                // bitangent
            pos1.x(), pos1.y(), pos1.z(), nm.x(), nm.y(), nm.z(), uv1.x(), uv1.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),
            pos2.x(), pos2.y(), pos2.z(), nm.x(), nm.y(), nm.z(), uv2.x(), uv2.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),
            pos3.x(), pos3.y(), pos3.z(), nm.x(), nm.y(), nm.z(), uv3.x(), uv3.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),

            pos1.x(), pos1.y(), pos1.z(), nm.x(), nm.y(), nm.z(), uv1.x(), uv1.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z(),
            pos3.x(), pos3.y(), pos3.z(), nm.x(), nm.y(), nm.z(), uv3.x(), uv3.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z(),
            pos4.x(), pos4.y(), pos4.z(), nm.x(), nm.y(), nm.z(), uv4.x(), uv4.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z()
        };

        unsigned int vbo;
        glGenVertexArrays(1, &d_ptr->quadVao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(d_ptr->quadVao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->quadVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void HGeometryEngine::renderCube(HOpenGLShaderProgram *)
{
    if (d_ptr->cubeVao == 0)
    {
        GLfloat position[] = {
            // Back face
           -1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           // Front face
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,
           // Left face
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           // Right face
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           // Bottom face
           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,
           // Top face
           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f
        };

        GLfloat normal[] = {
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,

             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,

            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,

             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,

             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f
        };

        GLfloat texture[] = {
            // Back face
            0.0f, 0.0f, // bottom-left
            1.0f, 1.0f, // top-right
            1.0f, 0.0f, // bottom-right
            1.0f, 1.0f, // top-right
            0.0f, 0.0f, // bottom-left
            0.0f, 1.0f, // top-left
            // Front face
            0.0f, 0.0f, // bottom-left
            1.0f, 0.0f, // bottom-right
            1.0f, 1.0f, // top-right
            1.0f, 1.0f, // top-right
            0.0f, 1.0f, // top-left
            0.0f, 0.0f, // bottom-left
            // Left face
            1.0f, 0.0f, // top-right
            1.0f, 1.0f, // top-left
            0.0f, 1.0f, // bottom-left
            0.0f, 1.0f, // bottom-left
            0.0f, 0.0f, // bottom-right
            1.0f, 0.0f, // top-right
            // Right face
            1.0f, 0.0f, // top-left
            0.0f, 1.0f, // bottom-right
            1.0f, 1.0f, // top-right
            0.0f, 1.0f, // bottom-right
            1.0f, 0.0f, // top-left
            0.0f, 0.0f, // bottom-left
            // Bottom face
            0.0f, 1.0f, // top-right
            1.0f, 1.0f, // top-left
            1.0f, 0.0f, // bottom-left
            1.0f, 0.0f, // bottom-left
            0.0f, 0.0f, // bottom-right
            0.0f, 1.0f, // top-right
            // Top face
            0.0f, 1.0f, // top-left
            1.0f, 0.0f, // bottom-right
            1.0f, 1.0f, // top-right
            1.0f, 0.0f, // bottom-right
            0.0f, 1.0f, // top-left
            0.0f, 0.0f  // bottom-left
        };

        unsigned int vbo;
        glGenVertexArrays(1, &d_ptr->cubeVao);
        glBindVertexArray(d_ptr->cubeVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(position) + sizeof(normal) + sizeof(texture), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(position), position);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(position), sizeof(normal), normal);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(position) + sizeof(normal), sizeof(texture), texture);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(position) + sizeof(normal)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }
    glBindVertexArray(d_ptr->cubeVao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void HGeometryEngine::renderSphere(HOpenGLShaderProgram *)
{
    if (d_ptr->sphereVao == 0)
    {
        QVector<QVector3D> positions;
        QVector<QVector3D> normals;
        QVector<QVector2D> uv;
        QVector<unsigned int> indices;

        const int X_SEGMENTS = 64;
        const int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (int x = 0; x <= X_SEGMENTS; ++x)
            {
                auto xSegment = 1.0f * x / X_SEGMENTS;
                auto ySegment = 1.0f * y / Y_SEGMENTS;
                auto xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                auto yPos = std::cos(ySegment * PI);
                auto zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions << QVector3D(xPos, yPos, zPos);
                normals << QVector3D(xPos, yPos, zPos);
                uv << QVector2D(xSegment, ySegment);
            }
        }

        bool oddRow = false;
        for (int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices <<  y      * (X_SEGMENTS + 1) + x
                            << (y + 1) * (X_SEGMENTS + 1) + x;
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices << (y + 1) * (X_SEGMENTS + 1) + x
                            <<  y      * (X_SEGMENTS + 1) + x;
                }
            }
            oddRow = !oddRow;
        }

        auto positionSize = sizeof(QVector3D) * positions.size();
        auto normalsSize = sizeof(QVector3D) * normals.size();
        auto uvSize = sizeof(QVector2D) * uv.size();
        auto indicesSize = sizeof(unsigned int) * indices.size();

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &d_ptr->sphereVao);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(d_ptr->sphereVao);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, positionSize + normalsSize + uvSize, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, positionSize, positions.data());
        glBufferSubData(GL_ARRAY_BUFFER, positionSize, normalsSize, normals.data());
        glBufferSubData(GL_ARRAY_BUFFER, positionSize + normalsSize, uvSize, uv.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &indices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(positionSize));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(positionSize + normalsSize));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(d_ptr->sphereVao);
    glDrawElements(GL_TRIANGLE_STRIP, 65 * 64 * 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void HGeometryEngine::renderSkybox(HOpenGLShaderProgram *)
{
    if (d_ptr->skyboxVao == 0)
    {
        GLfloat position[] = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        unsigned int vbo;
        glGenVertexArrays(1, &d_ptr->skyboxVao);
        glBindVertexArray(d_ptr->skyboxVao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glBindVertexArray(d_ptr->skyboxVao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}

void HGeometryEngine::renderScene(HOpenGLShaderProgram *p)
{
    QMatrix4x4 model;
    model.setToIdentity();
    p->setUniformValue("model", model);
    renderPlane(p);
    model.setToIdentity();
    model.translate(0.0f, 1.5f, 0.0f);
    model.scale(0.5f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(2.0f, 0.0f, 1.0f);
    model.scale(1.0f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(-1.0f, 0.0f, 2.0f);
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(0.25f);
    p->setUniformValue("model", model);
    renderCube(p);
}

void HGeometryEngine::renderRoom(HOpenGLShaderProgram *p)
{
    QMatrix4x4 model;
    model.scale(5.0f);
    p->setUniformValue("model", model);
    glDisable(GL_CULL_FACE); // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
    p->setUniformValue("reverseNormals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
    renderCube(p);
    p->setUniformValue("reverseNormals", 0); // and of course disable it
    glEnable(GL_CULL_FACE);
    model.setToIdentity();
    model.translate(0.0f, 1.5f, 0.0f);
    model.scale(0.5f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(2.0f, 0.0f, 1.0f);
    model.scale(1.0f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(-1.0f, 0.0f, 2.0f);
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(0.25f);
    p->setUniformValue("model", model);
    renderCube(p);

}

HE_REFERENCE_END_NAMESPACE
