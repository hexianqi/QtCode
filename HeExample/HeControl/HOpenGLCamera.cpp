#include "HOpenGLCamera_p.h"
#include <QtCore/QTime>
#include <QtCore/QtMath>
#include <QtGui/QtEvents>
#include <QtGui/QMatrix4x4>
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

HOpenGLCameraPrivate::HOpenGLCameraPrivate()
{
    position = QVector3D(0.0f, 0.0f, 0.0f);
    front = QVector3D(0.0f, 0.0f, -1.0f);
    worldUp = QVector3D(0.0f, 1.0f,  0.0f);
}

HOpenGLCamera::HOpenGLCamera(QObject *parent) :
    HAbstractEventFilter(*new HOpenGLCameraPrivate, parent)
{
}

HOpenGLCamera::HOpenGLCamera(HOpenGLCameraPrivate &p, QObject *parent) :
    HAbstractEventFilter(p, parent)
{
}

HOpenGLCamera::~HOpenGLCamera()
{
}

QString HOpenGLCamera::typeName()
{
    return "HOpenGLCamera";
}

bool HOpenGLCamera::addWatched(QObject *p)
{
    Q_D(HOpenGLCamera);
    if (!p->inherits("QWidget"))
        return false;
    d->widget = qobject_cast<QWidget *>(p);
    return HAbstractEventFilter::addWatched(p);
}

QVector3D HOpenGLCamera::position() const
{
    Q_D(const HOpenGLCamera);
    return d->position;
}

QVector3D HOpenGLCamera::front() const
{
    Q_D(const HOpenGLCamera);
    return d->front;
}

double HOpenGLCamera::zoom() const
{
    Q_D(const HOpenGLCamera);
    return d->zoom;
}

QMatrix4x4 HOpenGLCamera::view() const
{
    Q_D(const HOpenGLCamera);
    QMatrix4x4 view;
    view.lookAt(d->position, d->position + d->front, d->worldUp);
    return view;
}

void HOpenGLCamera::setLockMouse(bool b)
{
    Q_D(HOpenGLCamera);
    if (d->mouseLocked == b)
        return;
    d->mouseLocked = b;
    if (!d->widget->hasFocus())
        return;
    if (d->mouseLocked)
    {
        d->widget->setCursor(Qt::CrossCursor);
        setCursorCenter();
    }
    else
        d->widget->setCursor(Qt::ArrowCursor);
}

void HOpenGLCamera::setPosition(const QVector3D &value)
{
    Q_D(HOpenGLCamera);
    if (qFuzzyCompare(d->position, value))
        return;
    d->position = value;
    updateVectors();
}

void HOpenGLCamera::setUpVector(const QVector3D &value)
{
    Q_D(HOpenGLCamera);
    if (qFuzzyCompare(d->worldUp, value))
        return;
    d->worldUp = value;
    updateVectors();
}

void HOpenGLCamera::updateDelta()
{
    Q_D(HOpenGLCamera);
    auto time = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
    d->deltaTime = time - d->lastFrame;
    d->lastFrame = time;
}

bool HOpenGLCamera::handleEvent(QObject *watched, QEvent *event)
{
    Q_D(HOpenGLCamera);
    if (d->widget != watched)
        return false;
    if (event->type() == QEvent::Timer)
        return handleTimerEvent(event);
    if (event->type() == QEvent::FocusIn)
        return handleFocusInEvent(event);
    if (event->type() == QEvent::FocusOut)
        return handleFocusOutEvent(event);
    if (event->type() == QEvent::MouseButtonPress)
        return handleMousePressEvent(event);
    if (event->type() == QEvent::MouseButtonRelease)
        return handleMouseReleaseEvent(event);
    if (event->type() == QEvent::MouseMove)
         return handleMouseMoveEvent(event);
    if (event->type() == QEvent::Wheel)
        return handleWheelEvent(event);
    if (event->type() == QEvent::KeyPress)
        return handleKeyPressEvent(event);
    if (event->type() == QEvent::KeyRelease)
        return handleKeyReleaseEvent(event);
    return false;
}

bool HOpenGLCamera::handleTimerEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QTimerEvent *>(event);
    if (e->timerId() != d->timeId)
        return false;
    auto velocity = d->moveSpeed * d->deltaTime;
    if (d->keys.contains(Qt::Key_W))
        d->position += d->front * velocity;
    if (d->keys.contains(Qt::Key_S))
        d->position -= d->front * velocity;
    if (d->keys.contains(Qt::Key_A))
        d->position -= d->right * velocity;
    if (d->keys.contains(Qt::Key_D))
        d->position += d->right * velocity;
    if (d->keys.contains(Qt::Key_Space))
        d->position.setY(d->position.y() + velocity);
    if (d->keys.contains(Qt::Key_Shift))
        d->position.setY(d->position.y() - velocity);
    return true;
}

