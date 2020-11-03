#include "HOpenGLCamera_p.h"
#include <QtCore/QtMath>
#include <QtGui/QMatrix4x4>

HE_REFERENCE_BEGIN_NAMESPACE

HOpenGLCamera::HOpenGLCamera(QObject *parent) :
    QObject(parent),
    d_ptr(new HOpenGLCameraPrivate)
{
}

HOpenGLCamera::~HOpenGLCamera()
{
}

QVector3D HOpenGLCamera::position() const
{
    return d_ptr->position;
}

QVector3D HOpenGLCamera::front() const
{
    return d_ptr->front;
}

float HOpenGLCamera::zoom() const
{
    return d_ptr->zoom;
}

QMatrix4x4 HOpenGLCamera::viewMatrix() const
{
    QMatrix4x4 r;
    r.lookAt(d_ptr->position, d_ptr->position + d_ptr->front, d_ptr->worldUp);
    return r;
}

void HOpenGLCamera::setPosition(const QVector3D &value)
{
    if (qFuzzyCompare(d_ptr->position, value))
        return;
    d_ptr->position = value;
    updateVectors();
}

void HOpenGLCamera::setUpVector(const QVector3D &value)
{
    if (qFuzzyCompare(d_ptr->worldUp, value))
        return;
    d_ptr->worldUp = value;
    updateVectors();
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void HOpenGLCamera::processKeyboard(Movement direction, float deltaTime)
{
    auto velocity = d_ptr->movementSpeed * deltaTime;
    if (direction == FORWARD)
        d_ptr->position += d_ptr->front * velocity;
    if (direction == BACKWARD)
        d_ptr->position -= d_ptr->front * velocity;
    if (direction == LEFT)
        d_ptr->position -= d_ptr->right * velocity;
    if (direction == RIGHT)
        d_ptr->position += d_ptr->right * velocity;

    // make sure the user stays at the ground level
    // d_ptr->position.setY(0.0f); // <-- this one-liner keeps the user at the ground level (xz plane)
}

void HOpenGLCamera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= d_ptr->mouseSensitivity;
    yoffset *= d_ptr->mouseSensitivity;
    d_ptr->yaw   += xoffset;
    d_ptr->pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (d_ptr->pitch > 89.0f)
            d_ptr->pitch = 89.0f;
        if (d_ptr->pitch < -89.0f)
            d_ptr->pitch = -89.0f;
    }
    // update Front, Right and Up Vectors using the updated Euler angles
    updateVectors();
}

void HOpenGLCamera::processMouseScroll(float /*xoffset*/, float yoffset)
{
    d_ptr->zoom -= (float)yoffset;
    if (d_ptr->zoom < 1.0f)
        d_ptr->zoom = 1.0f;
    if (d_ptr->zoom > 45.0f)
        d_ptr->zoom = 45.0f;
}

void HOpenGLCamera::updateVectors()
{
    // calculate the new Front vector
    QVector3D front;
    front.setX(cos(qDegreesToRadians(d_ptr->yaw)) * cos(qDegreesToRadians(d_ptr->pitch)));
    front.setY(sin(qDegreesToRadians(d_ptr->pitch)));
    front.setZ(sin(qDegreesToRadians(d_ptr->yaw)) * cos(qDegreesToRadians(d_ptr->pitch)));
    d_ptr->front = front.normalized();
    d_ptr->right = QVector3D::normal(d_ptr->front, d_ptr->worldUp);
    d_ptr->up = QVector3D::normal(d_ptr->right, d_ptr->front);
}

HE_REFERENCE_END_NAMESPACE
