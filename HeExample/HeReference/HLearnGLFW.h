/***************************************************************************************************
**      2020-09-08  HLearnGLFW
**                  https://learnopengl-cn.github.io
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

class GLFWwindow;

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HLearnGLFWPrivate;

class HE_REFERENCE_EXPORT HLearnGLFW : public QObject
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
    int testCamera();
    int testCamera2();
    int testColor();
    int testLight();
    int testMaterials();
    int testLightMaps();
    int testLightCasterDirectional();
    int testLightCasterPoint();
    int testLightCasterSpot();
    int testLightMult();
    int testLightBlinn();
    int testLightGamma();
    int testModel();
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

protected:
    void initGlfw();
    bool initFlad();
    bool createWindow();
    void perFrameTime();
    void processInput(GLFWwindow *window);
    QVector3D lightPos();
    QVector3D lightColor();

protected:
    void renderScene(HOpenGLShaderProgram *shader, int type = 0);
    void renderCube();
    void renderQuad();
    void renderQuad2();
    void renderSphere();

protected:
    QScopedPointer<HLearnGLFWPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