bool HOpenGLCamera::handleFocusInEvent(QEvent *)
{
    Q_D(HOpenGLCamera);
    d->widget->setMouseTracking(true);
    if (d->mouseLocked)
    {
        d->widget->setCursor(Qt::CrossCursor);
        setCursorCenter();
    }
    return true;
}

bool HOpenGLCamera::handleFocusOutEvent(QEvent *)
{
    Q_D(HOpenGLCamera);
    d->widget->setMouseTracking(false);
    d->widget->setCursor(Qt::ArrowCursor);
    d->mouseLastPos = QPoint();
    d->keys.clear();
    stopTimer();
    return true;
}

bool HOpenGLCamera::handleMousePressEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QMouseEvent *>(event);
    if (!d->widget->rect().contains(e->pos()))
        return false;
    if (e->button() == Qt::RightButton)
    {
        d->widget->clearFocus();
        return true;
    }
    if (e->button() == Qt::LeftButton)
    {
        d->widget->setFocus();
        d->mousePressed = true;
        d->mouseLastPos = e->pos();
        return true;
    }
    if (e->button() == Qt::MiddleButton)
    {
        d->position = QVector3D(0.0f, 0.0f, 5.0f);
        d->yaw = -90.0;
        d->pitch = 0.0;
        d->zoom = 45;
        updateVectors();
    }
    return false;
}

bool HOpenGLCamera::handleMouseReleaseEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QMouseEvent *>(event);
    if (e->button() != Qt::LeftButton || !d->mousePressed)
        return false;
    d->mousePressed = false;
    return true;
}

bool HOpenGLCamera::handleMouseMoveEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    if (!d->mouseLocked && !d->mousePressed)
        return false;
    auto e = static_cast<QMouseEvent *>(event);
    auto pos = d->mouseLocked ? d->widget->rect().center() : (d->mouseLastPos.isNull() ? e->pos() : d->mouseLastPos);
    auto xoffset = d->sensitivity * (e->x() -pos.x());
    auto yoffset = d->sensitivity * (pos.y() - e->y());     // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    d->yaw   += xoffset;
    d->pitch = qBound(-89.0, d->pitch + yoffset, 89.0);     // 将俯视角限制到[-89°,89°]
    updateVectors();
    if (d->mouseLocked)
        setCursorCenter();
    else
        d->mouseLastPos = e->pos();
    return true;
}

bool HOpenGLCamera::handleWheelEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QWheelEvent *>(event);
    d->zoom = qBound(1.0, d->zoom - 5 * e->angleDelta().y() / 120, 45.0);
    return true;
}

bool HOpenGLCamera::handleKeyPressEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QKeyEvent *>(event);
    if (e->key() == Qt::Key_Escape)
    {
        d->widget->clearFocus();
        return true;
    }
    if (e->key() == Qt::Key_Control)
    {
        setLockMouse(!d->mouseLocked);
        return true;
    }
    if (isMoveKey(e->key()))
    {
        d->keys.insert(e->key());
        if (!e->isAutoRepeat() && d->timeId == 0) // isAutoRepeat用于判断此按键的来源是否是长按
            d->timeId = d->widget->startTimer(1);
        return true;
    }
    return false;
}

bool HOpenGLCamera::handleKeyReleaseEvent(QEvent *event)
{
    Q_D(HOpenGLCamera);
    auto e = static_cast<QKeyEvent *>(event);
    if (isMoveKey(e->key()))
    {
        d->keys.remove(e->key());
        if(!e->isAutoRepeat() && d->keys.empty())
            stopTimer();
        return true;
    }
    return false;
}

bool HOpenGLCamera::isMoveKey(int value)
{
    return value == Qt::Key_W || value == Qt::Key_S ||
           value == Qt::Key_A || value == Qt::Key_D ||
           value == Qt::Key_Space || value == Qt::Key_Shift;
}

void HOpenGLCamera::setCursorCenter()
{
    Q_D(HOpenGLCamera);
    QCursor::setPos(d->widget->mapToGlobal(d->widget->rect().center()));
}

void HOpenGLCamera::stopTimer()
{
    Q_D(HOpenGLCamera);
    if (d->timeId == 0)
        return;
    d->widget->killTimer(d->timeId);
    d->timeId = 0;
}

void HOpenGLCamera::updateVectors()
{
    Q_D(HOpenGLCamera);
    QVector3D front;
    front.setX(cos(qDegreesToRadians(d->yaw)) * cos(qDegreesToRadians(d->pitch)));
    front.setY(sin(qDegreesToRadians(d->pitch)));
    front.setZ(sin(qDegreesToRadians(d->yaw)) * cos(qDegreesToRadians(d->pitch)));
    d->front = front.normalized();
    d->right = QVector3D::normal(d->front, d->worldUp);
    d->up = QVector3D::normal(d->right, d->front);
}

HE_END_NAMESPACE
