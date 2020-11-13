#include "HLearnGLFW_p.h"
#include "HGeometryEngine.h"
#include <QtCore/QtMath>
#include <QtCore/QDebug>
#include <iostream>

HE_REFERENCE_BEGIN_NAMESPACE

HOpenGLCamera *camera = nullptr;

// whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow */*window*/, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow */*window*/, double xpos, double ypos)
{
    return camera->handleMouseMovement(xpos, ypos);
}

void scroll_callback(GLFWwindow */*window*/, double xoffset, double yoffset)
{
    camera->handleMouseScroll(xoffset, yoffset);
}

HLearnGLFWPrivate::HLearnGLFWPrivate()
{
    attenuations.insert(   7, QVector3D(1.0, 0.7, 1.8));
    attenuations.insert(  13, QVector3D(1.0, 0.35, 0.44));
    attenuations.insert(  20, QVector3D(1.0, 0.22, 0.20));
    attenuations.insert(  32, QVector3D(1.0, 0.14, 0.07));
    attenuations.insert(  50, QVector3D(1.0, 0.09, 0.032));
    attenuations.insert(  65, QVector3D(1.0, 0.07, 0.017));
    attenuations.insert( 100, QVector3D(1.0, 0.045, 0.0075));
    attenuations.insert( 160, QVector3D(1.0, 0.027, 0.0028));
    attenuations.insert( 200, QVector3D(1.0, 0.022, 0.0019));
    attenuations.insert( 325, QVector3D(1.0, 0.014, 0.0007));
    attenuations.insert( 600, QVector3D(1.0, 0.007, 0.0002));
    attenuations.insert(3250, QVector3D(1.0, 0.0014, 0.000007));

    cubeWorldPosition << QVector3D( 0.0f,  0.0f,  0.0f)
                       << QVector3D( 2.0f,  5.0f, -15.0f)
                       << QVector3D(-1.5f, -2.2f, -2.5f)
                       << QVector3D(-3.8f, -2.0f, -12.3f)
                       << QVector3D( 2.4f, -0.4f, -3.5f)
                       << QVector3D(-1.7f,  3.0f, -7.5f)
                       << QVector3D( 1.3f, -2.0f, -2.5f)
                       << QVector3D( 1.5f,  2.0f, -2.5f)
                       << QVector3D( 1.5f,  0.2f, -1.5f)
                       << QVector3D(-1.3f,  1.0f, -1.5f);
}

HLearnGLFW::HLearnGLFW(QObject *parent) :
    QObject(parent),
    d_ptr(new HLearnGLFWPrivate)
{
    d_ptr->engine = new HGeometryEngine(this);
    camera = new HOpenGLCamera(this);
    camera->setPosition(QVector3D(0.0f, 0.0f,  5.0f));
}

HLearnGLFW::~HLearnGLFW()
{
}

void HLearnGLFW::setEnableCursor(bool b)
{
    d_ptr->enableCursor = b;
}

void HLearnGLFW::setLightPosLoop(bool b)
{
    d_ptr->lightPosLoop = b;
}

void HLearnGLFW::setLightColorLoop(bool b)
{
    d_ptr->lightColorLoop = b;
}

void HLearnGLFW::setLineMode(bool b)
{
    d_ptr->lineMode = b;
}

// initialize and configure
void HLearnGLFW::initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

// load all OpenGL function pointers
bool HLearnGLFW::initFlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_MULTISAMPLE);
    return true;
}

bool HLearnGLFW::createWindow()
{
    d_ptr->window = glfwCreateWindow(d_ptr->width, d_ptr->height, "LearnOpenGL", nullptr, nullptr);
    if (d_ptr->window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }
    glfwSetWindowPos(d_ptr->window, 50, 300);
    glfwMakeContextCurrent(d_ptr->window);
    glfwSetFramebufferSizeCallback(d_ptr->window, framebuffer_size_callback);
    glfwSetCursorPosCallback(d_ptr->window, mouse_callback);
    glfwSetScrollCallback(d_ptr->window, scroll_callback);
    glfwSetInputMode(d_ptr->window, GLFW_CURSOR, d_ptr->enableCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    return true;
}

void HLearnGLFW::perFrameTime()
{
    auto currentFrame = glfwGetTime();
    d_ptr->deltaTime = currentFrame - d_ptr->lastFrame;
    d_ptr->lastFrame = currentFrame;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void HLearnGLFW::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !d_ptr->keyPressed_B)
    {
        d_ptr->keyPressed_B = true;
        d_ptr->blinn = !d_ptr->blinn;
        d_ptr->bloom = !d_ptr->bloom;
        qDebug() << "blinn:" << d_ptr->blinn;
        qDebug() << "bloom:" << d_ptr->bloom;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
        d_ptr->keyPressed_B = false;

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !d_ptr->keyPressed_G)
    {
        d_ptr->gamma = !d_ptr->gamma;
        d_ptr->keyPressed_G = true;
        qDebug() << "gamma:" << d_ptr->gamma;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
        d_ptr->keyPressed_G = false;

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !d_ptr->keyPressed_H)
    {
        d_ptr->shadows = !d_ptr->shadows;
        d_ptr->hdr = !d_ptr->hdr;
        d_ptr->keyPressed_H = true;
        qDebug() << "shadows:" << d_ptr->shadows;
        qDebug() << "hdr:" << d_ptr->hdr;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
        d_ptr->keyPressed_H = false;

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !d_ptr->keyPressed_L)
    {
        d_ptr->keyPressed_L = true;
        d_ptr->linearize = !d_ptr->linearize;
        qDebug() << "linearize:" << d_ptr->linearize;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
        d_ptr->keyPressed_L = false;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        d_ptr->heightScale = qMax(0.0f, d_ptr->heightScale - 0.0005f);
        d_ptr->exposure = qMax(0.0f, d_ptr->exposure - 0.001f);
        qDebug() << "heightScale:" << d_ptr->heightScale;
        qDebug() << "exposure:" << d_ptr->exposure;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        d_ptr->heightScale = qMin(1.0f, d_ptr->heightScale + 0.0005f);
        d_ptr->exposure = qMin(100.0f, d_ptr->exposure + 0.001f);
        qDebug() << "heightScale:" << d_ptr->heightScale;
        qDebug() << "exposure:" << d_ptr->exposure;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->handleKeyboard(HOpenGLCamera::FORWARD, d_ptr->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->handleKeyboard(HOpenGLCamera::BACKWARD, d_ptr->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->handleKeyboard(HOpenGLCamera::LEFT, d_ptr->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->handleKeyboard(HOpenGLCamera::RIGHT, d_ptr->deltaTime);
}

QVector3D HLearnGLFW::lightPos()
{
    if (d_ptr->lightPosLoop)
        return QVector3D(1.0f + sin(glfwGetTime()) * 2.0f,  sin(glfwGetTime() / 2.0f) * 1.0f, d_ptr->lightPos.z());
    return d_ptr->lightPos;
}

QVector3D HLearnGLFW::lightColor()
{
    if (d_ptr->lightColorLoop)
        return QVector3D(sin(glfwGetTime() * 2.0f), sin(glfwGetTime() * 0.7f), sin(glfwGetTime() * 1.3f));
    return d_ptr->lightColor;
}

HE_REFERENCE_END_NAMESPACE
