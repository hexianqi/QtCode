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
    int testTriangle();
    int testTexture();
    int testTexture2();
    int testCoordinate();
    int testCoordinate2();
    int testCamera();
    int testCamera2();

protected:
    void initGlfw();
    bool initFlad();
    bool createWindow();
    void processInput(GLFWwindow *window);

protected:
    QScopedPointer<HLearnGLFWPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

