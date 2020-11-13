/***************************************************************************************************
**      2020-12-21  HGameManager
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QKeyEvent;

HE_CONTROL_BEGIN_NAMESPACE

class HGameManagerPrivate;

class HGameManager : public QObject
{
    Q_OBJECT

public:
    explicit HGameManager(QObject *parent = nullptr);
    ~HGameManager() override;

public:
    // initialize game state (load all shaders/textures/levels)
    void init(int width, int height);
    // input
    void handleKeyPressEvent(QKeyEvent *);
    void handleKeyReleaseEvent(QKeyEvent *);
    // game loop
    void update();
    void render();
    // reset
    void resetLevel();
    void resetPlayer();

protected:
    HGameManager(HGameManagerPrivate &p, QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;
    void updateDelta();
    void handleBallChanged();
    void handlePropChanged(const QString &, bool);
    void collision();
    void checkLoss();
    void checkWin();

protected:
    QScopedPointer<HGameManagerPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

