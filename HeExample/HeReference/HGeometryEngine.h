/***************************************************************************************************
**      2020-11-06  HGeometryEngine
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HGeometryEnginePrivate;

class HGeometryEngine : public QObject
{
    Q_OBJECT

public:
    explicit HGeometryEngine(QObject *parent = nullptr);
    ~HGeometryEngine() override;

public:
    void renderTriangle(HOpenGLShaderProgram *);
    void renderRect(HOpenGLShaderProgram *);
    void renderScreen(HOpenGLShaderProgram *);
    void renderPlane(HOpenGLShaderProgram *);
    void renderQuad(HOpenGLShaderProgram *);
    void renderCube(HOpenGLShaderProgram *);
    void renderSphere(HOpenGLShaderProgram *);
    void renderSkybox(HOpenGLShaderProgram *);
    void renderScene(HOpenGLShaderProgram *);
    void renderRoom(HOpenGLShaderProgram *);

protected:
    HGeometryEngine(HGeometryEnginePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGeometryEnginePrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

