#include "HGameManager_p.h"
#include "HResourceManager.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLTexture2D.h"
#include "HSpriteRenderer.h"
#include "HParticleRenderer.h"
#include "HTextRenderer.h"
#include "HEffectRenderer.h"
#include "HGameLevel.h"
#include "HBrick.h"
#include "HPaddle.h"
#include "HBall.h"
#include "HPropManager.h"
#include "GLFW/glfw3.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

HGameManager::HGameManager(QObject *parent) :
    QObject(parent),
    d_ptr(new HGameManagerPrivate)
{
}

HGameManager::HGameManager(HGameManagerPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HGameManager::~HGameManager()
{
}

void HGameManager::init(int width, int height)
{
    d_ptr->width = width;
    d_ptr->height = height;

    // load textures
    HResourceManager::loadTexture("background",             ":/textures/background.jpg");
    HResourceManager::loadTexture("block",                  ":/textures/block.png");
    HResourceManager::loadTexture("block_solid",            ":/textures/block_solid.png");
    HResourceManager::loadTexture("paddle",                 ":/textures/paddle.png", true);
    HResourceManager::loadTexture("face",                   ":/textures/awesomeface.png", true);
    HResourceManager::loadTexture("particle",               ":/textures/particle.png", true);
    HResourceManager::loadTexture("powerup_speed",          ":/textures/powerup_speed.png", true);
    HResourceManager::loadTexture("powerup_sticky",         ":/textures/powerup_sticky.png", true);
    HResourceManager::loadTexture("powerup_increase",       ":/textures/powerup_increase.png", true);
    HResourceManager::loadTexture("powerup_confuse",        ":/textures/powerup_confuse.png", true);
    HResourceManager::loadTexture("powerup_chaos",          ":/textures/powerup_chaos.png", true);
    HResourceManager::loadTexture("powerup_passthrough",    ":/textures/powerup_passthrough.png", true);

    // load shaders
    auto s1 = HResourceManager::loadShader("sprite", ":/glsl/sprite.vs", ":/glsl/sprite.fs");
    auto s2 = HResourceManager::loadShader("particle", ":/glsl/particle.vs", ":/glsl/particle.fs");
    auto s3 = HResourceManager::loadShader("text", ":/glsl/text.vs", ":/glsl/text.fs");
    auto s4 = HResourceManager::loadShader("post_processing", ":/glsl/post_processing.vs", ":/glsl/post_processing.fs");
    // configure shaders
    QMatrix4x4 projection, projection2, model;
    projection.ortho(0.0, width, height, 0.0 , -1.0, 1.0);
    projection2.ortho(0.0, width, 0.0, height, -1.0, 1.0);

    s1->bind();
    s1->setUniformValue("projection", projection);
    s1->setUniformValue("texture1", 0);
    s2->bind();
    s2->setUniformValue("projection", projection);
    s2->setUniformValue("texture1", 0);
    s3->bind();
    s3->setUniformValue("projection", projection2);
    s3->setUniformValue("model", model);
    s3->setUniformValue("texture1", 0);

    // set render-specific controls
    d_ptr->sprite = new HSpriteRenderer(s1, this);
    d_ptr->particle = new HParticleRenderer(s2, 500, this);
    d_ptr->particle->setTexture(HResourceManager::texture("particle"));
    d_ptr->text = new HTextRenderer(s3, this);
    d_ptr->text->setFont(":/fonts/OCRAEXT.TTF", 64);
    d_ptr->effect = new HEffectRenderer(s4, width, height, this);

    // load levels
    auto files = QStringList() << ":/levels/one.lvl" << ":/levels/two.lvl" << ":/levels/three.lvl" << ":/levels/four.lvl";
    for (auto file : files)
    {
        auto level = new HGameLevel(this);
        level->load(file, width, height / 2);
        d_ptr->levels << level;
    }
    d_ptr->level = 0;

    // configure game objects
    auto paddlePos = QVector2D((width - d_ptr->paddleSize.x()) / 2.0f, height - d_ptr->paddleSize.y() - 20);
    auto ballPos = paddlePos + QVector2D(d_ptr->paddleSize.x() / 2.0f - d_ptr->ballRadius, -d_ptr->ballRadius * 2.0f);
    d_ptr->paddle = new HPaddle(this);
    d_ptr->paddle->setPosition(paddlePos);
    d_ptr->paddle->setSize(d_ptr->paddleSize);
    d_ptr->paddle->setTexture(HResourceManager::texture("paddle"));
    d_ptr->ball = new HBall(this);
    d_ptr->ball->setPosition(ballPos);
    d_ptr->ball->setRadius(d_ptr->ballRadius);
    d_ptr->ball->setVelocity(d_ptr->ballVelocity);
    d_ptr->ball->setTexture(HResourceManager::texture("face"));
    d_ptr->prop = new HPropManager(this);
    connect(d_ptr->ball, &HBall::positionChanged, this, &HGameManager::handleBallChanged);
    connect(d_ptr->prop, &HPropManager::propStateChanged, this, &HGameManager::handlePropChanged);
    HResourceManager::play(":/audio/breakout.mp3");
}

void HGameManager::keyPress(int key)
{
    d_ptr->keys[key] = true;
}

void HGameManager::KeyRelease(int key)
{
    d_ptr->keys[key] = false;
    d_ptr->keysProcessed[key] = false;
}

void HGameManager::processInput(float dt)
{
    if (d_ptr->state == GAME_MENU)
    {
        if (d_ptr->keys[GLFW_KEY_ENTER] && !d_ptr->keysProcessed[GLFW_KEY_ENTER])
        {
            d_ptr->state = GAME_ACTIVE;
            d_ptr->keysProcessed[GLFW_KEY_ENTER] = true;
        }
        if (d_ptr->keys[GLFW_KEY_W] && !d_ptr->keysProcessed[GLFW_KEY_W])
        {
            d_ptr->level = (d_ptr->level + 1) % 4;
            d_ptr->keysProcessed[GLFW_KEY_W] = true;
        }
        if (d_ptr->keys[GLFW_KEY_S] && !d_ptr->keysProcessed[GLFW_KEY_S])
        {
            d_ptr->level--;
            if (d_ptr->level < 0)
                d_ptr->level = 3;
            d_ptr->keysProcessed[GLFW_KEY_S] = true;
        }
    }
    if (d_ptr->state == GAME_WIN)
    {
        if (d_ptr->keys[GLFW_KEY_ENTER])
        {
            d_ptr->keysProcessed[GLFW_KEY_ENTER] = true;
            d_ptr->effect->setChaos(false);
            d_ptr->state = GAME_MENU;
        }
    }
    if (d_ptr->state == GAME_ACTIVE)
    {
        float velocity = d_ptr->paddleVelocity * dt;
        if (d_ptr->keys[GLFW_KEY_A])
        {
            d_ptr->paddle->move(-velocity, QVector2D(0, d_ptr->width));
            d_ptr->ball->move(-velocity, QVector2D(d_ptr->paddle->size().x() / 2.0, d_ptr->width - d_ptr->paddle->size().x() / 2.0), true);
        }
        if (d_ptr->keys[GLFW_KEY_D])
        {
            d_ptr->paddle->move(velocity, QVector2D(0, d_ptr->width));
            d_ptr->ball->move(velocity, QVector2D(d_ptr->paddle->size().x() / 2.0, d_ptr->width - d_ptr->paddle->size().x() / 2.0), true);
        }
        if (d_ptr->keys[GLFW_KEY_SPACE])
            d_ptr->ball->setStuck(false);
    }
}

void HGameManager::update(float dt)
{
    d_ptr->ball->move(dt, QVector2D(0, d_ptr->width), false);
    doCollisions();
    d_ptr->particle->update(dt);
    d_ptr->prop->update(dt);
    d_ptr->effect->updateShake(dt);

    // check loss condition
    if (d_ptr->ball->position().y() >= d_ptr->height)
    {
        d_ptr->lives--;
        if (d_ptr->lives == 0)
        {
            resetLevel();
            d_ptr->state = GAME_MENU;
        }
        resetPlayer();
    }
    // check win condition
    if (d_ptr->state == GAME_ACTIVE && d_ptr->levels[d_ptr->level]->isCompleted())
    {
        resetLevel();
        resetPlayer();
        d_ptr->effect->setChaos(true);
        d_ptr->state = GAME_WIN;
    }
}

void HGameManager::render()
{
    if (d_ptr->state == GAME_ACTIVE || d_ptr->state == GAME_MENU || d_ptr->state == GAME_WIN)
    {
        // begin rendering to postprocessing framebuffer
        d_ptr->effect->begin();
        // draw background
        HResourceManager::texture("background")->bind(0);
        d_ptr->sprite->draw(QVector2D(0.0, 0.0), QVector2D(d_ptr->width, d_ptr->height));
        //draw level
        d_ptr->levels.at(d_ptr->level)->draw(d_ptr->sprite);
        // draw particles
        d_ptr->particle->draw();
        // draw paddle
        d_ptr->paddle->draw(d_ptr->sprite);
        // draw prop
        d_ptr->prop->draw(d_ptr->sprite);
        // draw ball
        d_ptr->ball->draw(d_ptr->sprite);
        // end rendering to postprocessing framebuffer
        d_ptr->effect->end();
        d_ptr->effect->draw(glfwGetTime());
        // draw text (don't include in postprocessing)
        d_ptr->text->draw(QString("Lives: %1").arg(d_ptr->lives), QVector2D(5.0f, d_ptr->height - 25.0f), 20);
    }

    if (d_ptr->state == GAME_MENU)
    {
        d_ptr->text->draw("Press ENTER to start", QVector2D(200.0f, d_ptr->height / 2.0f), 32);
        d_ptr->text->draw("Press W or S to select level", QVector2D(220.0f, d_ptr->height / 2.0f - 20.0f), 20);
    }
    if (d_ptr->state == GAME_WIN)
    {
        d_ptr->text->draw("You WON!!!", QVector2D(250.0f, d_ptr->height / 2.0f + 30.0f), 32 ,QVector3D(0.0f, 1.0f, 0.0f));
        d_ptr->text->draw("Press ENTER to retry or ESC to quit", QVector2D(130.0f, d_ptr->height / 2.0f), 32, QVector3D(1.0f, 1.0f, 0.0f));
    }
}

void HGameManager::doCollisions()
{
    QVector2D difference;
    for (auto brick : d_ptr->levels.at(d_ptr->level)->bricks())
    {
        if (brick->isDestroyed())
            continue;
        if (!d_ptr->ball->checkCollision(brick, difference))
            continue;
        // destroy block if not solid
        if (!brick->isSolid())
        {
            brick->setDestroyed(true);
            d_ptr->prop->spawn(brick->position());
            HResourceManager::play(":/audio/bleep.mp3");
        }
        else
        {   // if block is solid, enable shake effect
            d_ptr->effect->setShakeTime(0.05f);
            HResourceManager::play(":/audio/solid.wav");
        }
         // don't do collision resolution on non-solid bricks if pass-through is activated
        if (!(d_ptr->ball->isPassThrough() && !brick->isSolid()))
            d_ptr->ball->relocation(difference);
    }

    // check collisions on props and if so, activate them
    d_ptr->prop->collision(d_ptr->paddle, d_ptr->height);
    // and finally check collisions for player pad (unless stuck)
    d_ptr->ball->collision(d_ptr->paddle, d_ptr->ballVelocity.x());
}

void HGameManager::resetLevel()
{
    d_ptr->levels.at(d_ptr->level)->reset();
    d_ptr->lives = 3;
}

void HGameManager::resetPlayer()
{
    auto paddlePos = QVector2D((d_ptr->width - d_ptr->paddleSize.x()) / 2.0f, d_ptr->height - d_ptr->paddleSize.y() - 20);
    auto ballPos = paddlePos + QVector2D(d_ptr->paddleSize.x() / 2.0f - d_ptr->ballRadius, -d_ptr->ballRadius * 2.0f);
    d_ptr->paddle->reset(paddlePos, d_ptr->paddleSize, QVector3D(1.0, 1.0, 1.0));
    d_ptr->ball->reset(ballPos, d_ptr->ballVelocity);
    d_ptr->effect->reset();
    d_ptr->prop->reset();
}

void HGameManager::handleBallChanged()
{
    d_ptr->particle->respawn(d_ptr->ball, 2);
}

void HGameManager::handlePropChanged(const QString &type, bool b)
{
    if (type == "speed" && b)
        d_ptr->ball->speed(1.2f);
    if (type == "increase" && b)
        d_ptr->paddle->increase(50.0f, QVector2D(0, d_ptr->width));
    if (type == "sticky")
    {
        d_ptr->ball->setSticky(b);
        d_ptr->paddle->setColor(b ? QVector3D(1.0f, 0.5f, 1.0f) : QVector3D(1.0f, 1.0f, 1.0f));
    }
    if (type == "passthrough")
    {
        d_ptr->ball->setPassThrough(b);
        d_ptr->paddle->setColor(b ? QVector3D(1.0f, 0.5f, 0.5f) : QVector3D(1.0f, 1.0f, 1.0f));
    }
    if (type == "confuse")
    {
        if (b)
        {
            d_ptr->effect->setChaos(false);
            d_ptr->effect->setConfuse(true);
        }
        else
            d_ptr->effect->setConfuse(false);
    }
    if (type == "chaos")
    {
        if (b)
        {
            d_ptr->effect->setConfuse(false);
            d_ptr->effect->setChaos(true);

        }
        else
            d_ptr->effect->setChaos(false);
    }
}
HE_END_NAMESPACE
