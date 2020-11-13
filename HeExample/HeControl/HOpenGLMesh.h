/***************************************************************************************************
**      2020-11-12  HMeshEngine 网格
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

class QOpenGLShaderProgram;
class QOpenGLTexture;

HE_CONTROL_BEGIN_NAMESPACE

struct Vertex
{
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
    QVector3D Tangent;
    QVector3D Bitangent;
};

class HHOpenGLMeshPrivate;

class HOpenGLMesh : public QObject
{
    Q_OBJECT

public:
    explicit HOpenGLMesh(QVector<Vertex> vertices, QVector<unsigned int> indices, QHash<QString, QOpenGLTexture *> textures, QObject *parent = nullptr);
    ~HOpenGLMesh() override;

public:
    void draw(QOpenGLShaderProgram *, int amount = 0);
    void setInstancedMatrix(int location);

protected:
    QScopedPointer<HHOpenGLMeshPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

