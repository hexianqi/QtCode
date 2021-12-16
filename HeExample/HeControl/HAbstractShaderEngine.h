/***************************************************************************************************
**      2020-11-09  HAbstractShaderEngine
***************************************************************************************************/

#pragma once

#include "IShaderEngine.h"
#include <QtGui/QOpenGLTexture>

HE_BEGIN_NAMESPACE

class HAbstractShaderEnginePrivate;

class HAbstractShaderEngine : public QObject, public IShaderEngine
{
    Q_OBJECT

public:
    explicit HAbstractShaderEngine(QObject *parent = nullptr);
    ~HAbstractShaderEngine() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void setData(QVariantMap value) override;

protected:
    HAbstractShaderEngine(HAbstractShaderEnginePrivate &p, QObject *parent = nullptr);

protected:
    void addTexture(const QString &fileName, bool gamma = false, QOpenGLTexture::WrapMode mode = QOpenGLTexture::ClampToEdge);
    void addTexture(const QStringList &fileNames);
    void buildTexture();
    QOpenGLTexture *createTexture(const QString &fileName, bool gamma = false, QOpenGLTexture::WrapMode mode = QOpenGLTexture::ClampToEdge);
    QOpenGLTexture *createTexture(int width, int height, QOpenGLTexture::Target target, QOpenGLTexture::TextureFormat format, QOpenGLTexture::WrapMode mode = QOpenGLTexture::ClampToEdge, QOpenGLTexture::Filter magFilter = QOpenGLTexture::Linear);
    double secs();

protected:
    QScopedPointer<HAbstractShaderEnginePrivate> d_ptr;
};

HE_END_NAMESPACE

