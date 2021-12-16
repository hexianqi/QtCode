/***************************************************************************************************
**      2020-11-05  HGeometryEngine 几何引擎
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class QOpenGLShaderProgram;

HE_BEGIN_NAMESPACE

class HOpenGLModel;
class HGeometryEnginePrivate;

class HGeometryEngine : public QObject
{
    Q_OBJECT

public:
    explicit HGeometryEngine(QObject *parent = nullptr);
    ~HGeometryEngine() override;

public:
    void renderTriangle(QOpenGLShaderProgram *);
    void renderRect(QOpenGLShaderProgram *);
    void renderScreen(QOpenGLShaderProgram *);
    void renderPlane(QOpenGLShaderProgram *);
    void renderQuad(QOpenGLShaderProgram *);
    void renderCube(QOpenGLShaderProgram *);
    void renderSphere(QOpenGLShaderProgram *);
    void renderSkybox(QOpenGLShaderProgram *);
    void renderScene(QOpenGLShaderProgram *);
    void renderRoom(QOpenGLShaderProgram *);
    void renderModel(QOpenGLShaderProgram *, const QString &fileName, int amount = 0);

public:
    HOpenGLModel *loadModel(const QString &fileName);

protected:
    HGeometryEngine(HGeometryEnginePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGeometryEnginePrivate> d_ptr;
};

HE_END_NAMESPACE

