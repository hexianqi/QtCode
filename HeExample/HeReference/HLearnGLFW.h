/***************************************************************************************************
**      2020-09-08  HLearnGLFW
**                  https://learnopengl-cn.github.io
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

class GLFWwindow;

HE_REFERENCE_BEGIN_NAMESPACE

class HLearnGLFWPrivate;

class HE_REFERENCE_EXPORT HLearnGLFW : public QObject
{
    Q_OBJECT

public:
    explicit HLearnGLFW(QObject *parent = nullptr);
    ~HLearnGLFW() override;

public:
    void setUseCamera(bool);
    void setLightPosLoop(bool);
    void setLightColorLoop(bool);

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

protected:
    void initGlfw();
    bool initFlad();
    bool createWindow();
    void perFrameTime();
    void processInput(GLFWwindow *window);
    unsigned int loadTexture(char const * path);
    QVector3D lightPos();
    QVector3D lightColor();

protected:
    QScopedPointer<HLearnGLFWPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

