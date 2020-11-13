#include "HGeometryEngine_p.h"
#include "HOpenGLModel.h"
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShaderProgram>

HE_CONTROL_BEGIN_NAMESPACE

HGeometryEnginePrivate::HGeometryEnginePrivate()
{
    funcs = QOpenGLContext::currentContext()->functions();
}

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
    d_ptr->triangleVao.destroy();
    d_ptr->rectVao.destroy();
    d_ptr->screenVao.destroy();
    d_ptr->planeVao.destroy();
    d_ptr->quadVao.destroy();
    d_ptr->cubeVao.destroy();
    d_ptr->sphereVao.destroy();
    d_ptr->skyboxVao.destroy();
    qDeleteAll(d_ptr->models);
    d_ptr->models.clear();
}

void HGeometryEngine::renderTriangle(QOpenGLShaderProgram *)
{
    if (!d_ptr->triangleVao.isCreated())
    {
        GLfloat position[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        GLfloat color[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->triangleVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(sizeof(position) + sizeof(color));
        vbo->write(0, position, sizeof(position));
        vbo->write(sizeof(position), color, sizeof(color));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(position)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
//        p->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
//        p->enableAttributeArray(0);
//        p->setAttributeBuffer(1, GL_FLOAT, sizeof(vertices), 3, , sizeof(GLfloat) * 3);
//        p->enableAttributeArray(1);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->triangleVao);
    d_ptr->funcs->glDrawArrays(GL_TRIANGLES, 0, 3);
}

void HGeometryEngine::renderRect(QOpenGLShaderProgram *)
{
    if (!d_ptr->rectVao.isCreated())
    {
        GLfloat position[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, 0.0f
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->rectVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        auto ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(sizeof(position) + sizeof(color) + sizeof(texture));
        vbo->write(0, position, sizeof(position));
        vbo->write(sizeof(position), color, sizeof(color));
        vbo->write(sizeof(position) + sizeof(color), texture, sizeof(texture));
        ebo->create();
        ebo->bind();
        ebo->allocate(indice, sizeof(indice));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(position)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(position) + sizeof(color)));
        d_ptr->funcs->glEnableVertexAttribArray(2);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->rectVao);
    d_ptr->funcs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void HGeometryEngine::renderScreen(QOpenGLShaderProgram *)
{
    if (!d_ptr->screenVao.isCreated())
    {
        GLfloat position[] = {
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->screenVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        auto ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(sizeof(position) + sizeof(normal) + sizeof(texture));
        vbo->write(0, position, sizeof(position));
        vbo->write(sizeof(position), normal, sizeof(normal));
        vbo->write(sizeof(position) + sizeof(normal), texture, sizeof(texture));
        ebo->create();
        ebo->bind();
        ebo->allocate(indice, sizeof(indice));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(position)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(position) + sizeof(normal)));
        d_ptr->funcs->glEnableVertexAttribArray(2);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->screenVao);
    d_ptr->funcs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void HGeometryEngine::renderPlane(QOpenGLShaderProgram *)
{
    if (!d_ptr->planeVao.isCreated())
    {
        GLfloat position[] = {
            -25.0f, -0.05f,  25.0f,
             25.0f, -0.05f,  25.0f,
            -25.0f, -0.05f, -25.0f,
             25.0f, -0.05f, -25.0f
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->planeVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        auto ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(sizeof(position) + sizeof(normal) + sizeof(texture));
        vbo->write(0, position, sizeof(position));
        vbo->write(sizeof(position), normal, sizeof(normal));
        vbo->write(sizeof(position) + sizeof(normal), texture, sizeof(texture));
        ebo->create();
        ebo->bind();
        ebo->allocate(indice, sizeof(indice));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(position)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(position) + sizeof(normal)));
        d_ptr->funcs->glEnableVertexAttribArray(2);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->planeVao);
    d_ptr->funcs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void HGeometryEngine::renderQuad(QOpenGLShaderProgram *)
{
    if (!d_ptr->quadVao.isCreated())
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->quadVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(quadVertices, sizeof(quadVertices));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        d_ptr->funcs->glEnableVertexAttribArray(2);
        d_ptr->funcs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        d_ptr->funcs->glEnableVertexAttribArray(3);
        d_ptr->funcs->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
        d_ptr->funcs->glEnableVertexAttribArray(4);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->quadVao);
    d_ptr->funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
}

void HGeometryEngine::renderCube(QOpenGLShaderProgram *)
{
    if (!d_ptr->cubeVao.isCreated())
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->cubeVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(sizeof(position) + sizeof(normal) + sizeof(texture));
        vbo->write(0, position, sizeof(position));
        vbo->write(sizeof(position), normal, sizeof(normal));
        vbo->write(sizeof(position) + sizeof(normal), texture, sizeof(texture));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(position)));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(position) + sizeof(normal)));
        d_ptr->funcs->glEnableVertexAttribArray(2);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->cubeVao);
    d_ptr->funcs->glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HGeometryEngine::renderSphere(QOpenGLShaderProgram *)
{
    if (!d_ptr->sphereVao.isCreated())
    {
        QVector<QVector3D> position;
        QVector<QVector3D> normal;
        QVector<QVector2D> uv;
        QVector<unsigned int> indice;
        int x, y;
        const int X_SEGMENTS = 64;
        const int Y_SEGMENTS = 64;
        for (y = 0; y <= Y_SEGMENTS; y++)
        {
            for (x = 0; x <= X_SEGMENTS; x++)
            {
                auto xSegment = 1.0f * x / X_SEGMENTS;
                auto ySegment = 1.0f * y / Y_SEGMENTS;
                auto xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
                auto yPos = std::cos(ySegment * M_PI);
                auto zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
                position << QVector3D(xPos, yPos, zPos);
                normal << QVector3D(xPos, yPos, zPos);
                uv << QVector2D(xSegment, ySegment);
            }
        }

        bool oddRow = false;
        for (y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (x = 0; x <= X_SEGMENTS; ++x)
                {
                    indice <<  y      * (X_SEGMENTS + 1) + x
                           << (y + 1) * (X_SEGMENTS + 1) + x;
                }
            }
            else
            {
                for (x = X_SEGMENTS; x >= 0; --x)
                {
                    indice << (y + 1) * (X_SEGMENTS + 1) + x
                           <<  y      * (X_SEGMENTS + 1) + x;
                }
            }
            oddRow = !oddRow;
        }

        auto positionSize = sizeof(QVector3D) * position.size();
        auto normalSize = sizeof(QVector3D) * normal.size();
        auto uvSize = sizeof(QVector2D) * uv.size();
        auto indiceSize = sizeof(unsigned int) * indice.size();
        QOpenGLVertexArrayObject::Binder binder(&d_ptr->sphereVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        auto ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(positionSize + normalSize + uvSize);
        vbo->write(0, position.data(), positionSize);
        vbo->write(positionSize, normal.data(), normalSize);
        vbo->write(positionSize + normalSize, uv.data(), uvSize);
        ebo->create();
        ebo->bind();
        ebo->allocate(indice.data(), indiceSize);
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
        d_ptr->funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(positionSize));
        d_ptr->funcs->glEnableVertexAttribArray(1);
        d_ptr->funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(positionSize + normalSize));
        d_ptr->funcs->glEnableVertexAttribArray(2);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->sphereVao);
    d_ptr->funcs->glDrawElements(GL_TRIANGLE_STRIP, 65 * 64 * 2, GL_UNSIGNED_INT, 0);
}

