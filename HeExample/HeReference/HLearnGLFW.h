/***************************************************************************************************
**      2020-09-08  HLearnGLFW
**                  https://learnopengl-cn.github.io
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class GLFWwindow;

HE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HLearnGLFWPrivate;

class HLearnGLFW : public QObject
{
    Q_OBJECT

public:
    explicit HLearnGLFW(QObject *parent = nullptr);
    ~HLearnGLFW() override;

public:
    void setEnableCursor(bool);
    void setUseCamera(bool);
    void setLightPosLoop(bool);
    void setLightColorLoop(bool);
    void setLineMode(bool);

public:
    int testTriangle();
    int testTexture();
    int testTexture2();
    int testCoordinate();
    int testCoordinate2();
    int testColor();
    int testLight();
    int testMaterials();
    int testLightMaps();
    int testLightCasterDirectional();
    int testLightCasterPoint();
    int testLightCasterSpot();
    int testLightCasterMult();
    int testLightBlinn();
    int testLightGamma();
    int testModel();
    int testDepth();
    int testStencil();
    int testBlending();
    int testBlending2();
    int testFramebuffers();
    int testCubemaps();
    int testCubemaps2();
    int testUbo();
    int testGeometry();
    int testGeometryExplode();
    int testGeometryNormals();
    int testInstancing();
    int testInstancing2();
    int testAntiAliasing();
    int testShadowMappingDepth();
    int testShadowMappingBase();
    int testShadowMapping();
    int testShadowPoint();
    int testNormalMapping();
    int testParallaxMapping();
    int testHDR();
    int testBloom();
    int testDeferredShading();
    int testSSAO();
    int testPBR();
    int testPBR2();
    int testPBR3();
    int testPBR4();
    int testPBR5();
    int testPBR6();
    int testText();

protected:
    void initGlfw();
    bool initFlad();
    bool createWindow();
    void perFrameTime();
    void processInput(GLFWwindow *window);
    QVector3D lightPos();
    QVector3D lightColor();

public:
    unsigned int loadCubemapFromHdr(const QString &fileName, int width, int height, int magFilter = 0x2601);
    unsigned int createCubemapIrradiance(unsigned int texture, int width, int height);
    unsigned int createCubemapPrefilter(unsigned int texture, int width, int height);
    unsigned int createCubemap(HOpenGLShaderProgram *, unsigned int target, unsigned int texture, int width, int height, int magFilter = 0x2601);
    unsigned int createTextureBrdf(int width, int height);

protected:
    QScopedPointer<HLearnGLFWPrivate> d_ptr;
};

HE_END_NAMESPACE

