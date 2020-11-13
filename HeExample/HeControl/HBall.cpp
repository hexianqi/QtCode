#include "HBall_p.h"
#include "HPaddle.h"
#include "HResourceManager.h"

HE_CONTROL_BEGIN_NAMESPACE

HBall::HBall(QObject *parent) :
    HGameObject(*new HBallPrivate, parent)
{
}

HBall::HBall(HBallPrivate &p, QObject *parent) :
    HGameObject(p, parent)
{
}

HBall::~HBall()
{
}

float HBall::radius()
{
    Q_D(HBall);
    return d->radius;
}

bool HBall::isStuck()
{
    Q_D(HBall);
    return d->stuck;
}

bool HBall::isPassThrough()
{
    Q_D(HBall);
    return d->passThrough;
}

void HBall::setRadius(float value)
{
    Q_D(HBall);
    d->radius = value;
    setSize(QVector2D(value * 2.0f, value * 2.0f));
}

void HBall::setStuck(bool b)
{
    Q_D(HBall);
    d->stuck = b;
}

void HBall::setSticky(bool b)
{
    Q_D(HBall);
    d->sticky = b;
}

void HBall::setPassThrough(bool b)
{
    Q_D(HBall);
    d->passThrough = b;
}

void HBall::speed(float value)
{
    Q_D(HBall);
    d->velocity *= value;
}

void HBall::move(float x, QVector2D scope, bool stuck)
{
    Q_D(HBall);

    if (d->stuck != stuck)
        return;

    if (!d->stuck)
    {
        // move the ball
        d->position += d->velocity * x;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (d->position.x() <= 0.0f)
        {
            d->velocity.setX(-d->velocity.x());
            d->position.setX(0.0f);
        }
        else if (d->position.x() + d->size.x() >= scope.y())
        {
            d->velocity.setX(-d->velocity.x());
            d->position.setX(scope.y() - d->size.x());
        }
        if (d->position.y() <= 0.0f)
        {
            d->velocity.setY(-d->velocity.y());
            d->position.setY(0.0f);
        }
    }
    else
        d->position.setX(qBound(scope.x() - d->radius, d->position.x() + x, scope.y() - d->radius));
    emit positionChanged(d->position);
}

void HBall::collision(HPaddle *paddle, float strength)
{
    Q_D(HBall);
    QVector2D difference;
    if (d->stuck || !checkCollision(paddle, difference))
        return;

    auto percentage = (center() - paddle->center()) / paddle->size();
    auto x = percentage.x() * strength;
    auto old = d->velocity;
    d->velocity.setX(x);
    d->velocity = d->velocity.normalized() * old.length();
    d->velocity.setY(-1.0f * std::abs(d->velocity.y()));
    // if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
    d->stuck = d->sticky;
    HResourceManager::play(":/audio/bleep.wav");
}

void HBall::relocation(QVector2D difference)
{
    Q_D(HBall);
    auto dir = calcDirection(difference);
    if (dir == 1 || dir == 3) // horizontal collision
    {
        // reverse horizontal velocity
        d->velocity.setX(-d->velocity.x());
        // relocate
        float penetration = d->radius - std::abs(difference.x());
        if (dir == 3)
            penetration *= -1.0f;
        d->position.setX(d->position.x() + penetration);
    }
    else // vertical collision
    {
        // reverse vertical velocity
        d->velocity.setY(-d->velocity.y());
        // relocate
        float penetration = d->radius - std::abs(difference.y());
        if (dir == 0)
            penetration *= -1.0f;
        d->position.setY(d->position.y() + penetration);
    }
}

void HBall::reset(QVector2D position, QVector2D velocity)
{
    Q_D(HBall);
    d->position = position;
    d->velocity = velocity;
    d->color = QVector3D(1.0, 1.0, 1.0);
    d->stuck = true;
    d->sticky = false;
    d->passThrough = false;
}

// AABB circle collision
bool HBall::checkCollision(HGameObject *other, QVector2D &difference)
{
    // get center point
    auto center1 = this->center();
    auto center2 = other->center();
    auto half = other->size() / 2.0f;
    // get difference vector between both centers
    difference = center1 - center2;
    auto clamped = QVector2D(qBound(-half.x(), difference.x(), half.x()), qBound(-half.y(), difference.y(), half.y()));
    // now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    auto closest = center2 + clamped;
    // now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center1;
    // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
    return difference.length() < this->radius();
}

// calculates which direction a vector is facing (N,E,S or W)
int HBall::calcDirection(QVector2D target)
{
    QList<QVector2D> compass;
    compass << QVector2D(0.0f, 1.0f)	// up
            << QVector2D(1.0f, 0.0f)	// right
            << QVector2D(.0f, -1.0f)	// down
            << QVector2D(-1.0f, 0.0f);	// left


    float max = 0.0f;
    int result = -1;
    target.normalize();
    for (int i = 0; i < compass.size(); i++)
    {
        auto dotProduct = QVector2D::dotProduct(target, compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            result = i;
        }
    }
    return result;
}

HE_CONTROL_END_NAMESPACE