void HGeometryEngine::renderSkybox(QOpenGLShaderProgram *)
{
    if (!d_ptr->skyboxVao.isCreated())
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

        QOpenGLVertexArrayObject::Binder binder(&d_ptr->skyboxVao);
        auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo->create();
        vbo->bind();
        vbo->allocate(position, sizeof(position));
        d_ptr->funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        d_ptr->funcs->glEnableVertexAttribArray(0);
    }
    QOpenGLVertexArrayObject::Binder binder(&d_ptr->skyboxVao);
    d_ptr->funcs->glDepthFunc(GL_LEQUAL);
    d_ptr->funcs->glDrawArrays(GL_TRIANGLES, 0, 36);
    d_ptr->funcs->glDepthFunc(GL_LESS);
}

void HGeometryEngine::renderScene(QOpenGLShaderProgram *p)
{
    QMatrix4x4 model;
    model.setToIdentity();
    p->setUniformValue("model", model);
    renderPlane(p);
    model.setToIdentity();
    model.translate(0.0f, 3.0f, 0.0f);
    model.scale(0.5f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(2.0f, 1.0f, 1.0f);
    model.scale(1.0f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(-1.0f, 1.0f, 2.0f);
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(0.25f);
    p->setUniformValue("model", model);
    renderCube(p);
}

void HGeometryEngine::renderRoom(QOpenGLShaderProgram *p)
{
    auto state  = d_ptr->funcs->glIsEnabled(GL_CULL_FACE);
    QMatrix4x4 model;
    model.scale(5.0f);
    p->setUniformValue("model", model);
    if (state == GL_TRUE)
        d_ptr->funcs->glDisable(GL_CULL_FACE); // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
    p->setUniformValue("reverseNormals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
    renderCube(p);
    p->setUniformValue("reverseNormals", 0); // and of course disable it
    if (state == GL_TRUE)
        d_ptr->funcs->glEnable(GL_CULL_FACE);
    model.setToIdentity();
    model.translate(0.0f, 3.0f, 0.0f);
    model.scale(0.5f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(2.0f, 1.0f, 1.0f);
    model.scale(1.0f);
    p->setUniformValue("model", model);
    renderCube(p);
    model.setToIdentity();
    model.translate(-1.0f, 1.0f, 2.0f);
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(0.25f);
    p->setUniformValue("model", model);
    renderCube(p);
}

void HGeometryEngine::renderModel(QOpenGLShaderProgram *p, const QString &fileName, int amount)
{
    auto model = loadModel(fileName);
    if (model != nullptr)
        model->draw(p, amount);
}

HOpenGLModel *HGeometryEngine::loadModel(const QString &fileName)
{
    if (!d_ptr->models.contains(fileName))
    {
        auto model = new HOpenGLModel(this);
        if (!model->load(fileName))
            return nullptr;
        d_ptr->models.insert(fileName, model);
    }
    return d_ptr->models.value(fileName);
}

HE_CONTROL_END_NAMESPACE
