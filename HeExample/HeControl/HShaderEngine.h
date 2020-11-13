/***************************************************************************************************
**      2020-11-09  HShaderEngine
***************************************************************************************************/

#pragma once

#include "HAbstractShaderEngine.h"

class QOpenGLShaderProgram;

HE_CONTROL_BEGIN_NAMESPACE

class HShaderEngine_TrianglePrivate;

class HShaderEngine_Triangle : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Triangle)

public:
    explicit HShaderEngine_Triangle(QObject *parent = nullptr);
    ~HShaderEngine_Triangle() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_TexturePrivate;

class HShaderEngine_Texture : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Texture)

public:
    explicit HShaderEngine_Texture(QObject *parent = nullptr);
    ~HShaderEngine_Texture() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_TextureBlendPrivate;

class HShaderEngine_TextureBlend : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_TextureBlend)

public:
    explicit HShaderEngine_TextureBlend(QObject *parent = nullptr);
    ~HShaderEngine_TextureBlend() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_CoordinateSystemPrivate;

class HShaderEngine_CoordinateSystem : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_CoordinateSystem)

public:
    explicit HShaderEngine_CoordinateSystem(QObject *parent = nullptr);
    ~HShaderEngine_CoordinateSystem() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ColorPrivate;

class HShaderEngine_Color : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Color)

public:
    explicit HShaderEngine_Color(QObject *parent = nullptr);
    ~HShaderEngine_Color() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightPrivate;

class HShaderEngine_Light : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Light)

public:
    explicit HShaderEngine_Light(QObject *parent = nullptr);
    ~HShaderEngine_Light() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightMaterialsPrivate;

class HShaderEngine_LightMaterials : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightMaterials)

public:
    explicit HShaderEngine_LightMaterials(QObject *parent = nullptr);
    ~HShaderEngine_LightMaterials() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightMapsPrivate;

class HShaderEngine_LightMaps : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightMaps)

public:
    explicit HShaderEngine_LightMaps(QObject *parent = nullptr);
    ~HShaderEngine_LightMaps() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightCasterDirectionalPrivate;

class HShaderEngine_LightCasterDirectional : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightCasterDirectional)

public:
    explicit HShaderEngine_LightCasterDirectional(QObject *parent = nullptr);
    ~HShaderEngine_LightCasterDirectional() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightCasterPointPrivate;

class HShaderEngine_LightCasterPoint : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightCasterPoint)

public:
    explicit HShaderEngine_LightCasterPoint(QObject *parent = nullptr);
    ~HShaderEngine_LightCasterPoint() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightCasterSpotPrivate;

class HShaderEngine_LightCasterSpot : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightCasterSpot)

public:
    explicit HShaderEngine_LightCasterSpot(QObject *parent = nullptr);
    ~HShaderEngine_LightCasterSpot() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightCasterMultiPrivate;

class HShaderEngine_LightCasterMulti : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightCasterMulti)

public:
    explicit HShaderEngine_LightCasterMulti(QObject *parent = nullptr);
    ~HShaderEngine_LightCasterMulti() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightBlinnPrivate;

class HShaderEngine_LightBlinn : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightBlinn)

public:
    explicit HShaderEngine_LightBlinn(QObject *parent = nullptr);
    ~HShaderEngine_LightBlinn() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_LightGammaPrivate;

class HShaderEngine_LightGamma : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_LightGamma)

public:
    explicit HShaderEngine_LightGamma(QObject *parent = nullptr);
    ~HShaderEngine_LightGamma() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ModelPrivate;

class HShaderEngine_Model : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Model)

public:
    explicit HShaderEngine_Model(QObject *parent = nullptr);
    ~HShaderEngine_Model() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_DepthPrivate;

class HShaderEngine_Depth : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Depth)

public:
    explicit HShaderEngine_Depth(QObject *parent = nullptr);
    ~HShaderEngine_Depth() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_StencilPrivate;

class HShaderEngine_Stencil : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Stencil)

public:
    explicit HShaderEngine_Stencil(QObject *parent = nullptr);
    ~HShaderEngine_Stencil() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_BlendingPrivate;

class HShaderEngine_Blending : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Blending)

public:
    explicit HShaderEngine_Blending(QObject *parent = nullptr);
    ~HShaderEngine_Blending() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_FramebufferPrivate;

class HShaderEngine_Framebuffer : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Framebuffer)

