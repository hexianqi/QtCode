#pragma once

#include "HOpenGLWidget.h"
#include <QtCore/QMap>
#include <QtGui/QVector3D>

class QOpenGLFunctions_3_3_Core;

HE_BEGIN_NAMESPACE

class IShaderEngine;
class HGeometryEngine;
class HOpenGLCamera;

class HOpenGLWidgetPrivate
{
public:
    HOpenGLWidgetPrivate();

public:
    QVector3D findAttenuation(double distance);

public:
    QString modelFileName;
    bool lightPosLoop = true;
    bool lightColorLoop = true;
    QVector3D lightPos;
    QVector3D lightColor;
    bool linearize = false;
    bool blinn = false;
    bool gamma = false;
    bool hdr = false;
    bool bloom = false;
    bool shadows = false;
    double exposure = 0.01;
    double heightScale = 0.0;

public:
    QVariantMap globalParam;
    QList<QVector3D> cubeWorldPosition;
    QMap<int, QVector3D> attenuations;

public:
    QTimer *timer = nullptr;

public:
    QOpenGLFunctions_3_3_Core *funcs = nullptr;
    HOpenGLCamera *camera = nullptr;
    HGeometryEngine *geometry = nullptr;
    IShaderEngine *shader = nullptr;
    QHash<QString, IShaderEngine *> shaders;
};

HE_END_NAMESPACE

