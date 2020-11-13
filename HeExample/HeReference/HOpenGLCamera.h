/***************************************************************************************************
**      2020-09-15  HOpenGLCamera   相机类。
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLCameraPrivate;

class HOpenGLCamera : public QObject
{
    Q_OBJECT

public:
    enum Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    Q_ENUM(Movement)

public:
    explicit HOpenGLCamera(QObject *parent = nullptr);
    ~HOpenGLCamera() override;

public:
    QVector3D position() const;
    QVector3D front() const;
    float zoom() const;
    QMatrix4x4 viewMatrix() const;

public:
    void setPosition(const QVector3D &);
    void setUpVector(const QVector3D &);
    void handleKeyboard(Movement direction, float deltaTime);
    void handleMouseMovement(float xpos, float ypos, bool constrainPitch = true);
    void handleMouseScroll(float xoffset, float yoffset);

protected:
    void updateVectors();

protected:
    QScopedPointer<HOpenGLCameraPrivate> d_ptr;
};

HE_REFERENCE_END_NAMESPACE

