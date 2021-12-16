#pragma once

#include "HOpenGLCamera.h"
#include "HAbstractEventFilter_p.h"
#include <QtGui/QVector3D>

HE_BEGIN_NAMESPACE

class HOpenGLCameraPrivate : public HAbstractEventFilterPrivate
{
public:
    HOpenGLCameraPrivate();

public:
    QVector3D position;                 // 位置
    QVector3D front;                    // 前
    QVector3D up;                       // 上
    QVector3D right;                    // 右
    QVector3D worldUp;                  // 世界上

public:
    double yaw = -90.0;                 // 偏航角
    double pitch = 0.0;                 // 俯视角
    double zoom = 45.0;
    double sensitivity = 0.1;           // 鼠标灵敏度
    double moveSpeed = 0.1;             // 控制移动速度


public:
    QWidget *widget = nullptr;
    int timeId = 0;                     // 此定时器用于完成键盘移动事件
    double deltaTime = 0.01;            // 当前帧与上一帧的时间差
    double lastFrame = 0;               // 上一帧的时间
    QSet<int> keys;                     // 记录当前被按下按键的集合
    bool mouseLocked = false;
    bool mousePressed = false;
    QPoint mouseLastPos;
};

HE_END_NAMESPACE

