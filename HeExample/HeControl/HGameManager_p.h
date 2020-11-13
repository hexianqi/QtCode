#pragma once

#include "HGameManager.h"
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtGui/QVector2D>

HE_CONTROL_BEGIN_NAMESPACE

class HGameLevel;
class HSpriteRenderer;
class HParticleRenderer;
class HTextRenderer;
class HEffectRenderer;
class HPaddle;
class HBall;
class HPropManager;

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class HGameManagerPrivate
{
public:
    QVector<HGameLevel *> levels;
    HSpriteRenderer *sprite = nullptr;
    HParticleRenderer *particle = nullptr;
    HEffectRenderer * effect = nullptr;
    HTextRenderer *text = nullptr;
    HPaddle *paddle = nullptr;
    HBall *ball = nullptr;
    HPropManager *prop = nullptr;

public:
    int width;
    int height;
    GameState state = GAME_MENU;
    int level = 0;
    int lives = 3;
    QVector2D paddleSize = QVector2D(100.0f, 20.0f);
    float paddleVelocity = 500.0f;
    float ballRadius = 12.5f;
    QVector2D ballVelocity = QVector2D(100.0f, -350.0f);

public:
    int timeId = 0;                     // 此定时器用于完成键盘移动事件
    double deltaTime = 0.01;            // 当前帧与上一帧的时间差
    double lastFrame = 0;               // 上一帧的时间
    QSet<int> keys;                     // 记录当前被按下按键的集合
};

HE_CONTROL_END_NAMESPACE

