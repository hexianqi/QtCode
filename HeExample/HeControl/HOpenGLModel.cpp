#include "HOpenGLModel_p.h"
#include "HOpenGLMesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <QtCore/QDir>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLBuffer>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HOpenGLModelPrivate::HOpenGLModelPrivate()
{

}

HOpenGLModel::HOpenGLModel(QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLModelPrivate)
{
}

HOpenGLModel::HOpenGLModel(HOpenGLModelPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HOpenGLModel::~HOpenGLModel()
{
    clear();
}

bool HOpenGLModel::load(const QString &fileName)
{
    clear();
    Assimp::Importer importer;
    auto scene = importer.ReadFile(fileName.toStdString(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP:: " << importer.GetErrorString();
        return false;
    }
    d_ptr->directory = fileName.left(fileName.lastIndexOf(QDir::separator()));
    processNode(scene->mRootNode, scene);
    return true;
}

void HOpenGLModel::draw(QOpenGLShaderProgram *p, int amount)
{
    for (auto i : d_ptr->meshes)
        i->draw(p, amount);
}

void HOpenGLModel::setInstancedMatrix(int location, QVector<QMatrix4x4> mat)
{
    auto count = sizeof(QVector4D) * 4;
    auto vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    // QMatrix4x4 带flagBits无法转换成GLSL中的mat4
    // vbo->allocate(mat.data(), sizeof(QMatrix4x4) * mat.size());
    vbo->allocate(nullptr, count * mat.size());
    for (int i = 0; i < mat.size(); i++)
        vbo->write(count * i, mat[i].constData(), count);
    for (auto i : d_ptr->meshes)
        i->setInstancedMatrix(location);
}

void HOpenGLModel::processNode(aiNode *node, const aiScene *scene)
{
    unsigned int i;
    for (i = 0; i < node->mNumMeshes; i++)
        d_ptr->meshes << processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    for (i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

void HOpenGLModel::clear()
{
    qDeleteAll(d_ptr->meshes);
    qDeleteAll(d_ptr->textures);
    d_ptr->meshes.clear();
    d_ptr->textures.clear();
}

HOpenGLMesh *HOpenGLModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    unsigned int i, j;
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QHash<QString, QOpenGLTexture *> textures;

    for (i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 位置
        vertex.Position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        // 法向量
        if (mesh->HasNormals())
            vertex.Normal = QVector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        // 纹理坐标
        if (mesh->mTextureCoords[0])
        {
            // 一个顶点最多可以包含8个不同的纹理坐标。因此我们假设我们不用
            // 使用一个顶点可以有多个纹理坐标的模型，所以我们总是取第一个集合(0)。
            vertex.TexCoords = QVector2D(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
            vertex.TexCoords = QVector2D(0.0f, 0.0f);
        if (mesh->HasTangentsAndBitangents())
        {
            vertex.Tangent = QVector3D(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            vertex.Bitangent = QVector3D(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
        }
        vertices << vertex;
    }
    // 将所有面的索引数据添加到索引数组中
    for (i = 0; i < mesh->mNumFaces; i++)
    {
        auto face = mesh->mFaces[i];
        for (j = 0; j < face.mNumIndices; j++)
            indices << face.mIndices[j];
    }
    // 处理材质
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    // height: texture_heightN
    auto material = scene->mMaterials[mesh->mMaterialIndex];
    textures.unite(processMaterial(material, aiTextureType_DIFFUSE,     "texture_diffuse"));
    textures.unite(processMaterial(material, aiTextureType_SPECULAR,    "texture_specular"));
    textures.unite(processMaterial(material, aiTextureType_HEIGHT,      "texture_normal"));
    textures.unite(processMaterial(material, aiTextureType_AMBIENT,     "texture_height"));
    return new HOpenGLMesh(vertices, indices, textures, this);
}

QHash<QString, QOpenGLTexture *> HOpenGLModel::processMaterial(aiMaterial *mat, int type, const QString &typeName)
{
    QHash<QString, QOpenGLTexture *> textures;
    auto count = mat->GetTextureCount((aiTextureType)type);
    for(unsigned int i = 0; i < count; i++)
    {
        auto name = QString("%1%2").arg(typeName).arg(i+1);
        aiString str;
        mat->GetTexture((aiTextureType)type, i, &str);
        QString key = str.C_Str();
        if (!d_ptr->textures.contains(key))
        {
            auto fileName = d_ptr->directory + QDir::separator() + key;
            auto texture = new QOpenGLTexture(QImage(fileName).mirrored());
            texture->setMinificationFilter(QOpenGLTexture::Nearest);
            texture->setMagnificationFilter(QOpenGLTexture::Linear);
            texture->setWrapMode(QOpenGLTexture::Repeat);
            d_ptr->textures.insert(key, texture);
        }
        textures.insert(name, d_ptr->textures.value(key));
    }
    return textures;
}

HE_CONTROL_END_NAMESPACE
