#include "HOpenGLModel_p.h"
#include "HOpenGLHelper.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glad/glad.h"
#include <QtCore/QDir>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>
#include <QTemporaryFile>

HE_REFERENCE_BEGIN_NAMESPACE

HOpenGLModel::HOpenGLModel(QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLModelPrivate)
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

void HOpenGLModel::setInstancedMatrix(int location, QVector<QMatrix4x4> mat)
{
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // QMatrix4x4 带flagBits无法转换成GLSL中的mat4
    // glBufferData(GL_ARRAY_BUFFER, mat.size() * sizeof(QMatrix4x4), mat[0].constData(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * mat.size(), nullptr, GL_STATIC_DRAW);
    for (int i = 0; i < mat.size(); i++)
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 16 * i, sizeof(float) * 16, mat[i].constData());

    for (auto i : d_ptr->meshes)
        i->setInstancedMatrix(location);
}

void HOpenGLModel::draw(HOpenGLShaderProgram *shade, int amount)
{
    for (auto i : d_ptr->meshes)
        i->draw(shade, amount);
}

void HOpenGLModel::clear()
{
    qDeleteAll(d_ptr->meshes);
    d_ptr->meshes.clear();
}

void HOpenGLModel::processNode(aiNode *node, const aiScene *scene)
{
    unsigned int i;
    // process each mesh located at the current node
    for (i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        d_ptr->meshes << processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

HOpenGLMesh *HOpenGLModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    unsigned int i, j;
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;
    // walk through each of the mesh's vertices
    for (i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        if (mesh->HasNormals())
            vertex.Normal = QVector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0])
        {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
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
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (i = 0; i < mesh->mNumFaces; i++)
    {
        auto face = mesh->mFaces[i];
        for (j = 0; j < face.mNumIndices; j++)
            indices << face.mIndices[j];
    }
    // process materials
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    // height: texture_heightN
    auto material = scene->mMaterials[mesh->mMaterialIndex];
    textures << processMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures << processMaterial(material, aiTextureType_SPECULAR, "texture_specular");
    textures << processMaterial(material, aiTextureType_HEIGHT, "texture_normal");
    textures << processMaterial(material, aiTextureType_AMBIENT, "texture_height");

    return new HOpenGLMesh(vertices, indices, textures, this);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
QVector<Texture> HOpenGLModel::processMaterial(aiMaterial *mat, int type, const QString &typeName)
{
    QVector<Texture> textures;
    auto count = mat->GetTextureCount((aiTextureType)type);
    for(unsigned int i = 0; i < count; i++)
    {
        aiString str;
        mat->GetTexture((aiTextureType)type, i, &str);
        QString name = str.C_Str();
        if (!d_ptr->textures.contains(name))
        {
            auto fileName = d_ptr->directory + QDir::separator() + name;
            Texture texture;
            texture.Id = HOpenGLHelper::loadTexture(fileName);
            texture.Type = typeName;
            d_ptr->textures.insert(name, texture);
        }
        textures << d_ptr->textures.value(name);
    }
    return textures;
}

HE_REFERENCE_END_NAMESPACE
