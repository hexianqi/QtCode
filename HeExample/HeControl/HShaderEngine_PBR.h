/***************************************************************************************************
**      2020-12-04  HShaderEngine_PBR
***************************************************************************************************/

#pragma once

#include "HAbstractShaderEngine.h"

class QOpenGLShaderProgram;

HE_CONTROL_BEGIN_NAMESPACE

class HShaderEngine_PBRPrivate;

class HShaderEngine_PBR : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR)

public:
    explicit HShaderEngine_PBR(QObject *parent = nullptr);
    ~HShaderEngine_PBR() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;

protected:
    HShaderEngine_PBR(HShaderEngine_PBRPrivate &p, QObject *parent = nullptr);

protected:
    virtual void beforeDrawSpheres(HGeometryEngine *, QVariantMap param);
    virtual void afterDrawSpheres(HGeometryEngine *, QVariantMap param);
    virtual void drawSpheres(HGeometryEngine *, QVariantMap param);
};

class HShaderEngine_PBR2Private;

class HShaderEngine_PBR2 : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR2)

public:
    explicit HShaderEngine_PBR2(QObject *parent = nullptr);
    ~HShaderEngine_PBR2() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_PBR3Private;

class HShaderEngine_PBR3 : public HShaderEngine_PBR
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR3)

public:
    explicit HShaderEngine_PBR3(QObject *parent = nullptr);
    ~HShaderEngine_PBR3() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HShaderEngine_PBR3(HShaderEngine_PBR3Private &p, QObject *parent = nullptr);

protected:
    void beforeDrawSpheres(HGeometryEngine *, QVariantMap param) override;
    void afterDrawSpheres(HGeometryEngine *, QVariantMap param) override;
    QOpenGLTexture *loadCubemapFromHdr(HGeometryEngine *, const QString &fileName, int width, int height, QOpenGLTexture::Filter magFilter = QOpenGLTexture::Linear);
    QOpenGLTexture *loadTextureFromHdr(const QString &fileName);
    void renderCubemap(QOpenGLShaderProgram *, HGeometryEngine *, QOpenGLTexture *, QOpenGLTexture *);
};

class HShaderEngine_PBR4Private;

class HShaderEngine_PBR4 : public HShaderEngine_PBR3
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR4)

public:
    explicit HShaderEngine_PBR4(QObject *parent = nullptr);
    ~HShaderEngine_PBR4() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HShaderEngine_PBR4(HShaderEngine_PBR4Private &p, QObject *parent = nullptr);

protected:
    void beforeDrawSpheres(HGeometryEngine *, QVariantMap param) override;
    QOpenGLTexture *createCubemapIrradiance(HGeometryEngine *, QOpenGLTexture *, int width, int height);
};

class HShaderEngine_PBR5Private;

class HShaderEngine_PBR5 : public HShaderEngine_PBR4
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR5)

public:
    explicit HShaderEngine_PBR5(QObject *parent = nullptr);
    ~HShaderEngine_PBR5() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HShaderEngine_PBR5(HShaderEngine_PBR5Private &p, QObject *parent = nullptr);

protected:
    void beforeDrawSpheres(HGeometryEngine *, QVariantMap param) override;
    QOpenGLTexture *createCubemapPrefilter(HGeometryEngine *, QOpenGLTexture *, int width, int height);
    QOpenGLTexture *createTextureBrdf(HGeometryEngine *, int width, int height);
};

class HShaderEngine_PBR6Private;

class HShaderEngine_PBR6 : public HShaderEngine_PBR5
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_PBR6)

public:
    explicit HShaderEngine_PBR6(QObject *parent = nullptr);
    ~HShaderEngine_PBR6() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    void drawSpheres(HGeometryEngine *, QVariantMap param) override;
};

HE_CONTROL_END_NAMESPACE

