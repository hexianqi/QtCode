#include "HBreakout_p.h"
#include "HGameManager.h"
#include "HResourceManager.h"
#include "GLFW/glfw3.h"
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

HGameManager game;

void framebufferSizeCallback(GLFWwindow */*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mode*/)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.keyPress(key);
        else if (action == GLFW_RELEASE)
            game.KeyRelease(key);
    }
}

HBreakout::HBreakout(QObject *parent) :
    QObject(parent),
    d_ptr(new HBreakoutPrivate)
{
}

HBreakout::HBreakout(HBreakoutPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HBreakout::~HBreakout()
{
}

void HBreakout::run()
{
    initGlfw();
    if (!createWindow() || !initFlad())
    {
        glfwTerminate();
        return;
    }

    // OpenGL configuration
    glViewport(0, 0, d_ptr->width, d_ptr->height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    game.init(d_ptr->width, d_ptr->height);

    while (!glfwWindowShouldClose(d_ptr->window))
    {
        perFrameTime();
        glfwPollEvents();

        // manage user input
        game.processInput(d_ptr->deltaTime);
        // update game state
        game.update(d_ptr->deltaTime);
        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        glfwSwapBuffers(d_ptr->window);
    }

    // delete all resources as loaded using the resource manager
    HResourceManager::clear();

    glfwTerminate();
}

void HBreakout::initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, false);
}

bool HBreakout::initFlad()
{
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return true;
    qDebug() << "Failed to initialize GLAD.";
    return false;
}

bool HBreakout::createWindow()
{
    d_ptr->window = glfwCreateWindow(d_ptr->width, d_ptr->height, "Breakout", nullptr, nullptr);
    if (d_ptr->window == nullptr)
    {
        qDebug() << "Failed to create GLFW window.";
        return false;
    }
    glfwSetWindowPos(d_ptr->window, 50, 300);
    glfwMakeContextCurrent(d_ptr->window);
    glfwSetKeyCallback(d_ptr->window, keyCallback);
    glfwSetFramebufferSizeCallback(d_ptr->window, framebufferSizeCallback);
    return true;
}

void HBreakout::perFrameTime()
{
    auto currentFrame = glfwGetTime();
    d_ptr->deltaTime = currentFrame - d_ptr->lastFrame;
    d_ptr->lastFrame = currentFrame;
}

HE_END_NAMESPACE
