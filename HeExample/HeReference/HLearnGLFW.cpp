#include "HLearnGLFW_p.h"
#include <QtCore/QtMath>
#include <QtCore/QDebug>
#include <iostream>

HE_REFERENCE_BEGIN_NAMESPACE

// camera
QVector3D cameraPos   = QVector3D(0.0f, 0.0f,  5.0f);
QVector3D cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
QVector3D cameraUp    = QVector3D(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

bool useCamera = false;
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
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    auto xoffset = xpos - lastX;
    auto yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    if (useCamera && camera)
        return camera->processMouseMovement(xoffset, yoffset);

    auto sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    QVector3D front;
    front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    front.setY(sin(qDegreesToRadians(pitch)));
    front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    cameraFront = front.normalized();
}

void scroll_callback(GLFWwindow */*window*/, double xoffset, double yoffset)
{
    if (useCamera && camera)
        return camera->processMouseScroll(xoffset, yoffset);

    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
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

    cubePosition = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    cubePositionSize = sizeof(float) * cubePosition.size();

    cubeTexture = {
        // Back face
        0.0f, 0.0f, // bottom-left
        1.0f, 1.0f, // top-right
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 0.0f, // bottom-left
        0.0f, 1.0f, // top-left
        // Front face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left
        0.0f, 0.0f, // bottom-left
        // Left face
        1.0f, 0.0f, // top-right
        1.0f, 1.0f, // top-left
        0.0f, 1.0f, // bottom-left
        0.0f, 1.0f, // bottom-left
        0.0f, 0.0f, // bottom-right
        1.0f, 0.0f, // top-right
        // Right face
        1.0f, 0.0f, // top-left
        0.0f, 1.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // bottom-right
        1.0f, 0.0f, // top-left
        0.0f, 0.0f, // bottom-left
        // Bottom face
        0.0f, 1.0f, // top-right
        1.0f, 1.0f, // top-left
        1.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-left
        0.0f, 0.0f, // bottom-right
        0.0f, 1.0f, // top-right
        // Top face
        0.0f, 1.0f, // top-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        1.0f, 0.0f, // bottom-right
        0.0f, 1.0f, // top-left
        0.0f, 0.0f  // bottom-left
    };
    cubeTextureSize = sizeof(float) * cubeTexture.size();

    cubeNormal = {
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

       -1.0f,  0.0f,  0.0f,
       -1.0f,  0.0f,  0.0f,
       -1.0f,  0.0f,  0.0f,
       -1.0f,  0.0f,  0.0f,
       -1.0f,  0.0f,  0.0f,
       -1.0f,  0.0f,  0.0f,

        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
    };
    cubeNormalSize = sizeof(float) * cubeNormal.size();

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

    planePosition = {
         25.0f, -0.5f,  25.0f,
        -25.0f, -0.5f,  25.0f,
        -25.0f, -0.5f, -25.0f,

         25.0f, -0.5f,  25.0f,
        -25.0f, -0.5f, -25.0f,
         25.0f, -0.5f, -25.0f
    };
    planePositionSize = sizeof(float) * planePosition.size();

    planeNormal = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    planeNormalSize = sizeof(float) * planeNormal.size();

    // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
    planeTexture = {
       25.0f,  0.0f,
        0.0f,  0.0f,
        0.0f, 25.0f,

       25.0f,  0.0f,
        0.0f, 25.0f,
       25.0f, 25.0f
    };
    planeTextureSize = sizeof(float) * planeTexture.size();

    transparentPosition = {
        0.0f,  0.5f,  0.0f,
        0.0f, -0.5f,  0.0f,
        1.0f, -0.5f,  0.0f,

        0.0f,  0.5f,  0.0f,
        1.0f, -0.5f,  0.0f,
        1.0f,  0.5f,  0.0f
    };
    transparentPositionSize = sizeof(float) * transparentPosition.size();

    // texture Coords (swapped y coordinates because texture is flipped upside down)
    transparentTexture = {
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,

        0.0f,  1.0f,
        1.0f,  0.0f,
        1.0f,  1.0f
    };
    transparentTextureSize = sizeof(float) * transparentTexture.size();

    skyboxPosition = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    skyboxPositionSize = sizeof(float) * skyboxPosition.size();


    quadPosition = {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };
    quadPositionSize = sizeof(float) * quadPosition.size();

    // texture Coords (swapped y coordinates because texture is flipped upside down)
    quadTexture = {
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  1.0f,
        1.0f,  0.0f
    };
    quadTextureSize = sizeof(float) * quadTexture.size();

}

HLearnGLFW::HLearnGLFW(QObject *parent) :
    QObject(parent),
    d_ptr(new HLearnGLFWPrivate)
{
    setUseCamera(true);
}

HLearnGLFW::~HLearnGLFW()
{
}

void HLearnGLFW::setEnableCursor(bool b)
{
    d_ptr->enableCursor = b;
}

void HLearnGLFW::setUseCamera(bool b)
{
    if (useCamera == b)
        return;
    useCamera = b;
    if (b && camera == nullptr)
    {
        camera = new HOpenGLCamera(this);
        camera->setPosition(cameraPos);
    }
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
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void HLearnGLFW::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !d_ptr->blinnKeyPressed)
    {
        d_ptr->blinn = !d_ptr->blinn;
        d_ptr->blinnKeyPressed = true;
        qDebug() << "blinn:" << d_ptr->blinn;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
    {
        d_ptr->blinnKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !d_ptr->gammaKeyPressed)
    {
        d_ptr->gamma = !d_ptr->gamma;
        d_ptr->gammaKeyPressed = true;
        qDebug() << "gamma:" << d_ptr->gamma;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
    {
        d_ptr->gammaKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !d_ptr->shadowsKeyPressed)
    {
        d_ptr->shadows = !d_ptr->shadows;
        d_ptr->shadowsKeyPressed = true;
        qDebug() << "shadows:" << d_ptr->shadows;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE)
    {
        d_ptr->shadowsKeyPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !d_ptr->hdrKeyPressed)
    {
        d_ptr->hdr = !d_ptr->hdr;
        d_ptr->hdrKeyPressed = true;
        qDebug() << "hdr:" << d_ptr->hdr;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
    {
        d_ptr->hdrKeyPressed = false;
    }
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

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !d_ptr->bloomKeyPressed)
    {
        d_ptr->bloom = !d_ptr->bloom;
        d_ptr->bloomKeyPressed = true;
        qDebug() << "bloom:" << d_ptr->bloom;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
    {
        d_ptr->bloomKeyPressed = false;
    }

    if (useCamera && camera)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyboard(HOpenGLCamera::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyboard(HOpenGLCamera::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyboard(HOpenGLCamera::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyboard(HOpenGLCamera::RIGHT, deltaTime);
    }
    else
    {
        auto cameraSpeed = 2.5 * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= QVector3D::normal(cameraFront, cameraUp) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += QVector3D::normal(cameraFront, cameraUp) * cameraSpeed;
    }
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
