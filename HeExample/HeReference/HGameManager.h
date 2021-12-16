/***************************************************************************************************
**      2020-12-08  HGameManager
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

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
    void keyPress(int key);
    void KeyRelease(int key);
    // game loop
    void processInput(float);
    void update(float dt);
    void render();
    void doCollisions();
    // reset
    void resetLevel();
    void resetPlayer();

protected:
    HGameManager(HGameManagerPrivate &p, QObject *parent = nullptr);

protected:
    void handleBallChanged();
    void handlePropChanged(const QString &, bool);

protected:
    QScopedPointer<HGameManagerPrivate> d_ptr;

private:

};

HE_END_NAMESPACE

