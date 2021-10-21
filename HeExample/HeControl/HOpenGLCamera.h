/***************************************************************************************************
**      2020-11-09  HOpenGLCamera
***************************************************************************************************/

#pragma once

#include "HAbstractEventFilter.h"

HE_CONTROL_BEGIN_NAMESPACE

class HOpenGLCameraPrivate;

class HOpenGLCamera : public HAbstractEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HOpenGLCamera)

public:
    explicit HOpenGLCamera(QObject *parent = nullptr);
    ~HOpenGLCamera() override;

public:
    QString typeName() override;
    bool addWatched(QObject *) override;

public:
    QVector3D position() const;
    QVector3D front() const;
    double zoom() const;
    QMatrix4x4 view() const;

public:
    void setLockMouse(bool b);
    void setPosition(const QVector3D &);
    void setUpVector(const QVector3D &);
    void updateDelta();

protected:
    HOpenGLCamera(HOpenGLCameraPrivate &p, QObject *parent = nullptr);

protected:
    bool handleEvent(QObject *, QEvent *) override;
    bool handleTimerEvent(QEvent *);
    bool handleFocusInEvent(QEvent *);
    bool handleFocusOutEvent(QEvent *);
    bool handleMousePressEvent(QEvent *);
    bool handleMouseReleaseEvent(QEvent *);
    bool handleMouseMoveEvent(QEvent *);
    bool handleWheelEvent(QEvent *);
    bool handleKeyPressEvent(QEvent *);
    bool handleKeyReleaseEvent(QEvent *);
    bool isMoveKey(int);
    void setCursorCenter();
    void stopTimer();
    void updateVectors();
};

HE_CONTROL_END_NAMESPACE

