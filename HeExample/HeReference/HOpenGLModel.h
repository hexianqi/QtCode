/***************************************************************************************************
**      2020-10-14  HOpenGLModel    模型类。
***************************************************************************************************/

#pragma once

#include "HOpenGLMesh.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLModelPrivate;

class HOpenGLModel : public QObject
{
    Q_OBJECT

public:
    explicit HOpenGLModel(QObject *parent = nullptr);
    ~HOpenGLModel() override;

public:
    bool load(const QString &fileName);
    void setInstancedMatrix(int location, QVector<QMatrix4x4> mat);
    void draw(HOpenGLShaderProgram *, int amount = 0);

protected:
    void processNode(aiNode *node, const aiScene *scene);
    HOpenGLMesh *processMesh(aiMesh *mesh, const aiScene *scene);
    QVector<Texture> processMaterial(aiMaterial *mat, int type, const QString &typeName);

protected:
    QScopedPointer<HOpenGLModelPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

