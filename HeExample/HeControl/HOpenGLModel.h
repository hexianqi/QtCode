/***************************************************************************************************
**      2020-11-13  HOpenGLModel    模型
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QOpenGLShaderProgram;
class QOpenGLTexture;

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

HE_CONTROL_BEGIN_NAMESPACE

class HOpenGLMesh;
class HOpenGLModelPrivate;

class HOpenGLModel : public QObject
{
    Q_OBJECT

public:
    explicit HOpenGLModel(QObject *parent = nullptr);
    ~HOpenGLModel() override;

public:
    bool load(const QString &fileName);
    void draw(QOpenGLShaderProgram *, int amount = 0);
    void setInstancedMatrix(int location, QVector<QMatrix4x4> mat);

protected:
    HOpenGLModel(HOpenGLModelPrivate &p, QObject *parent = nullptr);

protected:
    void clear();
    void processNode(aiNode *node, const aiScene *scene);
    HOpenGLMesh *processMesh(aiMesh *mesh, const aiScene *scene);
    QHash<QString, QOpenGLTexture *> processMaterial(aiMaterial *mat, int type, const QString &typeName);

protected:
    QScopedPointer<HOpenGLModelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