public:
    explicit HShaderEngine_Framebuffer(QObject *parent = nullptr);
    ~HShaderEngine_Framebuffer() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_CubemapsPrivate;

class HShaderEngine_Cubemaps : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Cubemaps)

public:
    explicit HShaderEngine_Cubemaps(QObject *parent = nullptr);
    ~HShaderEngine_Cubemaps() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_UboPrivate;

class HShaderEngine_Ubo : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Ubo)

public:
    explicit HShaderEngine_Ubo(QObject *parent = nullptr);
    ~HShaderEngine_Ubo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_GeometryHousePrivate;

class HShaderEngine_GeometryHouse : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_GeometryHouse)

public:
    explicit HShaderEngine_GeometryHouse(QObject *parent = nullptr);
    ~HShaderEngine_GeometryHouse() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_GeometryExplodePrivate;

class HShaderEngine_GeometryExplode : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_GeometryExplode)

public:
    explicit HShaderEngine_GeometryExplode(QObject *parent = nullptr);
    ~HShaderEngine_GeometryExplode() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_GeometryNormalPrivate;

class HShaderEngine_GeometryNormal : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_GeometryNormal)

public:
    explicit HShaderEngine_GeometryNormal(QObject *parent = nullptr);
    ~HShaderEngine_GeometryNormal() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_InstancingPrivate;

class HShaderEngine_Instancing : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Instancing)

public:
    explicit HShaderEngine_Instancing(QObject *parent = nullptr);
    ~HShaderEngine_Instancing() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_InstancingModelPrivate;

class HShaderEngine_InstancingModel : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_InstancingModel)

public:
    explicit HShaderEngine_InstancingModel(QObject *parent = nullptr);
    ~HShaderEngine_InstancingModel() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_AntiAliasingPrivate;

class HShaderEngine_AntiAliasing : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_AntiAliasing)

public:
    explicit HShaderEngine_AntiAliasing(QObject *parent = nullptr);
    ~HShaderEngine_AntiAliasing() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ShadowDepthPrivate;

class HShaderEngine_ShadowDepth : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_ShadowDepth)

public:
    explicit HShaderEngine_ShadowDepth(QObject *parent = nullptr);
    ~HShaderEngine_ShadowDepth() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ShadowMappingPrivate;

class HShaderEngine_ShadowMapping : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_ShadowMapping)

public:
    explicit HShaderEngine_ShadowMapping(QObject *parent = nullptr);
    ~HShaderEngine_ShadowMapping() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ShadowPointPrivate;

class HShaderEngine_ShadowPoint : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_ShadowPoint)

public:
    explicit HShaderEngine_ShadowPoint(QObject *parent = nullptr);
    ~HShaderEngine_ShadowPoint() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_NormalMappingPrivate;

class HShaderEngine_NormalMapping : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_NormalMapping)

public:
    explicit HShaderEngine_NormalMapping(QObject *parent = nullptr);
    ~HShaderEngine_NormalMapping() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_ParallaxMappingPrivate;

class HShaderEngine_ParallaxMapping : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_ParallaxMapping)

public:
    explicit HShaderEngine_ParallaxMapping(QObject *parent = nullptr);
    ~HShaderEngine_ParallaxMapping() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_HDRPrivate;

class HShaderEngine_HDR : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_HDR)

public:
    explicit HShaderEngine_HDR(QObject *parent = nullptr);
    ~HShaderEngine_HDR() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_BloomPrivate;

class HShaderEngine_Bloom : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Bloom)

public:
    explicit HShaderEngine_Bloom(QObject *parent = nullptr);
    ~HShaderEngine_Bloom() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_DeferredShadingPrivate;

class HShaderEngine_DeferredShading : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_DeferredShading)

public:
    explicit HShaderEngine_DeferredShading(QObject *parent = nullptr);
    ~HShaderEngine_DeferredShading() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QVariantMap value) override;
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_SSAOPrivate;

class HShaderEngine_SSAO : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_SSAO)

public:
    explicit HShaderEngine_SSAO(QObject *parent = nullptr);
    ~HShaderEngine_SSAO() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

class HShaderEngine_TextPrivate;

class HShaderEngine_Text : public HAbstractShaderEngine
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HShaderEngine_Text)

public:
    explicit HShaderEngine_Text(QObject *parent = nullptr);
    ~HShaderEngine_Text() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) override;
};

HE_CONTROL_END_NAMESPACE
