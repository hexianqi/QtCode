#pragma once

#include "HGameManager.h"
#include <QtCore/QVector>
#include <QtGui/QVector2D>

HE_REFERENCE_BEGIN_NAMESPACE

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
    bool keys[1024];
    bool keysProcessed[1024];
    int level = 0;
    int lives = 3;
    QVector2D paddleSize = QVector2D(100.0f, 20.0f);
    float paddleVelocity = 500.0f;
    float ballRadius = 12.5f;
    QVector2D ballVelocity = QVector2D(100.0f, -350.0f);
};

HE_REFERENCE_END_NAMESPACE

