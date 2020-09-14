#include "HLearnGLFW_p.h"
#include <QtCore/QtMath>
#include <iostream>

HE_REFERENCE_BEGIN_NAMESPACE

// camera
QVector3D cameraPos   = QVector3D(0.0f, 0.0f,  3.0f);
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

    if (!camera)
    {
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
    else
    {
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow */*window*/, double xoffset, double yoffset)
{
    if (!camera)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }
    else
        camera->processMouseScroll(xoffset, yoffset);
}

HLearnGLFW::HLearnGLFW(QObject *parent) :
    QObject(parent),
    d_ptr(new HLearnGLFWPrivate)
{

}

HLearnGLFW::~HLearnGLFW()
{

}

// initialize and configure
void HLearnGLFW::initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// load all OpenGL function pointers
bool HLearnGLFW::initFlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

bool HLearnGLFW::createWindow()
{
    d_ptr->window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (d_ptr->window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(d_ptr->window);
    glfwSetFramebufferSizeCallback(d_ptr->window, framebuffer_size_callback);
    glfwSetCursorPosCallback(d_ptr->window, mouse_callback);
    glfwSetScrollCallback(d_ptr->window, scroll_callback);
    glfwSetInputMode(d_ptr->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return true;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void HLearnGLFW::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (!camera)
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
    else
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
}

HE_REFERENCE_END_NAMESPACE
