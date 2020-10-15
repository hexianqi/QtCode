/***************************************************************************************************
**      2020-10-14  HOpenGLMesh 网格类。
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

struct Vertex
{
    // position
    QVector3D Position;
    // normal
    QVector3D Normal;
    // texCoords
    QVector2D TexCoords;
    // tangent
    QVector3D Tangent;
    // bitangent
    QVector3D Bitangent;
};

struct Texture
{
    unsigned int Id;
    QString Type;
    QString FileName;
};

class HOpenGLShaderProgram;
class HOpenGLMeshPrivate;

class HOpenGLMesh : public QObject
{
    Q_OBJECT

public:
    explicit HOpenGLMesh(QVector<Vertex> vertices, QVector<unsigned int> indices, QVector<Texture> textures, QObject *parent = nullptr);
    ~HOpenGLMesh() override;

public:
    void setInstancedMatrix(int location);
    void draw(HOpenGLShaderProgram *, int amount = 0);

protected:
    QScopedPointer<HOpenGLMeshPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

